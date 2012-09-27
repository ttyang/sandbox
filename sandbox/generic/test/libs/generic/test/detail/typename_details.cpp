/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/typename_details.hpp>
#include <boost/type_traits/is_same.hpp>

#define EMPTY_DETS                                                             \
BOOST_GENERIC_DETAIL_TYPENAME_DETS()

#define NOT_TYPENAME_DETS                                                      \
BOOST_GENERIC_DETAIL_TYPENAME_DETS( not_typename name )

#define PARENTHESIZED_NAME_DETS                                                \
BOOST_GENERIC_DETAIL_TYPENAME_DETS( typename (name) )

#define EMPTY_NAME_DETS                                                        \
BOOST_GENERIC_DETAIL_TYPENAME_DETS( typename )

#define EMPTY_DEFAULT_DETS                                                     \
BOOST_GENERIC_DETAIL_TYPENAME_DETS( typename name, )

#define VALID_DETS                                                             \
BOOST_GENERIC_DETAIL_TYPENAME_DETS( typename name )

#define VALID_WITH_DEFAULT_DETS                                                \
BOOST_GENERIC_DETAIL_TYPENAME_DETS( typename name, int )

#define INVALID_NESTED_DETS                                                    \
BOOST_GENERIC_DETAIL_TYPENAME_DETS( typename this name, int )

#define NESTED_WITH_DEFAULT_DETS                                               \
BOOST_GENERIC_DETAIL_TYPENAME_DETS( typename this(foo) name, int )

#define VALID_NESTED_DETS                                                      \
BOOST_GENERIC_DETAIL_TYPENAME_DETS( typename this(foo) name )

#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( EMPTY_DETS )
#error Empty arg detected as valid typename requirement.
#endif

#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( NOT_TYPENAME_DETS )
#error Non-typename detected as valid typename requirement.
#endif

#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( PARENTHESIZED_NAME_DETS )
#error Typename with parenthesized name detected as valid typename requirement.
#endif

#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( EMPTY_NAME_DETS )
#error Typename with no name detected as valid typename requirement.
#endif

#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( EMPTY_DEFAULT_DETS )
#error Typename with empty default detected as valid typename requirement.
#endif




#if !BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( VALID_DETS )
#error Valid typename requirement detected as invalid.
#endif

#if !BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID_WITHOUT_DEFAULT( VALID_DETS )
#error Valid typename requirement detected as having a default.
#endif


#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_HAS_DEFAULT( VALID_DETS )
#error Valid typename requirement without default detected as having default.
#endif

#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_NESTED( VALID_DETS )
#error Valid typename requirement without default detected as nested.
#endif

#if !BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( VALID_WITH_DEFAULT_DETS )
#error Valid typename requirement with default detected as invalid.
#endif

#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID_WITHOUT_DEFAULT( VALID_WITH_DEFAULT_DETS )
#error Valid typename requirement with default detected as not having a default.
#endif


#if !BOOST_GENERIC_DETAIL_TYPENAME_DETS_HAS_DEFAULT( VALID_WITH_DEFAULT_DETS )
#error Valid typename requirement with default detected as not having default.
#endif

#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_NESTED( VALID_WITH_DEFAULT_DETS )
#error Valid typename requirement with default detected as nested.
#endif

/////
#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( INVALID_NESTED_DETS )
#error Invalid nested typename requirement detected as valid.
#endif

#if BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( NESTED_WITH_DEFAULT_DETS )
#error Nested typename requirement with default detected as invalid.
#endif

#if !BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( VALID_NESTED_DETS )
#error Valid nested typename requirement detected as invalid.
#endif

#if !BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_NESTED( VALID_NESTED_DETS )
#error Valid nested typename requirement detected as not nested.
#endif

struct name {};

static_assert
( boost::is_same< name, BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( VALID_DETS ) >
  ::value
, "typename requirement \"name\" not deduced correctly."
);

static_assert
( boost::is_same
  < name, BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( VALID_WITH_DEFAULT_DETS ) >
  ::value
, "typename requirement \"name\" not deduced correctly."
);

static_assert
( boost::is_same
  < int
  , BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT( VALID_WITH_DEFAULT_DETS )
  >
  ::value
, "typename requirement \"default\" not deduced correctly."
);


#define VALID_VISIT_MACRO( name_, default_ )                                   \
static_assert( BOOST_GENERIC_DETAIL_IS_EMPTY( default_ )                       \
             , "Nonempty default parameter in visit without a default"         \
             );                                                                \
static_assert                                                                  \
( boost::is_same< name, name_ >                                                \
  ::value                                                                      \
, "typename requirement \"name\" not deduced correctly."                       \
);

// ToDo: Define this macro
#define INVALID_VISIT_MACRO( ... )

BOOST_GENERIC_DETAIL_TYPENAME_DETS_VISIT
( VALID_DETS, VALID_VISIT_MACRO, INVALID_VISIT_MACRO )
