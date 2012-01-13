
#ifndef BOOST_CLOSURE_DETAIL_PP_VOID_LIST_HPP_
#define BOOST_CLOSURE_DETAIL_PP_VOID_LIST_HPP_

#include <boost/closure/detail/preprocessor/keyword/void.hpp>
#include <boost/config.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/to_tuple.hpp>
#include <boost/preprocessor/variadic/size.hpp>

// PRIVATE //

// Argument: (token1)...
#define BOOST_CLOSURE_DETAIL_PP_VOID_LIST_FROM_SEQ_(unused, seq) \
    BOOST_PP_TUPLE_TO_LIST(BOOST_PP_SEQ_SIZE(seq), BOOST_PP_SEQ_TO_TUPLE(seq))

// Token: void | token1
#define BOOST_CLOSURE_DETAIL_PP_VOID_LIST_HANDLE_VOID_(is_void_macro, token) \
    BOOST_PP_IIF(is_void_macro(token), \
        BOOST_PP_NIL \
    , \
        (token, BOOST_PP_NIL) \
    )

// Token: (a)(b)... | empty | void | token
#define BOOST_CLOSURE_DETAIL_PP_VOID_LIST_HANDLE_SEQ_(is_void_macro, token) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(token), /* unary paren (a)... */ \
        BOOST_CLOSURE_DETAIL_PP_VOID_LIST_FROM_SEQ_ \
    , \
        BOOST_CLOSURE_DETAIL_PP_VOID_LIST_HANDLE_VOID_ \
    )(is_void_macro, token)

#ifdef BOOST_NO_VARIADIC_MACROS

#define BOOST_CLOSURE_DETAIL_PP_VOID_LIST_(is_void_macro, seq) \
    BOOST_CLOSURE_DETAIL_PP_VOId_LIST_HANDLE_SEQ_(is_void_macro, seq)

#else // variadic

// Argument: token1, ...
#define BOOST_CLOSURE_DETAIL_PP_VOID_LIST_FROM_VARIADIC_(unused, ...) \
    BOOST_PP_TUPLE_TO_LIST(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), (__VA_ARGS__))

#define BOOST_CLOSURE_DETAIL_PP_VOID_LIST_(is_void_macro, ...) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), 1), \
        BOOST_CLOSURE_DETAIL_PP_VOID_LIST_HANDLE_SEQ_ \
    , \
        BOOST_CLOSURE_DETAIL_PP_VOID_LIST_FROM_VARIADIC_ \
    )(is_void_macro, __VA_ARGS__)

#endif // variadic

#define BOOST_CLOSURE_DETAIL_PP_VOID_LIST_NEVER_(tokens) \
    0 /* void check always returns false */

// PUBLIC //

// NOTE: Empty list must always be represented is void (which is also a way to
// specify no function parameter) and it can never be empty because (1)
// IS_EMPTY(&var) fails (because of the leading non alphanumeric symbol) and
// (2) some compilers (MSVC) fail to correctly pass empty macro parameters
// even if they support variadic macros. Therefore, always using void to
// represent is more portable.

#ifdef BOOST_NO_VARIADIC_MACROS

// Expand `void | (a)(b)...` to pp-list `NIL | (a, (b, NIL))`.
#define BOOST_CLOSURE_DETAIL_PP_VOID_LIST(sign) \
    BOOST_CLOSURE_DETAIL_PP_VOID_LIST_( \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_VOID_BACK, sign)

// Expand `(a)(b)...` to pp-list `(a, (b, NIL))`.
#define BOOST_CLOSURE_DETAIL_PP_NON_VOID_LIST(seq) \
    BOOST_CLOSURE_DETAIL_PP_VOID_LIST_( \
            BOOST_CLOSURE_DETAIL_PP_VOID_LIST_NEVER_, seq)

#else // variadic

// Expand `void | (a)(b)... | a, b, ...` to pp-list `NIL | (a, (b, NIL))`.
#define BOOST_CLOSURE_DETAIL_PP_VOID_LIST(...) \
    BOOST_CLOSURE_DETAIL_PP_VOID_LIST_( \
            BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_VOID_BACK, __VA_ARGS__)

// Expand `(a)(b)... | a, b, ...` to pp-list `(a, (b, NIL))`.
#define BOOST_CLOSURE_DETAIL_PP_NON_VOID_LIST(...) \
    BOOST_CLOSURE_DETAIL_PP_VOID_LIST_( \
            BOOST_CLOSURE_DETAIL_PP_VOID_LIST_NEVER_, __VA_ARGS__)

#endif // variadic

#endif // #include guard

