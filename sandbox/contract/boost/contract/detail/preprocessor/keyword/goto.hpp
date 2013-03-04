
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_IS_goto (1) /* unary */
#define goto_BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_REMOVE_goto /* nothing */
#define goto_BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_GOTO_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_GOTO_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_GOTO_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_GOTO_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_GOTO_FRONT, goto)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_GOTO_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_GOTO_BACK, goto)

#endif // #include guard

