
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_IS_while (1) /* unary */
#define while_BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_REMOVE_while /* nothing */
#define while_BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_WHILE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_WHILE_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_WHILE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_WHILE_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_WHILE_FRONT, while)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_WHILE_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_WHILE_BACK, while)

#endif // #include guard

