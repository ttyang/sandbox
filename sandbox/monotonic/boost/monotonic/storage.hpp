// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_STORAGE_H
#define BOOST_MONOTONIC_STORAGE_H

#include <algorithm>
#include <boost/monotonic/fixed_storage.hpp>

namespace boost
{
	namespace monotonic
	{
		/// storage that spans the stack/heap boundary.
		///
		/// allocation requests first use inline fixed_storage of InlineSize bytes.
		/// once that is exhausted, later requests are serviced from the heap.
		///
		/// all allocations remain valid at all times.
		template <size_t InlineSize, size_t MinHeapIncrement, class Al>
		struct storage : storage_base
		{
			typedef Al Allocator;
			typedef typename Allocator::template rebind<char>::other CharAllocator;

			/// a link in the chain of heap-based memory buffers
			struct Link
			{
				size_t capacity, cursor;
				char *buffer;
				CharAllocator alloc;
				Link() : capacity(0), cursor(0), buffer(0)
				{
				}
				Link(Allocator const &al, size_t cap)
					: capacity(cap), cursor(0), buffer(0), alloc(al)
				{
				}
				void Construct()
				{
					buffer = alloc.allocate(capacity);
					if (buffer == 0)
						capacity = 0;
				}
				void reset()
				{
				    cursor = 0;
				}
				void clear()
				{
					alloc.deallocate(buffer, 1);
				}
				size_t used() const
				{
					return cursor;
				}
				bool CanAllocate(size_t num_bytes) const
				{
					return capacity - cursor >= num_bytes;
				}
				inline void *Allocate(size_t num_bytes, size_t alignment)
				{
					size_t extra = cursor & (alignment - 1);
					if (extra > 0)
						extra = alignment - extra;
					size_t required = num_bytes + extra;
					if (capacity - cursor < required)
						return 0;
					char *ptr = buffer + cursor;
					cursor += required;
					return ptr + extra;
				}
				friend bool operator<(Link const &A, Link const &B)
				{
					return A.capacity < B.capacity;
				}
			};
			typedef std::vector<Link, Al> Chain;	// maintained a priority-queue

		private:
			fixed_storage<InlineSize> fixed;	// the inline fixed-sized storage which may be on the stack
			Chain chain;						// heap-based storage
			Allocator alloc;					// allocator for heap-based storage

		public:
			storage()
			{
			}
			storage(Allocator const &A)
				: alloc(A)
			{
			}
			~storage()
			{
				release();
			}

			void reset()
			{
				fixed.reset();
				BOOST_FOREACH(Link &link, chain)
				{
				    link.reset();
				}
			}

			void release()
			{
				reset();
				BOOST_FOREACH(Link &link, chain)
				{
					link.clear();
				}
				chain.clear();
			}

			void *allocate(size_t num_bytes, size_t alignment)
			{
				if (void *ptr = fixed.allocate(num_bytes, alignment))
				{
					return ptr;
				}
				if (!chain.empty())
				{
					if (void *ptr = chain.front().Allocate(num_bytes, alignment))
					{
						return ptr;
					}
					std::make_heap(chain.begin(), chain.end());
					if (void *ptr = chain.front().Allocate(num_bytes, alignment))
					{
						return ptr;
					}
				}
				size_t size = std::max(MinHeapIncrement, num_bytes*2);
				return AddLink(size).Allocate(num_bytes, alignment);
			}

			size_t max_size() const
			{
				return std::numeric_limits<size_t>::max();
			}

			size_t fixed_remaining() const
			{
				return fixed.remaining();
			}

			size_t remaining() const
			{
				return max_size();
			}

			size_t used() const
			{
				size_t count = fixed.used();
				BOOST_FOREACH(Link const &link, chain)
					count += link.used();
				return count;
			}

		private:
			Link &AddLink(size_t size)
			{
				chain.push_back(Link(alloc, size));
				Link &link = chain.back();
				link.Construct();
				std::make_heap(chain.begin(), chain.end());
				return link;
			}
		};


	} // namespace monotonic

} // namespace boost

#endif // BOOST_MONOTONIC_STORAGE_H

//EOF
