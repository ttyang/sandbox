
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_IS_bool (1) /* unary */
#define bool_BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_REMOVE_bool /* nothing */
#define bool_BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BOOL_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BOOL_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BOOL_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BOOL_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BOOL_FRONT, bool)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_BOOL_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_BOOL_BACK, bool)

#endif // #include guard

