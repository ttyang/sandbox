
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_IS_auto (1) /* unary */
#define auto_BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_auto /* nothing */
#define auto_BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT, auto)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_BACK, auto)

#endif // #include guard

