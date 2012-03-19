/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef _BOOST_OVERLOAD_DETAIL_MEMBER_FUNCTION_TRAIT_HPP_
#define _BOOST_OVERLOAD_DETAIL_MEMBER_FUNCTION_TRAIT_HPP_


///////////////////////////////////////////////////////////////////////////////
// member function traits

#define BOOST_OVERLOAD_MEMB_FUNC_TRAIT(z, n, unused) \
template< typename ClassT,                                                     \
          typename R BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A) >            \
struct memb_func_trait< R (ClassT::*) ( BOOST_PP_ENUM_PARAMS(n, A) ) >         \
{                                                                              \
    typedef ClassT class_type;                                                 \
    typedef R sig_type( BOOST_PP_ENUM_PARAMS(n, A) );                          \
    typedef R (ClassT::* type) ( BOOST_PP_ENUM_PARAMS(n, A) );                 \
    typedef R (ClassT::* const_type) ( BOOST_PP_ENUM_PARAMS(n, A) ) const;     \
    typedef R binded_type( ClassT* BOOST_PP_ENUM_TRAILING_PARAMS(n, A) );      \
    typedef                                                                    \
        R const_binded_type(const ClassT* BOOST_PP_ENUM_TRAILING_PARAMS(n,A) );\
    BOOST_STATIC_CONSTANT( bool, const_qualified = false );                    \
};                                                                             \
                                                                               \
template< typename ClassT,                                                     \
          typename R BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A) >            \
struct memb_func_trait< R (ClassT::*) ( BOOST_PP_ENUM_PARAMS(n, A) ) const >   \
    : memb_func_trait< R (ClassT::*) ( BOOST_PP_ENUM_PARAMS(n, A) ) >          \
{                                                                              \
    BOOST_STATIC_CONSTANT( bool, const_qualified = true );                     \
};                                                                             \

// end macro BOOST_OVERLOAD_MEMB_FUNC_TRAIT


namespace boost{ namespace overloads{ namespace detail{

template< typename MemberPtr>
struct memb_func_trait
{};

BOOST_PP_REPEAT(BOOST_OVERLOAD_MAX_NUM_ARGS, BOOST_OVERLOAD_MEMB_FUNC_TRAIT, unused)

} } } // end namespaces

#undef BOOST_OVERLOAD_MEMB_FUNC_TRAIT

#endif // _BOOST_OVERLOAD_DETAIL_MEMBER_FUNCTION_TRAIT_HPP_

