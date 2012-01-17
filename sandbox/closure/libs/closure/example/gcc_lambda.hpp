
//[example_gcc_lambda_hpp
// Header: gcc_lambda.hpp
#ifndef GCC_LAMBDA_HPP_
#define GCC_LAMBDA_HPP_

#include <boost/closure.hpp>

// PUBLIC //

// void | [const] bind[&] var_ | type_ name_ [, default value_] | return type_
#define GCC_LAMBDA(...) \
    ({ /* open a GCC expression statement (GCC extension only) */ \
        BOOST_CLOSURE(GCC_LAMBDA_RETURN_( \
                BOOST_CLOSURE_DETAIL_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))

#define GCC_LAMBDA_END \
        BOOST_CLOSURE_END(BOOST_PP_CAT(gcc_lambda_, __LINE__)) \
        BOOST_PP_CAT(gcc_lambda, __LINE__); /* expr stmt returns the lambda */ \
    }) /* close the GCC expression statement (GCC extension only) */

// PRIVATE //

#define GCC_LAMBDA_RETURN_(sign_seq) \
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_RETURN_FRONT( \
            BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_REVERSE(sign_seq))), \
        sign_seq /* keep result type specified by user */ \
    , \
        sign_seq (return void) /* automatically void if no return specified */ \
    )

#endif // #include guard
//]

