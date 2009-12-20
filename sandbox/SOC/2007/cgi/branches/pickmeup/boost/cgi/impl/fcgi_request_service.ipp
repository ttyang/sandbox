//             -- fcgi/request_service.ipp --
//
//            Copyright (c) Darren Garvey 2007.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////
#ifndef CGI_FCGI_REQUEST_SERVICE_IPP_INCLUDED__
#define CGI_FCGI_REQUEST_SERVICE_IPP_INCLUDED__

#include <boost/fusion/support.hpp>
#include <boost/system/error_code.hpp>
#include <boost/fusion/include/vector.hpp>
////////////////////////////////////////////////////////////////
#include "boost/cgi/fcgi/error.hpp"
#include "boost/cgi/fcgi/client.hpp"
#include "boost/cgi/fcgi/request_service.hpp"
#include "boost/cgi/common/map.hpp"
#include "boost/cgi/common/tags.hpp"
#include "boost/cgi/common/role_type.hpp"
#include "boost/cgi/common/form_parser.hpp"
#include "boost/cgi/common/source_enums.hpp"
#include "boost/cgi/common/request_base.hpp"
#include "boost/cgi/common/parse_options.hpp"
#include "boost/cgi/http/status_code.hpp"
#include "boost/cgi/import/read.hpp"
#include "boost/cgi/import/io_service.hpp"
#include "boost/cgi/detail/service_base.hpp"
#include "boost/cgi/detail/throw_error.hpp"
#include "boost/cgi/config.hpp"

BOOST_CGI_NAMESPACE_BEGIN

   namespace detail {
     
     /// Helper class to asynchronously load a request.
     /**
      * This is just a function object that can be posted to another
      * thread to do the actual work of loading. It's operator()() does
      * the work.
      */
     template<typename T, typename Handler>
     struct async_load_helper
     {
       async_load_helper(T& t, typename T::implementation_type& impl
                        , bool parse_stdin, Handler h)
         : type(t)
         , impl_(impl)
         , parse_stdin_(parse_stdin)
         , handler_(h)
       {
       }

       void operator()()
       {
         boost::system::error_code ec;
         type.load(impl_, parse_stdin_, ec);
         handler_(ec);
       }

       T& type;
       typename T::implementation_type& impl_;
       bool parse_stdin_;
       Handler handler_;
     };

  } // namespace detail

  namespace fcgi {
 
    /// Close the request.
    BOOST_CGI_INLINE int
    fcgi_request_service::close(
        implementation_type& impl
      , ::BOOST_CGI_NAMESPACE::common::http::status_code& hsc
      , int program_status)
    {
      boost::system::error_code ec;
      close(impl, hsc, program_status, ec);
      detail::throw_error(ec);
      return program_status;
    }

    BOOST_CGI_INLINE int
    fcgi_request_service::close(
        implementation_type& impl
      , ::BOOST_CGI_NAMESPACE::common::http::status_code& hsc
      , int program_status
      , boost::system::error_code& ec)
    {
      /**
       * Apache on Windows with mod_fcgid requires that all of the
       * pending data for the connection is read before the response
       * is sent.
       */
      while(!ec 
        && impl.client_.status() < common::stdin_read
        && impl.request_status_ != common::loaded)
      {
        parse_packet(impl, ec);
      }

      impl.all_done_ = true;
      impl.client_.close(program_status, ec);
      impl.request_status_ = common::closed;
      return program_status;
    }

    BOOST_CGI_INLINE void
    fcgi_request_service::clear(implementation_type& impl)
    {
      /*
      BOOST_ASSERT
      (   impl.request_status_ < common::activated
       && impl.request_status_ > common::ok
       && "Are you trying to clear() a request without closing it?"
      );
      */
                
      impl.post_buffer_.clear();
      impl.param_buffer_.clear();
      common::get_vars(impl.vars_).clear();
      common::post_vars(impl.vars_).clear();
      common::cookie_vars(impl.vars_).clear();
      common::env_vars(impl.vars_).clear();
      impl.stdin_parsed_ = false;
      impl.get_parsed_ = false;
      impl.http_status_ = common::http::no_content;
      impl.request_status_ = common::null;
      impl.request_role_ = spec_detail::ANY;
      impl.all_done_ = false;
      impl.client_.status_ = common::none_;
      impl.client_.request_id_ = -1;
    }
      
    /// Load the request to a point where it can be usefully used.
    /**
     * FastCGI:
     * --------
     *
     *  - Calls client::construct() to claim a request id from the server.
     *  - Reads, parses and handles all packets until the closing `PARAMS`
     *    packet for this request arrives from the server.
     *
     */
    BOOST_CGI_INLINE boost::system::error_code
    fcgi_request_service::load(
        implementation_type& impl, common::parse_options opts
      , boost::system::error_code& ec)
    {
      BOOST_ASSERT(!ec &&
        "Can't load request due to previous errors.");

      impl.client_.construct(impl, ec);
      // Bomb out if the client isn't open here.
      if (!impl.client_.connection()->is_open())
          return error::client_not_open;

      while(!ec)
      {
        if (read_header(impl, ec))
          break;
        int id(spec::get_request_id(impl.header_buf_));
        if (id == spec::null_request_id::value)
          handle_admin_request(impl);
        else
        if (impl.id_ && impl.id_ != id)
        {
          // The library doesn't support multiplexed connections yet,
          // mainly because I've never had access to a server that
          // supports it.
          //
          // If you have one, can I use it?
          ec = error::multiplexing_not_supported;
        }
        else
        if (spec::get_type(impl.header_buf_) 
            == spec::begin_request::value)
        {
          impl.id_ = id;
          impl.client_.request_id_ = id;
          if (!read_header(impl, ec))
          {
            spec::begin_request packet(impl.header_buf_);
            impl.request_role_ = packet.role();
            impl.client_.keep_connection_
              = packet.flags() & spec::keep_connection;
            break;
          }
        }else
          handle_other_request_header(impl);
      }
      
      if (//impl.request_status_ < common::env_read &&
          opts & common::parse_env)
      {
        read_env_vars(impl, ec);
        //impl.request_status_ = common::env_read;
      }

      string_type const&
        request_method (env_vars(impl.vars_)["REQUEST_METHOD"]);
        
      if (request_method == "GET")
      {
        if (parse_get_vars(impl, ec))
          return ec;
      }
      else
      if (request_method == "POST" 
          && opts & common::parse_post_only)
      {
        std::cerr<< "Parsing post vars now.\n";

        if (opts & common::parse_post_only)
        {
          while(!ec 
            && impl.client_.status() < common::stdin_read
            && impl.request_status_ != common::loaded)
          {
            parse_packet(impl, ec);
          }
        }
        
        if (parse_post_vars(impl, ec))
	      return ec;
      }
      if (opts & common::parse_cookies_only)
        parse_cookie_vars(impl, ec);
        
      if (ec == error::eof) {
        ec = boost::system::error_code();
        return ec;
      }
      else if (ec) return ec;
      
      //bool check = impl.client_.is_open();

      return ec;
    }

    // **FIXME**
    template<typename Handler> BOOST_CGI_INLINE
    void fcgi_request_service::async_load(
        implementation_type& impl, bool parse_stdin, Handler handler)
    {
      this->io_service().post(
        detail::async_load_helper<self_type, Handler>(this, parse_stdin, handler)
      );
    }

    /// Check if the params have been read (ie. FCGI_PARAMS packets)
    BOOST_CGI_INLINE
    bool fcgi_request_service::params_read(implementation_type& impl)
    {
      return impl.client_.status() >= common::params_read;
    }

    BOOST_CGI_INLINE
    void fcgi_request_service::set_status(
        implementation_type& impl, common::request_status status)
    {
      impl.request_status_ = status;
    }

    /// Read and parse the cgi POST meta variables (greedily)
    BOOST_CGI_INLINE boost::system::error_code&
    fcgi_request_service::parse_post_vars(
        implementation_type& impl
      , boost::system::error_code& ec)
    {
      if (!impl.fp_)
        // Construct a form_parser instance.
        impl.fp_.reset(new implementation_type::form_parser_type());

      impl.client_.bytes_left_
         = boost::lexical_cast<std::size_t>(
             env_vars(impl.vars_)["CONTENT_LENGTH"]);
      
      // Create a context for this request.      
      implementation_type::form_parser_type::context
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

    /// Read and parse a single cgi POST meta variable (greedily)
    template<typename RequestImpl> BOOST_CGI_INLINE
    boost::system::error_code&
    fcgi_request_service::parse_one_post_var(
        implementation_type& impl, boost::system::error_code& ec)
    {
      //#     error "Not implemented"
      return ec;
    }

    // **FIXME**
    /// Read some data from the client.
    template<typename MutableBufferSequence>
    BOOST_CGI_INLINE std::size_t
    fcgi_request_service::read_some(
        implementation_type& impl, const MutableBufferSequence& buf
      , boost::system::error_code& ec)
    {
      if (impl.client_.status_ == common::closed_)
      {
        ec = common::error::client_closed;
        return 0;
      }

      //if (read_header(ec))
        return 0;

      //boost::tribool state = parse_header(impl);
      //std::size_t bytes_read;//( connection_->read_some(buf, ec) );
      //return bytes_read;
    }

    /// Read in the FastCGI (env) params
    // **FIXME**
    BOOST_CGI_INLINE boost::system::error_code
    fcgi_request_service::read_env_vars(
        implementation_type& impl, boost::system::error_code& ec)
    {
      while(!ec && !params_read(impl))
      {
        if (this->read_header(impl, ec))
          return ec;
          
        boost::tribool state = this->parse_header(impl);

        if (state)
          // the header has been handled and all is ok; continue.
          impl.client_.status(common::params_read);
        else
        if (!state)
          // The header is confusing; something's wrong. Abort.
          ec = error::bad_header_type;
        else // => (state == boost::indeterminate)
        {
          std::size_t remaining(
            fcgi::spec::get_length(impl.header_buf_));

          if (remaining)
          {
            implementation_type::mutable_buffers_type buf
              = impl.prepare_misc(remaining);

            if (this->read_body(impl, buf, ec))
              return ec;

            this->parse_body(impl, buf, ec);
          } else
            ec = error::couldnt_write_complete_packet;
        }

      } // while(!ec && !params_read(impl))
      return ec;
    }

    /// Read a single header, but do nothing with it.
    BOOST_CGI_INLINE boost::system::error_code
    fcgi_request_service::read_header(
        implementation_type& impl
      , boost::system::error_code& ec)
    {
      // clear the header first (might be unneccesary).
      impl.header_buf_ = implementation_type::header_buffer_type();

      if (8 != read(*impl.client_.connection(), buffer(impl.header_buf_)
                   , boost::asio::transfer_all(), ec) || ec)
        return ec;
      
      return ec;
    }

    /*** Various handlers go below here; they might find a
     * better place to live ***/

    // **FIXME**
    BOOST_CGI_INLINE void
    fcgi_request_service::handle_admin_request(implementation_type& impl)
    {
      //std::cerr<< std::endl << "**FIXME** " << __FILE__ << ":" << __LINE__ 
      //  << " handle_admin_request()" << std::endl;
    }

    // **FIXME**
    BOOST_CGI_INLINE void
    fcgi_request_service::handle_other_request_header(implementation_type& impl)
    {
      //std::cerr<< std::endl << "**FIXME** " << __FILE__ << ":" << __LINE__ 
      //  << " handle_other_request_header()" << std::endl;
    }

    BOOST_CGI_INLINE boost::system::error_code
    fcgi_request_service::process_abort_request(
        implementation_type& impl, boost::uint16_t id
      , const unsigned char* buf, boost::uint32_t
      , boost::system::error_code& ec)
    {
      if (id == fcgi::spec::get_request_id(impl.header_buf_))
      {
        impl.request_status_ = common::aborted;
        return ec;
      }
      try {
        //std::cerr<< "**FIXME** request aborted (id = " << id
        //  << ") but request not notified." << std::endl;
        //impl.client_.connection_->requests_.at(id - 1)->abort();
      }catch(...){
        ec = error::abort_request_record_recieved_for_invalid_request;
      }
      return ec;
    }

    BOOST_CGI_INLINE boost::system::error_code
    fcgi_request_service::process_params(
        implementation_type& impl, boost::uint16_t id
      , const unsigned char* buf, boost::uint32_t len
      , boost::system::error_code& ec)
    {
      if (0 == len)
      { // This is the final param record.
        
        impl.client_.status(common::params_read);
        return ec;
      }

      while(len)
      {
        boost::uint32_t   name_len, data_len;
        string_type name, data;
        if (*buf >> 7 == 0)
        {
            name_len = *(buf++);
            --len;
        }
        else
        {
            name_len = ((buf[0] & 0x7F) << 24)
                     +  (buf[1]         << 16)
                     +  (buf[2]         <<  8)
                     +   buf[3];
            buf += 4;
            len -= 4;
        }

        if (*buf >> 7 == 0)
        {
            data_len = *(buf++);
            --len;
        }
        else
        {
            data_len = ((buf[0] & 0x7F) << 24)
                     +  (buf[1]         << 16)
                     +  (buf[2]         <<  8)
                     +   buf[3];
            buf += 4;
            len -= 4;
        }
        name.assign(reinterpret_cast<const char*>(buf), name_len);
        data.assign(reinterpret_cast<const char*>(buf)+name_len, data_len);
        buf += (name_len + data_len);
        len -= (name_len + data_len);

        env_vars(impl.vars_)[name.c_str()] = data;
      }

      return ec;
    }


    BOOST_CGI_INLINE boost::system::error_code
    fcgi_request_service::process_stdin(
        implementation_type& impl, boost::uint16_t id
      , const unsigned char* buf, boost::uint32_t len
      , boost::system::error_code& ec)
    {
      if (0 == len)
      {
        impl.client_.status(common::stdin_read);
        return ec;
      }
      return ec;
    }

    /// Parse the current header
    BOOST_CGI_INLINE boost::tribool
    fcgi_request_service::parse_header(implementation_type& impl)
    {
      BOOST_ASSERT(fcgi::spec::get_version(impl.header_buf_) == 1
                   && "This library is only compatible with FastCGI 1.0");

      using namespace fcgi::spec_detail;

      switch(fcgi::spec::get_type(impl.header_buf_))
      {
      case BEGIN_REQUEST:
      case DATA:
      case GET_VALUES:
        return boost::indeterminate;
      case STDIN:
        if (0 == fcgi::spec::get_length(impl.header_buf_)) {
          impl.client_.status(common::stdin_read);
          return true;
        } else
          return boost::indeterminate;
      case PARAMS:
        if (0 == fcgi::spec::get_length(impl.header_buf_)) {
          impl.client_.status(common::params_read);
          return true;
        } else
          return boost::indeterminate;
      case ABORT_REQUEST:
        return false;
      case UNKNOWN_TYPE:
      default:
        return true;
      }
    }

    BOOST_CGI_INLINE boost::system::error_code
    fcgi_request_service::parse_packet(
        implementation_type& impl, boost::system::error_code& ec)
    {
      if (this->read_header(impl, ec))
        return ec;

      boost::tribool state = this->parse_header(impl);

      if (state)
      { 
        // the header has been handled and all is ok.
        // **NOOP**
      } else
      if (!state)
      { // The header is confusing; something's wrong. Abort.
        ec = error::bad_header_type;
      }
      else
      {
        std::size_t remaining(fcgi::spec::get_length(impl.header_buf_));
        if (remaining)
        {
          implementation_type::mutable_buffers_type buf
            = impl.prepare(remaining);

          if (this->read_body(impl, buf, ec))
            return ec;

          this->parse_body(impl, buf, ec);
        }
      }
      return ec;
    }

    /// Read the body of the current packet; do nothing with it.
    template<typename MutableBuffersType> BOOST_CGI_INLINE
    boost::system::error_code
    fcgi_request_service::read_body(
        implementation_type& impl, const MutableBuffersType& buf
      , boost::system::error_code& ec)
    {
      std::size_t bytes_read
        = read(*impl.client_.connection(), buf
              , boost::asio::transfer_all(), ec);

      BOOST_ASSERT(bytes_read == fcgi::spec::get_length(impl.header_buf_)
                   && "Couldn't read all of the record body.");
      return ec;
    }

    template<typename MutableBuffersType> BOOST_CGI_INLINE
    boost::system::error_code
    fcgi_request_service::parse_body(
        implementation_type& impl, const MutableBuffersType& buf
      , boost::system::error_code& ec)
    {
      switch(fcgi::spec::get_type(impl.header_buf_))
      {
      case 1: process_begin_request(impl, fcgi::spec::get_request_id(impl.header_buf_)
              , boost::asio::buffer_cast<unsigned char*>(buf)
              , boost::asio::buffer_size(buf), ec);
              break;
      case 2: process_abort_request(impl, fcgi::spec::get_request_id(impl.header_buf_)
              , boost::asio::buffer_cast<unsigned char*>(buf)
              , boost::asio::buffer_size(buf), ec);
              break;
      case 4: process_params(impl, fcgi::spec::get_request_id(impl.header_buf_)
              , boost::asio::buffer_cast<unsigned char*>(buf)
              , boost::asio::buffer_size(buf), ec);
              break;
      case 5: process_stdin(impl, fcgi::spec::get_request_id(impl.header_buf_)
              , boost::asio::buffer_cast<unsigned char*>(buf)
              , boost::asio::buffer_size(buf), ec);
              break;
      default: break;
      }
      return ec;
    }

    BOOST_CGI_INLINE boost::system::error_code
    fcgi_request_service::begin_request_helper(
        implementation_type& impl
      , implementation_type::header_buffer_type& header
      , boost::system::error_code& ec)
    {
       impl.client_.request_id_ = fcgi::spec::get_request_id(header);

       BOOST_STATIC_ASSERT((
        fcgi::spec::begin_request::body::size::value
        == fcgi::spec::header_length::value));
       
       // A begin request body is as long as a header, so we can optimise:
       if (read_header(impl, ec))
         return ec;
        
       spec::begin_request packet(impl.header_buf_);
       impl.request_role_ = packet.role();
       impl.client_.role_ = packet.role();
       impl.client_.keep_connection_
         = packet.flags() & spec::keep_connection;

       impl.client_.status_ = common::constructed;
       
       return ec;
    }

 } // namespace fcgi
BOOST_CGI_NAMESPACE_END

#include "boost/cgi/fcgi/request.hpp"
#include "boost/cgi/basic_request.hpp"

BOOST_CGI_NAMESPACE_BEGIN
 namespace fcgi {

    BOOST_CGI_INLINE boost::system::error_code
    fcgi_request_service::process_begin_request(
        implementation_type& impl, boost::uint16_t id
      , const unsigned char* buf, boost::uint32_t
      , boost::system::error_code& ec)
    {
      if (impl.client_.request_id_ == 0) // ie. hasn't been set yet.
      {
        begin_request_helper(impl, impl.header_buf_, ec);
      }
      else
      {
        //std::cerr<< "**FIXME** Role: " 
        //  << fcgi::spec::begin_request::get_role(impl.header_buf_) << std::endl;

        implementation_type::client_type::connection_type&
          conn = *impl.client_.connection();
      }
      return ec;
    }

 } // namespace fcgi
BOOST_CGI_NAMESPACE_END

#endif // CGI_FCGI_REQUEST_SERVICE_IPP_INCLUDED__

