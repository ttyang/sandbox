
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_IS_catch (1) /* unary */
#define catch_BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_REMOVE_catch /* nothing */
#define catch_BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT, catch)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_CATCH_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_BACK, catch)

#endif // #include guard

