
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_IS_static (1) /* unary */
#define static_BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_REMOVE_static /* nothing */
#define static_BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_STATIC_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_STATIC_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_STATIC_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_STATIC_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_STATIC_FRONT, static)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_STATIC_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_STATIC_BACK, static)

#endif // #include guard

