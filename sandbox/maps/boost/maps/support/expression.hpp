//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_SUPPORT_EXPRESSION_HPP )
#define BOOST_MAPS_SUPPORT_EXPRESSION_HPP

#include <boost/type_traits/common_type.hpp>

namespace boost { namespace maps {

//--

    template< class E >
    class expression_type
    {
    public:

        typedef expression_type type;
        typedef E value_type;
        typedef value_type const& const_reference;
        typedef value_type& reference;

        const_reference operator()() const
        {
            return *static_cast< const value_type* >( this );
        }

        reference operator()()
        {
            return *static_cast< value_type* >( this );
        }

    protected:

        expression_type() {}
        ~expression_type() {}

    };

//--
//--

    template< class E >
    class expression
        : expression_type< expression< E > >
    {
    public:

        typedef expression type;
        typedef E value_type;
        typedef value_type const& const_reference;
        typedef value_type& reference;

        const_reference operator()() const
        {
            return *static_cast< const value_type* >( this );
        }

        reference operator()()
        {
            return *static_cast< value_type* >( this );
        }

    };

//--
//--

    template< class T >
    struct expression_traits
    {
        typedef T type;
        typedef typename type::type_const_reference type_const_reference;
        typedef typename type::type_reference type_reference;
        typedef typename type::const_reference const_reference;
        typedef typename type::reference reference;
        typedef typename type::element_type element_type;
        typedef typename type::allocator_type allocator_type;
        typedef typename type::size_type size_type;
    };

    template< class T1, class T2 >
    struct expression_binary_traits
    {
        typedef typename expression_traits< T1 >::type_const_reference type_const_reference1;
        typedef typename expression_traits< T2 >::type_const_reference type_const_reference2;
        typedef typename expression_traits< T1 >::type_reference type_reference1;
        typedef typename expression_traits< T2 >::type_reference type_reference2;
        typedef typename expression_traits< T1 >::const_reference const_reference1;
        typedef typename expression_traits< T2 >::const_reference const_reference2;
        typedef typename expression_traits< T1 >::reference reference1;
        typedef typename expression_traits< T2 >::reference reference2;
        typedef typename expression_traits< T1 >::element_type element_type1;
        typedef typename expression_traits< T2 >::element_type element_type2;
        typedef typename common_type< element_type1,element_type2 >::type result_type;
        typedef typename expression_traits< T1 >::allocator_type allocator_type;
        typedef typename expression_traits< T1 >::size_type size_type;
    };

    template< class T >
    struct expression_unary_traits
    {
        typedef typename expression_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_traits< T >::type_reference type_reference;
        typedef typename expression_traits< T >::const_reference const_reference;
        typedef typename expression_traits< T >::reference reference;
        typedef typename expression_traits< T >::element_type element_type;
        typedef typename expression_traits< T >::element_type result_type;
        typedef typename expression_traits< T >::allocator_type allocator_type;
        typedef typename expression_traits< T >::size_type size_type;
    };

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_SUPPORT_EXPRESSION_HPP
