
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_IS_break (1) /* unary */
#define break_BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_REMOVE_break /* nothing */
#define break_BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BREAK_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BREAK_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BREAK_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BREAK_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BREAK_FRONT, break)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BREAK_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BREAK_BACK, break)

#endif // #include guard

