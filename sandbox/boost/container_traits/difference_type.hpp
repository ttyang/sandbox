// (C) Copyright Thorsten Ottosen 2003. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#ifndef BOOST_CONTAINER_TRAITS_DIFFERENCE_TYPE_HPP
#define BOOST_CONTAINER_TRAITS_DIFFERENCE_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/container_traits/detail/difference_type.hpp>
#else

#include <boost/detail/iterator.hpp>
#include <iterator>
#include <cstddef>
#include <utility>

namespace boost
{
    //////////////////////////////////////////////////////////////////////////
    // default
    //////////////////////////////////////////////////////////////////////////
    
    template< typename C >
    struct container_difference_type
    {
        typedef BOOST_DEDUCED_TYPENAME C::difference_type type;
    };
    
    //////////////////////////////////////////////////////////////////////////
    // pair
    //////////////////////////////////////////////////////////////////////////

    template< typename Iterator >
    struct container_difference_type< std::pair<Iterator,Iterator> >
    {
        typedef BOOST_DEDUCED_TYPENAME detail::iterator_traits<Iterator>::difference_type type;
    };
    
    template< typename Iterator >
    struct container_difference_type< const std::pair<Iterator,Iterator> >
    {
        typedef BOOST_DEDUCED_TYPENAME detail::iterator_traits<Iterator>::difference_type type;
    };


    //////////////////////////////////////////////////////////////////////////
    // array
    //////////////////////////////////////////////////////////////////////////

    template< typename T, std::size_t sz >
    struct container_difference_type< T[sz] >
    {
        typedef std::ptrdiff_t type;
    };

    template< typename T, std::size_t sz >
    struct container_difference_type< const T[sz] >
    {
        typedef std::ptrdiff_t type;
    };

    //////////////////////////////////////////////////////////////////////////
    // string
    //////////////////////////////////////////////////////////////////////////

    template<>
    struct container_difference_type< char* >
    {
        typedef std::ptrdiff_t type;
    };

    template<>
    struct container_difference_type< wchar_t* >
    {
        typedef std::ptrdiff_t type;
    };

    template<>
    struct container_difference_type< const char* >
    {
        typedef std::ptrdiff_t type;
    };

    template<>
    struct container_difference_type< const wchar_t* >
    {
        typedef std::ptrdiff_t type;
    };

    //////////////////////////////////////////////////////////////////////////
    // iterator
    //////////////////////////////////////////////////////////////////////////

    template< typename C, typename T, typename D, typename P >
    struct container_difference_type< std::istream_iterator<C,T,D,P> >
    {
        typedef BOOST_DEDUCED_TYPENAME detail::iterator_traits< std::istream_iterator<C,T,D,P> >::difference_type type;
    };
    
    template< typename C, typename T, typename D, typename P >
    struct container_difference_type< const std::istream_iterator<C,T,D,P> >
    {
        typedef BOOST_DEDUCED_TYPENAME detail::iterator_traits< std::istream_iterator<C,T,D,P> >::difference_type type;
    };

} // namespace boost

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif
