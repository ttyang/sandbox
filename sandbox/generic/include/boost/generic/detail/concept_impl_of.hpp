/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_CONCEPT_IMPL_OF_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_IMPL_OF_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

//#include <type_traits>

namespace boost { namespace generic { namespace detail {

template< class T >
struct concept_impl_of
{
  static bool const is_specialized = false;
  static bool const is_auto = false;

//  struct type
//  {
//    template< class >
//    struct boost_generic_detail_is_valid : std::false_type {};
//  };
};

} } }

#endif

#endif // BOOST_GENERIC_DETAIL_CONCEPT_IMPL_OF_HPP
