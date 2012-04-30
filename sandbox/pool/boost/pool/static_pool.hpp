// Copyright (C) 2012 Étienne Dupuis
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_STATIC_POOL_HPP
#define BOOST_STATIC_POOL_HPP
/*!
\file
\brief  Provides a template type boost::static_pool<T, UserAllocator>
that can be used for fast and efficient memory allocation of objects of type T.
It also provides automatic destruction of non-deallocated objects.
*/

#include <boost/pool/poolfwd.hpp>

// boost::pool
#include <boost/pool/pool.hpp>

namespace boost
{


// DOCUMENTATION TO BE INSERTED

template<typename UserAllocator>
class static_pool: protected pool<UserAllocator>
{
  public:  // Overridden functions
    explicit static_pool(const size_type nrequested_size, const size_t nrequested_items)
		:
		pool<UserAllocator>(nrequested_size, nrequested_items)
    { 
			free(pool<UserAllocator>::malloc());
		}

    void * malloc BOOST_PREVENT_MACRO_SUBSTITUTION()
		{ 
			return store().empty() ? NULL : store().malloc();
		}

		void * ordered_malloc()
		{
			return store().empty() ? NULL : store().malloc();
		}

		void * ordered_malloc(size_type n)
		{
			const size_type partition_size = alloc_size();
			const size_type total_req_size = n * requested_size;
			const size_type num_chunks = total_req_size / partition_size +
				((total_req_size % partition_size) ? true : false);

			return store().malloc_n(num_chunks, partition_size);
		}

  public:  // Inherited functions
		void free BOOST_PREVENT_MACRO_SUBSTITUTION(void * const chunk)
		{ 
			return pool<UserAllocator>::free(chunk);
		}

		void ordered_free(void * const chunk)
		{
			return pool<UserAllocator>::ordered_free(chunk);
		}

		void free BOOST_PREVENT_MACRO_SUBSTITUTION(void * const chunks, const size_type n)
    {
			return pool<UserAllocator>::free(chunks, n);
    }

    void ordered_free(void * const chunks, const size_type n)
		{
			return pool<UserAllocator>::ordered_free(chunks, n);
		}

    size_type get_requested_size() const
    { 
			return pool<UserAllocator>::get_requestedSize();
		}
       
    bool is_from(void * const chunk) const
    { 
			return pool<UserAllocator>::is_from(chunk);
		}
};

} // namespace boost

#endif
