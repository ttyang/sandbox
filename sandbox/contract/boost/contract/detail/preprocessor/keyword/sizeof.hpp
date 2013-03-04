
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_IS_sizeof (1) /* unary */
#define sizeof_BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_REMOVE_sizeof /* nothing */
#define sizeof_BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SIZEOF_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SIZEOF_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SIZEOF_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SIZEOF_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SIZEOF_FRONT, sizeof)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_SIZEOF_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_SIZEOF_BACK, sizeof)

#endif // #include guard

