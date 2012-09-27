/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_ASSERT_HPP
#define BOOST_GENERIC_ASSERT_HPP

//#include <boost/generic/detail/all_but_last_arg.hpp>
#include <boost/generic/detail/concept_is_valid.hpp>
#include <boost/generic/detail/instantiate.hpp>
#include <boost/generic/detail/is_concept.hpp>
//#include <boost/generic/detail/last_arg.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/variadic_stringize.hpp>

#define BOOST_GENERIC_ASSERT( ... )                                            \
BOOST_GENERIC_ASSERT_MSG_IMPL                                                  \
( (__VA_ARGS__)                                                                \
, "requires " BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE( __VA_ARGS__ )           \
)

#define BOOST_GENERIC_ASSERT_NOT( ... )                                        \
BOOST_GENERIC_ASSERT_NOT_MSG_IMPL                                              \
( (__VA_ARGS__)                                                                \
, "requires !" BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE( __VA_ARGS__ )          \
)

#define BOOST_GENERIC_ASSERT_MSG( ... )                                        \
BOOST_GENERIC_ASSERT_MSG_IMPL                                                  \
( ( BOOST_GENERIC_DETAIL_ALL_BUT_LAST_ARG( __VA_ARGS__ ) )                     \
, BOOST_GENERIC_DETAIL_LAST_ARG( __VA_ARGS__ )                                 \
)

#define BOOST_GENERIC_ASSERT_MSG_IMPL( concept_, msg )                         \
static_assert                                                                  \
( ::boost::generic::detail::is_concept                                         \
  < BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_ ) >::value                     \
, "Boost.Generic Assert expected a concept, but instead got: "                 \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE concept_                             \
);                                                                             \
static_assert                                                                  \
( ::boost::mpl::or_                                                            \
  < ::boost::mpl::not_< ::boost::generic::detail::is_concept                   \
                        < BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_ ) >      \
                      >                                                        \
  , ::boost::generic::detail::concept_is_valid                                 \
    < BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_ ) >                          \
  >::value                                                                     \
, msg                                                                          \
);                                                                             \
static_assert                                                                  \
( ::boost::mpl::identity                                                       \
  < decltype                                                                   \
    ( ::boost::generic::detail::instantiate_if_auto                            \
      < BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_ ) >()                      \
    )                                                                          \
  >::type::value                                                               \
, "This message should never be seen."                                         \
);                                                                             \
static_assert                                                                  \
( ::boost::mpl::identity                                                       \
  < decltype                                                                   \
    ( ::boost::generic::detail::instantiate_map                                \
      < BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_ ) >()                      \
    )                                                                          \
  >::type::value                                                               \
, "This message should never be seen."                                         \
)

#define BOOST_GENERIC_ASSERT_NOT_MSG_IMPL( concept_, msg )                     \
static_assert                                                                  \
( ::boost::generic::detail::is_concept                                         \
  < BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_ ) >::value                     \
, "Boost.Generic Assert expected a concept, but instead got: "                 \
  BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE concept_                             \
);                                                                             \
static_assert                                                                  \
( ::boost::mpl::not_                                                           \
  < ::boost::mpl::and_                                                         \
    <  ::boost::generic::detail::is_concept                                    \
       < BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_ ) >                       \
    , ::boost::generic::detail::concept_is_valid                               \
      < BOOST_GENERIC_DETAIL_REMOVE_PAREN( concept_ ) >                        \
    >                                                                          \
  >::value                                                                     \
, msg                                                                          \
)

#endif // BOOST_GENERIC_ASSERT_HPP
