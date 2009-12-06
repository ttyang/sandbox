//               -- cgi_request_impl.hpp --
//
//          Copyright (c) Darren Garvey 2007-2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////
#ifndef CGI_CGI_REQUEST_IMPL_HPP_INCLUDED__
#define CGI_CGI_REQUEST_IMPL_HPP_INCLUDED__

#include "boost/cgi/detail/push_options.hpp"

#include "boost/cgi/cgi/service.hpp"
#include "boost/cgi/basic_client.hpp"
#include "boost/cgi/connections/async_stdio.hpp"

// Make this ProtocolService-independent

BOOST_CGI_NAMESPACE_BEGIN

  class cgi_request_impl
  {
  public:
    typedef ::BOOST_CGI_NAMESPACE::common::map              map_type;
    typedef ::BOOST_CGI_NAMESPACE::cgi::service            protocol_service_type;
    typedef protocol_service_type::protocol_type            protocol_type;
    typedef connections::async_stdio                        connection_type;
    typedef
      ::BOOST_CGI_NAMESPACE::common::basic_client<
        connection_type, common::tags::cgi
      >
    client_type;
    typedef connection_type::pointer                        conn_ptr;

    /// Constructor
    cgi_request_impl()
      : stdin_parsed_(false)
      , stdin_data_read_(false)
      , stdin_bytes_left_(-1)
      , http_status_(common::http::ok)
      , request_status_(common::unloaded)
    {
    }

    protocol_service_type* service_;
        
    bool stdin_parsed()                      { return stdin_parsed_;   }
    common::http::status_code& http_status() { return http_status_;    }
    common::request_status& status()         { return request_status_; }

    conn_ptr& connection()                   { return connection_;     }

    bool stdin_parsed_;
    bool stdin_data_read_;
    std::size_t stdin_bytes_left_;
    
  private:

    common::http::status_code http_status_;
    common::request_status request_status_;

    conn_ptr connection_;

  };

BOOST_CGI_NAMESPACE_END

#include "boost/cgi/detail/pop_options.hpp"

#endif // CGI_CGI_REQUEST_IMPL_HPP_INCLUDED__

