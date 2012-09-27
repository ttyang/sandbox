/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_SUPPORT_HPP
#define BOOST_GENERIC_SUPPORT_HPP

#include <boost/config.hpp>

// ToDo: Remove this, add such a macro to Boost.Config
// Currently no compilers support this feature
#ifndef BOOST_NO_LAMBDA_IN_RETURN_TYPE
#define BOOST_NO_LAMBDA_IN_RETURN_TYPE
#endif

// The base requirements for BOOST_GENERIC_CONCEPT
// (should probably add extended SFINAE check as well)
#if !( defined( BOOST_NO_VARIADIC_MACROS ) )

#include <boost/generic/detail/is_recognized_arg.hpp>
#include <boost/generic/detail/param_id.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>

#if 0

#define BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_IMPL_UNREC(param_id) 1

// ToDo: Possibly produce error here if not recognized instead of yielding 1
#define BOOST_NO_BOOST_GENERIC_CONCEPT_PARAM( param_id )                       \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_RECOGNIZED_ARG( ( param_id ) )           \
            , BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_IMPL                       \
            , BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_IMPL_UNREC                 \
            )( param_id )


#else

#define BOOST_NO_BOOST_GENERIC_CONCEPT_PARAM( param_id )                       \
BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_IMPL( param_id )

#endif

#define BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_IMPL( param_id )                 \
BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_ ## param_id

#define BOOST_GENERIC_DETAIL_SPACED_ID_for         for
#define BOOST_GENERIC_DETAIL_SPACED_ID_for_typedef for typedef
#define BOOST_GENERIC_DETAIL_SPACED_ID_if          if
#define BOOST_GENERIC_DETAIL_SPACED_ID_if_not      if not
#define BOOST_GENERIC_DETAIL_SPACED_ID_if_typedef  if typedef
#define BOOST_GENERIC_DETAIL_SPACED_ID_typename    typename
#define BOOST_GENERIC_DETAIL_SPACED_ID_public      public
#define BOOST_GENERIC_DETAIL_SPACED_ID_try         try

#define BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_for         0
#define BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_for_typedef 0
#define BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_if          0
#define BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_if_not      0
#define BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_if_typedef  0
#define BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_typename    0
#define BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_public      0
#define BOOST_GENERIC_DETAIL_NO_CONCEPT_PARAM_try         0

#else // Else, BOOST_GENERIC_CONCEPT isn't supported

#define BOOST_NO_BOOST_GENERIC_CONCEPT

// Nothing is supported
#define BOOST_NO_BOOST_GENERIC_CONCEPT_PARAM( arg ) 1

#endif // End BOOST_GENERIC_CONCEPT support check

#endif // BOOST_GENERIC_SUPPORT_HPP
