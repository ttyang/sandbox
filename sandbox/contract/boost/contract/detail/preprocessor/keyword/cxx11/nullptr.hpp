
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_IS_nullptr (1) /* unary */
#define nullptr_BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_REMOVE_nullptr /* nothing */
#define nullptr_BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_NULLPTR_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_NULLPTR_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_NULLPTR_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_NULLPTR_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_NULLPTR_FRONT, nullptr)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_NULLPTR_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_NULLPTR_BACK, nullptr)

#endif // #include guard

