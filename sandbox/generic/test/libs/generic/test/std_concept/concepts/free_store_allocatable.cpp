/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/free_store_allocatable.hpp>

#include <boost/generic/assert.hpp>
#include <cstddef>

using boost::generic::std_concept::FreeStoreAllocatable;

struct free_store_allocatable_type {};

BOOST_GENERIC_ASSERT( FreeStoreAllocatable< int > );
BOOST_GENERIC_ASSERT( FreeStoreAllocatable< float > );
BOOST_GENERIC_ASSERT( FreeStoreAllocatable< free_store_allocatable_type > );

BOOST_GENERIC_ASSERT_NOT( FreeStoreAllocatable< void > );
BOOST_GENERIC_ASSERT_NOT( FreeStoreAllocatable< int& > );
BOOST_GENERIC_ASSERT_NOT( FreeStoreAllocatable< int() > );
BOOST_GENERIC_ASSERT_NOT( FreeStoreAllocatable< int[] > );

struct not_free_store_allocatable_type_no_new
{
  void* operator new( std::size_t size ) = delete;
  void* operator new( std::size_t size, std::nothrow_t );
};

struct not_free_store_allocatable_type_no_new_nothrow
{
  void* operator new( std::size_t size );
  void* operator new( std::size_t size, std::nothrow_t ) = delete;
};

struct not_free_store_allocatable_type_no_delete
{
  void operator delete( void* ) = delete;
  void operator delete( void*, std::nothrow_t );
};

struct not_free_store_allocatable_type_no_nothrow_delete
{
  void operator delete( void* );
  void operator delete( void*, std::nothrow_t ) = delete;
};

BOOST_GENERIC_ASSERT_NOT( FreeStoreAllocatable< not_free_store_allocatable_type_no_new > );
BOOST_GENERIC_ASSERT_NOT( FreeStoreAllocatable< not_free_store_allocatable_type_no_new_nothrow > );
BOOST_GENERIC_ASSERT_NOT( FreeStoreAllocatable< not_free_store_allocatable_type_no_delete > );
BOOST_GENERIC_ASSERT_NOT( FreeStoreAllocatable< not_free_store_allocatable_type_no_nothrow_delete > );

//
//, ( (void*)(this(T) operator new)( (std::size_t) size ) )
//, ( (void)(this(T) operator delete)( (void*) ) )
//, ( (void*)(this(T) operator new_array)( (std::size_t) size ), {
//      return T::operator new(size);
//    }
//  )
//, ( (void)(this(T) operator delete_array)( (void*) ptr ), {
//      return T::operator delete(ptr);
//    }
//  )
//, ( (void*)(this(T) operator new)( (std::size_t) size, (const std::nothrow_t&) ), {
//      try {
//        return T::operator new(size);
//      } catch(...) {
//        return 0;
//      }
//    }
//  )
//, ( (void*)(this(T) operator new_array)( (std::size_t) size, (const std::nothrow_t&) ), {
//      try {
//        return T::operator new[](size);
//      } catch(...) {
//        return 0;
//      }
//    }
//  )
//, ( (void)(this(T) operator delete)( (void*) ptr, (const std::nothrow_t&) ), {
//      T::operator delete(ptr);
//    }
//  )
//, ( (void)(this(T) operator delete_array)( (void*) ptr, (const std::nothrow_t&) ), {
//      T::operator delete[](ptr);
//    }
//  )
