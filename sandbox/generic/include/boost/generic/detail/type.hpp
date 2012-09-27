/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_TYPE_HPP
#define BOOST_GENERIC_DETAIL_TYPE_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#include <boost/mpl/bool.hpp>

namespace boost { namespace generic { namespace detail {

template< class T >
struct type_ { typedef T type; };

template< class T >
::boost::mpl::true_ boost_generic_detail_istantiate_if_auto( type_< T > );

} } }

#endif

#endif // BOOST_GENERIC_DETAIL_TYPE_HPP
