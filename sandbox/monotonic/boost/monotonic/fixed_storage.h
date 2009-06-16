// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cassert>
#include <boost/array.hpp>
#include <boost/aligned_storage.hpp>

// define this to use boost::auto_buffer<> rather than boost::array for monotonic::storage
//#define BOOST_MONOTONIC_USE_AUTOBUFFER
// this currently does not work, because resizing the underlying buffer breaks
// containers that may reference the previously used memory

#ifdef BOOST_MONOTONIC_USE_AUTOBUFFER
#	include <boost/auto_buffer.hpp>
#endif

namespace boost
{
	namespace monotonic
	{
		/// storage for an allocator that is on the stack or heap
		template <size_t N>
		struct fixed_storage : storage_base
		{
			typedef boost::array<char, N> Buffer;

		private:
			Buffer buffer;			///< the storage
			size_t cursor;				///< pointer to current index within storage for next allocation
#ifndef NDEBUG
			size_t num_allocations;
#endif
		public:
			fixed_storage() 
				: cursor(0)
#ifndef NDEBUG
				, num_allocations(0)
#endif
			{
			}

			Buffer const &get_buffer()  const
			{
				return buffer;
			}
			const char *begin() const
			{
				return &buffer[0];
			}
			const char *end() const
			{
				return &buffer[N - 1];
			}
			void reset()
			{
				cursor = 0;
#ifndef NDEBUG
				num_allocations = 0;
#endif
			}

			size_t get_cursor() const
			{
				return cursor;
			}

			void set_cursor(size_t c)
			{
				cursor = c;
			}

			/// allocate storage, given alignment requirement
			void *allocate(size_t num_bytes, size_t alignment)
			{
				// ensure we return a point on an aligned boundary
				size_t extra = cursor & (alignment - 1);
				if (extra > 0)
					extra = alignment - extra;
				size_t required = num_bytes + extra;
				if (cursor + required > N)
				{
					return 0;
				}
#ifndef NDEBUG
				++num_allocations;
#endif
				char *ptr = &buffer[cursor];
				cursor += required;
				return ptr + extra;
			}

			size_t max_size() const
			{
				return N;
			}

			size_t remaining() const
			{
				return N - cursor;
			}

			size_t used() const
			{
				return cursor;
			}

#ifndef NDEBUG
			size_t get_num_allocs() const
			{
				return num_allocations;
			}
#endif
		};
	
	} // namespace monotonic

} // namespace boost

//EOF
