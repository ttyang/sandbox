//  (C) Copyright Thorsten Ottosen 2003. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CONTAINER_TRAITS_DETAIL_CONST_ITERATOR_HPP
#define BOOST_CONTAINER_TRAITS_DETAIL_CONST_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/container_traits/detail/common.hpp>

//////////////////////////////////////////////////////////////////////////////
// missing partial specialization  workaround.
//////////////////////////////////////////////////////////////////////////////

namespace boost 
{
    namespace container_traits_detail 
    {      
        template< typename T >
        struct container_const_iterator_;

        template<>
        struct container_const_iterator_<std_container_>
        {
            template< typename C >
            struct pts
            {
                typedef BOOST_DEDUCED_TYPENAME C::const_iterator type;
            };
        };

        template<>
        struct container_const_iterator_<std_pair_>
        {
            template< typename P >
            struct pts
            {
                typedef BOOST_DEDUCED_TYPENAME P::first_type type;
            };
        };

        template<>
        struct container_const_iterator_<array_>; // give up

        template<>
        struct container_const_iterator_<char_ptr_>
        {
            template< typename S >
            struct pts
            {
                typedef const char* type; 
            };         
        };
        
        template<>
        struct container_const_iterator_<const_char_ptr_>
        {
            template< typename S >
            struct pts
            {
                typedef const char* type; 
            };         
        };

        template<>
        struct container_const_iterator_<wchar_t_ptr_>
        {
            template< typename S >
            struct pts
            {
                typedef const wchar_t* type; 
            };         
        };

        template<>
        struct container_const_iterator_<const_wchar_t_ptr_>
        {
             template< typename S >
             struct pts
             {
                 typedef const wchar_t* type; 
             };         
         };

        template<>
        struct container_const_iterator_<iterator_>
        {
            template< typename I >
            struct pts
            {
                typedef I type;
            };         
        };
    } 
    
    template< typename C >
    class container_const_iterator
    {
        typedef BOOST_DEDUCED_TYPENAME container_traits_detail::container<C>::type c_type;
    public:
        typedef BOOST_DEDUCED_TYPENAME container_traits_detail::container_const_iterator_<c_type>::BOOST_NESTED_TEMPLATE pts<C>::type type; 
    };

}

#endif
