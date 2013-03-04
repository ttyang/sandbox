
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_IS_extern (1) /* unary */
#define extern_BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_REMOVE_extern /* nothing */
#define extern_BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_EXTERN_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_EXTERN_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_EXTERN_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_EXTERN_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_EXTERN_FRONT, extern)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTERN_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_EXTERN_BACK, extern)

#endif // #include guard

