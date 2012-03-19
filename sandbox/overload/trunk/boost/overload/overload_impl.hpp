/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef _BOOST_OVERLOAD_IMPL_HPP_
#define _BOOST_OVERLOAD_IMPL_HPP_

#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/function_traits.hpp>

#include "detail/overload_base.hpp"
#include "detail/trait_by_index.hpp"
#include "detail/trait_by_signature.hpp"
#include "detail/trait_by_functor.hpp"
#include "detail/member_function_form.hpp"
#include "detail/result_type.hpp"

#if defined(BOOST_OVERLOAD_ENABLE_LAMBDA_SUPPORT)
    #include "detail/lambda_result_type_support.hpp"
#endif

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable: 4127) // conditional expression is constant.
#endif

// Workaround for MSVC < 8.0 tested on MSVC 7.1 
#if BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    #include "detail/function_trait.hpp"
#endif


namespace boost{ namespace overloads{

using detail::const_;
using detail::non_const;

template<
    BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig)
>
//template< typename Sig0, typename Sig1 = no_signature, ... >
class overload;

namespace detail {

template<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig)>
class get_function_tag< overloads::overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)> >
{
  public:
    typedef function_obj_tag type;
};

template<
    BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig),
    typename Sig>
struct functor_has_signature< overloads::overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>, Sig, function_obj_tag >
{
    typedef overloads::overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)> overload_type;
    BOOST_STATIC_CONSTANT( bool, value = (has_signature<Sig, overload_type>::value) );
};

template< typename F >
struct is_overload
{
    BOOST_STATIC_CONSTANT( bool, value = false );
};

template< BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig) >
struct is_overload<
    overloads::overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>
>
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

template< typename F, typename Signature >
struct disambiguate
{
    typedef F type;
};

template< BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig),
          typename Signature>
struct disambiguate<
    overloads::overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>,
    Signature>
{
    typedef const BOOST_OVERLOAD_WRAPPED_FUNC<Signature> & type;
};

}  // end namespace detail


///////////////////////////////////////////////////////////////////////////////
// overload class template

template< 
    typename Sig0, 
    BOOST_OVERLOAD_ENUM_SHIFTED_PARAMS_WITH_A_DEFAULT(BOOST_OVERLOAD_LIMIT, typename Sig, detail::no_signature)
>
//template< typename Sig0, typename Sig1 = no_signature, ... >
class overload
    : public detail::overload_base<0,BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>

{
  public:
    ///////////////////////////////////////////////////////////////////////////
    // type traits
    typedef overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)> this_type;
    typedef 
        detail::overload_base<0,BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>
        base_type;

    // wrapped function type
    template <typename Signature>
    struct wrapped_function
    {
        typedef BOOST_OVERLOAD_WRAPPED_FUNC<Signature> type;
    };

    // static const unsigned int extent = overloads::extent<this_type>::value;
    static const unsigned int extent;

    template< unsigned int N >
    struct signature
    {
        typedef typename detail::signature<N, this_type>::type type;
    };

    template< unsigned int N >
    struct function
    {
        typedef typename detail::function< N, this_type >::type type;
    };

    template< typename Sig >
    struct index_of_signature
    {
        BOOST_STATIC_CONSTANT( int, value =
            (static_cast<int>(detail::index_of_signature<Sig, this_type>::value)) );
    };

    template< typename Sig >
    struct has_signature
    {
        BOOST_STATIC_CONSTANT( bool, value =
            (detail::has_signature<Sig, this_type>::value) );
    };

    template< typename F >
    struct shares_any_signature_with
    {
        BOOST_STATIC_CONSTANT( bool, value =
            (detail::have_any_shared_signature<F, this_type>::value) );
    };

    ///////////////////////////////////////////////////////////////////////////
    // ResultOf library support

    template<typename ArgsType, typename Overload>
    friend struct detail::index_of_best_viable_function;

  private:
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    typedef detail::overload_candidate_set<BOOST_OVERLOAD_ENUM_NUM_CALLS_TPL(BOOST_OVERLOAD_LIMIT, typename signature, type)>
            overload_candidate_set;
#else
    template<typename ArgsType>
    struct overload_candidate_set
    {
        BOOST_STATIC_CONSTANT( unsigned int, arity = (boost::function_traits<ArgsType>::arity) );
        typedef detail::overload_candidate_set<arity, BOOST_OVERLOAD_ENUM_NUM_CALLS_TPL(BOOST_OVERLOAD_LIMIT, typename signature, type)>
                type;
    };
#endif

  public:
    template<typename CallType>
    struct result : public detail::result<CallType>
    {};

    ///////////////////////////////////////////////////////////////////////////
    // Lambda library support
#if defined(BOOST_OVERLOAD_ENABLE_LAMBDA_SUPPORT)
    template<typename Args>
    struct sig : public detail::sig<Args>
    {};
#endif

  private:
    ///////////////////////////////////////////////////////////////////////////
    // Workaround for MSVC < 8.0 tested on MSVC 7.1 
    // types used in the declaration of the function call operators
    
#if BOOST_WORKAROUND(BOOST_MSVC, < 1400)  
    typedef
        typename detail::zero_arity_signature<
            BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)
        >::type
        zero_arity_signature_type;

    BOOST_PP_REPEAT(BOOST_OVERLOAD_LIMIT, BOOST_OVERLOAD_REAL_OR_DUMMY_SIG_M, unused)
#endif

  public:
    overload()
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // workaround for MSVC compilers
    // copy constructor and copy assignment operator need to be defined
    // explicitly or we get some kind of 'ambiguos' error;
    // tested with MSVC 7.1, 8.0, 9.0, 10.0
#ifdef BOOST_MSVC
    overload( const this_type & _f )
    {
        copy_impl< detail::extent<this_type>::value - 1 >( _f );
    }

    this_type& operator=( const this_type & _f )
    {
        copy_impl< detail::extent<this_type>::value - 1 >( _f );
        return *this;
    }

  private:
    template<unsigned int N>
    void copy_impl( const this_type & _f )
    {
        get<N>() = _f.get<N>();
        copy_impl<N-1>( _f );
    }

    template<>
    void copy_impl<0>( const this_type & _f )
    {
        get<0>() = _f.get<0>();
    }

  public:
#endif

    ///////////////////////////////////////////////////////////////////////////
    // constructors and methods that supports signature deduction
 
    BOOST_PP_REPEAT_FROM_TO(0, BOOST_OVERLOAD_LIMIT, BOOST_OVERLOAD_CTOR, unused)

    template< typename F >
    this_type& set( F const& _f,
                    typename boost::disable_if<
                        boost::is_pointer<F>
                    >::type* = 0 )
    {
        BOOST_STATIC_ASSERT(( shares_any_signature_with<F>::value ));
        set_impl(_f);
        return *this;
    }

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_OVERLOAD_LIMIT, BOOST_OVERLOAD_SET, unused)

    ///////////////////////////////////////////////////////////////////////////
    // Workaround for MSVC < 8.0 tested on MSVC 7.1 
    // function call operators
 
#if BOOST_WORKAROUND(BOOST_MSVC, < 1400)  
	typename detail::func_trait< zero_arity_signature_type >::result_type
	operator() ()
    {
		return BOOST_OVERLOAD_WRAPPED_FUNC<zero_arity_signature_type>::operator()();
	}

	BOOST_PP_REPEAT_FROM_TO(0, BOOST_OVERLOAD_LIMIT, BOOST_OVERLOAD_FUNC_CALL_OPERATORS, Sig)
#endif

    ///////////////////////////////////////////////////////////////////////////
    // set the passed target for all compatible signatures

    template< typename F >
    this_type& set_for_each_shared_signature( F const& _f,
                                              typename boost::enable_if<
                                                  detail::is_ptr_or_memb_ptr<F>
                                              >::type* = 0 )
    {
	    BOOST_STATIC_ASSERT(( shares_any_signature_with<F>::value ));
        set_impl(_f);
        return *this;
    }

    template< typename F >
    this_type& set_for_each_shared_signature( F const& _f,
                                              typename boost::disable_if<
                                                  detail::is_ptr_or_memb_ptr<F>
                                               >::type* = 0 )
    {
        ///////////////////////////////////////////////////////////////////////
        // Workaround for MSVC 8.0
        // When we have a template function and a *single* explicit overload
        // ( e.g. T foo(T ) and int foo(int ) ) we do not get any compile time
        // error, instead we expect to get a compile time error pointing out
        // that the function is overloaded. What happens is that the template
        // parameter F is tied to the function type of the single explicit
        // overload (e.g. F is equal to int(int ) in our example); pay attention
        // here F results of type 'function' not of type 'pointer to function',
        // so we use the following static assertion for pointing out the problem

#if BOOST_WORKAROUND(BOOST_MSVC, == 1400)
        BOOST_STATIC_ASSERT(( !boost::is_function<F>::value ));
#endif
        BOOST_STATIC_ASSERT(( shares_any_signature_with<F>::value ));
        set_for_each_shared_signature_impl(_f);
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////
    // swap two boost::overloads

    void swap( this_type& _f )
    {
        swap_impl<base_type>(_f, this);
    }

    ///////////////////////////////////////////////////////////////////////////
    // swap two wrapped functions with the same call signature

    template< typename Sig >
    void swap_function( BOOST_OVERLOAD_WRAPPED_FUNC<Sig>& _f )
    {
        typedef typename wrapped_function<Sig>::type function_type;
        function_type::swap(_f);
    }

    ///////////////////////////////////////////////////////////////////////////
    // clear all the callable targets

    void clear_all()
    {
        clear_all_impl<typename this_type::base_type>(this);
    }

    ///////////////////////////////////////////////////////////////////////////
    // return true if all the callable targets are empty

    bool empty_all() const
    {
        return empty_all_impl<typename this_type::base_type>(this);
    }

    ///////////////////////////////////////////////////////////////////////////
    // return true if any the callable target is empty

    bool empty_any() const
    {
        return empty_any_impl<typename this_type::base_type>(this);
    }

    ///////////////////////////////////////////////////////////////////////////
    // return true if no callable target is empty

    bool empty_none() const
    {
        return !empty_any();
    }

    ///////////////////////////////////////////////////////////////////////////
    // return true if the functor if the functor is contained in at least one
    // of the internal function object

    template< typename F >
    bool contains( const F & f ) const
    {
        typedef typename detail::base_by_functor<F, this_type>::type base_type;
        return contains_impl<base_type, F>(this, f);
    }

    ///////////////////////////////////////////////////////////////////////////
    // signature based methods

    template< typename Sig >
    const typename wrapped_function<Sig>::type& get() const
    {
        BOOST_STATIC_ASSERT(( has_signature<Sig>::value ));
        return *this;
    }

    template< typename Sig >
    typename wrapped_function<Sig>::type& get()
    {
        BOOST_STATIC_ASSERT(( has_signature<Sig>::value ));
        return *this;
    }

    BOOST_OVERLOAD_FUNCTOR_ADAPTOR( this_type&, set, typename Sig, Sig, set_by_signature )

    template<typename Sig, typename const_qlf >
    this_type& set( typename detail::memb_func_form<Sig, const_qlf>::type _mf_ptr )
    {
        get<Sig>() = _mf_ptr;
        return *this;
    }

    template< typename Sig >
    bool empty() const
    {
        typedef typename wrapped_function<Sig>::type function_type;
        return function_type::empty();
    }

    template< typename Sig >
    void clear()
    {
        typedef typename wrapped_function<Sig>::type function_type;
        function_type::clear();
    }

    ///////////////////////////////////////////////////////////////////////////
    // index based methods

    template< unsigned int N >
    const typename function<N>::type& get() const
    {
        return *this;
    }

    template< unsigned int N >
    typename function<N>::type& get()
    {
        return *this;
    }

    BOOST_OVERLOAD_FUNCTOR_ADAPTOR( this_type&, set, int N, typename signature<N>::type, set_by_signature )

    template< unsigned int N >
    bool empty() const
    {
        typedef typename function<N>::type function_type;
        return function_type::empty();
    }

    template< unsigned int N >
    void clear()
    {
        typedef typename function<N>::type function_type;
        function_type::clear();
    }

  private:
    ///////////////////////////////////////////////////////////////////////////
    // function set_impl
    // 

    template< typename Sig >
    void set_impl( BOOST_OVERLOAD_WRAPPED_FUNC<Sig> const& _f )
    {
        typedef typename wrapped_function<Sig>::type function_type;
        function_type::operator=(_f);
    }

    template< typename F >
    void set_impl( F const& _f,
                   typename boost::enable_if<
                       detail::is_ptr_or_memb_ptr<F>
                   >::type* = 0 )
    {
        typedef typename detail::base_by_functor<F, this_type>::type
                base_type;

        set_impl<F, base_type>(_f, this);
    }

    template< typename F >
    void set_impl( F const& _f,
                   typename boost::disable_if<
                       detail::is_ptr_or_memb_ptr<F>
                   >::type* = 0 )
    {
        BOOST_STATIC_ASSERT(( detail::number_of_shared_signatures<F, this_type>::value == 1 ));
        typedef typename detail::base_by_functor<F, this_type>::type
                base_type;

        set_impl<F, base_type>(_f, this);
    }

    template< typename F, typename Base >
    void set_impl( F const& _f, Base const* )
    {
        typedef typename Base::signature_type signature_type;
        typedef typename detail::disambiguate<F, signature_type>::type
                cast_type;
        typedef typename wrapped_function<signature_type>::type function_type;

        function_type::operator=( static_cast<cast_type>(_f) );
    }

    // TODO: probably not needed
    template< typename F, typename Base>
    void set_impl( F const& , detail::final_overload_base const* )
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // function set_by_signature
    //

    template< typename Sig, typename F >
    this_type& set_by_signature( F const& _f )
    {
        get<Sig>() = _f;
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////
    // function set_target_for_all_compatible_signatures_impl
    //

    template< typename Sig >
    void set_for_each_shared_signature_impl( BOOST_OVERLOAD_WRAPPED_FUNC<Sig> const& _f )
    {
        typedef typename wrapped_function<Sig>::type function_type;
        function_type::operator=(_f);
    }

    template< typename F >
    void set_for_each_shared_signature_impl(
        F const& _f,
        typename boost::enable_if< shares_any_signature_with<F> >::type* = 0
    )
    {
        typedef typename detail::base_by_functor<F, this_type>::type
                base_type;

        set_for_each_shared_signature_impl<F, base_type>(_f, this);
    }

    template< typename F, typename Base >
    void set_for_each_shared_signature_impl( F const& _f, Base const* )
    {
        typedef typename detail::base_by_functor<F, Base>::type
                base_type;
        typedef typename Base::signature_type signature_type;
        typedef typename detail::disambiguate<F, signature_type>::type
                cast_type;
        typedef typename wrapped_function<signature_type>::type function_type;

        function_type::operator=( static_cast<cast_type>(_f) );
        set_for_each_shared_signature_impl<F, base_type>(_f, this);
    }

    template< typename F, typename Base>
    void set_for_each_shared_signature_impl(
            F const& ,
            detail::final_overload_base const*
    )
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // function clear_all_impl

    template< typename Base >
    void swap_impl(this_type & _f, Base const*)
    {
        typedef typename Base::base_type          base_type;
        typedef typename Base::signature_type     signature_type;
        typedef typename wrapped_function<signature_type>::type function_type;

        function_type::swap( static_cast<function_type &>(_f) );
        swap_impl<base_type>(_f, this);
    }

    template<typename Base>
    void swap_impl(this_type &,
                   detail::final_overload_base const* )
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // function clear_all_impl

    template< typename Base >
    void clear_all_impl(Base const* )
    {
        typedef typename Base::base_type          base_type;
        typedef typename Base::signature_type     signature_type;

        clear<signature_type>();
        clear_all_impl<base_type>(this);
    }

    template<typename Base>
    void clear_all_impl(detail::final_overload_base const* )
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // function empty_all_impl

    template< typename Base >
    bool empty_all_impl(Base const* ) const
    {
        typedef typename Base::base_type          base_type;
        typedef typename Base::signature_type     signature_type;

        return ( empty<signature_type>() && empty_all_impl<base_type>(this) );
    }

    template<typename Base>
    bool empty_all_impl(detail::final_overload_base const* ) const
    {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////
    // function empty_any_impl

    template< typename Base >
    bool empty_any_impl(Base const* ) const
    {
        typedef typename Base::base_type          base_type;
        typedef typename Base::signature_type     signature_type;

        return ( empty<signature_type>() || empty_any_impl<base_type>(this) );
    }

    template<typename Base>
    bool empty_any_impl(detail::final_overload_base const* ) const
    {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////////
    // function contains_impl

    template< typename Base, typename Functor >
    bool contains_impl( Base const*, const Functor & f ) const
    {
        typedef typename this_type::base_type       base_type;
        typedef typename Base::signature_type       signature_type;
        typedef typename wrapped_function<signature_type>::type function_type;

        if ( function_type::contains( f ) )
            return true;
        return contains_compatible_impl<base_type, Functor>(this, f);
    }

    template< typename Base, typename Functor >
    bool contains_impl( detail::final_overload_base const*,
                        const Functor & f ) const
    {
        typedef typename this_type::base_type       base_type;
        return contains_compatible_impl<base_type, Functor>(this, f);
    }

    template< typename Base, typename Functor >
    bool contains_compatible_impl( Base const*, const Functor & f ) const
    {
        typedef typename Base::base_type          base_type;
        typedef typename Base::signature_type     signature_type;
        typedef typename wrapped_function<signature_type>::type function_type;

        return ( function_type::contains( f )
                || contains_impl<base_type, Functor>(this, f) );
    }

    template< typename Base, typename Functor >
    bool containscompatible__impl( detail::final_overload_base const*,
                                   const Functor & ) const
    {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////////
    // return a pointer to this object casted to the correct base pointer 
    // for a generic functor

    template< typename F >
    typename wrapped_function<
        typename detail::signature_by_functor<F, this_type>::type
    >::type*
    base_ptr( F const& )
    {
        return this;
    }

}; // end class overload

// defined out of the class for compatibility with gcc 3.4 and intel 9.1
template< BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig) >
const unsigned int 
overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>::extent 
    = detail::extent<
          overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)> 
      >::value;

///////////////////////////////////////////////////////////////////////////////
// swap two boost::overloads
template<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig)>
void swap( overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>& f1,
           overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>& f2 )
{
    f1.swap(f2);
}

///////////////////////////////////////////////////////////////////////////////
// metafunctions for call wrapper type traits
//
// - extent<CallWrapperType>::value
// it provides the amount of signatures supported by a call wrapper type
//
// - signature<CallWrapperType, N = 0>::type
// it provides the N-th signature for a call wrapper type
// (indexing start from zero)
//
// - function<CallWrapperType, N = 0>::type
// it provides the type of the N-th wrapped function embedded object
// (indexing start from zero)
//
// - index_of_signature<CallWrapperType, Signature>::value
// it provides the index of a signature, and returns -1 if it's not found
//
// - has_signature<CallWrapperType, Signature>::value
// utility to discover if a given signature is supported by a call wrapper type
//
// - have_any_shared_signature<CallWrapperType, Functor>::value
// utility to discover if a given functor has a signature supported by
// a call wrapper type
//

///////////////////////////////////////////////////////////////////////////////
// - extent<CallWrapperType>::value
// it provides the amount of signatures supported by the call wrapper type

template<typename CallWrapperType>
struct extent
{
};

template<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig)>
struct extent< overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)> >
{
  private:
    typedef overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>
            overload_type;
  public:
    BOOST_STATIC_CONSTANT( int, value = (detail::extent<overload_type>::value) );
};

template<typename Signature>
struct extent< boost::function<Signature> >
{
    BOOST_STATIC_CONSTANT( int, value = 1 );
};

///////////////////////////////////////////////////////////////////////////////
// - signature<CallWrapperType, N = 0>::type
// it provides the N-th signature for a call wrapper type
// (indexing start from zero)

template<typename CallWrapperType, unsigned int N = 0>
struct signature
{
};

template<unsigned int N, BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig)>
struct signature< overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>, N >
{
  private:
    typedef overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>
            overload_type;
  public:
    typedef typename detail::signature<N, overload_type>::type type;
};

template<typename Signature>
struct signature< boost::function<Signature>, 0 >
{
    typedef Signature type;
};

///////////////////////////////////////////////////////////////////////////////
// - function<CallWrapperType, N = 0>::type
// it provides the type of the N-th boost::function embedded object
// (indexing start from zero)

template<typename CallWrapperType, unsigned int N = 0>
struct function
{
};

template<unsigned int N, BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig)>
struct function< overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>, N >
{
  private:
    typedef overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>
            overload_type;
  public:
    typedef typename detail::function<N, overload_type>::type type;
};

template<typename Signature>
struct function< boost::function<Signature>, 0 >
{
    typedef boost::function<Signature> type;
};

///////////////////////////////////////////////////////////////////////////////
// - index_of_signature<CallWrapperType, Signature>::value
// it provides the index of a signature, and returns -1 if it's not found

template<typename CallWrapperType, typename Signature>
struct index_of_signature
{
};

template<typename Signature, BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig)>
struct index_of_signature< overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>, Signature >
{
  private:
    typedef overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>
            overload_type;
  public:
    BOOST_STATIC_CONSTANT( int, value =
            (static_cast<int>(detail::index_of_signature<Signature, overload_type>::value)) );
};

template<typename FuncSignature, typename Signature>
struct index_of_signature< boost::function<FuncSignature>, Signature >
{
    BOOST_STATIC_CONSTANT(int, value = -1);
};

template<typename Signature>
struct index_of_signature< boost::function<Signature>, Signature >
{
    BOOST_STATIC_CONSTANT(int, value = 0);
};

///////////////////////////////////////////////////////////////////////////////
// - has_signature<CallWrapperType, Signature>::value
// utility to discover if a given signature is supported by a call wrapper type

template<typename CallWrapperType, typename Signature>
struct has_signature
{
};

template<typename Signature, BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig)>
struct has_signature< overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>, Signature >
{
  private:
    typedef overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>
            overload_type;
  public:
    BOOST_STATIC_CONSTANT( bool, value =
            (detail::has_signature<Signature, overload_type>::value) );
};

template<typename FuncSignature, typename Signature>
struct has_signature< boost::function<FuncSignature>, Signature >
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template<typename Signature>
struct has_signature< boost::function<Signature>, Signature >
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

///////////////////////////////////////////////////////////////////////////////
// - have_any_shared_signature<CallWrapperType, Functor>::value
// utility to discover if a given functor has a signature supported by
// a call wrapper type

template<typename CallWrapperType, typename Functor>
struct have_any_shared_signature
{
};

template<typename Functor, BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename Sig)>
struct have_any_shared_signature< overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>, Functor >
{
  private:
    typedef overload<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, Sig)>
            overload_type;
  public:
    BOOST_STATIC_CONSTANT( bool, value =
            (detail::have_any_shared_signature<Functor, overload_type>::value) );
};

template<typename Signature, typename Functor>
struct have_any_shared_signature< boost::function<Signature>, Functor >
{
    BOOST_STATIC_CONSTANT( bool, value =
            (detail::functor_has_signature<Functor, Signature>::value) );
};

} // end overloads namespace

using overloads::overload;
using overloads::swap;

} // end boost namespace


#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif // _BOOST_OVERLOAD_IMPL_HPP_


