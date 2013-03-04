
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_IS_decltype (1) /* unary */
#define decltype_BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_REMOVE_decltype /* nothing */
#define decltype_BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DECLTYPE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DECLTYPE_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DECLTYPE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DECLTYPE_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DECLTYPE_FRONT, decltype)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_DECLTYPE_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DECLTYPE_BACK, decltype)

#endif // #include guard

