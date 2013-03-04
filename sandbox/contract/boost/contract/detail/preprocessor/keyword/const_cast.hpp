
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_IS_const_cast (1) /* unary */
#define const_cast_BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_REMOVE_const_cast /* nothing */
#define const_cast_BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_CAST_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_CAST_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_CAST_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_CAST_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_CAST_FRONT, const_cast)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_CAST_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_CAST_BACK, const_cast)

#endif // #include guard

