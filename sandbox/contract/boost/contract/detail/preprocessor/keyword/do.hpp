
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_IS_do (1) /* unary */
#define do_BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_REMOVE_do /* nothing */
#define do_BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DO_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DO_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DO_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DO_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DO_FRONT, do)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DO_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DO_BACK, do)

#endif // #include guard

