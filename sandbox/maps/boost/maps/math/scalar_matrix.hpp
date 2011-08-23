//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_MATH_SCALAR_MATRIX_HPP )
#define BOOST_MAPS_MATH_SCALAR_MATRIX_HPP

#include <boost/maps/math/scalar_scalar.hpp>
#include <boost/maps/math/matrix_matrix.hpp>

namespace boost { namespace maps {

//--

    template< class E, class O, bool L >
    class scalar_matrix_unary_expression
        : public scalar_expression< scalar_matrix_unary_expression< E,O,L > >
    {
    public:

        typedef scalar_matrix_unary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef typename E::type_const_reference expression_const_reference;
        typedef E expression_type;
        typedef O operator_type;
        typedef typename O::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename operator_type::size_type size_type;
        typedef typename operator_type::allocator_type allocator_type;

        using scalar_expression< type >::operator();

        enum { size = 1 };
        enum { linear = ( L & E::linear ) };

        scalar_matrix_unary_expression( E const& );
        type_reference operator=( type_const_reference );

        expression_type const& expression() const;

        result_type const operator()( size_type ) const;

        template< class U >
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B >
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B >
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    private:

        expression_const_reference t;

    };

//--

    template< class E, class O, bool L >
    scalar_matrix_unary_expression< E,O,L >::scalar_matrix_unary_expression( E const& e )
        : t( e )
    {}

    template< class E, class O, bool L >
    typename scalar_matrix_unary_expression< E,O,L >::type_reference
        scalar_matrix_unary_expression< E,O,L >::operator=( type_const_reference e )
    {
        if( &e != this ) t = e.t;
        return *this;
    }

    template< class E, class O, bool L >
    typename scalar_matrix_unary_expression< E,O,L >::expression_type const& 
        scalar_matrix_unary_expression< E,O,L >::expression() const
    {
        return t;
    }

    template< class E, class O, bool L >
    typename scalar_matrix_unary_expression< E,O,L >::result_type const 
        scalar_matrix_unary_expression< E,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t );
    }

    template< class E, class O, bool L > template< class U >
    bool const scalar_matrix_unary_expression< E,O,L >::references( scalar< U > const& s ) const
    {
        return ( t().references( s ) );
    }

    template< class E, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const scalar_matrix_unary_expression< E,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t().references( v ) );
    }

    template< class E, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const scalar_matrix_unary_expression< E,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t().references( m ) );
    }

//--

    template< class T >
    struct matrix_norm_1
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t )
        {
            result_type r = result_type();
            for( size_type j = 0; j != t.cols; ++j )
            {   result_type s = result_type();
                for( size_type i = 0; i != t.rows; ++i )
                    s += std::abs( t( i,j ) );
                if( s > r ) r = s; 
            }
            return r;
        }
    };

//--

    template< class E, std::size_t M, std::size_t N >
    scalar_matrix_unary_expression< E,matrix_norm_1< E >,true >
    norm_1( matrix_expression< E,M,N > const& e )
    {
         return scalar_matrix_unary_expression< E,matrix_norm_1< E >,true >( e() );
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_MATH_SCALAR_MATRIX_HPP