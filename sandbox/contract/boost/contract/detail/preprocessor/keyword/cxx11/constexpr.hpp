
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_IS_constexpr (1) /* unary */
#define constexpr_BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_REMOVE_constexpr /* nothing */
#define constexpr_BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONSTEXPR_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONSTEXPR_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONSTEXPR_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONSTEXPR_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONSTEXPR_FRONT, constexpr)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONSTEXPR_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONSTEXPR_BACK, constexpr)

#endif // #include guard

