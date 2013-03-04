
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_IS_return (1) /* unary */
#define return_BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_REMOVE_return /* nothing */
#define return_BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_RETURN_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_RETURN_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_RETURN_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_RETURN_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_RETURN_FRONT, return)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_RETURN_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_RETURN_BACK, return)

#endif // #include guard

