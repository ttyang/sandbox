
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_IS_double (1) /* unary */
#define double_BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_REMOVE_double /* nothing */
#define double_BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DOUBLE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DOUBLE_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DOUBLE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DOUBLE_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DOUBLE_FRONT, double)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DOUBLE_BACK, double)

#endif // #include guard

