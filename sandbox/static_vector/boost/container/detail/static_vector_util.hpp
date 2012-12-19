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
//#include <boost/type_traits/has_nothrow_constructor.hpp>
//#include <boost/type_traits/has_nothrow_copy.hpp>
//#include <boost/type_traits/has_nothrow_assign.hpp>
//#include <boost/type_traits/has_nothrow_destructor.hpp>

#include <boost/utility/addressof.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace boost { namespace container { namespace detail { namespace static_vector {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

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

template <typename I, typename V>
struct is_corresponding_value :
    ::boost::is_same<
        ::boost::remove_const<
            typename ::boost::iterator_value<I>::type
        >,
        ::boost::remove_const<V>
    >
{};

// copy

template <typename V>
inline V * copy_dispatch(const V * first, const V * last, V * dst,
                          boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    typename std::iterator_traits<V*>::difference_type d = std::distance(first, last);
    ::memcpy(dst, first, sizeof(V) * d);
    return dst + d;
}

template <typename I, typename O>
inline O copy_dispatch(I first, I last, O dst,
                          boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    return std::copy(first, last, dst);                                         // may throw
}

template <typename I, typename O>
inline O copy(I first, I last, O dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding_pointers<I, O>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<O>::type
        >
    >::type use_memcpy;
    
    return copy_dispatch(first, last, dst, use_memcpy());                       // may throw
}

// uninitialized_copy

template <typename V>
V * uninitialized_copy_dispatch(const V * first, const V * last, V * dst,
                                boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    typename std::iterator_traits<V*>::difference_type d = std::distance(first, last);
    ::memcpy(dst, first, sizeof(V) * d);
    return dst + d;
}

template <typename I, typename F>
F uninitialized_copy_dispatch(I first, I last, F dst,
                                 boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    return std::uninitialized_copy(first, last, dst);                           // may throw
}

template <typename I, typename F>
F uninitialized_copy(I first, I last, F dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding_pointers<I, F>,
        ::boost::has_trivial_copy<
            typename ::boost::iterator_value<F>::type
        >
    >::type use_memcpy;

    return uninitialized_copy_dispatch(first, last, dst, use_memcpy());          // may throw
}

// uninitialized_fill

template <typename V>
void uninitialized_fill_dispatch(V * ptr, V const& v,
                                 boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    ::memcpy(ptr, boost::addressof(v), sizeof(V));
}

template <typename I, typename V>
void uninitialized_fill_dispatch(I pos, V const& v,
                                 boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    new (static_cast<void*>(&*pos)) V(v);                                        // may throw
}

template <typename I, typename V>
void uninitialized_fill(I dst, V const& v)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, V>,
        ::boost::has_trivial_copy<V>
    >::type
    use_memcpy;

    uninitialized_fill_dispatch(dst, v, use_memcpy());                          // may throw
}

// move

// TODO use boost::move(I, I, O) instead of copy/assignment

template <typename V>
V * move_dispatch(const V * first, const V * last, V * dst,
                  boost::mpl::bool_<true> const& /*use_memmove*/)
{
    typename std::iterator_traits<V*>::difference_type d = std::distance(first, last);
    ::memmove(dst, first, sizeof(V) * d);
    return dst + d;
}

template <typename I, typename O>
O move_dispatch(I first, I last, O dst,
                boost::mpl::bool_<false> const& /*use_memmove*/)
{
    return std::copy(first, last, dst);                                         // may throw
}

template <typename I, typename O>
O move(I first, I last, O dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding_pointers<I, O>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<O>::type
        >
    >::type
    use_memmove;

    return move_dispatch(first, last, dst, use_memmove());                      // may throw
}

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template <typename I, typename O>
inline O copy(I first, I last, O dst)
{
    return std::copy(first, last, dst);                                         // may throw
}

template <typename I, typename F>
F uninitialized_copy(I first, I last, F dst)
{
    return std::uninitialized_copy(first, last, dst);                           // may throw
}

template <typename I, typename V>
void uninitialized_fill(I pos, V const& v)
{
    new (static_cast<void*>(&*pos)) V(v);                                       // may throw
}

template <typename I, typename O>
O move(I first, I last, O dst)
{
    return std::copy(first, last, dst);                                         // may throw
}

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}}} // namespace boost::container::detail::static_vector

#endif // BOOST_CONTAINER_DETAIL_STATIC_VECTOR_UTIL_HPP
