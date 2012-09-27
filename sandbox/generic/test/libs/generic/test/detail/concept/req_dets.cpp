/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/concept/req_dets.hpp>
#include <boost/generic/detail/native_requirement.hpp> // ToDo: Remove

/////////////////////////
// Prepare Test Inputs //
/////////////////////////

#define INVALID_TYPENAME_PARAM                                                 \
BOOST_GENERIC_DETAIL_REQ_DETS( ( typename (value_type) ) )

#define VALID_REQ_EMPTY                                                        \
BOOST_GENERIC_DETAIL_REQ_DETS()

#define VALID_TYPENAME_REQ                                                     \
BOOST_GENERIC_DETAIL_REQ_DETS( ( typename value_type, int ) )

#define VALID_TWO_TYPENAME_REQ                                                 \
BOOST_GENERIC_DETAIL_REQ_DETS                                                  \
( ( typename iterator )                                                        \
, ( typename const_iterator )                                                  \
)

#define VALID_FUNCTION_REQ                                                     \
BOOST_GENERIC_DETAIL_REQ_DETS( ( (void)(begin)() const, {} ) )

#define VALID_EVERYTHING                                                       \
BOOST_GENERIC_DETAIL_REQ_DETS                                                  \
( ( typename iterator, typename T::iterator )                                  \
, ( typename const_iterator, typename T::const_iterator )                      \
, ( typename value_type )                                                      \
, ( (void)(push_back)( (T&) container_, (value_type const&) value_ )           \
  , {                                                                          \
      container_.push_back( value_ );                                          \
    }                                                                          \
  )                                                                            \
, ( typename this(T) size_type )                                               \
, ( (iterator)(this(T) begin)() )                                              \
, ( (const_iterator)(this(T) begin)() const )                                  \
, ( requires HasDereference< T > )                                             \
, ( (this(T))() )                                                              \
, ( explicit (this(T))() )                                                     \
, ( (this(T) destroy)() )                                                      \
, ( (operator foo)( (T&) a ) )                                                 \
, ( (T&)(this(T) operator assign)( (T const&) a ) )                            \
, ( explicit (operator bar)( (T&) a ) )                                        \
, ( (bool)(operator equal_to)( (T const&) a, (T const&) b ) )                  \
, ( (void*)(this(T) operator new)( (std::size_t) a, (T const&) b ) )           \
, ( (void)(this(T) operator delete_array)( (void*) a, (T const&) b ) )         \
, ( axiom something )                                                          \
)

#if BOOST_GENERIC_DETAIL_REQ_DETS_IS_VALID( INVALID_TYPENAME_PARAM )
#error Requirements considered valid with invalid typename param.
#endif

#if !BOOST_GENERIC_DETAIL_REQ_DETS_IS_VALID( VALID_REQ_EMPTY )
#error Nested type requirements considered invalid when no requirements are specified.
#endif

#if !BOOST_GENERIC_DETAIL_REQ_DETS_IS_VALID( VALID_TYPENAME_REQ )
#error Nested type requirements considered invalid with a typename requirement.
#endif

#if !BOOST_GENERIC_DETAIL_REQ_DETS_IS_VALID( VALID_FUNCTION_REQ )
#error Nested type requirements considered invalid with a function requirement.
#endif

#if !BOOST_GENERIC_DETAIL_REQ_DETS_IS_VALID( VALID_EVERYTHING )
#error Nested type requirements considered invalid with a complicated requirements list.
#endif
