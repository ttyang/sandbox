//              -- common/request_status.hpp --
//
//            Copyright (c) Darren Garvey 2007.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////
#ifndef CGI_COMMON_REQUEST_STATUS_HPP_INCLUDED__
#define CGI_COMMON_REQUEST_STATUS_HPP_INCLUDED__
#include "boost/cgi/config.hpp"

BOOST_CGI_NAMESPACE_BEGIN
 namespace common {

   enum request_status
     { null           = 0
     , unloaded       = null
     , activated      = 1
     , accepted       = activated
     , env_read       = 2
     , get_read       = 4
     , post_read      = 8
     , cookies_read   = 16
     , loaded         = 32
     , ok             = loaded
     , aborted
     , closed
     };

 } // namespace common
BOOST_CGI_NAMESPACE_END

#endif // CGI_COMMON_REQUEST_STATUS_HPP_INCLUDED__

