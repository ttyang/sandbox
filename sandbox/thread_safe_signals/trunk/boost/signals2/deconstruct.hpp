#ifndef BOOST_SIGNALS2_DECONSTRUCT_HPP
#define BOOST_SIGNALS2_DECONSTRUCT_HPP

//  deconstruct.hpp
//
// A factory function for creating a shared_ptr which creates
// an object and its owning shared_ptr with one allocation, similar
// to make_shared<T>().  It also supports postconstructors
// and predestructors through unqualified calls of adl_postconstruct() and
// adl_predestruct, relying on argument-dependent
// lookup to find the appropriate postconstructor or predestructor.
// Passing arguments to postconstructors is also supported.
//
//  based on make_shared.hpp and make_shared_access patch from Michael Marcin
//
//  Copyright (c) 2007, 2008 Peter Dimov
//  Copyright (c) 2008 Michael Marcin
//  Copyright (c) 2009 Frank Mori Hess
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org
//  for more information

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2/deconstruct_ptr.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/type_with_alignment.hpp>
#include <cstddef>
#include <new>

namespace boost
{
  template<typename T> class enable_shared_from_this;

  // fallback implementations of sp_accept_owner for older boost releases that don't support sp_accept_owner
  template< class Y >
    void sp_accept_owner( shared_ptr<Y> * ptr, ... )
  {
  }
  template< class T, class Y >
    void sp_accept_owner( shared_ptr<Y> * ptr, enable_shared_from_this<T> const * pe, ... /*pd*/ )
  {
    pe->_internal_weak_this = *ptr;
  }

namespace signals2
{

namespace detail
{
  template< class T > T forward( T t )
  {
      return t;
  }
  inline void adl_predestruct(...) {}
} // namespace detail

template<typename T>
    class postconstructor_invoker
{
public:
    operator const shared_ptr<T> & () const
    {
        return postconstruct();
    }
    const shared_ptr<T>& postconstruct() const
    {
        adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()));
        return _sp;
    }
#if defined( BOOST_HAS_VARIADIC_TMPL ) && defined( BOOST_HAS_RVALUE_REFS )
    template<class T, class... Args>
      const shared_ptr<T>& postconstruct(Args && ... args)
    {
      adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
        detail::forward<Args>(args)...);
    }
#else
    template<typename A1>
      const shared_ptr<T>& postconstruct(const A1 &a1) const
    {
        adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
          a1);
        return _sp;
    }
    template<typename A1, typename A2>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2) const
    {
        adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
          a1, a2);
        return _sp;
    }
    template<typename A1, typename A2, typename A3>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3) const
    {
        adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
          a1, a2, a3);
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) const
    {
        adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
          a1, a2, a3, a4);
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4, typename A5>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5) const
    {
        adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
          a1, a2, a3, a4, a5);
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5,
      const A6 &a6) const
    {
        adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
          a1, a2, a3, a4, a5, a6);
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6, typename A7>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5,
      const A6 &a6, const A7 &a7) const
    {
        adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
          a1, a2, a3, a4, a5, a6, a7);
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6, typename A7, typename A8>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5,
      const A6 &a6, const A7 &a7, const A8 &a8) const
    {
        adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
          a1, a2, a3, a4, a5, a6, a7, a8);
        return _sp;
    }
    template<typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6, typename A7, typename A8, typename A9>
      const shared_ptr<T>& postconstruct(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5,
      const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9) const
    {
        adl_postconstruct(_sp, const_cast<typename boost::remove_const<T>::type *>(_sp.get()),
          a1, a2, a3, a4, a5, a6, a7, a8, a9);
        return _sp;
    }
#endif // else defined( BOOST_HAS_VARIADIC_TMPL ) && defined( BOOST_HAS_RVALUE_REFS )
private:
    friend class deconstruct_access;
    postconstructor_invoker(const shared_ptr<T> & sp):
        _sp(sp)
    {}
    shared_ptr<T> _sp;
};

namespace detail
{

template< std::size_t N, std::size_t A > struct sp_aligned_storage
{
    union type
    {
        char data_[ N ];
        typename boost::type_with_alignment< A >::type align_;
    };
};

template< class T > class deconstruct_deleter
{
private:

    typedef typename sp_aligned_storage< sizeof( T ), ::boost::alignment_of< T >::value >::type storage_type;

    bool initialized_;
    storage_type storage_;

private:

    void destroy()
    {
        if( initialized_ )
        {
            T* p = reinterpret_cast< T* >( storage_.data_ );
            using boost::signals2::detail::adl_predestruct;
            adl_predestruct(const_cast<typename boost::remove_const<T>::type *>(p));
            p->~T();
            initialized_ = false;
        }
    }

public:

    deconstruct_deleter(): initialized_( false )
    {
    }

    // this copy constructor is an optimization: we don't need to copy the storage_ member,
    // and shouldn't be copying anyways after initialized_ becomes true
    deconstruct_deleter(const deconstruct_deleter &): initialized_( false )
    {
    }

    ~deconstruct_deleter()
    {
        destroy();
    }

    void operator()( T * )
    {
        destroy();
    }

    void * address()
    {
        return storage_.data_;
    }

    void set_initialized()
    {
        initialized_ = true;
    }
};

class deconstruct_access
{
public:

    template< class T >
    static postconstructor_invoker<T> deconstruct()
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T();
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;

    }

#if defined( BOOST_HAS_VARIADIC_TMPL ) && defined( BOOST_HAS_RVALUE_REFS )

    // Variadic templates, rvalue reference

    template< class T, class... Args >
    static postconstructor_invoker<T> deconstruct( Args && ... args )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( detail::forward<Args>( args )... );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;
    }

#else

    template< class T, class A1 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;
    }

    template< class T, class A1, class A2 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;
    }

    template< class T, class A1, class A2, class A3 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4, class A5 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4, a5 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4, class A5, class A6 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4, a5, a6 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4, a5, a6, a7 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4, a5, a6, a7, a8 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;
    }

    template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9 >
    static postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8, A9 const & a9 )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( a1, a2, a3, a4, a5, a6, a7, a8, a9 );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        sp_accept_owner(&retval, retval.get(), pd);
        return retval;
    }

#endif
};
}  // namespace detail

// Zero-argument versions
//
// Used even when variadic templates are available because of the new T() vs new T issue

template< class T > postconstructor_invoker<T> deconstruct()
{
	return detail::deconstruct_access::deconstruct<T>();
}

#if defined( BOOST_HAS_VARIADIC_TMPL ) && defined( BOOST_HAS_RVALUE_REFS )

// Variadic templates, rvalue reference

template< class T, class... Args > postconstructor_invoker< T > deconstruct( Args && ... args )
{
    return detail::deconstruct_access::deconstruct( detail::forward<Args>( args )... );
}

#else

// C++03 version

template< class T, class A1 >
postconstructor_invoker<T> deconstruct( A1 const & a1 )
{
	return detail::deconstruct_access::deconstruct<T>(a1);
}

template< class T, class A1, class A2 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2 )
{
   return detail::deconstruct_access::deconstruct<T>(a1,a2);
}

template< class T, class A1, class A2, class A3 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3 )
{
	return detail::deconstruct_access::deconstruct<T>(a1,a2,a3);
}

template< class T, class A1, class A2, class A3, class A4 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4 )
{
    return detail::deconstruct_access::deconstruct<T>(a1,a2,a3,a4);
}

template< class T, class A1, class A2, class A3, class A4, class A5 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5 )
{
    return detail::deconstruct_access::deconstruct<T>(a1,a2,a3,a4,a5);
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6 )
{
    return detail::deconstruct_access::deconstruct<T>(a1,a2,a3,a4,a5,a6);
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7 )
{
    return detail::deconstruct_access::deconstruct<T>(a1,a2,a3,a4,a5,a6,a7);
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8 )
{
    return detail::deconstruct_access::deconstruct<T>(a1,a2,a3,a4,a5,a6,a7,a8);
}

template< class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9 >
postconstructor_invoker<T> deconstruct( A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8, A9 const & a9 )
{
    return detail::deconstruct_access::deconstruct<T>(a1,a2,a3,a4,a5,a6,a7,a8,a9);
}

using detail::deconstruct_access;

#endif

} // namespace signals2
} // namespace boost

#endif // #ifndef BOOST_SIGNALS2_DECONSTRUCT_HPP
