//  Copyright (c) 2001-2008 Oliver Kowalke. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NET_IPV4_ADDRESS_INFO_H
#define BOOST_NET_IPV4_ADDRESS_INFO_H

#include <boost/net/detail/config.hpp>

extern "C"
{
#include <netinet/in.h>
}

#include <string>

#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/net/ipv4/address.hpp>
#include <boost/net/ipv4/utility.hpp>
#include <boost/net/types.hpp>

namespace boost { namespace net {
namespace ipv4
{
class address_info
{
private:
	shared_ptr< addrinfo_type >	root_;
	addrinfo_type			*	current_;

public:
	address_info(
		shared_ptr< addrinfo_type >	root,
		addrinfo_type * current)
	: root_( root), current_( current)
	{
		BOOST_ASSERT( root_);
		BOOST_ASSERT( current_);
	}

	const std::string canonical_name() const
	{
		BOOST_ASSERT( root_);
		return root_->ai_canonname ? root_->ai_canonname : "";
	}

	socket_type socktype() const
	{
		BOOST_ASSERT( root_);
		BOOST_ASSERT( current_);
		return static_cast< socket_type >( current_->ai_socktype);
	}

	protocol_type protocol() const
	{
		BOOST_ASSERT( root_);
		BOOST_ASSERT( current_);
		return static_cast< protocol_type >( current_->ai_protocol);
	}

	const address to_address() const
	{
		BOOST_ASSERT( root_);
		BOOST_ASSERT( current_);

		void * vp( current_->ai_addr);
		BOOST_ASSERT( current_->ai_family == PF_INET);
		sockaddr_in4_type * in4( static_cast< sockaddr_in4_type * >( vp) );
		return address( * in4);
	}

	operator const address() const
	{ return to_address(); }
};
}}}

#endif // BOOST_NET_IPV4_ADDRESS_INFO_H