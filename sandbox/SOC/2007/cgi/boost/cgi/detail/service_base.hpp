//                  -- service_base.hpp --
//                  (taken from Boost.Asio)
//
//     Copyright (c) 2003-2007 Christopher M. Kohlhoff
//               (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////
#ifndef CGI_DETAIL_SERVICE_ID_HPP_INCLUDED__
#define CGI_DETAIL_SERVICE_ID_HPP_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/asio/detail/service_id.hpp>

namespace cgi {
 namespace detail {

   // Special service base class to keep classes header-file only.
   template <typename Type>
   class service_base
     : public boost::asio::io_service::service
   {
   public:
     static boost::asio::detail::service_id<Type> id;

      // Constructor.
     service_base(boost::asio::io_service& io_service)
       : boost::asio::io_service::service(io_service)
     {
     }
   };

   template <typename Type>
   boost::asio::detail::service_id<Type> service_base<Type>::id;

 } // namespace detail
} // namespace cgi

#include <boost/asio/detail/pop_options.hpp>

#endif // CGI_DETAIL_SERVICE_ID_HPP_INCLUDED__
