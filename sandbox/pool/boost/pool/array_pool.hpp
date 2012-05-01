// Copyright (C) 2012 Étienne Dupuis
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ARRAY_POOL_HPP
#define BOOST_ARRAY_POOL_HPP
/*!
\file
\brief  Provides a template type boost::static_pool<T, UserAllocator>
that can be used for fast and efficient memory allocation of objects of type T.
It also provides automatic destruction of non-deallocated objects.
*/

#include <boost/pool/poolfwd.hpp>

// boost::static_pool
#include <boost/pool/static_pool.hpp>

namespace boost
{

// HELPER CLASS

struct array_pool_allocator
{
  typedef std::size_t size_type; //!< An unsigned integral type that can represent the size of the largest object to be allocated.
  typedef std::ptrdiff_t difference_type; //!< A signed integral type that can represent the difference of any two pointers.

  static char * malloc BOOST_PREVENT_MACRO_SUBSTITUTION(const size_type /*bytes*/)
  { //! Returns NULL as it should not be called
    return NULL;
  }

  static void free BOOST_PREVENT_MACRO_SUBSTITUTION(char * const /*block*/)
  { //! Ignore any given pointer
  }
};


// DOCUMENTATION TO BE INSERTED

template<size_t RequestedSize, size_t PoolSize>
class array_pool: public static_pool<array_pool_allocator>
{
  public :
    typedef typename static_pool<array_pool_allocator>::user_allocator user_allocator;
    typedef typename static_pool<array_pool_allocator>::size_type size_type;
    typedef typename static_pool<array_pool_allocator>::difference_type difference_type;

  public:
    explicit array_pool(const size_type /*nrequested_size*/ = RequestedSize, const size_type /*nrequested_items*/ = PoolSize)
    :
    static_pool<array_pool_allocator>(RequestedSize, PoolSize)
    { 
      const details::PODptr<size_type> node(memory, sizeof(memory));

      store().add_block(node.begin(), node.element_size(), s_alloc_size);
      node.next(list);
      list = node;
    }

  private :
    BOOST_STATIC_CONSTANT(size_type, min_alloc_size =
      (::boost::math::static_lcm<sizeof(void *), sizeof(size_type)>::value));
    BOOST_STATIC_CONSTANT(size_type, max_alloc_size =
      (::boost::static_unsigned_max<RequestedSize, min_alloc_size>::value));
    BOOST_STATIC_CONSTANT(size_type, min_align =
      (::boost::math::static_lcm<boost::alignment_of<void *>::value, boost::alignment_of<size_type>::value>::value));
    BOOST_STATIC_CONSTANT(size_type, s_alloc_size =
      ((max_alloc_size % min_align) ? max_alloc_size + min_align - max_alloc_size % min_align : max_alloc_size));
    BOOST_STATIC_CONSTANT(size_type, s_pod_size =
      (PoolSize * s_alloc_size + math::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type)));

    char memory[s_pod_size];
};

} // namespace boost

#endif
