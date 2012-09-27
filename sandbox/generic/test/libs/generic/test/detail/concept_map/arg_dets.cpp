/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/concept_map/arg_dets.hpp>

/////////////////////////
// Prepare Test Inputs //
/////////////////////////

#define VALID_EMPTY                                                            \
BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS( (Container)(T) )

#define VALID_EMPTY_WITH_TEMPLATE                                              \
BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS                                      \
( ( template ( (class) T ) ), (Container)(T) )

#define VALID_EVERYTHING                                                       \
BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS                                      \
( (Container)(T)                                                               \
, ( typedef int* iterator )                                                    \
, ( typedef int const* const_iterator )                                        \
, ( typedef int value_type )                                                   \
, ( (void)(push_back)( (T&) container_, (value_type const&) value_ ),          \
    {                                                                          \
      container_.push_back( value_ );                                          \
    }                                                                          \
  )                                                                            \
, ( (iterator)(this(T) begin)() )                                              \
, ( (const_iterator)(this(T) begin)() const )                                  \
, ( (this(T))() )                                                              \
, ( explicit (this(T))() )                                                     \
, ( (this(T) destroy)() )                                                      \
, ( (operator foo)( (T&) a ) )                                                 \
, ( explicit (operator bar)( (T&) a ) )                                        \
, ( (bool)(operator equal_to)( (T const&) a, (T const&) b ) )                  \
, ( (void*)(this(T) operator new)( (std::size_t) a, (T const&) b ) )           \
, ( (void)(this(T) operator delete_array)( (void*) a, (T const&) b ) )         \
)

#if !BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_IS_VALID( VALID_EMPTY )
#error Valid empty concept map arguments not considered valid.
#endif

#if !BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_IS_VALID( VALID_EMPTY_WITH_TEMPLATE )
#error Valid empty concept map template, arguments not considered valid.
#endif

#if !BOOST_GENERIC_CONCEPT_MAP_DETAIL_ARG_DETS_IS_VALID( VALID_EVERYTHING )
#error Valid complicated concept map arguments not considered valid.
#endif
