
#ifndef CONST_BLOCK_HPP_
#define CONST_BLOCK_HPP_

#include <boost/local_function.hpp>
#include <boost/local_function/detail/preprocessor/void_list.hpp>
#include <boost/local_function/detail/preprocessor/line_counter.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/cat.hpp>
#include <cassert>

// PRIVATE //

#define CONST_BLOCK_BIND_(r, unused, i, var) \
    BOOST_PP_COMMA_IF(i) const bind& var
    
#define CONST_BLOCK_(list) \
    void BOOST_LOCAL_FUNCTION( \
        BOOST_PP_IIF(BOOST_PP_LIST_IS_NIL(list), \
            void BOOST_PP_TUPLE_EAT(3) \
        , \
            BOOST_PP_LIST_FOR_EACH_I \
        )(CONST_BLOCK_BIND_, ~, list) \
    )

#define CONST_BLOCK_END_(id) \
    BOOST_LOCAL_FUNCTION_NAME(BOOST_PP_CAT(const_assert_, id)) \
    BOOST_PP_CAT(const_assert_, id)(); /* call local function immediately */

// PUBLIC //

// Arguments `void | var1, var2, ... | (var1) (var2) ...`.
#ifdef BOOST_NO_VARIADIC_MACROS
#   define CONST_BLOCK(void_or_seq) \
        CONST_BLOCK_(BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST(void_or_seq))
#else
#   define CONST_BLOCK(...) \
        CONST_BLOCK_(BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST(__VA_ARGS__))
#endif

#define CONST_BLOCK_END \
    CONST_BLOCK_END_(BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER)

#endif // #include guard

