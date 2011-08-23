//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_MATH_VECTOR_MATRIX_HPP )
#define BOOST_MAPS_MATH_VECTOR_MATRIX_HPP

#include <boost/maps/math/vector_vector.hpp>
#include <boost/maps/math/matrix_matrix.hpp>

namespace boost { namespace maps {

//--

    template< class E1, class E2, std::size_t N, class O, bool L >
    class vector_matrix_binary_expression
        : public vector_expression< vector_matrix_binary_expression< E1,E2,N,O,L >,N >
    {
    public:

        typedef vector_matrix_binary_expression type;
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

        using vector_expression< type,N >::operator();

        enum { size = N };
        enum { linear = ( L & E1::linear & E2::linear ) };

        vector_matrix_binary_expression( E1 const&, E2 const& );
        type_reference operator=( type_const_reference );

        expression_type1 const& expression1() const;
        expression_type2 const& expression2() const;

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

    template< class E1, class E2, std::size_t N, class O, bool L >
    vector_matrix_binary_expression< E1,E2,N,O,L >::vector_matrix_binary_expression( E1 const& e1, E2 const& e2 )
        : t1( e1 ), t2( e2 )
    {}

    template< class E1, class E2, std::size_t N, class O, bool L >
    typename vector_matrix_binary_expression< E1,E2,N,O,L >::type_reference
        vector_matrix_binary_expression< E1,E2,N,O,L >::operator=( type_const_reference e )
    {
        if( &e != this ) { t1 = e.t1; t2 = e.t2; }
        return *this;
    }

    template< class E1, class E2, std::size_t N, class O, bool L >
    typename vector_matrix_binary_expression< E1,E2,N,O,L >::expression_type1 const& 
        vector_matrix_binary_expression< E1,E2,N,O,L >::expression1() const
    {
        return t1;
    }

    template< class E1, class E2, std::size_t N, class O, bool L >
    typename vector_matrix_binary_expression< E1,E2,N,O,L >::expression_type2 const& 
        vector_matrix_binary_expression< E1,E2,N,O,L >::expression2() const
    {
        return t2;
    }

    template< class E1, class E2, std::size_t N, class O, bool L >
    typename vector_matrix_binary_expression< E1,E2,N,O,L >::result_type const 
        vector_matrix_binary_expression< E1,E2,N,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t1,t2,s );
    }

    template< class E1, class E2, std::size_t N, class O, bool L > template< class U >
    bool const vector_matrix_binary_expression< E1,E2,N,O,L >::references( scalar< U > const& s ) const
    {
        return ( t1().references( s ) || t2().references( s ) );
    }

    template< class E1, class E2, std::size_t N, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const vector_matrix_binary_expression< E1,E2,N,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t1().references( v ) || t2().references( v ) );
    }

    template< class E1, class E2, std::size_t N, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const vector_matrix_binary_expression< E1,E2,N,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t1().references( m ) || t2().references( m ) );
    }

//--
//--

    template< class T1, class T2 >
    struct matrix_vector_traits
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
        typedef typename vector_matrix_type< element_type1,element_type2 >::type result_type;

    };

//--
//--

    template< class T1, class T2 >
    struct matrix_vector_product
        : matrix_vector_traits< T1,T2 >
    {
        typedef typename matrix_vector_traits< T1,T2 >::result_type result_type;
        typedef typename matrix_vector_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename matrix_vector_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename matrix_vector_traits< T1,T2 >::const_reference1 const_reference1;
        typedef typename matrix_vector_traits< T1,T2 >::const_reference2 const_reference2;
        typedef typename matrix_vector_traits< T1,T2 >::size_type size_type;

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type s )
        {
            result_type r = result_type();
            for( size_type k = 0; k != t1.cols; ++k )
                r += t1( s,k ) * t2( k );
            return r;
        }

        result_type operator()( const_reference1 t1, const_reference2 t2 )
        {
            return t1 * t2;
        }
    };

    template< class T1, class T2 >
    struct vector_matrix_product
        : matrix_vector_traits< T1,T2 >
    {
        typedef typename matrix_vector_traits< T1,T2 >::result_type result_type;
        typedef typename matrix_vector_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename matrix_vector_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename matrix_vector_traits< T1,T2 >::const_reference1 const_reference1;
        typedef typename matrix_vector_traits< T1,T2 >::const_reference2 const_reference2;
        typedef typename matrix_vector_traits< T1,T2 >::size_type size_type;

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2, size_type s )
        {
            result_type r = result_type();
            for( size_type k = 0; k != t2.rows; ++k )
                r += t1( k ) * t2( k,s );
            return r;
        }

        result_type operator()( const_reference1 t1, const_reference2 t2 )
        {
            return t1 * t2;
        }
    };

//--

    template< class E1, class E2, std::size_t M, std::size_t N >
    vector_matrix_binary_expression< E1,E2,M,matrix_vector_product< E1,E2 >,false >
    operator*( matrix_expression< E1,M,N > const& e1, vector_expression< E2,N > const& e2 )
    {
        return vector_matrix_binary_expression< E1,E2,M, 
            matrix_vector_product< E1,E2 >,false >( e1(), e2() );
    }

    template< class E1, class E2, std::size_t M, std::size_t N >
    vector_matrix_binary_expression< E1,E2,N,vector_matrix_product< E1,E2 >,false >
    operator*( vector_expression< E1,M > const& e1, matrix_expression< E2,M,N > const& e2 )
    {
        return vector_matrix_binary_expression< E1,E2,N, 
            vector_matrix_product< E1,E2 >,false >( e1(), e2() );
    }

//--
//--

    template< class E, std::size_t N, class O, bool L >
    class vector_matrix_unary_expression
        : public vector_expression< vector_matrix_unary_expression< E,N,O,L >,N >
    {
    public:

        typedef vector_matrix_unary_expression type;
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

        using vector_expression< type,N >::operator();

        enum { size = N };
        enum { linear = ( L & E::linear ) };

        vector_matrix_unary_expression( E const& );
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

    template< class E, std::size_t N, class O, bool L >
    vector_matrix_unary_expression< E,N,O,L >::vector_matrix_unary_expression( E const& e )
        : t( e )
    {}

    template< class E, std::size_t N, class O, bool L >
    typename vector_matrix_unary_expression< E,N,O,L >::type_reference
        vector_matrix_unary_expression< E,N,O,L >::operator=( type_const_reference e )
    {
        if( &e != this ) { t = e.t; }
        return *this;
    }

    template< class E, std::size_t N, class O, bool L >
    typename vector_matrix_unary_expression< E,N,O,L >::expression_type const& 
        vector_matrix_unary_expression< E,N,O,L >::expression() const
    {
        return t;
    }

    template< class E, std::size_t N, class O, bool L >
    typename vector_matrix_unary_expression< E,N,O,L >::result_type const 
        vector_matrix_unary_expression< E,N,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t,s );
    }

    template< class E, std::size_t N, class O, bool L > template< class U >
    bool const vector_matrix_unary_expression< E,N,O,L >::references( scalar< U > const& s ) const
    {
        return ( t().references( s ) );
    }

    template< class E, std::size_t N, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const vector_matrix_unary_expression< E,N,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t().references( v ) );
    }

    template< class E, std::size_t N, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const vector_matrix_unary_expression< E,N,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t().references( m ) );
    }

//--
//--

    template< class T >
    struct matrix_trace
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t, size_type i )
        {
            return t( i,i );
        }
    };

//--

    template< class E, std::size_t N >
    vector_matrix_unary_expression< E,N,matrix_trace< E >,true >
    trace( matrix_expression< E,N,N > const& e )
    {
         return vector_matrix_unary_expression< E,N,matrix_trace< E >,true >( e() );
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_MATH_VECTOR_MATRIX_HPP