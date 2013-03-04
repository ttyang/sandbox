
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_IS_long (1) /* unary */
#define long_BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_REMOVE_long /* nothing */
#define long_BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_LONG_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_LONG_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_LONG_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_LONG_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_LONG_FRONT, long)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_LONG_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_LONG_BACK, long)

#endif // #include guard

