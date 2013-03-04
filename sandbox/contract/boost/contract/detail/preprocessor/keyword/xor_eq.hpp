
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_IS_xor_eq (1) /* unary */
#define xor_eq_BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_REMOVE_xor_eq /* nothing */
#define xor_eq_BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_EQ_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_EQ_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_EQ_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_EQ_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_EQ_FRONT, xor_eq)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_XOR_EQ_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_XOR_EQ_BACK, xor_eq)

#endif // #include guard

