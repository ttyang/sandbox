/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef _BOOST_OVERLOAD_DETAIL_MACRO_DEF_HPP_
#define _BOOST_OVERLOAD_DETAIL_MACRO_DEF_HPP_

#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/if.hpp>

#define BOOST_OVERLOAD_WRAPPED_FUNC boost::function

#define BOOST_OVERLOAD_MAKE_NTH_PARAM_WITH_A_DEFAULT(z, n, seq) \
    BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, seq), n) = BOOST_PP_SEQ_ELEM(1, seq)

#define BOOST_OVERLOAD_ENUM_SHIFTED_PARAMS_WITH_A_DEFAULT(n, param, dv) \
    BOOST_PP_ENUM_SHIFTED(n, BOOST_OVERLOAD_MAKE_NTH_PARAM_WITH_A_DEFAULT, (param)(dv))

#define BOOST_OVERLOAD_MAKE_NTH_CALL(z, n, seq) \
    BOOST_PP_SEQ_ELEM(0, seq)BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(1, seq), n)BOOST_PP_SEQ_ELEM(2, seq)

#define BOOST_OVERLOAD_ENUM_CALLS_TPL(n, func, arg, result) \
    BOOST_PP_ENUM(n, BOOST_OVERLOAD_MAKE_NTH_CALL, (func<)(arg)(>::result))

#define BOOST_OVERLOAD_MAKE_NTH_NUM_CALL(z, n, seq) \
    BOOST_PP_SEQ_ELEM(0, seq) n BOOST_PP_SEQ_ELEM(1, seq)

#define BOOST_OVERLOAD_ENUM_NUM_CALLS_TPL(n, func, result) \
    BOOST_PP_ENUM(n, BOOST_OVERLOAD_MAKE_NTH_NUM_CALL, (func<)(>::result))

#define BOOST_OVERLOAD_SET_IMPL(z,  n,  f) \
    set_impl( BOOST_PP_CAT(f, n) );

#define BOOST_OVERLOAD_SET(z, n, unused) \
template< BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), typename F) > \
this_type& set( BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n), F, const& _f) ) \
{ \
    BOOST_PP_REPEAT(BOOST_PP_INC(n), BOOST_OVERLOAD_SET_IMPL, _f) \
    return *this; \
}
// end macro BOOST_OVERLOAD_SET

#define BOOST_OVERLOAD_CTOR(z, n, unused) \
template< BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), typename F) > \
overload( BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n), F, const& _f) ) \
{ \
    set( BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), _f) ); \
}
// end macro BOOST_OVERLOAD_CTOR

#define BOOST_OVERLOAD_MAKE_NTH_MAKE_OVERLOAD(z, n, unused) \
template<BOOST_PP_ENUM_PARAMS(n, typename F)> \
typename detail::make_overload_type<BOOST_PP_ENUM_PARAMS(n, F)>::type \
make_overload(BOOST_PP_ENUM_BINARY_PARAMS(n, const F, & f)) \
{ \
    typedef typename detail::make_overload_type<BOOST_PP_ENUM_PARAMS(n, F)>::type \
            overload_type; \
    return overload_type(BOOST_PP_ENUM_PARAMS(n, f)); \
}
// end macro BOOST_OVERLOAD_MAKE_NTH_MAKE_OVERLOAD

#define BOOST_OVERLOAD_FUNCTOR_ADAPTOR(result_type, func, template_param, signature, func_impl) \
template<template_param> \
result_type func( signature* _f_ptr ) \
{ \
    return func_impl< signature >( _f_ptr ); \
} \
\
template<template_param> \
result_type func( typename detail::memb_func_form< signature >::type _mf_ptr ) \
{ \
    return func_impl< signature >( _mf_ptr ); \
} \
 \
template<template_param> \
result_type func( typename detail::memb_func_form< signature, detail::const_>::type _mf_ptr ) \
{ \
    return func_impl< signature >( _mf_ptr ); \
} \
 \
template<template_param, typename F> \
result_type func( F const& _f, \
                  typename boost::disable_if< \
                      detail::is_ptr_or_memb_ptr_and_has_matching_signature< F, signature > \
                  >::type* = 0 ) \
{ \
    typedef typename detail::disambiguate< F, signature >::type cast_type; \
    return func_impl< signature >( static_cast<cast_type>(_f) ); \
}
// end macro BOOST_OVERLOAD_FUNCTOR_ADAPTOR


///////////////////////////////////////////////////////////////////////////////
// Workarounds for MSVC < 8.0 tested on MSVC 7.1 

#if BOOST_WORKAROUND(BOOST_MSVC, < 1400)  

#define BOOST_OVERLOAD_REAL_OR_DUMMY_SIG_M_N(z, m, n) \
typedef                                                                        \
    typename detail::real_or_dummy_signature<n, BOOST_PP_CAT(Sig, n), m>::type \
    BOOST_PP_CAT(sig_, BOOST_PP_CAT(n, BOOST_PP_CAT(_, BOOST_PP_CAT(m, _t)))); \

//end macro BOOST_OVERLOAD_REAL_OR_DUMMY_SIG_M_N

#define BOOST_OVERLOAD_REAL_OR_DUMMY_SIG_M(z, n, unused) \
BOOST_PP_REPEAT(BOOST_OVERLOAD_MAX_NUM_ARGS, BOOST_OVERLOAD_REAL_OR_DUMMY_SIG_M_N, n)
// end macro BOOST_OVERLOAD_REAL_OR_DUMMY_SIG_M

#define BOOST_OVERLOAD_FC_OP_PARAM(z, m, tuple) \
typename detail::func_trait<                                                   \
    BOOST_PP_CAT(sig_,                                                         \
        BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 0, tuple),                         \
            BOOST_PP_CAT(_,                                                    \
                BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 1, tuple), _t)             \
            )                                                                  \
         )                                                                     \
    )                                                                          \
>::BOOST_PP_CAT(arg, BOOST_PP_CAT(m, _type)) BOOST_PP_CAT(a, m)                \

// end macro BOOST_OVERLOAD_FC_OP_PARAM

#define BOOST_OVERLOAD_FUNC_CALL_OPERATOR_M_N(z, m, n) \
typename detail::func_trait<BOOST_PP_CAT(Sig,n)>::result_type                  \
operator() ( BOOST_PP_ENUM_SHIFTED(BOOST_PP_INC(m), BOOST_OVERLOAD_FC_OP_PARAM, (n, m)) ) \
{                                                                              \
    typedef                                                                    \
        BOOST_PP_CAT(sig_,BOOST_PP_CAT(n,BOOST_PP_CAT(_,BOOST_PP_CAT(m, _t)))) \
        signature_type;                                                        \
    return BOOST_OVERLOAD_WRAPPED_FUNC<signature_type>::                       \
           operator()( BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(m), a) );     \
}                                                                              \

// end macro BOOST_OVERLOAD_FUNC_CALL_OPERATOR_M_N

#define BOOST_OVERLOAD_FUNC_CALL_OPERATORS(z, n, unused) \
BOOST_PP_REPEAT_FROM_TO(1, BOOST_OVERLOAD_MAX_NUM_ARGS, BOOST_OVERLOAD_FUNC_CALL_OPERATOR_M_N, n)
// end macro BOOST_OVERLOAD_FUNC_CALL_OPERATORS

#endif
// end workarounds for MSVC < 8.0 tested on MSVC 7.1
///////////////////////////////////////////////////////////////////////////////

// so we can include the header responsible of undef macro once more
#undef _BOOST_DETAIL_OVERLOAD_MACRO_UNDEF_HPP_

#endif // _BOOST_OVERLOAD_DETAIL_MACRO_DEF_HPP_

