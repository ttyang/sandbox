//               -- cgi_service_impl.hpp --
//
//          Copyright (c) Darren Garvey 2007-2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////
#ifndef CGI_CGI_SERVICE_IMPL_HPP_INCLUDED__
#define CGI_CGI_SERVICE_IMPL_HPP_INCLUDED__

#include "boost/cgi/detail/push_options.hpp"

#include "boost/cgi/common/tags.hpp"
#include "boost/cgi/common/map.hpp"
#include "boost/cgi/cgi/request_impl.hpp"
#include "boost/cgi/import/io_service.hpp"
#include "boost/cgi/detail/service_base.hpp"
#include "boost/cgi/detail/extract_params.hpp"
#include "boost/cgi/connections/async_stdio.hpp"

#include <boost/bind.hpp>
#include <boost/assert.hpp>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/system/error_code.hpp>
#include <boost/algorithm/string/find.hpp>
///////////////////////////////////////////////////////////
#include "boost/cgi/common/map.hpp"
#include "boost/cgi/basic_client.hpp"
#include "boost/cgi/common/is_async.hpp"
#include "boost/cgi/common/role_type.hpp"
#include "boost/cgi/common/form_part.hpp"
#include "boost/cgi/detail/throw_error.hpp"
#include "boost/cgi/common/form_parser.hpp"
#include "boost/cgi/common/request_base.hpp"
#include "boost/cgi/common/parse_options.hpp"
#include "boost/cgi/common/request_status.hpp"
#include "boost/cgi/detail/extract_params.hpp"
#include "boost/cgi/detail/save_environment.hpp"

BOOST_CGI_NAMESPACE_BEGIN

  class cgi_request_service
    : public common::request_base<cgi_request_impl>
    , public detail::service_base<cgi_request_service>
  {
  public:
    typedef common::tags::cgi                   protocol_type;
    typedef cgi_service                         protocol_service_type;
    typedef cgi_request_impl                    impl_type;
    typedef cgi_request_service                 self_type;
    typedef common::request_base<self_type>     base_type;
    typedef ::BOOST_CGI_NAMESPACE::common::map  map_type;

    struct implementation_type
      : impl_type
      , base_type::impl_base
    {
      typedef impl_type::client_type  client_type;
      typedef detail::form_parser     form_parser_type;

      implementation_type()
        : fp_(NULL)
      {
      }

      client_type client_;

      // The number of characters left to read (ie. "content_length - 
      // bytes_read")
      std::size_t characters_left_;
      
      boost::scoped_ptr<form_parser_type> fp_;
    };

    template<typename Service>
    struct callback_functor
    {
      callback_functor(implementation_type& impl, Service* service)
        : impl_(impl)
        , service_(service)
      {
      }

      std::size_t operator()(boost::system::error_code& ec)
      {
        return service_->read_some(impl_, ec);
      }

    private:
      implementation_type& impl_;
      Service* service_;
    };
    

    cgi_request_service(common::io_service& ios)
      : detail::service_base<cgi_request_service>(ios)
    {
    }

    void shutdown_service()
    {
    }

    void construct(implementation_type& impl)
    {
      impl.client_.set_connection(
        implementation_type::connection_type::create(this->get_io_service())
      );
    }

    void destroy(implementation_type& impl)
    {
    }
    
    void set_service(implementation_type& impl, protocol_service_type& ps)
    {
      impl.service_ = &ps;
    }

    /// Return if the request is still open
    /**
     * For CGI, this always returns true. However, in the case that a
     * "Location: xxx" header is sent and the header is terminated, the
     * request can be taken to be 'closed'.
     */
    bool is_open(implementation_type& impl)
    {
      return impl.status() >= common::accepted 
          && impl.status() <= common::aborted;
    }

    void clear(implementation_type& impl) { }

    int request_id(implementation_type& impl) { return 1; }

    /// Return the connection associated with the request
    implementation_type::client_type&
      client(implementation_type& impl)
    {
      return impl.client_;
    }

    // **FIXME** should return error_code
    int close(implementation_type& impl, common::http::status_code& http_s
      , int status, boost::system::error_code& ec)
    {
      std::cerr<< "In close." << std::endl;
      impl.status() = common::closed;
      impl.http_status() = http_s;
      return status;
    }

    /// Synchronously read/parse the request data
    boost::system::error_code&
    load(implementation_type& impl, common::parse_options parse_opts
        , boost::system::error_code& ec)
    {
      if (parse_opts & common::parse_env)
      {
        if (read_env_vars(impl, ec)) // returns an error_code
          return ec;
      }

      std::string const& cl = env_vars(impl.vars_)["CONTENT_LENGTH"];
      impl.characters_left_
         = cl.empty() ? 0 : boost::lexical_cast<std::size_t>(cl);
      impl.client_.bytes_left()
         = impl.characters_left_;
      std::string const& request_method
         = env_vars(impl.vars_)["REQUEST_METHOD"];

      if ((request_method == "GET" || request_method == "HEAD")
          && parse_opts > common::parse_env
          && parse_opts & common::parse_get_only)
      {
        parse_get_vars(impl, ec);
      }
      else
      if (request_method == "POST"
          && (parse_opts & common::parse_post_only))
      {
        parse_post_vars(impl, ec);
      }

      if (ec) return ec;

      if (parse_opts & common::parse_cookie_only)
      {
        if (parse_cookie_vars(impl, ec)) // returns an error_code
          return ec;
      }

      set_status(impl, common::loaded);

      return ec;
    }

    common::role_type
    get_role(implementation_type& impl)
    {
      return common::responder;
    }

    /// Set the request status
    void set_status(
       implementation_type& impl, common::request_status status)
    {
      impl.status() = status;
    }

    std::size_t
    read_some(implementation_type& impl, boost::system::error_code& ec)
    {
      return impl.client_.read_some(impl.prepare(64), ec);
    }

  protected:
    /// Read the environment variables into an internal map.
    template<typename RequestImpl>
    boost::system::error_code
    read_env_vars(RequestImpl& impl, boost::system::error_code& ec)
    {
      // Only call this once.
      if (!impl.env_parsed_)
        detail::save_environment(env_vars(impl.vars_));
      impl.env_parsed_ = true;
      return ec;
    }

    /// Read and parse the cgi POST meta variables (greedily)
    template<typename RequestImpl>
    boost::system::error_code
    parse_post_vars(RequestImpl& impl, boost::system::error_code& ec)
    {
      // **FIXME** use callback_functor<> in form_parser instead.
      std::size_t& bytes_left (impl.client_.bytes_left_);
      std::size_t bytes_read (0);
      do {
         bytes_read = read_some(impl, ec);
         bytes_left -= bytes_read;
      } while (!ec && bytes_left);
      
      // Return an error, except ignore EOF, as this is expected.
      if (ec)
        if (ec == boost::cgi::common::error::eof)
          ec = boost::system::error_code();
        else
          return ec;

      if (!impl.fp_)
        // Construct a form_parser instance.
        impl.fp_.reset(new typename implementation_type::form_parser_type());

      // Create a context for this request.      
      typename implementation_type::form_parser_type::context
          context
              = { env_vars(impl.vars_)["CONTENT_TYPE"]
                , impl.post_buffer_
                , impl.form_parts_
                , impl.client_.bytes_left_
                , post_vars(impl.vars_)
                , callback_functor<self_type>(impl, this)
                , impl.stdin_parsed_
                , env_vars(impl.vars_)["REMOTE_ADDR"]
                };

      // Parse the current request.
      impl.fp_->parse(context, ec);
      
      return ec;
    }
  };

BOOST_CGI_NAMESPACE_END

#include "boost/cgi/detail/pop_options.hpp"

#endif // CGI_CGI_SERVICE_IMPL_HPP_INCLUDED__
