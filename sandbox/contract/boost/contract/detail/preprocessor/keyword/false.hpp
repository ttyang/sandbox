
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_IS_false (1) /* unary */
#define false_BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_REMOVE_false /* nothing */
#define false_BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FALSE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FALSE_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FALSE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FALSE_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FALSE_FRONT, false)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_FALSE_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FALSE_BACK, false)

#endif // #include guard

