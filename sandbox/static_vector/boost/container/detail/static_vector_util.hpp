// Boost.Container
//
// StaticVector details
//
// Copyright (c) 2012 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2011-2012 Andrew Hundt.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTAINER_DETAIL_STATIC_VECTOR_UTIL_HPP
#define BOOST_CONTAINER_DETAIL_STATIC_VECTOR_UTIL_HPP

#include <cstring>
#include <memory>

#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/int.hpp>

#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>
#include <boost/type_traits/has_nothrow_assign.hpp>
//#include <boost/type_traits/has_nothrow_destructor.hpp>

#include <boost/iterator/iterator_traits.hpp>

namespace boost { namespace container { namespace detail { namespace static_vector {

template <typename I, typename O>
struct are_corresponding_pointers :
    ::boost::mpl::and_<
        ::boost::is_same<
            ::boost::remove_const<
                typename ::boost::iterator_value<I>::type
            >,
            ::boost::remove_const<
                typename ::boost::iterator_value<O>::type
            >
        >,
        ::boost::is_pointer<I>,
        ::boost::is_pointer<O>
    >
{};

template <typename V>
inline void copy_dispatch(const V * first, const V * last, V * dst,
                          boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    ::memcpy(dst, first, sizeof(V) * std::distance(first, last));
}

template <typename I, typename O>
inline void copy_dispatch(I first, I last, O dst,
                          boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    std::copy(first, last, dst);                                                // may throw
}

template <typename I, typename O>
inline void copy(I first, I last, O dst)
{
    namespace bm = ::boost::mpl;
    typedef typename
    bm::and_<
        are_corresponding_pointers<I, O>,
        has_trivial_assign<
            typename ::boost::iterator_value<O>::type
        >
    >::type use_memcpy;
    
    copy_dispatch(first, last, dst, use_memcpy());                              // may throw
}

}}}} // namespace boost::container::detail::static_vector

#endif // BOOST_CONTAINER_DETAIL_STATIC_VECTOR_UTIL_HPP
