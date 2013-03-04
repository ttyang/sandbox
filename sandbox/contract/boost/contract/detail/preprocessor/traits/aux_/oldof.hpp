
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_OLDOF_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_OLDOF_HPP_

#include <boost/contract/aux_/config.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>

// PROTECTED //

// Make sure OLDOF symbol is not defined by users.
#ifdef BOOST_CONTRACT_DETAIL_PP_TRAITS_OLDOF
#   error ERROR_internal_macro_BOOST_CONTRACT_DETTAIL_PP_TRAITS_OLDOF_must_be_undefined
#endif

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_OLDOF_IS_BOOST_CONTRACT_DETAIL_PP_TRAITS_OLDOF \
    (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_OLDOF_REMOVE_BOOST_CONTRACT_DETAIL_PP_TRAITS_OLDOF \
    /* nothing */

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_OLDOF_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_OLDOF_IS_)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_OLDOF_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_OLDOF_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_OLDOF_REMOVE_)

#endif // #include guard

