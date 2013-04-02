// Copyright Fabian Bösch 2012
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 *  @file 
 *  @brief This file contains traits classes for Constant / Unit Stride Iterators.
 */

#ifndef BOOST_IS_STRIDE_ITERATOR_HPP
#define BOOST_IS_STRIDE_ITERATOR_HPP

#include <iterator>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <vector>

namespace boost {

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace range_generate {

namespace detail {

template <typename T>
struct has_typedef_value_type {
    typedef char yes[1];
    typedef char no[2];

    template <typename C>
    static yes& test(typename C::value_type*);

    template <typename>
    static no& test(...);

    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

} // detail

/*
**
 *  @brief Traits class for an Iterator's value type
 *
 *  If Iterator is a pointer, return the type pointed to, otherwise
 *  return Iterator::value_type.
 *
 *
template <class Iterator>
struct iterator_value_type
{
	#ifndef DOXYGEN_SHOULD_SKIP_THIS
	typedef typename Iterator::value_type type;
	#endif // DOXYGEN_SHOULD_SKIP_THIS
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <class Iterator>
struct iterator_value_type<Iterator*>
{
	typedef Iterator type;
};

#endif // DOXYGEN_SHOULD_SKIP_THIS
*/

} // range_generate

#endif // DOXYGEN_SHOULD_SKIP_THIS

/**
 *  @brief Traits class for Constant Stride Iterators
 *  
 *  Is the type @c Iterator a Constant Stride Iterator?
 *
 *  @tparam Iterator An Iterator type
 *  @tparam Enable Auxillary type for SFINAE specializations
 *
 */
template <class Iterator, class Enable = void>
struct is_constant_stride_iterator : public boost::mpl::false_ {};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <class Iterator>
struct is_constant_stride_iterator<Iterator, typename boost::enable_if<boost::is_pointer<Iterator> >::type>
: public boost::mpl::true_ {};

/*
template <class Iterator>
struct is_constant_stride_iterator<Iterator, typename boost::enable_if_c<range_generate::detail::has_typedef_value_type<Iterator>::value>::type>
: public boost::is_same<Iterator,typename std::vector<typename Iterator::value_type>::iterator>::type {};*/

template <class Iterator>
struct is_constant_stride_iterator<Iterator, typename boost::enable_if_c<!boost::is_pointer<Iterator>::value && range_generate::detail::has_typedef_value_type<typename std::iterator_traits<Iterator> >::value>::type>
: public boost::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::iterator>::type {};


#endif // DOXYGEN_SHOULD_SKIP_THIS

/**
 *  @brief Traits class for the stride of a Constant Stride Iterator
 *  @tparam Iterator An Iterator type
 *  @tparam Enable Auxillary type for SFINAE specializations
 *
 */
template <class Iterator, class Enable = void>
struct stride : public boost::mpl::int_<0> { };

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <class Iterator>
struct stride<Iterator, typename boost::enable_if<boost::is_pointer<Iterator> >::type> : public boost::mpl::int_<1> {};

/*template <class Iterator>
struct stride<Iterator, typename boost::enable_if_c<range_generate::detail::has_typedef_value_type<Iterator>::value>::type> : public 
boost::mpl::eval_if<
	typename boost::is_same<Iterator,typename std::vector<typename Iterator::value_type>::iterator>::type,
	boost::mpl::int_<1>,
	boost::mpl::int_<0>
>::type
{};*/

template <class Iterator>
struct stride<Iterator, typename boost::enable_if_c<!boost::is_pointer<Iterator>::value && range_generate::detail::has_typedef_value_type<typename std::iterator_traits<Iterator> >::value>::type> : public 
boost::mpl::eval_if<
	typename boost::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::iterator>::type,
	boost::mpl::int_<1>,
	boost::mpl::int_<0>
>::type
{};

#endif // DOXYGEN_SHOULD_SKIP_THIS

/**
 *  @brief Traits class for Unit Stride Iterators
 *  
 *  Is the type @c Iterator a Unit Stride Iterator?
 *
 *  @tparam Iterator An Iterator type
 *
 */
template <class Iterator>
struct is_unit_stride_iterator :
boost::mpl::eval_if<
    typename is_constant_stride_iterator<Iterator>::type,
    typename boost::mpl::equal_to<
        typename stride<Iterator>::type,
        typename boost::mpl::int_<1>
    >::type,
    boost::mpl::false_
>::type
{ };


} // boost

/// Register iterator type as Constant Stride Iterator with stride n
#define BOOST_IS_CONSTANT_STRIDE_ITERATOR(iterator,n)     \
namespace boost {                                         \
template<>                                                \
struct is_constant_stride_iterator<iterator>              \
: public boost::mpl::true_ {};                            \
template<>                                                \
struct stride<iterator>                                   \
: public boost::mpl::int_<n> {BOOST_STATIC_ASSERT(n>0);}; \
}

/// Register iterator type as Unit Stride Iterator
#define BOOST_IS_UNIT_STRIDE_ITERATOR(iterator)           \
namespace boost {                                         \
template<>                                                \
struct is_constant_stride_iterator<iterator>              \
: public boost::mpl::true_ {};                            \
template<>                                                \
struct stride<iterator>                                   \
: public boost::mpl::int_<1> {BOOST_STATIC_ASSERT(n>0);}; \
}

#endif // BOOST_IS_STRIDE_ITERATOR_HPP

