
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_IS_mutable (1) /* unary */
#define mutable_BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_REMOVE_mutable /* nothing */
#define mutable_BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_MUTABLE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_MUTABLE_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_MUTABLE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_MUTABLE_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_MUTABLE_FRONT, mutable)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_MUTABLE_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_MUTABLE_BACK, mutable)

#endif // #include guard

