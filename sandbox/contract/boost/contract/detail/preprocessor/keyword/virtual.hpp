
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_IS_virtual (1) /* unary */
#define virtual_BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_REMOVE_virtual /* nothing */
#define virtual_BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL_FRONT, virtual)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL_BACK, virtual)

#endif // #include guard

