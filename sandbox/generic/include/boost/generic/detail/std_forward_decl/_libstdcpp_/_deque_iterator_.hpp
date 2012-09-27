/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_STD_FORWARD_DECL_LIBSTDCPP_DEQUE_ITERATOR_HPP
#define BOOST_GENERIC_DETAIL_STD_FORWARD_DECL_LIBSTDCPP_DEQUE_ITERATOR_HPP

namespace _GLIBCXX_STD_D {

// std::deque iterators
template< typename _Tp, typename _Ref, typename _Ptr >
struct _Deque_iterator;

}

#define BOOST_GENERIC_DETAIL_STD_FWD_DECL_PARAMS_libstdcpp_deque_iterator()    \
( template ( ( typename ) _Tp, ( typename ) _Ref, ( typename ) _Ptr ) )

#define BOOST_GENERIC_DETAIL_STD_FWD_DECL_NAME_libstdcpp_deque_iterator()      \
::_GLIBCXX_STD_D::_Deque_iterator< _Tp, _Ref, _Ptr >

#endif // BOOST_GENERIC_DETAIL_STD_FORWARD_DECL_LIBSTDCPP_DEQUE_ITERATOR_HPP
