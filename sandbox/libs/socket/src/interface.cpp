// Copyright (C) 2002 Hugo Duncan

// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Hugo Duncan makes no representations
// about the suitability of this software for any purpose.
// It is provided "as is" without express or implied warranty.

#ifdef _MSC_VER
#pragma warning (disable: 4786 4305)
  // 4786 truncated debug symbolic name
  // 4305 truncation from const double to float
#endif

#if defined(__BORLANDC__)
#pragma hdrstop
#endif

#include "boost/socket/config.hpp"
#include "boost/socket/interface.hpp"
#include "boost/socket/any_address.hpp"

#ifdef USES_WINSOCK2
#include <Winsock2.h>
#include <Ws2tcpip.h>
#else

#endif

#include <iostream>
#include <string.h>

#ifdef _MSC_VER
#pragma warning (push, 4)
#pragma warning (disable: 4786 4305)
#endif


namespace boost
{
  namespace socket
  {

    inline INTERFACE_INFO*&
    cast_interfaceinfo(boost::socket::interfaceinfo*& iface)
    {
      return (INTERFACE_INFO*&)(iface);
    }

    inline INTERFACE_INFO const*
    cast_interfaceinfo(const boost::socket::interfaceinfo* iface)
    {
      return (INTERFACE_INFO const*)(iface);
    }


    any_address interface_info::address() const
    {
      return any_address(
        AF_INET,
        (sockaddr_in*)&cast_interfaceinfo(m_interfaceinfo)->iiAddress,
        sizeof(sockaddr_in));
    }

    any_address interface_info::netmask() const
    {
      return any_address(
        AF_INET,
        (sockaddr_in*)&cast_interfaceinfo(m_interfaceinfo)->iiNetmask,
        sizeof(sockaddr_in));
    }

    any_address interface_info::broadcast() const
    {
      return any_address(
        AF_INET,
        (sockaddr_in*)&cast_interfaceinfo(m_interfaceinfo)->iiBroadcastAddress,
        sizeof(sockaddr_in));
    }

    bool interface_info::is_up() const
    {
      return cast_interfaceinfo(m_interfaceinfo)->iiFlags && IFF_UP;
    }

    bool interface_info::is_point_to_point() const
    {
      return cast_interfaceinfo(m_interfaceinfo)->iiFlags && IFF_POINTTOPOINT;
    }

    bool interface_info::is_loopback() const
    {
      return cast_interfaceinfo(m_interfaceinfo)->iiFlags && IFF_LOOPBACK;
    }

    bool interface_info::can_broadcast() const
    {
      return cast_interfaceinfo(m_interfaceinfo)->iiFlags && IFF_BROADCAST;
    }

    bool interface_info::can_multicast() const
    {
      return cast_interfaceinfo(m_interfaceinfo)->iiFlags && IFF_MULTICAST;
    }

    interface_info::interface_info()
        : m_interfaceinfo(0)
    {}

    void interface_info::set(interfaceinfo const* info)
    {
      m_interfaceinfo=info;
    }


    namespace
    {
      const std::size_t buffer_len=20*sizeof(INTERFACE_INFO);
    }

    interface_info_list::interface_info_list()
    {
      SOCKET socket=::WSASocket(AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
      m_buffer.reset(new char[buffer_len]);

      unsigned long nBytesReturned;
      if (::WSAIoctl(socket,
                     SIO_GET_INTERFACE_LIST, 0, 0, &*m_buffer,
                     buffer_len,
                     &nBytesReturned, 0, 0) == SOCKET_ERROR)
      {
        std::cerr << "Failed calling WSAIoctl: error "
                  << WSAGetLastError() << std::endl;
      }
      m_num_interfaces=nBytesReturned / sizeof(INTERFACE_INFO);

      ::closesocket(socket);
    }

    interface_info_list::~interface_info_list()
    {
    }

    interface_info_list::iterator interface_info_list::begin() const
    {
      return iterator((interfaceinfo*)m_buffer.get());
    }

    interface_info_list::iterator interface_info_list::end() const
    {
      return iterator((interfaceinfo*)
                      (((INTERFACE_INFO*)m_buffer.get())+m_num_interfaces));
    }

    interfaceinfo const* interface_info_list::next(interfaceinfo const* arg)
    {
      return (interfaceinfo*) (++(INTERFACE_INFO*)arg);
    }


  }// namespace
}// namespace

#ifdef _MSC_VER
#pragma warning (pop)
#endif
