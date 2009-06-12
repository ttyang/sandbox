// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <list>
#include <boost/monotonic/allocator.h>

namespace boost
{
	namespace monotonic
	{
		/// A std::list<T> that uses a monotonic allocator
		template <class T>
		struct list : std::list<T, allocator<T> >
		{
			typedef allocator<T> Allocator;
			typedef std::list<T, Allocator> List;

			list() { }
			list(storage_base &storage) 
				: List(Allocator(storage)) { }
			list(Allocator const &A) 
				: List(A) { }
			template <class II>
			list(II F, II L, storage_base &S)
				: List(F,L,Allocator(S)) { }
			template <class II>
			list(II F, II L, Allocator const &A)
				: List(F,L,A) { }
		};
	}
}

//EOF
