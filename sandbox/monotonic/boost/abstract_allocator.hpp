// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ABSTRACT_ALLOCATOR_HPP
#define BOOST_ABSTRACT_ALLOCATOR_HPP

#include <memory>

namespace boost
{
	/// base class for (wrapped) allocators that may be used with cloneable::base
	struct abstract_allocator
	{
		typedef char *pointer;

		virtual pointer allocate_bytes(size_t num_bytes, size_t alignment) = 0;

		virtual void deallocate_bytes(pointer) = 0;
	};

} // namespace boost

#endif // BOOST_ABSTRACT_ALLOCATOR_HPP

//EOF
