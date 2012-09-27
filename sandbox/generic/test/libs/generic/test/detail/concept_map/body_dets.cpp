/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/concept_map/body_dets.hpp>

/////////////////////////
// Prepare Test Inputs //
/////////////////////////

#define INVALID_TYPEDEF_PARAM                                                  \
BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS( ( typedef (value_type) ) )

#define VALID_TYPEDEF_SPEC                                                     \
BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS( ( typedef int value_type ) )

#define VALID_TWO_TYPEDEF_SPEC                                                 \
BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS                                     \
( ( typedef int* iterator )                                                    \
, ( typedef int const* const_iterator )                                        \
)

#define VALID_FUNCTION_SPEC                                                    \
BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS( ( (void)(begin)() const, {} ) )

#define VALID_EVERYTHING                                                       \
BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS                                     \
( ( typedef int* iterator )                                                    \
, ( typedef int const* const_iterator )                                        \
, ( (void)(push_back)( (T&) container_, (value_type const&) value_ )           \
  , {                                                                          \
      container_.push_back( value_ );                                          \
    }                                                                          \
  )                                                                            \
, ( (iterator)(this(T) begin)() )                                              \
, ( (const_iterator)(this(T) begin)() const )                                  \
, ( (this(T))() )                                                              \
, ( explicit (this(T))() )                                                     \
, ( (this(T) destroy)() )                                                      \
, ( (operator foo)( (T&) a ) )                                                 \
, ( (T&)(this(T) operator assign)( (T const&) a ) )                            \
, ( explicit (operator bar)( (T&) a ) )                                        \
, ( (bool)(operator equal_to)( (T const&) a, (T const&) b ) )                  \
, ( (void*)(this(T) operator new)( (std::size_t) a, (T const&) b ) )           \
, ( (void)(this(T) operator delete_array)( (void*) a, (T const&) b ) )         \
)


#if BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IS_VALID( INVALID_TYPEDEF_PARAM )
#error Body considered valid with invalid an typedef specifier.
#endif

#if !BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IS_VALID( VALID_TYPEDEF_SPEC )
#error Body considered invalid with a typedef specifier.
#endif

#if !BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IS_VALID( VALID_FUNCTION_SPEC )
#error Body considered invalid with a function specifier.
#endif

#if !BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IS_VALID( VALID_EVERYTHING )
#error Body considered invalid with a complicated specifier list.
#endif
