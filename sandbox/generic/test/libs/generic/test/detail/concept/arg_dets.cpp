/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/concept/arg_details.hpp>

/////////////////////////
// Prepare Test Inputs //
/////////////////////////

#define VALID_EMPTY_BODY                                                       \
BOOST_GENERIC_DETAIL_CONCEPT_DETS( (SameType)( (typename) T, (typename) U ) )

#define VALID_EVERYTHING                                                       \
BOOST_GENERIC_DETAIL_CONCEPT_DETS                                              \
( (Container)((class) T), ( public Regular< T > )                              \
, ( typename iterator, typename T::iterator )                                  \
, ( typename const_iterator, typename T::const_iterator )                      \
, ( typename value_type )                                                      \
, ( (ObjectType) other_value_type )                                            \
, ( (void)(push_back)( (T&) container_, (value_type const&) value_ ),          \
    {                                                                          \
      container_.push_back( value_ );                                          \
    }                                                                          \
  )                                                                            \
, ( typename this(T) size_type )                                               \
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
, ( axiom something )                                                          \
)

#if !BOOST_GENERIC_DETAIL_CONCEPT_DETS_IS_VALID( VALID_EMPTY_BODY )
#error Valid concept with empty body not considered valid.
#endif

#if !BOOST_GENERIC_DETAIL_CONCEPT_DETS_IS_VALID( VALID_EVERYTHING )
#error Valid complicated concept arguments not considered valid.
#endif
