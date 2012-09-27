/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_STD_FORWARD_DECL_LIBSTDCPP_VECTOR_ITERATOR_HPP
#define BOOST_GENERIC_DETAIL_STD_FORWARD_DECL_LIBSTDCPP_VECTOR_ITERATOR_HPP

namespace __gnu_cxx {

// std::vector iterators
template< typename _Iterator, typename _Container >
class __normal_iterator;

}

#define BOOST_GENERIC_DETAIL_STD_FWD_DECL_PARAMS_libstdcpp_vector_iterator()   \
( template ( ( typename ) _Iterator, ( typename ) _Container ) )

#define BOOST_GENERIC_DETAIL_STD_FWD_DECL_NAME_libstdcpp_vector_iterator()     \
::__gnu_cxx::__normal_iterator< _Iterator, _Container >

#endif // BOOST_GENERIC_DETAIL_STD_FORWARD_DECL_LIBSTDCPP_VECTOR_ITERATOR_HPP
