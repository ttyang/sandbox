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

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
//#include <boost/type_traits/has_nothrow_constructor.hpp>
//#include <boost/type_traits/has_nothrow_copy.hpp>
//#include <boost/type_traits/has_nothrow_assign.hpp>
//#include <boost/type_traits/has_nothrow_destructor.hpp>

#include <boost/detail/no_exceptions_support.hpp>
#include <boost/config.hpp>
#include <boost/move/move.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/iterator/iterator_traits.hpp>

// TODO - move vectors iterators optimization to the other, optional file instead of checking defines?

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#if defined(BOOST_CONTAINER_STATIC_VECTOR_ENABLE_VECTORS_OPTIMIZATION) && !defined(BOOST_NO_EXCEPTIONS)
#include <vector>
#include <boost/container/vector.hpp>
#endif // BOOST_CONTAINER_STATIC_VECTOR_ENABLE_ITERATORS_OPTIMIZATION && !BOOST_NO_EXCEPTIONS

namespace boost { namespace container { namespace static_vector_detail {

template <typename I>
struct are_elements_contiguous : boost::is_pointer<I>
{};

#if defined(BOOST_CONTAINER_STATIC_VECTOR_ENABLE_VECTORS_OPTIMIZATION) && !defined(BOOST_NO_EXCEPTIONS)

template <typename Pointer>
struct are_elements_contiguous<
    boost::container_detail::vector_const_iterator<Pointer>
> : boost::true_type
{};

template <typename Pointer>
struct are_elements_contiguous<
    boost::container_detail::vector_iterator<Pointer>
> : boost::true_type
{};

#if defined(BOOST_DINKUMWARE_STDLIB)

template <typename T>
struct are_elements_contiguous<
    std::_Vector_const_iterator<T>
> : boost::true_type
{};

template <typename T>
struct are_elements_contiguous<
    std::_Vector_iterator<T>
> : boost::true_type
{};

#elif defined(BOOST_GNU_STDLIB)

template <typename P, typename T, typename A>
struct are_elements_contiguous<
    __gnu_cxx::__normal_iterator<P, std::vector<T, A> >
> : boost::true_type
{};

#elif defined(_LIBCPP_VERSION)

// TODO - test it first

//template <typename P>
//struct are_elements_contiguous<
//    __wrap_iter<P>
//> : boost::true_type
//{};

#else // OTHER_STDLIB

// TODO - add other iterators implementations

#endif // STDLIB

#endif // BOOST_CONTAINER_STATIC_VECTOR_ENABLE_VECTORS_OPTIMIZATION && !BOOST_NO_EXCEPTIONS

}}} // namespace boost::container::static_vector_detail

#endif // !BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost { namespace container { namespace static_vector_detail {

// TODO
// Does BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION checks have any sense?
// Boost.MPL and Boost.Container might not be used but
// Boost.Iterator also uses partial specialization
// and in fact iterator_traits won't work if there is no partial specialization

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename I, typename O>
struct are_corresponding :
    ::boost::mpl::and_<
        ::boost::is_same<
            ::boost::remove_const<
                typename ::boost::iterator_value<I>::type
            >,
            ::boost::remove_const<
                typename ::boost::iterator_value<O>::type
            >
        >,
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
    return std::uninitialized_copy(first, last, dst);                                       // may throw
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

// uninitialized_move(I, I, O)

template <typename I, typename O>
O uninitialized_move_dispatch(I first, I last, O dst,
                              boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memcpy(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}

template <typename I, typename O>
O uninitialized_move_dispatch(I first, I last, O dst,
                              boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    //return boost::uninitialized_move(first, last, dst);                         // may throw

    O o = dst;

    BOOST_TRY
    {
        typedef typename std::iterator_traits<O>::value_type value_type;
        for (; first != last; ++first, ++o )
            new (boost::addressof(*o)) value_type(boost::move(*first));
    }
    BOOST_CATCH(...)
    {
        destroy(dst, o);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END

    return dst;
}

template <typename I, typename O>
O uninitialized_move(I first, I last, O dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<I, O>,
        ::boost::has_trivial_copy<
            typename ::boost::iterator_value<O>::type
        >
    >::type
    use_memcpy;

    return uninitialized_move_dispatch(first, last, dst, use_memcpy());         // may throw
}

// TODO - move uses memmove - implement 2nd version using memcpy?

// move(I, I, O)

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
    return boost::move(first, last, dst);                                         // may throw
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

// TODO - move_backward uses memmove - implement 2nd version using memcpy?

// move_backward(BDI, BDI, BDO)

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
    return boost::move_backward(first, last, dst);                                // may throw
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

// uninitialized_fill(I, I)

template <typename I>
void uninitialized_fill_dispatch(I /*first*/, I /*last*/,
                                 boost::true_type const& /*has_trivial_constructor*/)
{}

template <typename I>
void uninitialized_fill_dispatch(I first, I last,
                                 boost::false_type const& /*has_trivial_constructor*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    I it = first;

    BOOST_TRY
    {
        for ( ; it != last ; ++it )
            new (boost::addressof(*it)) value_type();                           // may throw
    }
    BOOST_CATCH(...)
    {
        destroy(first, it);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END
}

template <typename I>
void uninitialized_fill(I first, I last)
{
    typedef typename boost::iterator_value<I>::type value_type;
    uninitialized_fill_dispatch(first, last, has_trivial_constructor<value_type>());     // may throw
}

// construct(I, V)

template <typename I, typename V>
void construct_dispatch(I pos, V const& v,
                        boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}

template <typename I, typename P>
void construct_dispatch(I pos, P const& p,
                        boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type V;
    new (static_cast<void*>(boost::addressof(*pos))) V(p);                      // may throw
}

template <typename I, typename P>
void construct(I pos, P const& p)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, P>,
        ::boost::has_trivial_copy<P>
    >::type
    use_memcpy;

    construct_dispatch(pos, p, use_memcpy());                                   // may throw
}

// Needed by push_back(V &&)

template <typename I, typename P>
void construct(I pos, BOOST_RV_REF(P) p)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, P>,
        ::boost::has_trivial_copy<P>
    >::type
    use_memcpy;

    typedef typename boost::iterator_value<I>::type V;
    new (static_cast<void*>(boost::addressof(*pos))) V(p);                      // may throw
}

// Needed by emplace_back() and emplace()

#if !defined(BOOST_CONTAINER_STATIC_VECTOR_DISABLE_EMPLACE)
#if !defined(BOOST_NO_VARIADIC_TEMPLATES)

template <typename I, class ...Args>
void construct(I pos, BOOST_FWD_REF(Args) ...args)
{
    typedef typename boost::iterator_value<I>::type V;
    new (static_cast<void*>(boost::addressof(*pos))) V(::boost::forward<Args>(args)...);    // may throw
}

#else // !BOOST_NO_VARIADIC_TEMPLATES

// BOOST_NO_RVALUE_REFERENCES -> P0 const& p0
// !BOOST_NO_RVALUE_REFERENCES -> P0 && p0
// which means that version with one parameter may take V const& v

#define BOOST_PP_LOCAL_MACRO(n)                                                                     \
template <typename I, typename P BOOST_PP_ENUM_TRAILING_PARAMS(n, typename P) >                     \
void construct(I pos,                                                                               \
               BOOST_CONTAINER_PP_PARAM(P, p)                                                       \
               BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_LIST, _))                         \
{                                                                                                   \
    typedef typename boost::iterator_value<I>::type V;                                              \
    new                                                                                             \
    (static_cast<void*>(boost::addressof(*pos)))                                                    \
    V(p, BOOST_PP_ENUM(n, BOOST_CONTAINER_PP_PARAM_FORWARD, _));                   /*may throw*/    \
}                                                                                                   \
//
#define BOOST_PP_LOCAL_LIMITS (1, BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS)
#include BOOST_PP_LOCAL_ITERATE()

#endif // !BOOST_NO_VARIADIC_TEMPLATES
#endif // !BOOST_CONTAINER_STATIC_VECTOR_DISABLE_EMPLACE

// assign(I, V)

template <typename I, typename V>
void assign_dispatch(I pos, V const& v,
                     boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}

template <typename I, typename V>
void assign_dispatch(I pos, V const& v,
                     boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    *pos = v;                                                                   // may throw
}

template <typename I, typename V>
void assign(I pos, V const& v)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, V>,
        ::boost::has_trivial_assign<V>
    >::type
    use_memcpy;

    assign_dispatch(pos, v, use_memcpy());                                        // may throw
}

template <typename I, typename V>
void assign(I pos, BOOST_RV_REF(V) v)
{
    *pos = v;                                                                     // may throw
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

template <typename I, typename O>
O uninitialized_move(I first, I last, O dst)
{
    //return boost::uninitialized_move(first, last, dst);                         // may throw

    O o = dst;

    BOOST_TRY
    {
        typedef typename std::iterator_traits<O>::value_type value_type;
        for (; first != last; ++first, ++o )
            new (boost::addressof(*o)) value_type(boost::move(*first));
    }
    BOOST_CATCH(...)
    {
        destroy(dst, o);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END

    return dst;
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
void uninitialized_fill(I first, I last)
{
    typedef typename boost::iterator_value<I>::type value_type;
    I it = first;
    
    BOOST_TRY
    {
        for ( ; it != last ; ++it )
            new (boost::addressof(*it)) value_type();                           // may throw
    }
    BOOST_CATCH(...)
    {
        destroy(first, it);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END
}

template <typename I, typename V>
inline void construct(I pos, V const& v)
{
    new (static_cast<void*>(boost::addressof(*pos))) V(v);                      // may throw
}

template <typename I, typename V>
inline void assign(I pos, V const& v)
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

    BOOST_TRY
    {
        for ( ; first != last ; ++it, ++first, ++count )
        {
            if ( max_count <= count )
                return (std::numeric_limits<std::size_t>::max)();

            construct(it, *first);                                              // may throw
        }
    }
    BOOST_CATCH(...)
    {
        destroy(dest, it);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END

    return count;
}

// scoped_destructor

template<class T>
class scoped_destructor
{
public:
    scoped_destructor(T * ptr) : m_ptr(ptr) {}

    ~scoped_destructor()
    {
        if(m_ptr)
            destroy(m_ptr);
    }

    void release() { m_ptr = 0; }

private:
    T * m_ptr;
};

}}} // namespace boost::container::static_vector_detail

#endif // BOOST_CONTAINER_DETAIL_STATIC_VECTOR_UTIL_HPP
