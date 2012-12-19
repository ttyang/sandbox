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

#include <cstddef>
#include <cstring>
#include <memory>
#include <limits>

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

// copy(I, I, O)

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

// uninitialized_copy(I, I, O)

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

// uninitialized_fill(I, V)

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
    new (static_cast<void*>(boost::addressof(*pos))) V(v);                      // may throw
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

// move(I, I, O)

// TODO use boost::move(I, I, O) instead of copy

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

// move_backward(BDI, BDI, BDO)

// TODO use boost::move_backward(I, I, O) instead of copy_backward

template <typename V>
V * move_backward_dispatch(const V * first, const V * last, V * dst,
                           boost::mpl::bool_<true> const& /*use_memmove*/)
{
    typename std::iterator_traits<V*>::difference_type d = std::distance(first, last);
    ::memmove(dst - d, first, sizeof(V) * d);
    return dst - d;
}

template <typename BDI, typename BDO>
BDO move_backward_dispatch(BDI first, BDI last, BDO dst,
                           boost::mpl::bool_<false> const& /*use_memmove*/)
{
    return std::copy_backward(first, last, dst);                                // may throw
}

template <typename BDI, typename BDO>
BDO move_backward(BDI first, BDI last, BDO dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding_pointers<BDI, BDO>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<BDO>::type
        >
    >::type
    use_memmove;

    return move_backward_dispatch(first, last, dst, use_memmove());             // may throw
}

// fill(I, V)

template <typename V>
void fill_dispatch(V * ptr, V const& v,
                   boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    ::memcpy(ptr, boost::addressof(v), sizeof(V));
}

template <typename I, typename V>
void fill_dispatch(I pos, V const& v,
                   boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    *pos = v;                                                                   // may throw
}

template <typename I, typename V>
void fill(I pos, V const& v)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, V>,
        ::boost::has_trivial_assign<V>
    >::type
    use_memcpy;

    fill_dispatch(pos, v, use_memcpy());                                        // may throw
}

// destroy(I, I)

template <typename I>
void destroy_dispatch(I /*first*/, I /*last*/,
                      boost::true_type const& /*has_trivial_destructor*/)
{}

template <typename I>
void destroy_dispatch(I first, I last,
                      boost::false_type const& /*has_trivial_destructor*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    for ( ; first != last ; ++first )
        first->~value_type();
}

template <typename I>
void destroy(I first, I last)
{
    typedef typename boost::iterator_value<I>::type value_type;
    destroy_dispatch(first, last, has_trivial_destructor<value_type>());
}

// destroy(I)

template <typename I>
void destroy_dispatch(I /*pos*/,
                      boost::true_type const& /*has_trivial_destructor*/)
{}

template <typename I>
void destroy_dispatch(I pos,
                      boost::false_type const& /*has_trivial_destructor*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    pos->~value_type();
}

template <typename I>
void destroy(I pos)
{
    typedef typename boost::iterator_value<I>::type value_type;
    destroy_dispatch(pos, has_trivial_destructor<value_type>());
}

// construct

template <typename I>
void construct_dispatch(I /*first*/, I /*last*/,
                        boost::true_type const& /*has_trivial_constructor*/)
{}

template <typename I>
void construct_dispatch(I first, I last,
                        boost::false_type const& /*has_trivial_constructor*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    I it = first;
    try
    {
        for ( ; it != last ; ++it )
            new (it) value_type();                                              // may throw
    }
    catch(...)
    {
        destroy(first, it);
        throw;
    }
}

template <typename I>
void construct(I first, I last)
{
    typedef typename boost::iterator_value<I>::type value_type;
    construct_dispatch(first, last, has_trivial_constructor<value_type>());     // may throw
}

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template <typename I, typename O>
inline O copy(I first, I last, O dst)
{
    return std::copy(first, last, dst);                                         // may throw
}

template <typename I, typename F>
inline F uninitialized_copy(I first, I last, F dst)
{
    return std::uninitialized_copy(first, last, dst);                           // may throw
}

template <typename I, typename V>
inline void uninitialized_fill(I pos, V const& v)
{
    new (static_cast<void*>(&*pos)) V(v);                                       // may throw
}

template <typename I, typename O>
inline O move(I first, I last, O dst)
{
    return std::copy(first, last, dst);                                         // may throw
}

template <typename BDI, typename BDO>
inline BDO move_backward(BDI first, BDI last, BDO dst)
{
    return std::copy_backward(first, last, dst);                                // may throw
}

template <typename I, typename V>
inline void fill(I pos, V const& v)
{
    *pos = v;                                                                   // may throw
}

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

// uninitialized_copy_checked

template <typename I, typename F>
inline std::size_t uninitialized_copy_s(I first, I last, F dest, std::size_t max_count)
{
    std::size_t count = 0;
    F it = dest;
    try
    {
        for ( ; first != last ; ++it, ++first, ++count )
        {
            if ( max_count <= count )
                return (std::numeric_limits<std::size_t>::max)();

            uninitialized_fill(it, *first);                                     // may throw
        }
    }
    catch(...)
    {
        destroy(dest, it);
        throw;
    }
    return count;
}

}}}} // namespace boost::container::detail::static_vector

#endif // BOOST_CONTAINER_DETAIL_STATIC_VECTOR_UTIL_HPP
