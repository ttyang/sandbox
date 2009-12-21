//              -- common/request_base.hpp --
//
//            Copyright (c) Darren Garvey 2007.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////
//
// Defines `request_base` - a base class for all CGI requests.
// Contains common data members and functionality.
//
#ifndef CGI_COMMON_REQUEST_BASE_HPP_INCLUDE_
#define CGI_COMMON_REQUEST_BASE_HPP_INCLUDE_

#include <string>
////////////////////////////////////////////////////////////////
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/fusion/include/vector.hpp>
////////////////////////////////////////////////////////////////
#include "boost/cgi/common/map.hpp"
#include "boost/cgi/common/form_part.hpp"
#include "boost/cgi/common/parse_options.hpp"
#include "boost/cgi/common/request_status.hpp"
#include "boost/cgi/detail/extract_params.hpp"
#include "boost/cgi/detail/protocol_traits.hpp"
#include "boost/cgi/detail/save_environment.hpp"
#include "boost/cgi/config.hpp"

BOOST_CGI_NAMESPACE_BEGIN
 namespace common {

  /// ABC that defines the common interface for basic_request<>s
  /**
   * This class provides generic member functions that can be used by any
   * request type.
   */
  template<typename Protocol>
  class request_base
  {
  public:
    typedef common::request_base<Protocol> base_type;

    /// Get the request ID of a FastCGI request, or 1.
    template<typename ImplType>
    boost::uint16_t const& request_id(ImplType& impl) const
    {
      return impl.client_.request_id();
    }

    // impl_base is the common base class for all request types'
    // implementation_type and should be inherited by it.
    struct impl_base
    {
      typedef impl_base                              base_type;
      typedef Protocol                               protocol_type;
      typedef detail::protocol_traits<Protocol>      traits;

      typedef typename traits::char_type             char_type;
      typedef typename traits::string_type           string_type;
      typedef typename traits::buffer_type           buffer_type;
      typedef typename traits::const_buffers_type    const_buffers_type;
      typedef typename traits::mutable_buffers_type  mutable_buffers_type;
      
      typedef typename traits::form_parser_type      form_parser_type;
 
      typedef typename traits::client_type           client_type;
      typedef typename traits::connection_type       connection_type;
      typedef typename connection_type::pointer      conn_ptr;
      typedef typename traits::request_type          request_type;
      typedef typename traits::protocol_service_type protocol_service_type;
      
      /**
       * If you want to add a new data type to a request you need to:
       *   > Update this file (just below)
       *   > Update source_enums.hpp
       *   > Update map.hpp with a new map type
       *   > Add a member variable to basic_request<>
       */
      typedef boost::fusion::vector<
          common::env_map, common::get_map
        , common::post_map, common::cookie_map
        , common::session_map
      >   var_map_type;
      
      /// Construct.
      impl_base()
        : service_(NULL)
        , vars_(), post_buffer_()
        , stdin_parsed_(false)
        , all_done_(false)
        , bytes_left_(0)
        , http_status_(common::http::no_content)
        , request_status_(common::unloaded)
        , client_()
        , fp_(NULL)
      {}
      
      bool stdin_parsed()                      { return stdin_parsed_;   }
      common::http::status_code& http_status() { return http_status_;    }
      common::request_status status() const    { return request_status_; }
      void status(common::request_status& st)  { request_status_ = st; }

      protocol_service_type* service_;
      
      var_map_type vars_;
      buffer_type post_buffer_;
      /// Whether the post data has been parsed yet.
      bool stdin_parsed_;
      
      bool all_done_;

      // The number of bytes left to read (ie. content_length - bytes_read)
      std::size_t bytes_left_;

      common::http::status_code http_status_;
      common::request_status request_status_;
      
      client_type client_;
      
      boost::scoped_ptr<form_parser_type> fp_;

      std::vector<common::form_part> form_parts_;

      mutable_buffers_type prepare(std::size_t size)
      {
        // Make sure we're not trying to make a zero-sized buffer.
        BOOST_ASSERT(size && "Attempting to allocate a zero-sized buffer.");
        std::size_t bufsz(post_buffer_.size());
        post_buffer_.resize(bufsz + size);
        return boost::asio::buffer(&post_buffer_[bufsz], size);
      }
    };
    
    template<typename ImplType, typename Service>
    struct callback_functor
    {
      callback_functor(ImplType& impl, Service* service)
        : impl_(impl)
        , service_(service)
      {
      }

      std::size_t operator()(boost::system::error_code& ec)
      {
        return service_->read_some(impl_, ec);
      }

    private:
      ImplType& impl_;
      Service* service_;
    };
     
    /// Load the base_environment into the current environment.
    /**
     * Parsed the base_environment and add it to the current request's
     * environment. This overwrites any environment variables with the
     * existing key.
     *
     * If `is_command_line` is true, then the first argument is skipped as
     * this is the name of the program and ignored. Using it actually causes
     * a crash on Windows (MSVC 9) anyway: I'm not exactly sure why.
     */
    template<typename ImplType>
    void load_environment(
        ImplType& impl,
        char** base_environment,
        bool is_command_line
      )
    {
      if (is_command_line) ++base_environment;
      detail::save_environment(env_vars(impl.vars_), base_environment);
    }

    /// Read some data into the internal buffer.
    template<typename ImplType>
    std::size_t
    read_some(ImplType& impl, boost::system::error_code& ec)
    {
      return impl.client_.read_some(impl.prepare(64), ec);
    }

    /// Read some data from the client into the supplied buffer.
    template<typename ImplType, typename MutableBufferSequence>
    std::size_t
    read_some(ImplType& impl, const MutableBufferSequence& buf
             , boost::system::error_code& ec)
    {
      return impl.client_.read_some(buf,ec);
    }

    template<typename ImplType>
    void destroy(ImplType& impl)
    {
    }
    
    /// Return the connection associated with the request
    template<typename ImplType>
    typename ImplType::client_type&
      client(ImplType& impl)
    {
      return impl.client_;
    }

    template<typename ImplType>
    void set_service(
        ImplType& impl,
        typename ImplType::protocol_service_type& ps
      )
    {
      impl.service_ = &ps;
    }

    /// Get the request status.
    template<typename ImplType>
    common::request_status status(ImplType& impl) const
    {
      return impl.status();
    }

    /// Set the request status.
    template<typename ImplType>
    void status(ImplType& impl, common::request_status status)
    {
      impl.status(status);
    }

    /// Return if the request is still open.
    template<typename ImplType>
    bool is_open(ImplType& impl)
    {
      return !impl.all_done_ 
          && impl.status() >= common::accepted 
          && impl.status() <= common::aborted
          && impl.client_.is_open();
    }

    /// Check if a given POST variable represents a file upload.
    template<typename ImplType>
    bool is_file(ImplType& impl
                , typename ImplType::string_type const& key)
    {
      boost::optional<common::form_part&>
        part = get_form_part(impl, key);
      return part && !part->filename.empty();
    }
    
    /// Get the form_part for the passed key, which may not exist.
    template<typename ImplType>
    boost::optional<common::form_part&>
      get_form_part(ImplType& impl, typename ImplType::string_type const& key)
    {
       typedef std::vector<common::form_part>::iterator
          iter_t;

       for(iter_t iter (impl.form_parts_.begin())
          , end (impl.form_parts_.end()); iter != end; ++iter)
       {
          if (iter->name == key.c_str())
             return boost::optional<common::form_part&>(*iter);
       }
       return boost::optional<common::form_part&>();
    }

    /// Synchronously read/parse the request meta-data
    template<typename ImplType>
    boost::system::error_code
    load(ImplType& impl, common::parse_options parse_opts
        , boost::system::error_code& ec)
    {
      if (parse_opts & common::parse_env)
      {
        if (!read_env_vars(impl, ec)) // returns an error_code
          return ec;
      }

      std::string const& cl = env_vars(impl.vars_)["CONTENT_LENGTH"];
      // This will throw if the content-length isn't a valid number 
      // (which shouldn't ever happen).
      impl.bytes_left_
         = cl.empty() ? 0 : boost::lexical_cast<std::size_t>(cl);
      impl.client_.bytes_left() = impl.bytes_left_;

      std::string const& request_method
         = env_vars(impl.vars_)["REQUEST_METHOD"];

      if ((request_method == "GET" || request_method == "HEAD")
          && (parse_opts & common::parse_get_only))
      {
        parse_get_vars(impl, ec);
      }
      else
      if (request_method == "POST"
          && parse_opts & common::parse_post_only)
      {
        parse_post_vars(impl, ec);
      }

      if (ec) return ec;

      if (parse_opts & common::parse_cookies_only)
      {
        if (!parse_cookie_vars(impl, ec)) // returns an error_code
          return ec;
      }

      status(impl, common::loaded);

      return ec;
    }

    /// Read and parse the cgi GET meta variables
    template<typename ImplType>
    boost::system::error_code
    parse_get_vars(ImplType& impl, boost::system::error_code& ec)
    {
      // Make sure the request is in a pre-loaded state
      //BOOST_ASSERT (impl.status() <= unloaded);
      if (!(status(impl) & common::get_read))
      {
        std::string const& vars (env_vars(impl.vars_)["QUERY_STRING"]);
        if (!vars.empty())
          detail::extract_params(vars, get_vars(impl.vars_)
                                , boost::char_separator<char>
                                   ("", "=&", boost::keep_empty_tokens)
                                , ec);
        status(impl, (common::request_status)(status(impl) | common::get_read));
      }  
      return ec;
    }

    /// Read and parse the HTTP_COOKIE meta variable
    template<typename ImplType>
    boost::system::error_code
    parse_cookie_vars(ImplType& impl, boost::system::error_code& ec)
    {
      // Make sure the request is in a pre-loaded state
      //BOOST_ASSERT (impl.status() <= unloaded);
      if (!(status(impl) & common::cookies_read))
      {
        std::string const& vars (env_vars(impl.vars_)["HTTP_COOKIE"]);
        if (!vars.empty())
          detail::extract_params(vars, cookie_vars(impl.vars_)
                                , boost::char_separator<char>
                                    ("", "=;", boost::keep_empty_tokens)
                                , ec);
        status(impl, (common::request_status)(status(impl) | common::cookies_read));
      }
      return ec;
    }
    
    /// Read and parse the cgi POST meta variables.
    template<typename ImplType, typename Callback>
    boost::system::error_code&
      parse_post_vars(ImplType& impl, Callback callback, boost::system::error_code& ec)
    {
      if (!(status(impl) & common::post_read))
      {
        if (!impl.fp_)
          // Construct a form_parser instance.
          impl.fp_.reset(new typename ImplType::form_parser_type());

        // Create a context for this request.      
        typename ImplType::form_parser_type::context
            context
                = { env_vars(impl.vars_)["CONTENT_TYPE"]
                  , impl.post_buffer_
                  , impl.form_parts_
                  , impl.client_.bytes_left_
                  , post_vars(impl.vars_)
                  , callback
                  , impl.stdin_parsed_
                  , env_vars(impl.vars_)["REMOTE_ADDR"]
                  };

        // Parse the current request.
        impl.fp_->parse(context, ec);
        status(impl, (common::request_status)(status(impl) | common::post_read));
      }  
      return ec;
    }
  };

 } // namespace common
BOOST_CGI_NAMESPACE_END

#endif // CGI_COMMON_REQUEST_BASE_HPP_INCLUDE_

