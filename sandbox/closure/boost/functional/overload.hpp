
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef DOXY // Doxygen documentation only.

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_FUNCTIONAL_OVERLOAD_HPP_
#       define BOOST_FUNCTIONAL_OVERLOAD_HPP_

#       include <boost/functional/detail/overload_base.hpp>
#       include <boost/functional/detail/function_type.hpp>
#       include <boost/functional/config.hpp>
#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/preprocessor/repetition/enum.hpp>
#       include <boost/preprocessor/repetition/repeat.hpp>
#       include <boost/preprocessor/control/expr_iif.hpp>
#       include <boost/preprocessor/control/expr_if.hpp>
#       include <boost/preprocessor/comparison/greater.hpp>
#       include <boost/preprocessor/comparison/less.hpp>
#       include <boost/preprocessor/cat.hpp>
#       include <boost/preprocessor/arithmetic/add.hpp>
#       include <boost/preprocessor/tuple/eat.hpp>
#       include <boost/preprocessor/logical/and.hpp>
#       include <boost/preprocessor/logical/not.hpp>
#       include <boost/preprocessor/facilities/expand.hpp>

#define BOOST_FUNCTIONAL_f_type(z, n, unused) \
    BOOST_PP_CAT(F, n)

#define BOOST_FUNCTIONAL_f_arg(z, n, unused) \
    BOOST_PP_CAT(f, n)

#define BOOST_FUNCTIONAL_f_tparam(z, n, unused) \
    typename BOOST_FUNCTIONAL_f_type(z, n, ~) \

#define BOOST_FUNCTIONAL_f_tparam_dflt(z, n, is_tspec) \
    BOOST_FUNCTIONAL_f_tparam(z, n, ~) \
    /* overload requires at least 2 functors so F0 and F1 not optional */ \
    BOOST_PP_EXPR_IIF(BOOST_PP_AND(BOOST_PP_NOT(is_tspec), \
            BOOST_PP_GREATER(n, 1)), \
        = void \
    )

#define BOOST_FUNCTIONAL_f_arg_decl(z, n, unused) \
    BOOST_FUNCTIONAL_f_type(z, n, ~) /* no qualifier to deduce tparam */ \
    BOOST_FUNCTIONAL_f_arg(z, n, ~)

#define BOOST_FUNCTIONAL_g_type(z, n, unused) \
    BOOST_PP_CAT(G, n)

#define BOOST_FUNCTIONAL_g_arg(z, n, unused) \
    BOOST_PP_CAT(g, n)

#define BOOST_FUNCTIONAL_g_tparam(z, n, unused) \
    typename BOOST_FUNCTIONAL_g_type(z, n, ~)

#define BOOST_FUNCTIONAL_g_arg_decl(z, n, unused) \
    BOOST_FUNCTIONAL_g_type(z, n, ~) /* no qualifier to deduce tparam */ \
    BOOST_FUNCTIONAL_g_arg(z, n, ~)

#define BOOST_FUNCTIONAL_overload_base(z, n, unused) \
    ::boost::functional::detail::overload_base< \
        BOOST_FUNCTIONAL_f_type(z, n, ~) \
    >

#define BOOST_FUNCTIONAL_overload_inherit(z, n, unused) \
    public BOOST_FUNCTIONAL_overload_base(z, n, ~)

#define BOOST_FUNCTIONAL_overload_base_init(z, n, unused) \
    BOOST_FUNCTIONAL_overload_base(z, n, ~)( /* base init paren `()` */ \
            BOOST_FUNCTIONAL_g_arg(z, n, ~))

#define BOOST_FUNCTIONAL_using_operator_call(z, n, unused) \
    using BOOST_FUNCTIONAL_overload_base(z, n, ~)::operator();

#define BOOST_FUNCTIONAL_function_type(z, n, unused) \
    typename detail::function_type< BOOST_FUNCTIONAL_f_type(z, n, ~) >::type

namespace boost { namespace functional {

// Iterate within namespace.
#       define BOOST_PP_ITERATION_PARAMS_1 \
                /* need at least 2 functors to overload so iter 2, 3, ... */ \
                (3, (0, BOOST_PP_SUB(BOOST_FUNCTIONAL_CONFIG_OVERLOAD_MAX, 2), \
                "boost/functional/overload.hpp"))
#       include BOOST_PP_ITERATE() // Iterate over function arity.

} }

#undef BOOST_FUNCTIONAL_f_type
#undef BOOST_FUNCTIONAL_f_arg
#undef BOOST_FUNCTIONAL_f_tparam
#undef BOOST_FUNCTIONAL_f_arg_decl
#undef BOOST_FUNCTIONAL_f_tparam_dflt
#undef BOOST_FUNCTIONAL_g_type
#undef BOOST_FUNCTIONAL_g_arg
#undef BOOST_FUNCTIONAL_g_tparam
#undef BOOST_FUNCTIONAL_g_arg_decl
#undef BOOST_FUNCTIONAL_overload_base
#undef BOOST_FUNCTIONAL_overload_inherit
#undef BOOST_FUNCTIONAL_overload_base_init
#undef BOOST_FUNCTIONAL_using_operator_call
#undef BOOST_FUNCTIONAL_function_type

#   endif // #include guard

#elif BOOST_PP_ITERATION_DEPTH() == 1
#   define BOOST_FUNCTIONAL_overloads \
        /* iterate as OVERLOADS, OVERLOADS-1, OVERLOADS-2, ... */ \
        BOOST_PP_SUB(BOOST_FUNCTIONAL_CONFIG_OVERLOAD_MAX, \
                BOOST_PP_FRAME_ITERATION(1))
#   define BOOST_FUNCTIONAL_is_tspec \
        /* if template specialization */ \
        BOOST_PP_LESS(BOOST_FUNCTIONAL_overloads, \
                BOOST_FUNCTIONAL_CONFIG_OVERLOAD_MAX)

template<
    BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_f_tparam_dflt,
            BOOST_FUNCTIONAL_is_tspec)
>
class overload
    // Template specialization.
    BOOST_PP_EXPR_IIF(BOOST_PP_EXPAND(BOOST_FUNCTIONAL_is_tspec), <)
    BOOST_PP_IIF(BOOST_FUNCTIONAL_is_tspec,
        BOOST_PP_ENUM
    ,
        BOOST_PP_TUPLE_EAT(3)
    )(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_f_type, ~)
    BOOST_PP_EXPR_IIF(BOOST_PP_EXPAND(BOOST_FUNCTIONAL_is_tspec), >)
    // Bases (overloads >= 2 so always at least 2 bases).
    : BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads,
            BOOST_FUNCTIONAL_overload_inherit, ~)
{
public:
    template<
        BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_g_tparam, ~)
    > /* implicit */ inline overload(
            BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads,
                    BOOST_FUNCTIONAL_g_arg_decl, ~))
            // Overloads >= 2 so always at least 2 bases to initialize.
            : BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads,
                    BOOST_FUNCTIONAL_overload_base_init, ~)
    {}

    BOOST_PP_REPEAT(BOOST_FUNCTIONAL_overloads, 
            BOOST_FUNCTIONAL_using_operator_call, ~)
};

template<
    BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_f_tparam, ~)
>
overload<
    BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_function_type, ~)
> make_overload(
    BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_f_arg_decl, ~)
) {
    return overload<
        BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads,
                BOOST_FUNCTIONAL_function_type, ~)
    >(BOOST_PP_ENUM(BOOST_FUNCTIONAL_overloads, BOOST_FUNCTIONAL_f_arg, ~));
}

#   undef BOOST_FUNCTIONAL_overloads
#   undef BOOST_FUNCTIONAL_is_tspec
#endif // iteration

#else // DOXY: Doxygen documentation only.

/** @file
 * @brief Defines a functor that can be used to overload the call operator of
 *  a set of specified functors.
 */

namespace boost { namespace funcational {

/**
 * @brief Functor to overload local functions and other functors.
 *
 * This functor aggregates together calls to functions of all the specified
 * function types <c>F1</c>, <c>F2</c>, etc.
 * Each function type must be specified following the Boost.Function preferred
 * syntax:
 * @code
 *  ResultType (ArgumentType1, ArgumgnetType2, ...)
 * @endcode
 *
 * The maximum number of overloaded function types is specified by the
 * @RefMacro{BOOST_FUNCTIONAL_CONFIG_OVERLOAD_MAX} configuration macro.
 * The maximum number of function parameters for each of the specified function
 * type is specified by the @RefMacro{BOOST_FUNCTIONAL_CONFIG_OVERLOAD_MAX}
 * configuration macro.
 *
 * @See @RefSect2{Advanced_Topics, Advanced Topics} section,
 *  @RefMacro{BOOST_FUNCTIONAL_CONFIG_OVERLOAD_MAX},
 *  @RefMacro{BOOST_FUNCTIONAL_CONFIG_OVERLOAD_MAX}, Boost.Function.
 */
template<typename F1, typename F2, ...>
class overload {
public:
    /**
     * @brief Construct the overloading functor.
     *
     * Any functor that can be converted to a <c>boost::function</c> funcotr
     * can be specified (local functions, function pointers, other functors,
     * etc).
     */
    overload(const boost::function<F1>&, const boost::function<F2>&, ...);

    /**
     * @brief Call operator matching the signature of the function type
     *  specified as first.
     *
     * This will in turn invoke the call operator of the first functor that was
     * passed to the constructor.
     */
    typename boost::function_traits<F1>::result_type operator()(
            typename boost::function_traits<F1>::arg1_type,
            typename boost::function_traits<F1>::arg2_type,
            ...) const;

    /**
     * @brief Call operator matching the signature of the function type
     *  specified as second.
     *
     * This will in turn invoke the call operator of the second functor that
     * was passed to the constructor.
     */
    typename boost::function_traits<F2>::result_type operator()(
            typename boost::function_traits<F2>::arg1_type,
            typename boost::function_traits<F2>::arg2_type,
            ...) const;
};

} }

#endif // DOXY

