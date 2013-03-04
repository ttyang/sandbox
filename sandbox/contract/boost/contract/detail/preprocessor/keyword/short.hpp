
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_IS_short (1) /* unary */
#define short_BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_REMOVE_short /* nothing */
#define short_BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SHORT_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SHORT_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SHORT_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SHORT_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SHORT_FRONT, short)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SHORT_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SHORT_BACK, short)

#endif // #include guard

