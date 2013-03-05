
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#if !BOOST_PP_IS_ITERATING
#   ifndef BOOST_CONTRACT_AUX_SIGNATURE_TRAITS_HPP_
#       define BOOST_CONTRACT_AUX_SIGNATURE_TRAITS_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/aux_/arg_const.hpp>
#include <boost/contract/aux_/result_const.hpp>
#include <boost/contract/aux_/mpl_assert.hpp>
#include <boost/contract/aux_/preprocessor/iteration/params.hpp>
#include <boost/function.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <list>

#define BOOST_CONTRACT_comma_class_Base(z, n, unused) \
    , class BOOST_PP_CAT(Base, n)
#define BOOST_CONTRACT_comma_Base(z, n, unused) \
    , BOOST_PP_CAT(Base, n)

#define BOOST_CONTRACT_Arg(z, n, unused) \
    BOOST_PP_CAT(Arg, n)
#define BOOST_CONTRACT_comma_typename_Arg(z, n, unused) \
    , typename BOOST_PP_CAT(Arg, n)
#define BOOST_CONTRACT_typedef_arg_types(z, n, unused) \
    typedef BOOST_PP_CAT(Arg, n) BOOST_PP_CAT(arg_type, n) ; \
    typedef typename arg_const< BOOST_PP_CAT(Arg, n) >::type \
            BOOST_PP_CAT(const_arg_type, n) ;
#define BOOST_CONTRACT_const_arg_type(z, n, unused) \
    BOOST_PP_CAT(const_arg_type, n)
#define BOOST_CONTRACT_comma_const_arg_type(z, n, unused) \
    , BOOST_PP_CAT(const_arg_type, n)

#define BOOST_CONTRACT_typedef_constructor_and_subcontracted_oldof_type() \
    typedef \
        bound_postcondition_type \
        ( * constructor_oldof_type ) \
        ( \
            body_type \
            , const_obj_type const \
            BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY, \
                    BOOST_CONTRACT_comma_const_arg_type, ~) \
        ) \
    ; \
    typedef \
        std::list< bound_postcondition_type > \
        ( Class:: \
          * subcontracted_oldof_type ) \
        ( \
            body_type \
            BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY, \
                    BOOST_CONTRACT_comma_const_arg_type, ~) \
        ) \
        const \
        BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE \
    ;
#define BOOST_CONTRACT_typedef_derived_traits_base(z, n, unused) \
    typedef \
        signature_traits< \
            Result \
                    ( BOOST_PP_CAT(Base, n) :: * ) \
                    ( BOOST_PP_ENUM(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY, \
                            BOOST_CONTRACT_Arg, ~) ) \
                    BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST \
                    BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE \
        > \
        BOOST_PP_CAT(base, n) \
    ;

namespace boost { namespace contract { namespace aux {

template< typename F >
struct signature_traits
{
    BOOST_CONTRACT_AUX_MPL_ASSERT_MSG(sizeof(F) == 0,
ERROR_too_many_function_parameters_see_BOOST_CONTRACT_CONFIG_FUNCTION_ARITY_MAX,
            (types< F >));
};

// NOTE: In principle, this and the template above could be merged into one
// making the base tparam optional (providing a default parameter like
// void_base for them). Then template specializations could be used to program
// derived_signature_traits as a special signature_traits that specified
// non-void base types. This was tried, it worked on GCC but too many
// specializations confused MSVC (plus too many specializations might slow down
// the compiler more).
template<
    typename F
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_comma_class_Base, ~)
>
struct derived_signature_traits
{
    BOOST_CONTRACT_AUX_MPL_ASSERT_MSG(sizeof(F) == 0,
ERROR_too_many_function_parameters_see_BOOST_CONTRACT_CONFIG_FUNCTION_ARITY_MAX,
            (types< F /* can't print bases b/c could be more than 4 */ >));
};

} } } // namespace

#       define BOOST_PP_ITERATION_PARAMS_1 \
                BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_ARITY( \
                        "boost/contract/aux_/signature_traits.hpp")
#       include BOOST_PP_ITERATE()
#       undef BOOST_CONTRACT_comma_class_Base
#       undef BOOST_CONTRACT_comma_Base
#       undef BOOST_CONTRACT_Arg
#       undef BOOST_CONTRACT_comma_typename_Arg
#       undef BOOST_CONTRACT_typedef_arg
#       undef BOOST_CONTRACT_const_arg_type
#       undef BOOST_CONTRACT_comma_const_arg_type
#       undef BOOST_CONTRACT_typedef_constructor_and_subcontracted_oldof_type
#       undef BOOST_CONTRACT_typedef_derived_traits_base
#   endif // #include guard
#elif BOOST_PP_ITERATION_DEPTH() == 1 // arity iteration
#   define BOOST_PP_ITERATION_PARAMS_2 \
            BOOST_CONTRACT_AUX_PP_ITERATION_PARAMS_CV_MEMBER( \
                    "boost/contract/aux_/signature_traits.hpp")
#   include BOOST_PP_ITERATE()
#elif BOOST_PP_ITERATION_DEPTH() == 2 // free, member, cv iteration
// Define BOOST_CONTRACT_AUX_PP_ITERATION_ARITY (from iteration frame 1).
#   include <boost/contract/aux_/preprocessor/iteration/arity_1.hpp>
// Define ..._IS_MEMBER, ..._MEMBER_CONST, and ..._MEMBER_VOLATILE (iter 2).
#   include <boost/contract/aux_/preprocessor/iteration/cv_member_2.hpp>

namespace boost { namespace contract { namespace aux {

template<
    typename Result
    BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER)
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER, class Class)
    BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
            BOOST_CONTRACT_comma_typename_Arg, ~)
>
struct signature_traits<
    Result
    ( BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER, Class::) * )
    (
        BOOST_PP_ENUM(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                BOOST_CONTRACT_Arg, ~)
    )
    BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST
    BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE
> {
    // Function types.
    typedef Result result_type;
    typedef typename result_const< Result >::type const_result_type;
    BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
            BOOST_CONTRACT_typedef_arg_types, ~)

    // Object types.
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER,
        typedef Class class_type;
        typedef Class BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST
                BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE*
                cv_qualified_obj_type;
        typedef Class const BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE*
                const_obj_type;
    )
    
    // Body function types.
    typedef
        Result
        ( BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER, Class::)
          * body_type )
        (
            BOOST_PP_ENUM(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                    BOOST_CONTRACT_Arg, ~)
        )
        BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST
        BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE
    ;

    // Precondition function types.
    typedef
        void
        ( BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER, Class::)
          * precondition_type )
        (
            body_type
            BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                    BOOST_CONTRACT_comma_const_arg_type, ~)
        )
        BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER, const)
        BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE
    ;
    typedef
        void
        (* static_precondition_type)
        (
            body_type
            BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                    BOOST_CONTRACT_comma_const_arg_type, ~)
        )
    ;

    // Postcondition (and old-of) function types.
    typedef
        boost::function<
            void
            (
                BOOST_PP_ENUM(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                        BOOST_CONTRACT_const_arg_type, ~)
                BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY)
                const_result_type
            )
        >
        bound_postcondition_type
    ;
    typedef
        bound_postcondition_type
        ( BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER, Class::)
          * oldof_type )
        (
            body_type
            BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                    BOOST_CONTRACT_comma_const_arg_type, ~)
        )
        BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER, const)
        BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE
    ;
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER,
        BOOST_CONTRACT_typedef_constructor_and_subcontracted_oldof_type
    ,
        BOOST_PP_EMPTY
    )()

    // NOTE: Static class invariant is defined even if not a member because
    // this signature class for free-functions is also used for static member
    // functions (for simplicity so to avoid defining another set signatures
    // and because static member signature does not need class/object types).
    typedef void ( * static_class_invariant_type ) ( ) ;
    
    // Dynamic const or const volatile class invariant.
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER,
        typedef void ( Class:: * class_invariant_type ) ( ) const
                BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE ;
    )
};

template<
    typename Result
    BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER)
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER, class Class)
    BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
            BOOST_CONTRACT_comma_typename_Arg, ~)
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_comma_class_Base, ~)
>
struct derived_signature_traits<
    Result
    ( BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER, Class::) * )
    (
        BOOST_PP_ENUM(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                BOOST_CONTRACT_Arg, ~)
    )
    BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST
    BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_comma_Base, ~)
>
    : signature_traits<
        Result
        ( BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_ITERATION_IS_MEMBER, Class::)
          * )
        (
            BOOST_PP_ENUM(BOOST_CONTRACT_AUX_PP_ITERATION_ARITY,
                    BOOST_CONTRACT_Arg, ~)
        )
        BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_CONST
        BOOST_CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE
    >
{
    BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX,
            BOOST_CONTRACT_typedef_derived_traits_base, ~)
};

} } } // namespace

#else // iteration
#   error "INTERNAL ERROR: iteration index out-of-range"
#endif // iteration

