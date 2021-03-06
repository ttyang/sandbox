//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_MATH_MATRIX_SCALAR_HPP )
#define BOOST_MAPS_MATH_MATRIX_SCALAR_HPP

#include <boost/maps/math/matrix_matrix.hpp>
#include <boost/maps/math/scalar_scalar.hpp>

namespace boost { namespace maps {

//--

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    class matrix_scalar_binary_expression
        : public matrix_expression< matrix_scalar_binary_expression< E1,E2,M,N,O,L >,M,N >
    {
    public:

        typedef matrix_scalar_binary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef typename E1::type_const_reference expression1_const_reference;
        typedef typename E2::type_const_reference expression2_const_reference;
        typedef E1 expression_type1;
        typedef E2 expression_type2;
        typedef O operator_type;
        typedef typename O::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename operator_type::size_type size_type;
        typedef typename operator_type::allocator_type allocator_type;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = ( L & E1::linear & E2::linear ) };

        matrix_scalar_binary_expression( E1 const&, E2 const& );
        type_reference operator=( type_const_reference );

        expression_type1 const& expression1() const;
        expression_type2 const& expression2() const;

        reference operator()( reference, size_type, size_type ) const;
        result_type const operator()( size_type, size_type ) const;
        result_type const operator()( size_type ) const;

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    private:

        expression1_const_reference t1;
        expression2_const_reference t2;

    };

    //--

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    matrix_scalar_binary_expression< E1,E2,M,N,O,L >::matrix_scalar_binary_expression( E1 const& e1, E2 const& e2 )
        : t1( e1 ), t2( e2 )
    {}

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_scalar_binary_expression< E1,E2,M,N,O,L >::type_reference
        matrix_scalar_binary_expression< E1,E2,M,N,O,L >::operator=( type_const_reference e )
    {
        if( &e != this ) { t1 = e.t1; t2 = e.t2; }
        return *this;
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_scalar_binary_expression< E1,E2,M,N,O,L >::expression_type1 const& 
        matrix_scalar_binary_expression< E1,E2,M,N,O,L >::expression1() const
    {
        return t1;
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_scalar_binary_expression< E1,E2,M,N,O,L >::expression_type2 const& 
        matrix_scalar_binary_expression< E1,E2,M,N,O,L >::expression2() const
    {
        return t2;
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_scalar_binary_expression< E1,E2,M,N,O,L >::reference 
        matrix_scalar_binary_expression< E1,E2,M,N,O,L >::operator()( reference r, size_type i, size_type j ) const
    {
        return operator_type()( r,t1,t2,i,j );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_scalar_binary_expression< E1,E2,M,N,O,L >::result_type const 
        matrix_scalar_binary_expression< E1,E2,M,N,O,L >::operator()( size_type i, size_type j ) const
    {
        return operator_type()( t1,t2,i,j );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_scalar_binary_expression< E1,E2,M,N,O,L >::result_type const 
        matrix_scalar_binary_expression< E1,E2,M,N,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t1,t2,s );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L > template< class U >
    bool const matrix_scalar_binary_expression< E1,E2,M,N,O,L >::references( scalar< U > const& s ) const
    {
        return ( t1().references( s ) || t2().references( s ) );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_scalar_binary_expression< E1,E2,M,N,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t1().references( v ) || t2().references( v ) );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_scalar_binary_expression< E1,E2,M,N,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t1().references( m ) || t2().references( m ) );
    }

//--
//--

    template< class T1, class T2 >
    struct matrix_scalar_traits
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
        typedef typename expression_traits< T1 >::allocator_type allocator_type;
        typedef typename expression_traits< T1 >::size_type size_type;
        typedef typename matrix_scalar_type< element_type1,element_type2 >::type result_type;

    };

//--
//--

    template< class T1, class T2 >
    struct matrix_scalar_product
        : matrix_scalar_traits< T1,T2 >
    {
        typedef typename matrix_scalar_traits< T1,T2 >::result_type result_type;
        typedef typename matrix_scalar_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename matrix_scalar_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename matrix_scalar_traits< T1,T2 >::size_type size_type;

        result_type& operator()( result_type& r, type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            return r = t1( r,i,j ) * t2();
        }

        result_type& operator()( result_type& r, type_const_reference1 t1, type_const_reference2 t2, size_type s )
        {
            return r = t1( r,s ) * t2();
        }

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            return t1( i,j ) * t2();
        }

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type s )
        {
            return t1( s ) * t2();
        }
    };

    template< class T1, class T2 >
    struct scalar_matrix_product
        : matrix_scalar_traits< T1,T2 >
    {
        typedef typename matrix_scalar_traits< T1,T2 >::result_type result_type;
        typedef typename matrix_scalar_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename matrix_scalar_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename matrix_scalar_traits< T1,T2 >::size_type size_type;

        result_type& operator()( result_type& r, type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            return r = t1() * t2( r,i,j );
        }

        result_type& operator()( result_type& r, type_const_reference1 t1, type_const_reference2 t2, size_type s )
        {
            return r = t1() * t2( r,s );
        }

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            return t1() * t2( i,j );
        }

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type s )
        {
            return t1() * t2( s );
        }
    };

//--

    template< class E1, class E2, std::size_t M, std::size_t N >
    matrix_scalar_binary_expression< E1,E2,M,N,matrix_scalar_product< E1,E2 >,true >
    operator*( matrix_expression< E1,M,N > const& e1, scalar_expression< E2 > const& e2 )
    {
        return matrix_scalar_binary_expression< E1,E2,M,N, 
            matrix_scalar_product< E1,E2 >,true >( e1(), e2() );
    }

    template< class E1, class E2, std::size_t M, std::size_t N >
    matrix_scalar_binary_expression< E1,E2,M,N,scalar_matrix_product< E1,E2 >,true >
    operator*( scalar_expression< E1 > const& e1, matrix_expression< E2,M,N > const& e2 )
    {
        return matrix_scalar_binary_expression< E1,E2,M,N, 
            scalar_matrix_product< E1,E2 >,true >( e1(), e2() );
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_MATH_MATRIX_SCALAR_HPP