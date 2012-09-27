/*==============================================================================
    Copyright (c) 2010 - 2011 Matt Calabrese
                  2001 - 2003 John Maddock
                  2001 - 2002 Jens Maurer

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_CONFIG_STD_LIB_HPP
#define BOOST_GENERIC_CONFIG_STD_LIB_HPP

#include <boost/generic/detail/nary_cat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/bool.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// The detectable configurations. Format is:
//   (unique_value)(cstring_name)(if_supported_bit)
#define BOOST_GENERIC_STD_LIB_unknown    (0)("unknown standard library")(0)
#define BOOST_GENERIC_STD_LIB_stl_port   (1)("STL Port")(0)
#define BOOST_GENERIC_STD_LIB_comeau     (2)("Comeau STL")(0)
#define BOOST_GENERIC_STD_LIB_rogue_wave (3)("Rogue Wave")(0)
#define BOOST_GENERIC_STD_LIB_libcpp     (4)("libc++")(0)
#define BOOST_GENERIC_STD_LIB_libstdcpp  (5)("libstdc++")(1)
#define BOOST_GENERIC_STD_LIB_sgi        (6)("SGI STL")(0)
#define BOOST_GENERIC_STD_LIB_msl        (7)("MSL")(0)
#define BOOST_GENERIC_STD_LIB_vacpp      (8)("VACPP")(0)
#define BOOST_GENERIC_STD_LIB_modena     (9)("Modena")(0)
#define BOOST_GENERIC_STD_LIB_dinkumware (10)("Dinkumware")(0)

// Yields the ID of the detected standard library
#define BOOST_GENERIC_STD_LIB_ID()                                             \
BOOST_GENERIC_STD_LIB_ID_OF( BOOST_GENERIC_STD_LIB )

// Yields the name of the detected standard library (as a c-string)
#define BOOST_GENERIC_STD_LIB_NAME()                                           \
BOOST_GENERIC_STD_LIB_NAME_OF( BOOST_GENERIC_STD_LIB )

// Yields 1 if a specific standard library was detected, else 0
#define BOOST_GENERIC_STD_LIB_IS_KNOWN()                                       \
BOOST_PP_BOOL( BOOST_GENERIC_STD_LIB_ID() )

// Yields an integer identifier of a specified standard library
#define BOOST_GENERIC_STD_LIB_ID_OF( name )                                    \
BOOST_PP_SEQ_ELEM( 0, BOOST_PP_CAT( BOOST_GENERIC_STD_LIB_, name ) )

// Yields the name of a specified standard library (as a c-string)
#define BOOST_GENERIC_STD_LIB_NAME_OF( name )                                  \
BOOST_PP_SEQ_ELEM( 1, BOOST_PP_CAT( BOOST_GENERIC_STD_LIB_, name ) )

// Yields a 1 if the current detected standard library is supported, else 0
#define BOOST_GENERIC_STD_LIB_IS_SUPPORTED()                                   \
BOOST_PP_SEQ_ELEM                                                              \
( 2                                                                            \
, BOOST_PP_CAT( BOOST_GENERIC_STD_LIB_, BOOST_GENERIC_STD_LIB )                \
)

// Yields 1 if the detected standard library matches the parameter, else 0
#define BOOST_GENERIC_STD_LIB_IS( name )                                       \
BOOST_PP_EQUAL( BOOST_GENERIC_STD_LIB_ID()                                     \
              , BOOST_GENERIC_STD_LIB_ID_OF( name )                            \
              )

// Yields a compiler error if the detected standard library is not supported
#define BOOST_GENERIC_ASSERT_STD_LIB_IS_NOT_SUPPORTED()                        \
static_assert( false, "Standard library: " BOOST_GENERIC_STD_LIB_NAME()        \
                      " is not supported by Boost.Generic."                    \
             );

// Yields 1 if concepts are to be emulated, else 0
#define BOOST_GENERIC_CONFIG_STD_LIB_EMULATE_CONCEPTS()                        \
BOOST_PP_BITOR                                                                 \
( defined( BOOST_GENERIC_FORCE_CONCEPT_EMULATION )                             \
, BOOST_PP_CAT( BOOST_GENERIC_CONFIG_STD_LIB_EMULATE_CONCEPTS_                 \
              , BOOST_GENERIC_STD_LIB                                          \
              )                                                                \
)

// Yields 1 if an std::array iterator is a raw pointer, else 0
#define BOOST_GENERIC_CONFIG_STD_LIB_ARRAY_ITERATOR_IS_POINTER()               \
BOOST_PP_CAT( BOOST_GENERIC_CONFIG_STD_LIB_ARRAY_ITERATOR_IS_POINTER_          \
            , BOOST_GENERIC_STD_LIB                                            \
            )

// Yields 1 if an std::vector iterator is a raw pointer, else 0
#define BOOST_GENERIC_CONFIG_STD_LIB_VECTOR_ITERATOR_IS_POINTER()              \
BOOST_PP_CAT( BOOST_GENERIC_CONFIG_STD_LIB_VECTOR_ITERATOR_IS_POINTER_         \
            , BOOST_GENERIC_STD_LIB                                            \
            )

// Yields 1 if an std::array iterator and std::vector iterator are the same,
// else 0
#define BOOST_GENERIC_CONFIG_STD_LIB_VECTOR_ITERATOR_IS_ARRAY_ITERATOR()       \
BOOST_PP_CAT( BOOST_GENERIC_CONFIG_STD_LIB_VECTOR_ITERATOR_IS_ARRAY_ITERATOR_  \
            , BOOST_GENERIC_STD_LIB                                            \
            )

// Yields the config header
#define BOOST_GENERIC_CONFIG_STD_LIB_HEADER()                                  \
BOOST_GENERIC_DETAIL_NARY_CAT                                                  \
( <boost/generic/config/std_lib/detail/_, BOOST_GENERIC_STD_LIB, _.hpp> )

// If the user explicitly specified a standard library, use that
// ToDo: Gracefully handle when a user specifies a name that we don't recognize
#ifndef BOOST_GENERIC_STD_LIB

// First include <cstddef> to determine if some version of STLport is in use as
// the std lib (do not rely on this header being included since users can
// short-circuit this header if they know whose std lib they are using.)
#include <cstddef>

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
// STLPort library; this _must_ come first, otherwise since
// STLport typically sits on top of some other library, we
// can end up detecting that first rather than STLport:
#define BOOST_GENERIC_STD_LIB stl_port

#else

// If our std lib was not some version of STLport, then include <utility> as it
// is about the smallest of the std lib headers that includes real C++ stuff.
// (Some std libs do not include their C++-related macros in <cstddef> so this
// additional include makes sure we get those definitions)
// (again do not rely on this header being included since users can
// short-circuit this header if they know whose std lib they are using.)
#include <boost/config/no_tr1/utility.hpp>

#if defined(__LIBCOMO__)
// Comeau STL:
#define BOOST_GENERIC_STD_LIB comeau

#elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
// Rogue Wave library:
#define BOOST_GENERIC_STD_LIB rogue_wave

#elif defined(_LIBCPP_VERSION)
// libc++
#define BOOST_GENERIC_STD_LIB libcpp

#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
// GNU libstdc++ 3
#define BOOST_GENERIC_STD_LIB libstdcpp

#elif defined(__STL_CONFIG_H)
// generic SGI STL
#define BOOST_GENERIC_STD_LIB sgi

#elif defined(__MSL_CPP__)
// MSL standard lib:
#define BOOST_GENERIC_STD_LIB msl

#elif defined(__IBMCPP__)
// take the default VACPP std lib
#define BOOST_GENERIC_STD_LIB vacpp

#elif defined(MSIPL_COMPILE_H)
// Modena C++ standard library
#define BOOST_GENERIC_STD_LIB modena

#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
// Dinkumware Library (has to appear after any possible replacement libraries):
#define BOOST_GENERIC_STD_LIB dinkumware

#else
// Unknown standard library
#define BOOST_GENERIC_STD_LIB unknown

#endif // End standard library checks

#endif // End STL Port check

#endif // End check for explicit standard library specification

// Include the standard-library-specific config information
#include BOOST_GENERIC_CONFIG_STD_LIB_HEADER()

#endif // BOOST_GENERIC_CONFIG_STD_LIB_HPP
