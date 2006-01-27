//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Shmem of boost/detail/shared_count.hpp
//
// (C) Copyright Peter Dimov and Multi Media Ltd. 2001, 2002, 2003
// (C) Copyright Peter Dimov 2004-2005
// (C) Copyright Ion Gazta�aga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/shmem for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SHMEM_DETAIL_SHARED_COUNT_HPP_INCLUDED
#define BOOST_SHMEM_DETAIL_SHARED_COUNT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/checked_delete.hpp>
#include <boost/throw_exception.hpp>
#include <boost/shmem/smart_ptr/detail/bad_weak_ptr.hpp>
#include <boost/shmem/smart_ptr/detail/sp_counted_impl.hpp>
#include <boost/shmem/detail/utilities.hpp>
#include <functional>

#include <functional>       // std::less

namespace boost {
namespace shmem {
namespace detail{

template<class T, class A, class D>
class weak_count;

template<class T, class A, class D>
class shared_count
{
   private:
   typedef sp_counted_impl_pd<A, D>             counted_impl;
   typedef typename detail::pointer_to_other
      <typename A::pointer, counted_impl>::type counted_impl_ptr;
   typedef typename A::template rebind
      <counted_impl>::other                     counted_impl_allocator;
   typedef typename detail::pointer_to_other
            <typename A::pointer, const D>::type   const_deleter_pointer;
   typedef typename detail::pointer_to_other
            <typename A::pointer, const A>::type   const_allocator_pointer;

   public:
   typedef typename detail::pointer_to_other
      <typename A::pointer, T>::type            pointer;

   private:
   pointer           m_px;
   counted_impl_ptr  m_pi;

   template <class T2, class A2, class D2>
   friend class weak_count;

   template <class T2, class A2, class D2>
   friend class shared_count;

   public:

   shared_count()
      :  m_px(0), m_pi(0) // nothrow
   {}

   shared_count(const pointer &p, const A &a, D d)
      :  m_px(p), m_pi(0)
   {
      try{
         if(p){
            counted_impl_allocator alloc(a);
            m_pi = alloc.allocate(1);
            //Anti-exception deallocator
            scoped_ptr<counted_impl, 
                     scoped_deallocator<counted_impl_allocator> >
                        deallocator(m_pi, alloc);
            //It's more correct to use A::construct but
            //this needs copy constructor and we don't like it
            new(detail::get_pointer(m_pi))counted_impl(a, d);
            deallocator.release();
         }
      }
      catch (...){
         d(p); // delete p
         throw;
      }
   }

   ~shared_count() // nothrow
   {  
      if( m_pi != 0 ) 
         m_pi->release(m_px);
   }

   shared_count(shared_count const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   { if( m_pi != 0 ) m_pi->add_ref_copy(); }

   //this is a test
   template<class Y>
   explicit shared_count(shared_count<Y, A, D> const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if( m_pi != 0 ) m_pi->add_ref_copy();  }

   //this is a test
   template<class Y>
   explicit shared_count(const pointer & ptr, shared_count<Y, A, D> const & r)
      :  m_px(ptr), m_pi(r.m_pi) // nothrow
   {  if( m_pi != 0 ) m_pi->add_ref_copy();  }

/*
   explicit shared_count(weak_count<Y, A, D> const & r)
      // throws bad_weak_ptr when r.use_count() == 0
      : m_pi( r.m_pi )
   {
      if( m_pi == 0 || !m_pi->add_ref_lock() ){
         boost::throw_exception( boost::shmem::bad_weak_ptr() );
      }
   }
*/
   template<class Y>
   explicit shared_count(weak_count<Y, A, D> const & r)
      // throws bad_weak_ptr when r.use_count() == 0
      : m_px(r.m_px), m_pi( r.m_pi )
   {
      if( m_pi == 0 || !m_pi->add_ref_lock() ){
         boost::throw_exception( boost::shmem::bad_weak_ptr() );
      }
   }

   const pointer &get_pointer() const
   {  return m_px;   }

   pointer &get_pointer()
   {  return m_px;   }

   shared_count & operator= (shared_count const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if( tmp != m_pi ){
         if(tmp != 0)   tmp->add_ref_copy();
         if(m_pi != 0)  m_pi->release(m_px);
         m_pi = tmp;
      }
      return *this;
   }

   template<class Y>
   shared_count & operator= (shared_count<Y, A, D> const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if( tmp != m_pi ){
         if(tmp != 0)   tmp->add_ref_copy();
         if(m_pi != 0)  m_pi->release(m_px);
         m_pi = tmp;
      }
      return *this;
   }

   void swap(shared_count & r) // nothrow
   {  detail::swap(m_px, r.m_px);   detail::swap(m_pi, r.m_pi);   }

   long use_count() const // nothrow
   {  return m_pi != 0? m_pi->use_count(): 0;  }

   bool unique() const // nothrow
   {  return use_count() == 1;   }

   const_deleter_pointer get_deleter() const
   {  return m_pi ? m_pi->get_deleter() : 0; }

   const_allocator_pointer get_allocator() const
   {  return m_pi ? m_pi->get_allocator() : 0; }

   template<class T2, class A2, class D2>
   bool internal_equal (shared_count<T2, A2, D2> const & other) const
   {  return this->m_pi == other.m_pi;   }

   template<class T2, class A2, class D2>
   bool internal_less  (shared_count<T2, A2, D2> const & other) const
   {  return std::less<counted_impl_ptr>()(this->m_pi, other.m_pi);   }
};

template<class T, class A, class D, class T2, class A2, class D2> inline
bool operator==(shared_count<T, A, D> const & a, shared_count<T2, A2, D2> const & b)
{  return a.internal_equal(b);  }

template<class T, class A, class D, class T2, class A2, class D2> inline
bool operator<(shared_count<T, A, D> const & a, shared_count<T2, A2, D2> const & b)
{  return a.internal_less(b);   }


template<class T, class A, class D>
class weak_count
{
   private:

   typedef sp_counted_impl_pd<A, D>             counted_impl;
   typedef typename detail::pointer_to_other
      <typename A::pointer, counted_impl>::type counted_impl_ptr;

   public:
   typedef typename detail::pointer_to_other
      <typename A::pointer, T>::type            pointer;

   private:
   pointer           m_px;
   counted_impl_ptr  m_pi;

   template <class T2, class A2, class D2>
   friend class weak_count;

   template <class T2, class A2, class D2>
   friend class shared_count;

   public:

   weak_count(): m_px(0), m_pi(0) // nothrow
   {}

   template <class Y>
   explicit weak_count(shared_count<Y, A, D> const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if(m_pi != 0) m_pi->weak_add_ref(); }

   weak_count(weak_count const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if(m_pi != 0) m_pi->weak_add_ref(); }

   template<class Y>
   weak_count(weak_count<Y, A, D> const & r)
      : m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if(m_pi != 0) m_pi->weak_add_ref(); }

   ~weak_count() // nothrow
   {  if(m_pi != 0) m_pi->weak_release(); }

   template<class Y>
   weak_count & operator= (shared_count<Y, A, D> const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if(tmp != 0)   tmp->weak_add_ref();
      if(m_pi != 0)  m_pi->weak_release();
      m_pi = tmp;
      return *this;
   }

   weak_count & operator= (weak_count const & r) // nothrow
   {
      counted_impl_ptr tmp = r.m_pi;
      if(tmp != 0) tmp->weak_add_ref();
      if(m_pi != 0) m_pi->weak_release();
      m_pi = tmp;
      return *this;
   }

   void set_pointer(const pointer &ptr)
   {  m_px = ptr; }

   template<class Y>
   weak_count & operator= (weak_count<Y, A, D> const& r) // nothrow
   {
      counted_impl_ptr tmp = r.m_pi;
      if(tmp != 0) tmp->weak_add_ref();
      if(m_pi != 0) m_pi->weak_release();
      m_pi = tmp;
      return *this;
   }

   void swap(weak_count & r) // nothrow
   {  detail::swap(m_px, r.m_px);  detail::swap(m_pi, r.m_pi);   }

   long use_count() const // nothrow
   {  return m_pi != 0? m_pi->use_count() : 0;   }

   template<class T2, class A2, class D2>
   bool internal_equal (weak_count<T2, A2, D2> const & other) const
   {  return this->m_pi == other.m_pi;   }

   template<class T2, class A2, class D2>
   bool internal_less (weak_count<T2, A2, D2> const & other) const
   {  return std::less<counted_impl_ptr>()(this->m_pi, other.m_pi);   }
};

template<class T, class A, class D, class T2, class A2, class D2> inline
bool operator==(weak_count<T, A, D> const & a, weak_count<T2, A2, D2> const & b)
{  return a.internal_equal(b);  }

template<class T, class A, class D, class T2, class A2, class D2> inline
bool operator<(weak_count<T, A, D> const & a, weak_count<T2, A2, D2> const & b)
{  return a.internal_less(b);   }

} // namespace detail
} // namespace shmem
} // namespace boost

#endif  // #ifndef BOOST_SHMEM_DETAIL_SHARED_COUNT_HPP_INCLUDED
