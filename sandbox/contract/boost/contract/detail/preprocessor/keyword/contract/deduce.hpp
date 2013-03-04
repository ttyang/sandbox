
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_IS_deduce (1) /* unary */
#define deduce_BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_deduce /* nothing */
#define deduce_BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT, deduce)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_BACK, deduce)

#endif // #include guard

