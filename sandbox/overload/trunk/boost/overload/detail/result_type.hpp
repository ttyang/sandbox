/*=============================================================================
    Copyright (c) 2007-2012 Marco Cecchetti

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef _BOOST_OVERLOAD_RESULT_TYPE_HPP_
#define _BOOST_OVERLOAD_RESULT_TYPE_HPP_
#if BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    #include "function_trait.hpp"
#endif
#include "trait_by_index.hpp"
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/comma_if.hpp>


#define BOOST_OVERLOAD_OVERLOAD_CANDIDATE(z, n, S) \
        public overload_candidate<BOOST_PP_CAT(S,n), n>
#define BOOST_OVERLOAD_OVERLOAD_CANDIDATE_INVOKE(z, n, S) \
        using overload_candidate<BOOST_PP_CAT(S,n), n>::invoke;
#define BOOST_OVERLOAD_OVERLOAD_CANDIDATE_DEF(z, n, unused) \
template<unsigned int N, typename R BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A)> \
struct overload_candidate<R (BOOST_PP_ENUM_PARAMS(n, A) ), N> \
{ \
    typedef char index_type[N+1]; \
    static index_type& invoke(BOOST_PP_ENUM_PARAMS(n, A) ); \
};
// end macro BOOST_OVERLOAD_OVERLOAD_CANDIDATE_DEF
#define BOOST_OVERLOAD_ARG_N(z, n, unused) \
        static BOOST_PP_CAT(A,n) BOOST_PP_CAT(arg,n);

#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
#define BOOST_OVERLOAD_INDEX_OF_BEST_OVERLOAD_CANDIDATE_DEF(z, n, unused) \
template<typename Candidates, typename R BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A)> \
struct index_of_best_overload_candidate<R (BOOST_PP_ENUM_PARAMS(n, A) ), Candidates> \
{ \
    BOOST_PP_REPEAT(n, BOOST_OVERLOAD_ARG_N, unused) \
    BOOST_STATIC_CONSTANT( unsigned int, value = ((sizeof(Candidates::invoke(BOOST_PP_ENUM_PARAMS(n, arg))) / sizeof(char)) - 1) ); \
};
#else
#define BOOST_OVERLOAD_INDEX_OF_BEST_OVERLOAD_CANDIDATE_DEF(z, n, unused) \
template<typename Candidates, typename R BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A)> \
struct index_of_best_overload_candidate<R (BOOST_PP_ENUM_PARAMS(n, A) ), Candidates> \
{ \
    BOOST_PP_REPEAT(n, BOOST_OVERLOAD_ARG_N, unused) \
    static arity_type<n> arity_object; \
    BOOST_STATIC_CONSTANT( unsigned int, value = ((sizeof(Candidates::invoke( BOOST_PP_ENUM_PARAMS(n, arg) BOOST_PP_COMMA_IF(n) arity_object )) / sizeof(char)) - 1) ); \
};
// end macro BOOST_OVERLOAD_INVOKER_DEF
#endif


namespace boost{ namespace overloads{ namespace detail{

#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
///////////////////////////////////////////////////////////////////////////////
// class:     overload_candidate<S, N>
// requires:  S is a call signature (that is a function type)
//            N is a positive integer
// provides:  defines a static member function 'invoke' with parameter types
//            the same specified in the call signature S and with result type
//            a type R such that sizeof(R) == (N * sizeof(char))


template<typename S, unsigned int N>
struct overload_candidate
{
};

template<unsigned int N>
struct overload_candidate<no_signature, N>
{
    struct dummy_type;
    template<typename T>
    static void invoke(dummy_type );
};

BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_OVERLOAD_MAX_NUM_ARGS), BOOST_OVERLOAD_OVERLOAD_CANDIDATE_DEF, unused)

///////////////////////////////////////////////////////////////////////////////
// class:      overload_candidate_set<S0, ..., SN>
// requires:   S0, ..., SN are call signatures (that is function types)
// provides:   inherits from each overload_candidate<SK, K> and exposes an
//             'invoke' static member function for each call signature SK.

template<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename S)>
struct overload_candidate_set
    : BOOST_PP_ENUM(BOOST_OVERLOAD_LIMIT, BOOST_OVERLOAD_OVERLOAD_CANDIDATE, S)
{
    BOOST_PP_REPEAT(BOOST_OVERLOAD_LIMIT, BOOST_OVERLOAD_OVERLOAD_CANDIDATE_INVOKE, S)
};

#else  // BOOST_WORKAROUND(BOOST_MSVC, < 1400)

///////////////////////////////////////////////////////////////////////////////
// helper macros

#define BOOST_OVERLOAD_GET_ARG_BY_INDEX(z, n, unused) \
template<typename SignatureTraits> \
struct get_arg_by_index<n, SignatureTraits> \
{ \
    typedef typename SignatureTraits::BOOST_PP_CAT(BOOST_PP_CAT(arg, BOOST_PP_INC(n)), _type) type; \
}; \
BOOST_PP_EMPTY()
// end macro BOOST_OVERLOAD_GET_ARG_BY_INDEX

#define BOOST_OVERLOAD_INVOKE_SIG_TRAITS(m) \
        BOOST_PP_CAT(BOOST_PP_CAT(sig, m), _traits)

#define BOOST_OVERLOAD_INVOKE_RESULT_TYPE(m) \
        BOOST_PP_CAT(BOOST_PP_CAT(result, m), _type)

#define BOOST_OVERLOAD_INVOKE_ARG_TYPE(m, n) \
        BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT(arg_, m), _), n), _type)

#define BOOST_OVERLOAD_INVOKE_ARG_TYPE_M(z, n, m) \
        BOOST_OVERLOAD_INVOKE_ARG_TYPE(m, n)

#define BOOST_OVERLOAD_INVOKE_ARG_TYPEDEF(z, n, m) \
    typedef typename get_arg_type<n, BOOST_OVERLOAD_INVOKE_SIG_TRAITS(m), m>::type BOOST_OVERLOAD_INVOKE_ARG_TYPE(m, n); \
    BOOST_PP_EMPTY()
// end macro BOOST_OVERLOAD_INVOKE_ARG_TYPEDEF

#define BOOST_OVERLOAD_OVERLOAD_CANDIDATE_SET_INVOKE(z, m, n) \
    typedef func_trait<BOOST_PP_CAT(S, m)> BOOST_OVERLOAD_INVOKE_SIG_TRAITS(m); \
    BOOST_PP_REPEAT(n, BOOST_OVERLOAD_INVOKE_ARG_TYPEDEF, m) \
    typedef char BOOST_OVERLOAD_INVOKE_RESULT_TYPE(m)[BOOST_PP_INC(m)]; \
    static BOOST_OVERLOAD_INVOKE_RESULT_TYPE(m) & \
    invoke( BOOST_PP_ENUM(n, BOOST_OVERLOAD_INVOKE_ARG_TYPE_M, m) BOOST_PP_COMMA_IF(n) arity_type<BOOST_OVERLOAD_INVOKE_SIG_TRAITS(m)::arity> ); \
    BOOST_PP_EMPTY() \
    BOOST_PP_EMPTY()
// end macro BOOST_OVERLOAD_OVERLOAD_CANDIDATE_SET_INVOKE

#define BOOST_OVERLOAD_OVERLOAD_CANDIDATE_SET(z, n, unused) \
template<BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename S)> \
struct overload_candidate_set<n, BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, S)> \
{ \
    BOOST_PP_REPEAT(BOOST_OVERLOAD_LIMIT, BOOST_OVERLOAD_OVERLOAD_CANDIDATE_SET_INVOKE, n) \
}; \
BOOST_PP_EMPTY()
// end macro BOOST_OVERLOAD_OVERLOAD_CANDIDATE_SET

///////////////////////////////////////////////////////////////////////////////
// class:      arity_type<N>
// provides:   a tag type for discriminating call signature arities

template<unsigned int N> struct arity_type {};

///////////////////////////////////////////////////////////////////////////////
// metafunction:  get_arg_by_index<N, SignatureTraits>
// requires:      N is a non-negative integer, SignatureTraits is a class
//                template that is derived from boost::function_traits
// returns:       the N+1 argument type as reported by SignatureTraits

template<unsigned int N, typename SignatureTraits>
struct get_arg_by_index
{
};

BOOST_PP_REPEAT(BOOST_OVERLOAD_MAX_NUM_ARGS, BOOST_OVERLOAD_GET_ARG_BY_INDEX, unused)

///////////////////////////////////////////////////////////////////////////////
// metafunction:  get_arg_type<ArgIndex, SignatureTraits, SigIndex>
// requires:      ArgIndex and SigIndex are a non-negative integers,
//                SignatureTraits is a class template that is derived from
//                boost::function_traits
// returns:       the type of the ArgIndex+1 argument as reported by
//                SignatureTraits if ArgIndex < SignatureTraits::arity,
//                dummy_type otherwise

template<
    unsigned int ArgIndex,
    typename SignatureTraits,
    unsigned int SigIndex,
    bool IsOverRequiredArity = (ArgIndex >= SignatureTraits::arity)
    >
struct get_arg_type
{
    typedef typename get_arg_by_index<ArgIndex, SignatureTraits>::type type;
};

template<
    unsigned int ArgIndex,
    typename SignatureTraits,
    unsigned int SigIndex
    >
struct get_arg_type<ArgIndex, SignatureTraits, SigIndex, true>
{
    struct dummy_type;
    typedef dummy_type type;
};

template<
    unsigned int ArgIndex,
    unsigned int SigIndex
    >
struct get_arg_type<ArgIndex, func_trait<no_signature>, SigIndex, false>
{
    struct dummy_type;
    typedef dummy_type type;
};

///////////////////////////////////////////////////////////////////////////////
// class:      overload_candidate_set<RequiredArity, S0, ..., SN>
// requires:   S0, ..., SN are call signatures (that is function types)
//             RequiredArity is a non-negative integer
// provides:   defines a static member function 'invoke' for each call
//             signature SK with parameter types the same ones specified in
//             the call signature SK and with result type a type RK such that
//             sizeof(RK) == ((K+1) * sizeof(char))

template<unsigned int RequiredArity, BOOST_PP_ENUM_PARAMS(BOOST_OVERLOAD_LIMIT, typename S)>
struct overload_candidate_set
{
};

BOOST_PP_REPEAT(BOOST_OVERLOAD_MAX_NUM_ARGS, BOOST_OVERLOAD_OVERLOAD_CANDIDATE_SET, unused)


#undef BOOST_OVERLOAD_OVERLOAD_CANDIDATE_SET
#undef BOOST_OVERLOAD_OVERLOAD_CANDIDATE_SET_INVOKE
#undef BOOST_OVERLOAD_INVOKE_ARG_TYPEDEF
#undef BOOST_OVERLOAD_INVOKE_ARG_TYPE_M
#undef BOOST_OVERLOAD_INVOKE_ARG_TYPE
#undef BOOST_OVERLOAD_INVOKE_RESULT_TYPE
#undef BOOST_OVERLOAD_INVOKE_SIG_TRAITS
#undef BOOST_OVERLOAD_GET_ARG_BY_INDEX

#endif


///////////////////////////////////////////////////////////////////////////////
// metafunction:  index_of_best_overload_candidate<ArgsType, Candidates>
// requires:      ArgsType is a function type R (A0, A1, ..., AN) where
//                A0, ..., AN are the arguments of the required function call,
//                Candidates is an instantiation of the overload_candidate_set
//                class template
// returns:       the index of the best overload candidate included into
//                the ordered overload set Candidates

template<typename ArgsType, typename Candidates>
struct index_of_best_overload_candidate
{
};

BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_OVERLOAD_MAX_NUM_ARGS), BOOST_OVERLOAD_INDEX_OF_BEST_OVERLOAD_CANDIDATE_DEF, unused)

///////////////////////////////////////////////////////////////////////////////
// metafunction:  index_of_best_viable_function<ArgsType, Overload>
// requires:      ArgsType is a function type R (A0, A1, ..., AN) where
//                A0, ..., AN are the arguments of the required function call,
//                Overload is an instantiation of the boost::overload class
//                template
// returns:       the index of the call signature of the best viable function
//                supported by Overload respect with the arguments specified in
//                ArgsType, or a compile-time error if the best viable
//                function can not be determined

template<typename ArgsType, typename Overload>
struct index_of_best_viable_function
{
  private:
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    typedef typename Overload::overload_candidate_set candidates_type;
#else
    typedef typename Overload::template overload_candidate_set<ArgsType>::type
            candidates_type;
#endif
    typedef index_of_best_overload_candidate<ArgsType, candidates_type>
            index_type;
  public:
    BOOST_STATIC_CONSTANT( unsigned int, value = (index_type::value) );
};

///////////////////////////////////////////////////////////////////////////////
// metafunction:  result<CallType>
// requires:      CallType is a function type F (A0, A1, ..., AN) where
//                F is an instantiation of the boost::overload class template
// returns:       the result type of the best viable function supported by F
//                respect with the arguments specified in CallType or a compiler
//                error if the best viable function can not be determined
// provides:      support for Boost.ResultOf

template<typename CallType>
struct result
{
  private:
    typedef typename boost::function_traits<CallType>::result_type overload_type;
    BOOST_STATIC_CONSTANT( unsigned int, index =
            (index_of_best_viable_function<CallType, overload_type>::value) );
    typedef typename signature<index, overload_type>::type signature;
  public:
    typedef typename boost::function_traits<signature>::result_type type;
};

} } } // end namespaces


#undef BOOST_OVERLOAD_INDEX_OF_BEST_OVERLOAD_CANDIDATE_DEF
#undef BOOST_OVERLOAD_ARG_N
#undef BOOST_OVERLOAD_OVERLOAD_CANDIDATE_DEF
#undef BOOST_OVERLOAD_OVERLOAD_CANDIDATE_INVOKE
#undef BOOST_OVERLOAD_OVERLOAD_CANDIDATE


#endif // _BOOST_OVERLOAD_RESULT_TYPE_HPP_
