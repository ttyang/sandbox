
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_IS_public (1) /* unary */
#define public_BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_REMOVE_public /* nothing */
#define public_BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_FRONT, public)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_BACK, public)

#endif // #include guard

