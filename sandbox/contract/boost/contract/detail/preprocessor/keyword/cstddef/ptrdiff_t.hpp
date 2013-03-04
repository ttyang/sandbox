
/**************************************************************/
/* WARNING:   FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "keyword/generate.py" */
/**************************************************************/

#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_HPP_

#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/add.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PRIVATE //

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_IS_ptrdiff_t (1) /* unary */
#define ptrdiff_t_BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_IS (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_REMOVE_ptrdiff_t /* nothing */
#define ptrdiff_t_BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_REMOVE /* nothing */

// PUBLIC //

// Is.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PTRDIFF_T_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_IS_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PTRDIFF_T_BACK(token) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_BACK(token, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_IS)

// Remove.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PTRDIFF_T_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_REMOVE_)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_REMOVE_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PTRDIFF_T_BACK, \
            _BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_REMOVE)

// Add.

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_ADD_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PTRDIFF_T_FRONT, ptrdiff_t)

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_ADD_BACK(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK(tokens, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PTRDIFF_T_BACK, ptrdiff_t)

#endif // #include guard

