// Copyright (C) 2000, 2001 Stephen Cleary
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_OBJECT_POOL_HPP
#define BOOST_OBJECT_POOL_HPP
/*!
\file
\brief  Provides a template type boost::object_pool<T, UserAllocator>
that can be used for fast and efficient memory allocation of objects of type T.
It also provides automatic destruction of non-deallocated objects.
*/

#include <boost/pool/poolfwd.hpp>

// boost::pool
#include <boost/pool/pool.hpp>
// boost::static_pool
#include <boost/pool/static_pool.hpp>
// boost::array_pool
#include <boost/pool/array_pool.hpp>

// The following code will be put into Boost.Config in a later revision
#if defined(BOOST_MSVC) || defined(__KCC)
# define BOOST_NO_TEMPLATE_CV_REF_OVERLOADS
#endif

// The following code might be put into some Boost.Config header in a later revision
#ifdef __BORLANDC__
# pragma option push -w-inl
#endif

// There are a few places in this file where the expression "this->m" is used.
// This expression is used to force instantiation-time name lookup, which I am
//   informed is required for strict Standard compliance.  It's only necessary
//   if "m" is a member of a base class that is dependent on a template
//   parameter.
// Thanks to Jens Maurer for pointing this out!

namespace boost {

/*! \brief A template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

\details

<b>T</b> The type of object to allocate/deallocate.
T must have a non-throwing destructor.

<b>Pool</b>
Defines the underlying Pool will use to manage memory from the system.
This is intended to be either a Pool or a StaticPool.

Class object_pool_base is a template base class which is used
to define classes object_pool and static_object_pool.
*/

template <typename T, typename Pool>
class object_pool_base: protected Pool
{ //!
  public:
    typedef T element_type; //!< ElementType
    typedef typename Pool::user_allocator user_allocator; //!<
    typedef typename Pool::size_type size_type; //!<   pool<UserAllocator>::size_type
    typedef typename Pool::difference_type difference_type; //!< pool<UserAllocator>::difference_type

  private:
    size_type allocated;

  protected:
    //! \return The underlying boost:: \ref pool storage used by *this.
    Pool & store()
    { 
      return *this;
    }
    //! \return The underlying boost:: \ref pool storage used by *this.
    const Pool & store() const
    { 
      return *this;
    }

    // for the sake of code readability :)
    static void * & nextof(void * const ptr)
    { //! \returns The next memory block after ptr (for the sake of code readability :)
      return *(static_cast<void **>(ptr));
    }

  public:
    explicit object_pool_base(const size_type arg_requested_objects)
    :
    Pool(sizeof(T), arg_requested_objects)
    { //! Constructs a new (empty by default) ObjectPoolBase.
      //! \param arg_requested_objects Number of memory chunks to allocate at initialization.
      allocated = 0;
    }

    ~object_pool_base();

    // Returns 0 if out-of-memory.
    element_type * malloc BOOST_PREVENT_MACRO_SUBSTITUTION()
    { //! Allocates memory that can hold one object of type ElementType.
      //!
      //! If out of memory, returns 0. 
      //!
      //! Amortized O(1).
      element_type *element = static_cast<element_type *>(store().malloc());
      if (element)
        allocated += 1;

      return element;
    }

    void free BOOST_PREVENT_MACRO_SUBSTITUTION(element_type * const chunk)
    { //! De-Allocates memory that holds a chunk of type ElementType.
      //!
      //!  Note that p may not be 0.\n
      //!
      //! Note that the destructor for p is not called. O(N).
      store().free(chunk);
      if (chunk)
        allocated -= 1;
    }

    bool is_from(element_type * const chunk) const
    { /*! \returns true  if chunk was allocated from *this or
      may be returned as the result of a future allocation from *this.

      Returns false if chunk was allocated from some other pool or
      may be returned as the result of a future allocation from some other pool.

      Otherwise, the return value is meaningless.

      \note This function may NOT be used to reliably test random pointer values!
    */
      return store().is_from(chunk);
    }

    element_type * construct()
    { //! \returns A pointer to an object of type T, allocated in memory from the underlying pool
      //! and default constructed.  The returned objected can be freed by a call to \ref destroy.
      //! Otherwise the returned object will be automatically destroyed when *this is destroyed.
      element_type * const ret = (malloc)();
      if (ret == 0)
        return ret;
      try { new (ret) element_type(); }
      catch (...) { (free)(ret); throw; }
      return ret;
    }


#if defined(BOOST_DOXYGEN)
    template <class Arg1, ... class ArgN>
    element_type * construct(Arg1&, ... ArgN&)
    {
       //! \returns A pointer to an object of type T, allocated in memory from the underlying pool
       //! and constructed from arguments Arg1 to ArgN.  The returned objected can be freed by a call to \ref destroy.
       //! Otherwise the returned object will be automatically destroyed when *this is destroyed.
       //!
       //! \note Since the number and type of arguments to this function is totally arbitrary, a simple system has been 
       //! set up to automatically generate template construct functions. This system is based on the macro preprocessor 
       //! m4, which is standard on UNIX systems and also available for Win32 systems.\n\n
       //! detail/pool_construct.m4, when run with m4, will create the file detail/pool_construct.ipp, which only defines 
       //! the construct functions for the proper number of arguments. The number of arguments may be passed into the 
       //! file as an m4 macro, NumberOfArguments; if not provided, it will default to 3.\n\n
       //! For each different number of arguments (1 to NumberOfArguments), a template function is generated. There 
       //! are the same number of template parameters as there are arguments, and each argument's type is a reference 
       //! to that (possibly cv-qualified) template argument. Each possible permutation of the cv-qualifications is also generated.\n\n
       //! Because each permutation is generated for each possible number of arguments, the included file size grows 
       //! exponentially in terms of the number of constructor arguments, not linearly. For the sake of rational 
       //! compile times, only use as many arguments as you need.\n\n
       //! detail/pool_construct.bat and detail/pool_construct.sh are also provided to call m4, defining NumberOfArguments 
       //! to be their command-line parameter. See these files for more details.
    }
#else
// Include automatically-generated file for family of template construct() functions.
// Copy .inc renamed .ipp to conform to Doxygen include filename expectations, PAB 12 Jan 11.
// But still get Doxygen warning:
// I:/boost-sandbox/guild/pool/boost/pool/object_pool.hpp:82:
// Warning: include file boost/pool/detail/pool_construct.ipp
// not found, perhaps you forgot to add its directory to INCLUDE_PATH?
// But the file IS found and referenced OK, but cannot view code.
// This seems because not at the head of the file
// But if moved this up, Doxygen is happy, but of course it won't compile,
// because the many constructors *must* go here.

#ifndef BOOST_NO_TEMPLATE_CV_REF_OVERLOADS
#   include <boost/pool/detail/pool_construct.ipp>
#else
#   include <boost/pool/detail/pool_construct_simple.ipp>
#endif
#endif
    void destroy(element_type * const chunk)
    { //! Destroys an object allocated with \ref construct. 
      //!
      //! Equivalent to:
      //!
      //! p->~ElementType(); this->free(p);
      //!
      //! \pre p must have been previously allocated from *this via a call to \ref construct.
      if (chunk)
      {
        chunk->~T();
        (free)(chunk);
      }
    }
};

template <typename T, typename Pool>
object_pool_base<T, Pool>::~object_pool_base()
{
  // handle trivial case of invalid list.
  if (!this->list.valid())
    return;

  // do not do useless work
  if (!allocated)
    return;

  // sort store
  store().order();

  details::PODptr<size_type> iter = this->list;
  details::PODptr<size_type> next = iter;

  // Start 'freed_iter' at beginning of free list
  void * freed_iter = this->first;

  const size_type partition_size = this->alloc_size();

  do
  {
    // increment next
    next = next.next();

    // delete all contained objects that aren't freed.

    // Iterate 'i' through all chunks in the memory block.
    for (char * i = iter.begin(); i != iter.end(); i += partition_size)
    {
      // If this chunk is free,
      if (i == freed_iter)
      {
        // Increment freed_iter to point to next in free list.
        freed_iter = nextof(freed_iter);

        // Continue searching chunks in the memory block.
        continue;
      }

      // This chunk is not free (allocated), so call its destructor,
      static_cast<T *>(static_cast<void *>(i))->~T();
      // and continue searching chunks in the memory block.
    }

    // free storage.
    (Pool::free)(iter.begin());

    // increment iter.
    iter = next;
  } while (iter.valid());

  // Make the block list empty so that the inherited destructor doesn't try to
  // free it again.
  this->list.invalidate();
}

/*! \brief A template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

\details

<b>T</b> The type of object to allocate/deallocate.
T must have a non-throwing destructor.

<b>UserAllocator</b>
Defines the allocator that the underlying Pool will use to allocate memory from the system.
See <a href="boost_pool/pool/pooling.html#boost_pool.pool.pooling.user_allocator">User Allocators</a> for details.

Class object_pool is a template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

When the object pool is destroyed, then the destructor for type T
is called for each allocated T that has not yet been deallocated. O(N).

Whenever an object of type ObjectPool needs memory from the system,
it will request it from its UserAllocator template parameter.
The amount requested is determined using a doubling algorithm;
that is, each time more system memory is allocated,
the amount of system memory requested is doubled.
Users may control the doubling algorithm by the parameters passed
to the object_pool's constructor.
*/

template<typename T, typename UserAllocator>
class object_pool : public object_pool_base<T, pool<UserAllocator> >
{
  public:
    typedef typename object_pool_base<T, pool<UserAllocator> >::element_type element_type; //!< ElementType
    typedef typename object_pool_base<T, pool<UserAllocator> >::user_allocator user_allocator; //!<
    typedef typename object_pool_base<T, pool<UserAllocator> >::size_type size_type; //!<   pool<UserAllocator>::size_type
    typedef typename object_pool_base<T, pool<UserAllocator> >::difference_type difference_type; //!< pool<UserAllocator>::difference_type

  public:
    explicit object_pool(const size_type arg_next_size = 32, const size_type arg_max_size = 0)
    :
    object_pool_base<T, pool<UserAllocator> >(arg_next_size)
    { //! Constructs a new (empty by default) ObjectPool.
      //! \param arg_next_size Number of chunks to request from the system the next time that object needs to allocate system memory (default 32).
      //! \pre next_size != 0.
      //! \param arg_max_size Maximum number of chunks to ever request from the system - this puts a cap on the doubling algorithm
      //! used by the underlying pool.
      set_max_size(arg_max_size);
    }

  public:
    size_type get_next_size() const
    { //! \returns The number of chunks that will be allocated next time we run out of memory.
      return pool<UserAllocator>::get_next_size();
    }

    void set_next_size(const size_type nnext_size)
    { //! Set a new number of chunks to allocate the next time we run out of memory.
      //! \param nnext_size wanted next_size (must not be zero).
      pool<UserAllocator>::set_next_size(nnext_size);
    }

    size_type get_max_size() const
    { //! \returns max_size.
      return pool<UserAllocator>::get_max_size();
    }

    void set_max_size(const size_type nmax_size)
    { //! Set max_size.
      pool<UserAllocator>::set_max_size(nmax_size);
    }

    size_type get_size() const
    {
      return pool<UserAllocator>::get_size();
    }
};

/*! \brief A template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

\details

<b>T</b> The type of object to allocate/deallocate.
T must have a non-throwing destructor.

<b>UserAllocator</b>
Defines the allocator that the underlying StaticPool will use to allocate memory from the system.
See <a href="boost_pool/pool/pooling.html#boost_pool.pool.pooling.user_allocator">User Allocators</a> for details.

Class static_object_pool is a template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

When the object pool is destroyed, then the destructor for type T
is called for each allocated T that has not yet been deallocated. O(N).

The StaticObjectPool allocates all memory needed at initialization.
*/

template<typename T, typename UserAllocator>
class static_object_pool : public object_pool_base<T, static_pool<UserAllocator> >
{
  public:
    typedef typename object_pool_base<T, static_pool<UserAllocator> >::element_type element_type; //!< ElementType
    typedef typename object_pool_base<T, static_pool<UserAllocator> >::user_allocator user_allocator; //!<
    typedef typename object_pool_base<T, static_pool<UserAllocator> >::size_type size_type; //!<   pool<UserAllocator>::size_type
    typedef typename object_pool_base<T, static_pool<UserAllocator> >::difference_type difference_type; //!< pool<UserAllocator>::difference_type

  public:
    explicit static_object_pool(const size_type arg_requested_objects)
    :
    object_pool_base<T, static_pool<UserAllocator> >(arg_requested_objects)
    { //! Constructs a new (empty by default) StaticObjectPool.
      //! \param arg_requested_objects Number of memory chunks to allocate at initialization. 
      //!  It defines the maximum number of objects that can be malloc'ed from this pool.
    }
};

/*! \brief A template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

\details

<b>T</b> The type of object to allocate/deallocate.
T must have a non-throwing destructor.

<b>UserAllocator</b>
Defines the allocator that the underlying StaticPool will use to allocate memory from the system.
See <a href="boost_pool/pool/pooling.html#boost_pool.pool.pooling.user_allocator">User Allocators</a> for details.

Class static_object_pool is a template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

When the object pool is destroyed, then the destructor for type T
is called for each allocated T that has not yet been deallocated. O(N).

The ArrayObjectPool does not allocate any memory as it's size is known at compile time.
*/

template<typename T, size_t PoolSize>
class array_object_pool : public object_pool_base<T, array_pool<sizeof(T), PoolSize> >
{
  public:
    typedef typename object_pool_base<T, array_pool<sizeof(T), PoolSize> >::element_type element_type; //!< ElementType
    typedef typename object_pool_base<T, array_pool<sizeof(T), PoolSize> >::user_allocator user_allocator; //!<
    typedef typename object_pool_base<T, array_pool<sizeof(T), PoolSize> >::size_type size_type; //!<   pool<UserAllocator>::size_type
    typedef typename object_pool_base<T, array_pool<sizeof(T), PoolSize> >::difference_type difference_type; //!< pool<UserAllocator>::difference_type

  public:
    explicit array_object_pool()
    :
    object_pool_base<T, array_pool<sizeof(T), PoolSize> >(PoolSize)
    { //! Constructs a new (empty by default) ArrayObjectPool.
    }
};

} // namespace boost

// The following code might be put into some Boost.Config header in a later revision
#ifdef __BORLANDC__
# pragma option pop
#endif

#endif
