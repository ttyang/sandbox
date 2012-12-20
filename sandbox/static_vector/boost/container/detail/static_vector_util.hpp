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

// TODO - move this to the other, optional file?
#include <vector>
#include <boost/container/vector.hpp>

namespace boost { namespace container { namespace detail { namespace static_vector {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename I>
struct are_elements_contiguous : boost::is_pointer<I>
{};

// TODO - move this to the other, optional file?

template <typename Pointer>
struct are_elements_contiguous< container_detail::vector_const_iterator<Pointer> > : boost::true_type
{};

template <typename Pointer>
struct are_elements_contiguous< container_detail::vector_iterator<Pointer> > : boost::true_type
{};

#if defined(_MSC_VER)

template <typename T>
struct are_elements_contiguous< std::_Vector_const_iterator<T> > : boost::true_type
{};

template <typename T>
struct are_elements_contiguous< std::_Vector_iterator<T> > : boost::true_type
{};

// TODO - add other iterators implementations

#endif

template <typename I, typename O>
struct are_corresponding :
    boost::mpl::and_<
        boost::is_same<
            boost::remove_const<
                typename boost::iterator_value<I>::type
            >,
            boost::remove_const<
                typename boost::iterator_value<O>::type
            >
        >,
        /*boost::is_same<
            typename boost::iterator_traversal<I>::type,
            boost::random_access_traversal_tag
        >,
        boost::is_same<
            typename boost::iterator_traversal<O>::type,
            boost::random_access_traversal_tag
        >,*/
        are_elements_contiguous<I>,
        are_elements_contiguous<O>
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

template <typename I, typename O>
inline O copy_dispatch(I first, I last, O dst,
                       boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memcpy(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
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
        are_corresponding<I, O>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<O>::type
        >
    >::type use_memcpy;
    
    return copy_dispatch(first, last, dst, use_memcpy());                       // may throw
}

// uninitialized_copy(I, I, O)

template <typename I, typename O>
O uninitialized_copy_dispatch(I first, I last, O dst,
                              boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memcpy(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
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
        are_corresponding<I, F>,
        ::boost::has_trivial_copy<
            typename ::boost::iterator_value<F>::type
        >
    >::type use_memcpy;

    return uninitialized_copy_dispatch(first, last, dst, use_memcpy());          // may throw
}

// uninitialized_fill(I, V)

template <typename I, typename V>
void uninitialized_fill_dispatch(I pos, V const& v,
                                 boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
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

template <typename I, typename O>
O move_dispatch(I first, I last, O dst,
                  boost::mpl::bool_<true> const& /*use_memmove*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memmove(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
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
        are_corresponding<I, O>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<O>::type
        >
    >::type
    use_memmove;

    return move_dispatch(first, last, dst, use_memmove());                      // may throw
}

// move_backward(BDI, BDI, BDO)

// TODO use boost::move_backward(I, I, O) instead of copy_backward

template <typename BDI, typename BDO>
BDO move_backward_dispatch(BDI first, BDI last, BDO dst,
                           boost::mpl::bool_<true> const& /*use_memmove*/)
{
    typedef typename boost::iterator_value<BDI>::type value_type;
    typename boost::iterator_difference<BDI>::type d = std::distance(first, last);

    BDO foo(dst - d);
    ::memmove(boost::addressof(*foo), boost::addressof(*first), sizeof(value_type) * d);
    return foo;
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
        are_corresponding<BDI, BDO>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<BDO>::type
        >
    >::type
    use_memmove;

    return move_backward_dispatch(first, last, dst, use_memmove());             // may throw
}

// fill(I, V)

template <typename I, typename V>
void fill_dispatch(I pos, V const& v,
                   boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
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
            new (boost::addressof(*it)) value_type();                           // may throw
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

template <typename I>
struct are_elements_contiguous
{};

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
    new (static_cast<void*>(boost::addressof(*pos))) V(v);                      // may throw
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

template <typename I>
void destroy(I first, I last)
{
    typedef typename boost::iterator_value<I>::type value_type;
    for ( ; first != last ; ++first )
        first->~value_type();
}

template <typename I>
void destroy(I pos)
{
    typedef typename boost::iterator_value<I>::type value_type;
    pos->~value_type();
}

template <typename I>
void construct(I first, I last)
{
    typedef typename boost::iterator_value<I>::type value_type;
    I it = first;
    try
    {
        for ( ; it != last ; ++it )
            new (boost::addressof(*it)) value_type();                           // may throw
    }
    catch(...)
    {
        destroy(first, it);
        throw;
    }
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
