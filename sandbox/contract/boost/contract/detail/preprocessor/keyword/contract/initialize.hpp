
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_IS_initialize (1) /* unary */
#define initialize_BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_REMOVE_initialize /* nothing */
#define initialize_BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_INITIALIZE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_INITIALIZE_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_INITIALIZE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_INITIALIZE_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_INITIALIZE_FRONT, initialize)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_INITIALIZE_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_INITIALIZE_BACK, initialize)

#endif // #include guard

