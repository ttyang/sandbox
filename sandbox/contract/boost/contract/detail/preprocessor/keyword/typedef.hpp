
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_IS_typedef (1) /* unary */
#define typedef_BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_REMOVE_typedef /* nothing */
#define typedef_BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TYPEDEF_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TYPEDEF_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TYPEDEF_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TYPEDEF_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TYPEDEF_FRONT, typedef)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPEDEF_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TYPEDEF_BACK, typedef)

#endif // #include guard

