
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_IS_private (1) /* unary */
#define private_BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_REMOVE_private /* nothing */
#define private_BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE_FRONT, private)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE_BACK, private)

#endif // #include guard

