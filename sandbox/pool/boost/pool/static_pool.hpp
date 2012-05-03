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
  public :
    typedef typename pool<UserAllocator>::user_allocator user_allocator;
    typedef typename UserAllocator::size_type size_type;
    typedef typename UserAllocator::difference_type difference_type;

  public:  // Overridden functions
    explicit static_pool(const size_type nrequested_size, const size_type nrequested_items)
    :
    pool<UserAllocator>(nrequested_size, nrequested_items)
    { 
      free BOOST_PREVENT_MACRO_SUBSTITUTION(pool<UserAllocator>::malloc BOOST_PREVENT_MACRO_SUBSTITUTION());
    }

    void * malloc BOOST_PREVENT_MACRO_SUBSTITUTION()
    { 
      return this->store().empty() ? NULL : this->store().malloc BOOST_PREVENT_MACRO_SUBSTITUTION();
    }

    void * ordered_malloc()
    {
      return this->store().empty() ? NULL : this->store().malloc BOOST_PREVENT_MACRO_SUBSTITUTION();
    }

    void * ordered_malloc(size_type n)
    {
      const size_type partition_size = this->alloc_size();
      const size_type total_req_size = n * this->requested_size;
      const size_type num_chunks = total_req_size / partition_size +
        ((total_req_size % partition_size) ? true : false);

      return this->store().malloc_n(num_chunks, partition_size);
    }

  public:  // Inherited functions
    void free BOOST_PREVENT_MACRO_SUBSTITUTION(void * const chunk)
    { 
      return pool<UserAllocator>::free BOOST_PREVENT_MACRO_SUBSTITUTION(chunk);
    }

    void ordered_free(void * const chunk)
    {
      return pool<UserAllocator>::ordered_free(chunk);
    }

    void free BOOST_PREVENT_MACRO_SUBSTITUTION(void * const chunks, const size_type n)
    {
      return pool<UserAllocator>::free BOOST_PREVENT_MACRO_SUBSTITUTION(chunks, n);
    }

    void ordered_free(void * const chunks, const size_type n)
    {
      return pool<UserAllocator>::ordered_free(chunks, n);
    }

    size_type get_requested_size() const
    { 
      return pool<UserAllocator>::get_requested_size();
    }
       
    bool is_from(void * const chunk) const
    { 
      return pool<UserAllocator>::is_from(chunk);
    }
};

} // namespace boost

#endif
