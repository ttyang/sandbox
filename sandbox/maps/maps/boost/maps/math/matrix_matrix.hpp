//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_MATH_MATRIX_MATRIX_HPP )
#define BOOST_MAPS_MATH_MATRIX_MATRIX_HPP

#include <boost/maps/math/scalar_scalar.hpp>

namespace boost { namespace maps { 

//--

    template< class E, std::size_t M, std::size_t N >
    class matrix_expression
        : expression< matrix_expression< E,M,N > >
    {
    public:

        typedef matrix_expression type;
        typedef E value_type;
        typedef value_type const& const_reference;
        typedef value_type& reference;

        const_reference operator()() const
        {
            return *static_cast< value_type const* >( this );
        }

        reference operator()()
        {
            return *static_cast< value_type* >( this );
        }

    };

//--

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    class matrix_binary_expression
        : public matrix_expression< matrix_binary_expression< E1,E2,M,N,O,L >,M,N >
    {
    public:

        typedef matrix_binary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef typename E1::type_const_reference expression1_const_reference;
        typedef typename E2::type_const_reference expression2_const_reference;
        typedef E1 expression_type1;
        typedef E2 expression_type2;
        typedef O operator_type;
        typedef typename operator_type::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename operator_type::size_type size_type;
        typedef typename operator_type::allocator_type allocator_type;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = ( L & E1::linear & E2::linear ) };

        matrix_binary_expression( E1 const&, E2 const& );
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
    matrix_binary_expression< E1,E2,M,N,O,L >::matrix_binary_expression( E1 const& e1, E2 const& e2 )
        : t1( e1 ), t2( e2 )
    {}

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_binary_expression< E1,E2,M,N,O,L >::type_reference
        matrix_binary_expression< E1,E2,M,N,O,L >::operator=( type_const_reference e )
    {
        if( &e != this ) { t1 = e.t1; t2 = e.t2; }
        return *this;
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_binary_expression< E1,E2,M,N,O,L >::expression_type1 const& 
        matrix_binary_expression< E1,E2,M,N,O,L >::expression1() const
    {
        return t1;
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_binary_expression< E1,E2,M,N,O,L >::expression_type2 const& 
        matrix_binary_expression< E1,E2,M,N,O,L >::expression2() const
    {
        return t2;
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_binary_expression< E1,E2,M,N,O,L >::reference 
        matrix_binary_expression< E1,E2,M,N,O,L >::operator()( reference r, size_type i, size_type j ) const
    {
        return operator_type()( r,t1,t2,i,j );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_binary_expression< E1,E2,M,N,O,L >::result_type const 
        matrix_binary_expression< E1,E2,M,N,O,L >::operator()( size_type i, size_type j ) const
    {
        return operator_type()( t1,t2,i,j );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_binary_expression< E1,E2,M,N,O,L >::result_type const 
        matrix_binary_expression< E1,E2,M,N,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t1( s ), t2( s ) );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L > template< class U >
    bool const matrix_binary_expression< E1,E2,M,N,O,L >::references( scalar< U > const& s ) const
    {
        return ( t1().references( s ) || t2().references( s ) );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< E1,E2,M,N,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t1().references( v ) || t2().references( v ) );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< E1,E2,M,N,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t1().references( m ) || t2().references( m ) );
    }

//--
//--

    template< class T1, class T2 > struct matrix_matrix_product;

    // matrix product
    template< class E1, class E2, std::size_t M, std::size_t N, bool L >
    class matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >
        : public matrix_expression< matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >,M,N >
    {
    public:

        typedef matrix_binary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef E1 expression_type1;
        typedef E2 expression_type2;
        typedef matrix_matrix_product< E1,E2 > operator_type;
        typedef typename operator_type::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename operator_type::size_type size_type;
        typedef typename operator_type::allocator_type allocator_type;
        typedef matrix< element_type,M,N,false,allocator_type > matrix_type;
        typedef matrix_type expression_type;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = false };

        matrix_binary_expression( E1 const&, E2 const& );

        expression_type const& expression() const;

        const_reference operator()( size_type, size_type ) const;
        const_reference operator()( size_type ) const;

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    private:

        matrix_type t;

    };

//--

    template< class E1, class E2, std::size_t M, std::size_t N, bool L >
    matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >::matrix_binary_expression( E1 const& e1, E2 const& e2 )
    {
        result_type s;
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
        {   s = result_type();
            for( std::size_t k = 0; k != E1::cols; ++k )
                s += e1( i,k ) * e2( k,j );
            t( i,j ) = s;
        }
    }

    template< class E1, class E2, std::size_t M, std::size_t N, bool L >
    typename matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >::expression_type const&
        matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >::expression() const
    {
        return t;
    }

    template< class E1, class E2, std::size_t M, std::size_t N, bool L >
    typename matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >::const_reference
        matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >::operator()( size_type i, size_type j ) const
    {
        return t( i,j );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, bool L >
    typename matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >::const_reference 
        matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >::operator()( size_type s ) const
    {
        return t( s );
    }

    template< class E1, class E2, std::size_t M, std::size_t N, bool L > template< class U >
    bool const matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >::references( scalar< U > const& ) const
    {
        return false;
    }

    template< class E1, class E2, std::size_t M, std::size_t N, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >::references( vector< U,Q,J,B > const& ) const
    {
        return false;
    }

    template< class E1, class E2, std::size_t M, std::size_t N, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,L >::references( matrix< U,P,Q,J,B > const& ) const
    {
        return false;
    }

//--
//--

    // The following specializations are for blocked matrix types.

    // matrix< matrix< ... > > * E
    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    class matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >
        : public matrix_expression< matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >,M,N >
    {
    public:

        typedef matrix_binary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 > expression_type1;
        typedef E expression_type2;
        typedef matrix_matrix_product< expression_type1,expression_type2 > operator_type;
        typedef typename operator_type::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename operator_type::size_type size_type;
        typedef typename operator_type::allocator_type allocator_type;
        typedef matrix< element_type,M,N,true,A2 > matrix_type;
        typedef matrix_type expression_type;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = false };

        matrix_binary_expression( expression_type1 const&, expression_type2 const& );

        expression_type const& expression() const;

        const_reference operator()( size_type, size_type ) const;
        const_reference operator()( size_type ) const;

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    private:

        matrix_type t;

    };

//--

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::matrix_binary_expression( expression_type1 const& e1, expression_type2 const& e2 )
    {
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
        for( std::size_t k = 0; k != R; ++k )
            t( i,j ) += product( e1( i,k ), e2( k,j ) );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::expression_type const&
        matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::expression() const
    {
        return t;
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::const_reference
        matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::operator()( size_type i, size_type j ) const
    {
        return t( i,j );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::const_reference 
        matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::operator()( size_type s ) const
    {
        return t( s );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U >
    bool const matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::references( scalar< U > const& ) const
    {
        return false;
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::references( vector< U,Q,J,B > const& ) const
    {
        return false;
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_matrix_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::references( matrix< U,P,Q,J,B > const& ) const
    {
        return false;
    }

//--
//--

    // E * matrix< matrix< ... > >
    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    class matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >
        : public matrix_expression< matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >,M,N >
    {
    public:

        typedef matrix_binary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef E expression_type1;
        typedef matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > expression_type2;
        typedef matrix_matrix_product< expression_type1,expression_type2 > operator_type;
        typedef typename operator_type::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename operator_type::size_type size_type;
        typedef typename operator_type::allocator_type allocator_type;
        typedef matrix< element_type,M,N,true,A2 > matrix_type;
        typedef matrix_type expression_type;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = false };

        matrix_binary_expression( expression_type1 const&, expression_type2 const& );

        expression_type const& expression() const;

        const_reference operator()( size_type, size_type ) const;
        const_reference operator()( size_type ) const;

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    private:

        matrix_type t;

    };

//--

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::matrix_binary_expression( expression_type1 const& e1, expression_type2 const& e2 )
    {
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
        for( std::size_t k = 0; k != R; ++k )
            t( i,j ) += product( e1( i,k ), e2( k,j ) );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::expression_type const&
        matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::expression() const
    {
        return t;
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::const_reference
        matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::operator()( size_type i, size_type j ) const
    {
        return t( i,j );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::const_reference 
        matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::operator()( size_type s ) const
    {
        return t( s );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U >
    bool const matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::references( scalar< U > const& ) const
    {
        return false;
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::references( vector< U,Q,J,B > const& ) const
    {
        return false;
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_matrix_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::references( matrix< U,P,Q,J,B > const& ) const
    {
        return false;
    }

//--
//--

    // matrix< matrix< ... > > * matrix< matrix< ... > >
    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    class matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >
        : public matrix_expression< matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >,M,N >
    {
    public:

        typedef matrix_binary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 > expression_type1;
        typedef matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > expression_type2;
        typedef matrix_matrix_product< expression_type1,expression_type2 > operator_type;
        typedef typename operator_type::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename operator_type::size_type size_type;
        typedef typename operator_type::allocator_type allocator_type;
        typedef matrix< element_type,M,N,true,A2 > matrix_type;
        typedef matrix_type expression_type;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = false };

        matrix_binary_expression( expression_type1 const&, expression_type2 const& );

        expression_type const& expression() const;

        const_reference operator()( size_type, size_type ) const;
        const_reference operator()( size_type ) const;

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    private:

        matrix_type t;

    };

//--

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::matrix_binary_expression( expression_type1 const& e1, expression_type2 const& e2 )
    {
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
        for( std::size_t k = 0; k != R; ++k )
            t( i,j ) += product( e1( i,k ), e2( k,j ) );
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    typename matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::expression_type const&
        matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::expression() const
    {
        return t;
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    typename matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::const_reference
        matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::operator()( size_type i, size_type j ) const
    {
        return t( i,j );
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    typename matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::const_reference 
        matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::operator()( size_type s ) const
    {
        return t( s );
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L > template< class U >
    bool const matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::references( scalar< U > const& ) const
    {
        return false;
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::references( vector< U,Q,J,B > const& ) const
    {
        return false;
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_matrix_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::references( matrix< U,P,Q,J,B > const& ) const
    {
        return false;
    }

//--
//--

    template< class T1, class T2 > struct matrix_expression_product;

    // matrix product
    // The following specializations are for blocked matrix types.

    // matrix< matrix< ... > > * E
    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    class matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >
        : public matrix_expression< matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >,M,N >
    {
    public:

        typedef matrix_binary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 > expression_type1;
        typedef E expression_type2;
        typedef typename expression_type1::type_const_reference expression1_const_reference;
        typedef typename expression_type2::type_const_reference expression2_const_reference;
        typedef matrix_expression_product< expression_type1,expression_type2 > operator_type;
        typedef typename operator_type::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename result_type::size_type size_type;
        typedef typename result_type::allocator_type allocator_type;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = false };

        matrix_binary_expression( expression_type1 const&, expression_type2 const& );

        expression_type1 const& expression1() const;
        expression_type2 const& expression2() const;

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

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::matrix_binary_expression( expression_type1 const& e1, expression_type2 const& e2 )
        : t1( e1 ), t2( e2 )
    {}

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::expression_type1 const&
        matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::expression1() const
    {
        return t1;
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::expression_type2 const&
        matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::expression2() const
    {
        return t2;
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::result_type const
        matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::operator()( size_type i, size_type j ) const
    {
        return operator_type()( t1,t2,i,j );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::result_type const 
        matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::operator()( size_type s ) const
    {
        return operator_type()( t1( s ), t2( s ) );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U >
    bool const matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::references( scalar< U > const& s ) const
    {
        return ( t1().references( s ) || t2().references( s ) );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t1().references( v ) || t2().references( v ) );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E,M,N,matrix_expression_product< matrix< matrix< T,M1,N1,I1,A1 >,M,R,I2,A2 >,E >,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t1().references( m ) || t2().references( m ) );
    }

//--
//--

    // E * matrix< matrix< ... > >
    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    class matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >
        : public matrix_expression< matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >,M,N >
    {
    public:

        typedef matrix_binary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef E expression_type1;
        typedef matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > expression_type2;
        typedef typename expression_type1::type_const_reference expression1_const_reference;
        typedef typename expression_type2::type_const_reference expression2_const_reference;
        typedef matrix_expression_product< expression_type1,expression_type2 > operator_type;
        typedef typename operator_type::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename result_type::size_type size_type;
        typedef typename result_type::allocator_type allocator_type;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = false };

        matrix_binary_expression( expression_type1 const&, expression_type2 const& );

        expression_type1 const& expression1() const;
        expression_type2 const& expression2() const;

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

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::matrix_binary_expression( expression_type1 const& e1, expression_type2 const& e2 )
        : t1( e1 ), t2( e2 )
    {}

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::expression_type1 const&
        matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::expression1() const
    {
        return t1;
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::expression_type2 const&
        matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::expression2() const
    {
        return t2;
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::result_type const
        matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::operator()( size_type i, size_type j ) const
    {
        return operator_type()( t1,t2,i,j );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L >
    typename matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::result_type const 
        matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::operator()( size_type s ) const
    {
        return operator_type()( t1( s ), t2( s ) );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U >
    bool const matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::references( scalar< U > const& s ) const
    {
        return ( t1().references( s ) || t2().references( s ) );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t1().references( v ) || t2().references( v ) );
    }

    template< class E, class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, std::size_t N, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 >,M,N,matrix_expression_product< E,matrix< matrix< T,M1,N1,I1,A1 >,R,N,I2,A2 > >,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t1().references( m ) || t2().references( m ) );
    }

//--
//--

    // matrix< matrix< ... > > * matrix< matrix< ... > >
    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    class matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >
        : public matrix_expression< matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >,M,N >
    {
    public:

        typedef matrix_binary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 > expression_type1;
        typedef matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > expression_type2;
        typedef typename expression_type1::type_const_reference expression1_const_reference;
        typedef typename expression_type2::type_const_reference expression2_const_reference;
        typedef matrix_expression_product< expression_type1,expression_type2 > operator_type;
        typedef typename operator_type::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename result_type::size_type size_type;
        typedef typename result_type::allocator_type allocator_type;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = false };

        matrix_binary_expression( expression_type1 const&, expression_type2 const& );

        expression_type1 const& expression1() const;
        expression_type2 const& expression2() const;

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

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::matrix_binary_expression( expression_type1 const& e1, expression_type2 const& e2 )
        : t1( e1 ), t2( e2 )
    {}

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    typename matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::expression_type1 const&
        matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::expression1() const
    {
        return t1;
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    typename matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::expression_type2 const&
        matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::expression2() const
    {
        return t2;
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    typename matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::result_type const
        matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::operator()( size_type i, size_type j ) const
    {
        return operator_type()( t1,t2,i,j );
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L >
    typename matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::result_type const 
        matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::operator()( size_type s ) const
    {
        return operator_type()( t1( s ), t2( s ) );
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L > template< class U >
    bool const matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::references( scalar< U > const& s ) const
    {
        return ( t1().references( s ) || t2().references( s ) );
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t1().references( v ) || t2().references( v ) );
    }

    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_binary_expression< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 >,M,N,matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t1().references( m ) || t2().references( m ) );
    }

//--
//--

    template< class T1, class T2 >
    struct matrix_product_traits
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
        typedef typename matrix_product_type< element_type1,element_type2 >::type result_type;

    };

//--
//--

    template< class T1, class T2 >
    struct matrix_matrix_product
        : matrix_product_traits< T1,T2 >
    {
        typedef typename matrix_product_traits< T1,T2 >::result_type result_type;
        typedef typename matrix_product_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename matrix_product_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename matrix_product_traits< T1,T2 >::size_type size_type;

        result_type& operator()( result_type& r, type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            for( size_type k = 0; k != t1.cols; ++k )
                r += t1( r,i,k ) * t2( r,k,j );
            return r;
        }

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            result_type r = result_type();
            for( size_type k = 0; k != t1.cols; ++k )
                r += t1( i,k ) * t2( k,j );
            return r;
        }
    };

//--

    template< class T1, class T2 >
    struct matrix_expression_product
        : matrix_product_traits< T1,T2 >
    {
        typedef typename matrix_product_traits< T1,T2 >::result_type result_type;
        typedef typename matrix_product_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename matrix_product_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename matrix_product_traits< T1,T2 >::size_type size_type;

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            result_type r = result_type();
            for( size_type k = 0; k != t1.cols; ++k )
                r += t1( i,k ) * t2( k,j );
            return r;
        }
    };

    // matrix< matrix< ... > > * T
    template< class T, class T1, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I2, class A2 >
    struct matrix_expression_product< matrix< matrix< T1,M1,N1,I1,A1 >,M,N,I2,A2 >,T >
        : matrix_product_traits< matrix< matrix< T1,M1,N1,I1,A1 >,M,N,I2,A2 >,T >
    {
        typedef matrix_product_traits< matrix< matrix< T1,M1,N1,I1,A1 >,M,N,I2,A2 >,T > traits;
        typedef typename traits::result_type result_type;
        typedef typename traits::type_const_reference1 type_const_reference1;
        typedef typename traits::type_const_reference2 type_const_reference2;
        typedef typename traits::size_type size_type;

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            result_type r = result_type();
            for( size_type k = 0; k != t1.cols; ++k )
                r += product( t1( i,k ), t2( k,j ) );
            return r;
        }
    };

    // T * matrix< matrix< ... > >
    template< class T, class T1, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I2, class A2 >
    struct matrix_expression_product< T,matrix< matrix< T1,M1,N1,I1,A1 >,M,N,I2,A2 > >
        : matrix_product_traits< T,matrix< matrix< T1,M1,N1,I1,A1 >,M,N,I2,A2 > >
    {
        typedef matrix_product_traits< T,matrix< matrix< T1,M1,N1,I1,A1 >,M,N,I2,A2 > > traits;
        typedef typename traits::result_type result_type;
        typedef typename traits::type_const_reference1 type_const_reference1;
        typedef typename traits::type_const_reference2 type_const_reference2;
        typedef typename traits::size_type size_type;

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            result_type r = result_type();
            for( size_type k = 0; k != t1.cols; ++k )
                r += product( t1( i,k ), t2( k,j ) );
            return r;
        }
    };

    // matrix< matrix< ... > > * matrix< matrix< ... > >
    template< class T1, std::size_t M1, std::size_t P1, bool I1, class A1, std::size_t M, std::size_t R, bool I2, class A2, class T2, std::size_t N1, bool I3, class A3, std::size_t N,  bool I4, class A4 >
    struct matrix_expression_product< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >
        : matrix_product_traits< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > >
    {
        typedef matrix_product_traits< matrix< matrix< T1,M1,P1,I1,A1 >,M,R,I2,A2 >,matrix< matrix< T2,P1,N1,I3,A3 >,R,N,I4,A4 > > traits;
        typedef typename traits::result_type result_type;
        typedef typename traits::type_const_reference1 type_const_reference1;
        typedef typename traits::type_const_reference2 type_const_reference2;
        typedef typename traits::size_type size_type;

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            result_type r = result_type();
            for( size_type k = 0; k != t1.cols; ++k )
                r += product( t1( i,k ), t2( k,j ) );
            return r;
        }
    };

//--

    template< class T1, class T2 >
    struct matrix_matrix_addition
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::result_type result_type;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::const_reference1 const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::const_reference2 const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::size_type size_type;

        result_type& operator()( result_type& r, type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            return r = t1( r,i,j ) + t2( r,i,j );
        }

        result_type& operator()( result_type& r, const_reference1 t1, const_reference2 t2 )
        {
            return r = t1 + t2;
        }

        result_type operator()( const_reference1 t1, const_reference2 t2 )
        {
            return t1 + t2;
        }

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            return t1( i,j ) + t2( i,j );
        }
    };

    template< class T1, class T2 >
    struct matrix_matrix_subtraction
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::result_type result_type;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::const_reference1 const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::const_reference2 const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::size_type size_type;

        result_type& operator()( result_type& r, type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            return r = t1( r,i,j ) - t2( r,i,j );
        }

        result_type& operator()( result_type& r, const_reference1 t1, const_reference2 t2 )
        {
            return r = t1 - t2;
        }

        result_type operator()( const_reference1 t1, const_reference2 t2 )
        {
            return t1 - t2;
        }

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            return t1( i,j ) - t2( i,j );
        }
    };

//--
//--

    template< class E1, class E2, std::size_t M, std::size_t P, std::size_t N >
    matrix_binary_expression< E1,E2,M,N,matrix_matrix_product< E1,E2 >,false >
    operator*( matrix_expression< E1,M,P > const& e1, matrix_expression< E2,P,N > const& e2 )
    {
        return matrix_binary_expression< E1,E2,M,N, 
            matrix_matrix_product< E1,E2 >,false >( e1(), e2() );
    }

    template< class E1, class E2, std::size_t M, std::size_t P, std::size_t N >
    matrix_binary_expression< E1,E2,M,N,matrix_expression_product< E1,E2 >,false >
    product( matrix_expression< E1,M,P > const& e1, matrix_expression< E2,P,N > const& e2 )
    {
        return matrix_binary_expression< E1,E2,M,N, 
            matrix_expression_product< E1,E2 >,false >( e1(), e2() );
    }

    template< class E1, class E2, std::size_t M, std::size_t N >
    matrix_binary_expression< E1,E2,M,N,matrix_matrix_addition< E1,E2 >,true >
    operator+( matrix_expression< E1,M,N > const& e1, matrix_expression< E2,M,N > const& e2 )
    {
        return matrix_binary_expression< E1,E2,M,N, 
            matrix_matrix_addition< E1,E2 >,true >( e1(), e2() );
    }

    template< class E1, class E2, std::size_t M, std::size_t N >
    matrix_binary_expression< E1,E2,M,N,matrix_matrix_subtraction< E1,E2 >,true >
    operator-( matrix_expression< E1,M,N > const& e1, matrix_expression< E2,M,N > const& e2 )
    {
        return matrix_binary_expression< E1,E2,M,N, 
            matrix_matrix_subtraction< E1,E2 >,true >( e1(), e2() );
    }

//--

    template< class T1, class T2 >
    struct matrix_matrix_assign
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::reference1 reference1;
        typedef typename expression_binary_traits< T1,T2 >::const_reference2 const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::type_reference1 type_reference1;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::size_type size_type;

        void operator()( reference1 t1, const_reference2 t2 )
        {
            t1 = t2;
        }

        void operator()( type_reference1 t1, type_const_reference2 t2, size_type i, size_type j )
        {
            t1( i,j ) = t2( i,j );
        }
    };

//--

    template< class T, class E, std::size_t M, std::size_t N, class O, bool L, bool C >
    struct matrix_assign
    {
        typedef T& reference;
        typedef matrix_expression< E,M,N > const& expression_const_reference;
        typedef O operator_type;

        void operator()( reference m, expression_const_reference e )
        {
            if( e().references( m ) )
            {   T t;
                for( std::size_t i = 0; i != M; ++i )
                for( std::size_t j = 0; j != N; ++j )
                    operator_type()( t( i,j ), e()( i,j ) );
                t.swap( m );
            }else
            {   for( std::size_t i = 0; i != M; ++i )
                for( std::size_t j = 0; j != N; ++j )
                    operator_type()( m( i,j ), e()( i,j ) );
            }
        }
    };

//--

    template< class T, class E, std::size_t M, std::size_t N, class O, bool C >
    struct matrix_assign< T,E,M,N,O,true,C >
    {
        typedef T& reference;
        typedef matrix_expression< E,M,N > const& expression_const_reference;
        typedef O operator_type;

        void operator()( reference m, expression_const_reference e )
        {
            for( std::size_t i = 0; i != m.size; ++i )
                operator_type()( m( i ), e()( i ) );
        }
    };

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A, class E, class O, bool C >
    struct matrix_assign< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,E,M,N,O,true,C >
    {
        typedef matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >& reference;
        typedef matrix_expression< E,M,N > const& expression_const_reference;

        void operator()( reference m, expression_const_reference e )
        {
            for( std::size_t i = 0; i != M; ++i )
            for( std::size_t j = 0; j != N; ++j )
                e()( m( i,j ),i,j );
        }
    };

//--

    template< class T, class E, std::size_t M, std::size_t N, class O >
    struct matrix_assign< T,E,M,N,O,false,true >
    {
        typedef T& reference;
        typedef matrix_expression< E,M,N > const& expression_const_reference;
        typedef O operator_type;

        void operator()( reference m, expression_const_reference e )
        {
            for( std::size_t i = 0; i != M; ++i )
            for( std::size_t j = 0; j != N; ++j )
                operator_type()( m( i,j ), e()( i,j ) );
        }
    };

//--
//--

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    class matrix_unary_expression
        : public matrix_expression< matrix_unary_expression< E,M,N,O,L >,M,N >
    {
    public:

        typedef matrix_unary_expression type;
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

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = ( L & E::linear ) };

        matrix_unary_expression( E const& );
        type_reference operator=( type_const_reference );

        expression_type const& expression() const;

        result_type const operator()( reference, size_type, size_type ) const;
        result_type const operator()( size_type, size_type ) const;
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

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    matrix_unary_expression< E,M,N,O,L >::matrix_unary_expression( E const& e )
        : t( e )
    {}

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_unary_expression< E,M,N,O,L >::type_reference
        matrix_unary_expression< E,M,N,O,L >::operator=( type_const_reference e )
    {
        if( &e != this ) t = e.t;
        return *this;
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_unary_expression< E,M,N,O,L >::expression_type const& 
        matrix_unary_expression< E,M,N,O,L >::expression() const
    {
        return t;
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_unary_expression< E,M,N,O,L >::result_type const 
        matrix_unary_expression< E,M,N,O,L >::operator()( reference r, size_type i, size_type j ) const
    {
        return operator_type()( r,t,i,j );
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_unary_expression< E,M,N,O,L >::result_type const 
        matrix_unary_expression< E,M,N,O,L >::operator()( size_type i, size_type j ) const
    {
        return operator_type()( t,i,j );
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_unary_expression< E,M,N,O,L >::result_type const 
        matrix_unary_expression< E,M,N,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t( s ) );
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L > template< class U >
    bool const matrix_unary_expression< E,M,N,O,L >::references( scalar< U > const& s ) const
    {
        return ( t().references( s ) );
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_unary_expression< E,M,N,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t().references( v ) );
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_unary_expression< E,M,N,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t().references( m ) );
    }

//--
//--

    template< class T > struct matrix_transpose;

    // matrix transpose matrix< matrix< ... > >
    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A, bool L >
    class matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >
        : public matrix_expression< matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >,N,M >
    {
    public:

        typedef matrix_unary_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > expression_type1;
        typedef expression_type1 const& expression_const_reference;
        typedef matrix_transpose< expression_type1 > operator_type;
        typedef typename operator_type::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename operator_type::size_type size_type;
        typedef typename operator_type::allocator_type allocator_type;
        typedef typename matrix_transpose_type< expression_type1 >::type matrix_type;
        typedef matrix_type expression_type;

        using matrix_expression< type,N,M >::operator();

        enum { rows = N, cols = M };
        enum { linear = false };

        matrix_unary_expression( expression_const_reference );
        
        type_reference operator=( type_const_reference );

        expression_type const& expression() const;

        const_reference operator()( size_type, size_type ) const;
        const_reference operator()( size_type ) const;

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    private:

        matrix_type t;

    };

//--

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A, bool L >
    matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::matrix_unary_expression( expression_const_reference e )
    {
        operator_type()( t,e );
    }

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A, bool L >
    typename matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::type_reference
        matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::operator=( type_const_reference e )
    {
        if( &e != this ) t = e.t;
        return *this;
    }

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A, bool L >
    typename matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::expression_type const& 
        matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::expression() const
    {
        return t;
    }

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A, bool L >
    typename matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::const_reference 
        matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::operator()( size_type i, size_type j ) const
    {
        return t( i,j );
    }

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A, bool L >
    typename matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::const_reference 
        matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::operator()( size_type s ) const
    {
        return t( s );
    }

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A, bool L > template< class U >
    bool const matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::references( scalar< U > const& ) const
    {
        return false;
    }

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::references( vector< U,Q,J,B > const& ) const
    {
        return false;
    }

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_unary_expression< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A >,N,M,matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >,L >::references( matrix< U,P,Q,J,B > const& ) const
    {
        return false;
    }

//--
//--

    template< class T >
    struct matrix_transpose_traits
    {
        typedef typename matrix_transpose_type< T >::type T1;
        typedef typename expression_traits< T1 >::type_const_reference type_const_reference1;
        typedef typename expression_traits< T >::type_const_reference type_const_reference2;
        typedef typename expression_traits< T1 >::type_reference type_reference1;
        typedef typename expression_traits< T >::type_reference type_reference2;
        typedef typename expression_traits< T1 >::const_reference const_reference1;
        typedef typename expression_traits< T >::const_reference const_reference2;
        typedef typename expression_traits< T1 >::reference reference1;
        typedef typename expression_traits< T >::reference reference2;
        typedef typename expression_traits< T1 >::element_type element_type1;
        typedef typename expression_traits< T >::element_type element_type2;
        typedef typename expression_traits< T1 >::allocator_type allocator_type;
        typedef typename expression_traits< T1 >::size_type size_type;
        typedef element_type1 result_type;

    };

//--
//--

    namespace detail {

    template< class T, bool E >
    struct matrix_transpose
        : matrix_transpose_traits< T >
    {
        typedef typename matrix_transpose_traits< T >::result_type result_type;
        typedef typename matrix_transpose_traits< T >::const_reference2 const_reference2;

        result_type operator()( const_reference2 t )
        {
            return transpose( t );
        }
    };

    template< class T >
    struct matrix_transpose< T,false >
        : matrix_transpose_traits< T >
    {
        typedef typename matrix_transpose_traits< T >::const_reference2 const_reference2;

        const_reference2 operator()( const_reference2 t )
        {
            return t;
        }
    };

    } // namespace detail

    template< class T >
    struct matrix_transpose
        : matrix_transpose_traits< T >
    {
        typedef typename matrix_transpose_traits< T >::result_type result_type;
        typedef typename matrix_transpose_traits< T >::type_const_reference2 type_const_reference2;
        typedef typename matrix_transpose_traits< T >::type_reference1 type_reference1;
        typedef typename matrix_transpose_traits< T >::size_type size_type;

        result_type operator()( type_const_reference2 t, size_type i, size_type j )
        {
            return detail::matrix_transpose< T,is_matrix< result_type >::type::value >()( t( j,i ) );
        }

        void operator()( type_reference1 t1, type_const_reference2 t2 )
        {
            for( std::size_t i = 0; i != t2.rows; ++i )
            for( std::size_t j = 0; j != t2.cols; ++j )
                t1( j,i ) = t2( i,j );
        }
    };

    template< class T, std::size_t M1, std::size_t N1, bool I1, class A1, std::size_t M, std::size_t N, bool I, class A >
    struct matrix_transpose< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >
        : matrix_transpose_traits< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > >
    {
        typedef matrix_transpose_traits< matrix< matrix< T,M1,N1,I1,A1 >,M,N,I,A > > traits;
        typedef typename traits::type_reference1 type_reference1;
        typedef typename traits::type_const_reference2 type_const_reference2;

        void operator()( type_reference1 t1, type_const_reference2 t2 )
        {
            for( std::size_t i = 0; i != M; ++i )
            for( std::size_t j = 0; j != N; ++j )
                matrix_transpose< matrix< T,M1,N1,I1,A1 > >()( t1( j,i ), t2( i,j ) );
        }
    };

    template< class T >
    struct matrix_scalar_negate
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return -t( i,j );
        }

        result_type operator()( const_reference t )
        {
            return -t;
        }
    };

    template< class T >
    struct matrix_scalar_sin
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::sin( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::sin( t );
        }
    };

    template< class T >
    struct matrix_scalar_cos
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::cos( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::cos( t );
        }
    };

    template< class T >
    struct matrix_scalar_tan
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::tan( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::tan( t );
        }
    };

    template< class T >
    struct matrix_scalar_cosec
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return T(1) / std::sin( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return T(1) / std::sin( t );
        }
    };

    template< class T >
    struct matrix_scalar_sec
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return T(1) / std::cos( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return T(1) / std::cos( t );
        }
    };

    template< class T >
    struct matrix_scalar_cot
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return T(1) / std::tan( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return T(1) / std::tan( t );
        }
    };

    template< class T >
    struct matrix_scalar_sinh
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::sinh( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::sinh( t );
        }
    };

    template< class T >
    struct matrix_scalar_cosh
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::cosh( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::cosh( t );
        }
    };

    template< class T >
    struct matrix_scalar_tanh
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::tanh( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::tanh( t );
        }
    };

    template< class T >
    struct matrix_scalar_cosech
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return T(1) / std::sinh( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return T(1) / std::sinh( t );
        }
    };

    template< class T >
    struct matrix_scalar_sech
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return T(1) / std::cosh( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return T(1) / std::cosh( t );
        }
    };

    template< class T >
    struct matrix_scalar_coth
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return T(1) / std::tanh( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return T(1) / std::tanh( t );
        }
    };

    template< class T >
    struct matrix_scalar_asin
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::asin( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::asin( t );
        }
    };

    template< class T >
    struct matrix_scalar_asin< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return math::asin( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return math::asin( t );
        }
    };

    template< class T >
    struct matrix_scalar_acos
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::acos( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::cos( t );
        }
    };

    template< class T >
    struct matrix_scalar_acos< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return math::acos( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return math::acos( t );
        }
    };

    template< class T >
    struct matrix_scalar_atan
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::atan( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::atan( t );
        }
    };

    template< class T >
    struct matrix_scalar_atan< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return math::atan( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return math::atan( t );
        }
    };

    template< class T >
    struct matrix_scalar_asinh
        : expression_unary_traits< T >
    {};

    template< class T >
    struct matrix_scalar_acosh
        : expression_unary_traits< T >
    {};

    template< class T >
    struct matrix_scalar_atanh
        : expression_unary_traits< T >
    {};

    template< class T >
    struct matrix_scalar_asinh< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return math::asinh( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return math::asinh( t );
        }
    };

    template< class T >
    struct matrix_scalar_acosh< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return math::acosh( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return math::acosh( t );
        }
    };

    template< class T >
    struct matrix_scalar_atanh< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return math::atanh( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return math::atanh( t );
        }
    };

    template< class T >
    struct matrix_scalar_exp
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::exp( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::exp( t );
        }
    };

    template< class T >
    struct matrix_scalar_log
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::log( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::log( t );
        }
    };

    template< class T >
    struct matrix_scalar_log10
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::log10( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::log10( t );
        }
    };

    template< class T >
    struct matrix_scalar_sqrt
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::sqrt( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::sqrt( t );
        }
    };

    template< class T >
    struct matrix_scalar_abs
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::abs( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::abs( t );
        }
    };

    template< class T >
    struct matrix_scalar_fabs
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::const_reference const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return std::fabs( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return std::fabs( t );
        }
    };

    template< class T >
    struct matrix_scalar_fabs< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;
        typedef typename expression_unary_traits< std::complex< T > >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i, size_type j )
        {
            return math::fabs( t( i,j ) );
        }

        result_type operator()( const_reference t )
        {
            return math::fabs( t );
        }
    };

//--

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,N,M,matrix_transpose< E >,false >
    transpose( matrix_expression< E,M,N > const& e )
    {
         return matrix_unary_expression< E,N,M,matrix_transpose< E >,false >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_negate< E >,true >
    operator-( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_negate< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_sin< E >,true >
    sin( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_sin< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_cos< E >,true >
    cos( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_cos< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_tan< E >,true >
    tan( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_tan< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_cosec< E >,true >
    cosec( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_cosec< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_sec< E >,true >
    sec( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_sec< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_cot< E >,true >
    cot( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_cot< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_sinh< E >,true >
    sinh( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_sinh< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_cosh< E >,true >
    cosh( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_cosh< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_tanh< E >,true >
    tanh( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_tanh< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_cosech< E >,true >
    cosech( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_cosech< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_sech< E >,true >
    sech( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_sech< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_coth< E >,true >
    coth( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_coth< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_asin< E >,true >
    asin( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_asin< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_acos< E >,true >
    acos( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_acos< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_atan< E >,true >
    atan( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_atan< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_asinh< E >,true >
    asinh( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_asinh< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_acosh< E >,true >
    acosh( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_acosh< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_atanh< E >,true >
    atanh( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_atanh< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_exp< E >,true >
    exp( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_exp< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_log< E >,true >
    log( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_log< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_log10< E >,true >
    log10( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_log10< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_sqrt< E >,true >
    sqrt( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_sqrt< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_abs< E >,true >
    abs( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_abs< E >,true >( e() );
    }

    template< class E, std::size_t M, std::size_t N >
    matrix_unary_expression< E,M,N,matrix_scalar_fabs< E >,true >
    fabs( matrix_expression< E,M,N > const& e )
    {
        return matrix_unary_expression< E,M,N,matrix_scalar_fabs< E >,true >( e() );
    }

//--

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    class matrix_matrix_expression
        : public matrix_expression< matrix_matrix_expression< E,M,N,O,L >,M,N >
    {
    public:

        typedef matrix_matrix_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef E expression_type;
        typedef O operator_type;
        typedef typename O::result_type result_type;
        typedef result_type element_type;
        typedef element_type const& const_reference;
        typedef element_type& reference;
        typedef typename operator_type::size_type size_type;
        typedef typename operator_type::allocator_type allocator_type;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N };
        enum { linear = ( L & E::linear ) };

        matrix_matrix_expression();

        result_type const operator()( size_type, size_type ) const;
        result_type const operator()( size_type ) const;

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    };

//--

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    matrix_matrix_expression< E,M,N,O,L >::matrix_matrix_expression()
    {}

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_matrix_expression< E,M,N,O,L >::result_type const 
        matrix_matrix_expression< E,M,N,O,L >::operator()( size_type i, size_type j ) const
    {
        return operator_type()( i,j );
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L >
    typename matrix_matrix_expression< E,M,N,O,L >::result_type const 
        matrix_matrix_expression< E,M,N,O,L >::operator()( size_type s ) const
    {
        return operator_type()( s );
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L > template< class U >
    bool const matrix_matrix_expression< E,M,N,O,L >::references( scalar< U > const& ) const
    {
        return false;
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const matrix_matrix_expression< E,M,N,O,L >::references( vector< U,Q,J,B > const& ) const
    {
        return false;
    }

    template< class E, std::size_t M, std::size_t N, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const matrix_matrix_expression< E,M,N,O,L >::references( matrix< U,P,Q,J,B > const& ) const
    {
        return false;
    }

//--

    template< class T >
    struct matrix_matrix_zero
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( size_type, size_type )
        {
            return result_type(0);
        }

        result_type operator()( size_type )
        {
            return result_type(0);
        }
    };

    template< class T >
    struct matrix_matrix_identity
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( size_type i, size_type j )
        {
            return i == j ? result_type(1) : result_type(0);
        }

        result_type operator()( size_type s )
        {
            return ((s % (T::cols + 1)) == 0) ? result_type(1) : result_type(0);
        }
    };

//--

    template< class T, std::size_t M, std::size_t N >
    matrix_matrix_expression< matrix< T,M,N >,M,N,matrix_matrix_zero< matrix< T,M,N > >,true >
    matrix_zero()
    {
        return matrix_matrix_expression< matrix< T,M,N >,M,N, 
            matrix_matrix_zero< matrix< T,M,N > >,true >();
    }

    template< class T, std::size_t N >
    matrix_matrix_expression< matrix< T,N,N >,N,N,matrix_matrix_identity< matrix< T,N,N > >,true >
    matrix_identity()
    {
        return matrix_matrix_expression< matrix< T,N,N >,N,N, 
            matrix_matrix_identity< matrix< T,N,N > >,true >();
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_MATH_MATRIX_MATRIX_HPP