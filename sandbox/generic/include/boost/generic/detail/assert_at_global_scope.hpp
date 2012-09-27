/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE_HPP
#define BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

void boost_generic_detail_global_scope_check() {}

namespace boost_generic_detail_scope_checker {

template< void (&L)(), void (&R)() >
struct boost_generic_detail_is_same_fun { static bool const value = false; };

template< void (&L)() >
struct boost_generic_detail_is_same_fun< L, L >
{
  static bool const value = true;
};

namespace {

void boost_generic_detail_global_scope_check() {}

}

}

#endif

#define BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE( message )                 \
namespace boost_generic_detail_scope_checker {                                 \
static_assert                                                                  \
( ::boost_generic_detail_scope_checker::boost_generic_detail_is_same_fun       \
  < boost_generic_detail_global_scope_check                                    \
  , ::boost_generic_detail_scope_checker                                       \
    ::boost_generic_detail_global_scope_check                                  \
  >::value                                                                     \
, message                                                                      \
);                                                                             \
}

#endif // BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE_HPP
