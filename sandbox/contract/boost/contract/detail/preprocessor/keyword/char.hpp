
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_IS_char (1) /* unary */
#define char_BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_REMOVE_char /* nothing */
#define char_BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR_FRONT, char)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CHAR_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR_BACK, char)

#endif // #include guard

