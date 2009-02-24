//  Copyright (c) 2001-2008 Oliver Kowalke. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NET_IPV4_TCP_ONE2ONE_H
#define BOOST_NET_IPV4_TCP_ONE2ONE_H

#include <boost/assert.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/utility.hpp>

#include <boost/net/detail/operations.hpp>
#include <boost/net/detail/options.hpp>
#include <boost/net/detail/socket.hpp>
#include <boost/net/ipv4/address.hpp>
#include <boost/net/ipv4/detail/options.hpp>
#include <boost/net/ipv4/tcp/detail/options.hpp>
#include <boost/net/ipv4/utility.hpp>
#include <boost/net/shutdown_mode.hpp>
#include <boost/net/types.hpp>

namespace boost { namespace net {
namespace ipv4 { namespace tcp
{
class one2one
:
private base_from_member< net::detail::socket >,
private net::detail::options,
private ipv4::detail::options,
private detail::options
{
private:
	typedef base_from_member< net::detail::socket >  socket_base_type;

	friend class one2one_listener;

	one2one( native_handle_type handle)
	:
	socket_base_type( handle),
	net::detail::options( member),
	ipv4::detail::options( member),
	detail::options( member)
	{}

public:
//------------------------------------------
	one2one()
	:
	socket_base_type( family_ipv4, socket_stream, protocol_tcp),
	net::detail::options( member),
	ipv4::detail::options( member),
	detail::options( member)
	{}

//------------------------------------------

	native_handle_type native_handle() const
	{ return member.native_handle(); }

	bool is_valid() const
	{ return member.is_valid(); }

	void close()
	{ member.close(); }

	const system::error_code error() const
	{
		BOOST_ASSERT( is_valid() );

		return member.error();
	}

	bool is_non_blocking() const
	{
		BOOST_ASSERT( is_valid() );

		return member.is_non_blocking();
	}

	void non_blocking( bool value)
	{
		BOOST_ASSERT( is_valid() );

		member.non_blocking( value);
	}

//------------------------------------------

	void shutdown( shutdown_mode const& mode)
	{
		BOOST_ASSERT( is_valid() );

		system::error_code ec;
		net::detail::shutdown( native_handle(), mode, ec);
		if ( ec) throw_exception( system::system_error( ec) );
	}

	bool connect( address const& addr)
	{
		BOOST_ASSERT( is_valid() );

		system::error_code ec;
		net::detail::connect(
			native_handle(),
			addr.sockaddr_ptr(),
			addr.size(),
			ec);
		if ( ec)
		{
			if ( ec.value() == system::errc::interrupted ||
				ec.value() == system::errc::operation_in_progress)
				return false;
			else
				throw_exception( system::system_error( ec) );
		}
		return true;
	}

	bool connect(
		address const& addr,
		posix_time::time_duration const& timeout)
	{
		BOOST_ASSERT( is_valid() );
		BOOST_ASSERT( ! timeout.is_special() );
		BOOST_ASSERT( ! timeout.is_negative() );
	
		system::error_code ec;
		net::detail::is_readable( native_handle(), timeout, ec);
		if ( ec) throw_exception( system::system_error( ec) );
	
		return connect( addr);
	}

//------------------------------------------

	const address local_address() const
	{
		BOOST_ASSERT( is_valid() );

		system::error_code ec;
		sockaddr_in4_type sa;
		sockaddr_len_type len( sizeof( sockaddr_in4_type) );
		void * vp( & sa);
		net::detail::getsockname(
			native_handle(),
			static_cast< sockaddr_type * >( vp),
			& len,
			ec);
		if ( ec) throw_exception( system::system_error( ec) );
		return address( sa);
	}

	const address peer_address() const
	{
		BOOST_ASSERT( is_valid() );

		system::error_code ec;
		sockaddr_in4_type sa;
		sockaddr_len_type len( sizeof( sockaddr_in4_type) );
		void * vp( & sa);
		net::detail::getpeername(
			native_handle(),
			static_cast< sockaddr_type * >( vp),
			& len,
			ec);
		if ( ec) throw_exception( system::system_error( ec) );
		return address( sa);
	}

//-----------------------------------------

	using net::detail::options::debug;
	using net::detail::options::dont_route;
	using net::detail::options::keep_alive;
	using net::detail::options::linger;
	using net::detail::options::receive_buffer;
	using net::detail::options::receive_lowat;
	using net::detail::options::receive_timeout;
	using net::detail::options::send_buffer;
	using net::detail::options::send_lowat;
	using net::detail::options::send_timeout;

//-----------------------------------------

	using ipv4::detail::options::time_to_live;
	using ipv4::detail::options::type_of_service;

//-----------------------------------------

	using detail::options::no_delay;
	using detail::options::max_segment_size;
};
}}}}

#endif // BOOST_NET_IPV4_TCP_ONE2ONE_H
