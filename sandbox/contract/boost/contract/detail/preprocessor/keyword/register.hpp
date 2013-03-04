
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_IS_register (1) /* unary */
#define register_BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_REMOVE_register /* nothing */
#define register_BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REGISTER_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REGISTER_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REGISTER_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REGISTER_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REGISTER_FRONT, register)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REGISTER_BACK, register)

#endif // #include guard

