
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_IS_using (1) /* unary */
#define using_BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_REMOVE_using /* nothing */
#define using_BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_USING_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_USING_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_USING_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_USING_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_USING_FRONT, using)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_USING_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_USING_BACK, using)

#endif // #include guard

