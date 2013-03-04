
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_IS_unsigned (1) /* unary */
#define unsigned_BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_REMOVE_unsigned /* nothing */
#define unsigned_BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_UNSIGNED_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_UNSIGNED_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_UNSIGNED_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_UNSIGNED_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_UNSIGNED_FRONT, unsigned)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_UNSIGNED_BACK, unsigned)

#endif // #include guard

