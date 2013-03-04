
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_IS_for (1) /* unary */
#define for_BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_REMOVE_for /* nothing */
#define for_BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FOR_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FOR_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FOR_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FOR_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FOR_FRONT, for)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FOR_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FOR_BACK, for)

#endif // #include guard

