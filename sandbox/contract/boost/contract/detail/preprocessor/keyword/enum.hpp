
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_IS_enum (1) /* unary */
#define enum_BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_REMOVE_enum /* nothing */
#define enum_BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_ENUM_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_ENUM_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_ENUM_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_ENUM_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_ENUM_FRONT, enum)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_ENUM_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_ENUM_BACK, enum)

#endif // #include guard

