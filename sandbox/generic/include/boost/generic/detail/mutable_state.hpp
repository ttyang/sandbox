/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_MUTABLE_STATE_HPP
#define BOOST_GENERIC_DETAIL_MUTABLE_STATE_HPP

#include <boost/mpl/apply.hpp>

namespace boost { namespace generic { namespace detail {

// The maximum number of times a mutable state can be modified
// Note: GCC 4.7 fails after 512 and Clang 3.1 fails only slightly beyond 512
constexpr unsigned max_mutations = 512;

// Mutation count is what associates a given mutation with the current number of
// mutations that have occurred. Inheritance is used so that when passing an
// instance of mutation count to a function, the most recent mutation is the
// best match.
template< unsigned Val = max_mutations >
struct mutation_count : mutation_count< Val - 1 > {};

template<> struct mutation_count< 0 > {};

template< class Operation, class PreviousStateHolder >
struct modify_mutable_state_holder
{
  static unsigned const value = PreviousStateHolder::value + 1;
  static mutation_count< value + 1 > next_index();
  typedef typename boost::mpl::apply
          < Operation, typename PreviousStateHolder::state >::type state;
};

template< class NewState, class PreviousStateHolder >
struct set_mutable_state_holder
{
  static unsigned const value = PreviousStateHolder::value + 1;
  static mutation_count< value + 1 > next_index();
  typedef NewState state;
};

template< class InitialState >
struct initial_mutable_state_holder
{
  static unsigned const value = 0;
  static mutation_count< 1 > next_index();
  typedef InitialState state;
};

} } }

#define BOOST_GENERIC_DETAIL_INITIALIZE_STATE( tag, ... )                      \
::boost::generic::detail::initial_mutable_state_holder< __VA_ARGS__ >          \
boost_generic_detail_get_mutable_state_holder                                  \
( tag, ::boost::generic::detail::mutation_count< 0 > const& );

#define BOOST_GENERIC_DETAIL_MODIFY_STATE( tag, mutator )                      \
::boost::generic::detail::modify_mutable_state_holder                          \
< mutator                                                                      \
, decltype                                                                     \
  ( boost_generic_detail_get_mutable_state_holder                              \
    ( tag(), ::boost::generic::detail::mutation_count<>() )                    \
  )                                                                            \
>                                                                              \
boost_generic_detail_get_mutable_state_holder                                  \
( tag                                                                          \
, decltype                                                                     \
  ( boost_generic_detail_get_mutable_state_holder                              \
    ( tag(), ::boost::generic::detail::mutation_count<>() ).next_index()       \
  ) const&                                                                     \
);

#define BOOST_GENERIC_DETAIL_SET_STATE( tag, ... )                             \
::boost::generic::detail::set_mutable_state_holder                             \
< __VA_ARGS__                                                                  \
, decltype                                                                     \
  ( boost_generic_detail_get_mutable_state_holder                              \
    ( tag(), ::boost::generic::detail::mutation_count<>() )                    \
  )                                                                            \
>                                                                              \
boost_generic_detail_get_mutable_state_holder                                  \
( tag                                                                          \
, decltype                                                                     \
  ( boost_generic_detail_get_mutable_state_holder                              \
    ( tag(), ::boost::generic::detail::mutation_count<>() ).next_index()       \
  ) const&                                                                     \
);

// TODO allow for namespace qualification
#define BOOST_GENERIC_DETAIL_GET_STATE( ... )                                  \
decltype                                                                       \
( boost_generic_detail_get_mutable_state_holder                                \
  ( __VA_ARGS__(), ::boost::generic::detail::mutation_count<>() )              \
)                                                                              \
::state

#endif // BOOST_GENERIC_DETAIL_MUTABLE_STATE_HPP
