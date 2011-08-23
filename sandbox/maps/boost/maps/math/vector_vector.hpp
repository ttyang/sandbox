//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_MATH_VECTOR_VECTOR_HPP )
#define BOOST_MAPS_MATH_VECTOR_VECTOR_HPP

#include <boost/maps/math/scalar_scalar.hpp>

namespace boost { namespace maps {

//--

    template< class E, std::size_t N >
    class vector_expression
        : expression< vector_expression< E,N > >
    {
    public:

        typedef vector_expression type;
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

    template< class E1, class E2, std::size_t N, class O, bool L >
    class vector_binary_expression
        : public vector_expression< vector_binary_expression< E1,E2,N,O,L >,N >
    {
    public:

        typedef vector_binary_expression type;
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

        vector_binary_expression( E1 const&, E2 const& );
        type_reference operator=( type_const_reference );

        expression_type1 const& expression1() const;
        expression_type2 const& expression2() const;

        reference operator()( reference, size_type ) const;
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
    vector_binary_expression< E1,E2,N,O,L >::vector_binary_expression( E1 const& e1, E2 const& e2 )
        : t1( e1 ), t2( e2 )
    {}

    template< class E1, class E2, std::size_t N, class O, bool L >
    typename vector_binary_expression< E1,E2,N,O,L >::type_reference
        vector_binary_expression< E1,E2,N,O,L >::operator=( type_const_reference e )
    {
        if( &e != this ) { t1 = e.t1; t2 = e.t2; }
        return *this;
    }

    template< class E1, class E2, std::size_t N, class O, bool L >
    typename vector_binary_expression< E1,E2,N,O,L >::expression_type1 const& 
        vector_binary_expression< E1,E2,N,O,L >::expression1() const
    {
        return t1;
    }

    template< class E1, class E2, std::size_t N, class O, bool L >
    typename vector_binary_expression< E1,E2,N,O,L >::expression_type2 const& 
        vector_binary_expression< E1,E2,N,O,L >::expression2() const
    {
        return t2;
    }

    template< class E1, class E2, std::size_t N, class O, bool L >
    typename vector_binary_expression< E1,E2,N,O,L >::reference 
        vector_binary_expression< E1,E2,N,O,L >::operator()( reference r, size_type s ) const
    {
        return operator_type()( r,t1,t2,s );
    }

    template< class E1, class E2, std::size_t N, class O, bool L >
    typename vector_binary_expression< E1,E2,N,O,L >::result_type const 
        vector_binary_expression< E1,E2,N,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t1( s ), t2( s ) );
    }

    template< class E1, class E2, std::size_t N, class O, bool L > template< class U >
    bool const vector_binary_expression< E1,E2,N,O,L >::references( scalar< U > const& s ) const
    {
        return ( t1().references( s ) || t2().references( s ) );
    }

    template< class E1, class E2, std::size_t N, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const vector_binary_expression< E1,E2,N,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t1().references( v ) || t2().references( v ) );
    }

    template< class E1, class E2, std::size_t N, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const vector_binary_expression< E1,E2,N,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t1().references( m ) || t2().references( m ) );
    }

//--
//--

    template< class T1, class T2 >
    struct vector_vector_addition
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::result_type result_type;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::const_reference1 const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::const_reference2 const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::size_type size_type;

        result_type& operator()( result_type& r, type_const_reference1 t1, type_const_reference2 t2, size_type s )
        {
            return r = t1( s ) + t2( s );
        }

        result_type operator()( const_reference1 t1, const_reference2 t2 )
        {
            return t1 + t2;
        }
    };

    template< class T1, class T2 >
    struct vector_vector_subtraction
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::result_type result_type;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::const_reference1 const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::const_reference2 const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::size_type size_type;

        result_type& operator()( result_type& r, type_const_reference1 t1, type_const_reference2 t2, size_type s )
        {
            return r = t1( s ) - t2( s );
        }

        result_type operator()( const_reference1 t1, const_reference2 t2 )
        {
            return t1 - t2;
        }
    };

//--

    template< class E1, class E2, std::size_t N >
    vector_binary_expression< E1,E2,N,vector_vector_addition< E1,E2 >,true >
    operator+( vector_expression< E1,N > const& e1, vector_expression< E2,N > const& e2 )
    {
        return vector_binary_expression< E1,E2,N, 
            vector_vector_addition< E1,E2 >,true >( e1(), e2() );
    }

    template< class E1, class E2, std::size_t N >
    vector_binary_expression< E1,E2,N,vector_vector_subtraction< E1,E2 >,true >
    operator-( vector_expression< E1,N > const& e1, vector_expression< E2,N > const& e2 )
    {
        return vector_binary_expression< E1,E2,N, 
            vector_vector_subtraction< E1,E2 >,true >( e1(), e2() );
    }

//--

    template< class T1, class T2 >
    struct vector_vector_assign
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::reference1 reference1;
        typedef typename expression_binary_traits< T1,T2 >::const_reference2 const_reference2;

        void operator()( reference1 t1, const_reference2 t2 )
        {
            t1 = t2;
        }
    };

//--

    template< class T, class E, std::size_t N, class O, bool L, bool C >
    struct vector_assign
    {
        typedef T type;
        typedef type& reference;
        typedef vector_expression< E,N > const& expression_const_reference;
        typedef O operator_type;

        void operator()( reference v, expression_const_reference e )
        {
            if( e().references( v ) )
            {   type t;
                for( std::size_t i = 0; i != N; ++i )
                    operator_type()( t( i ), e()( i ) );
                t.swap( v );
            }else
            {   for( std::size_t i = 0; i != N; ++i )
                    operator_type()( v( i ), e()( i ) );
            }
        }
    };

//--

    template< class T, class E, std::size_t N, class O, bool C >
    struct vector_assign< T,E,N,O,true,C >
    {
        typedef T& reference;
        typedef vector_expression< E,N > const& expression_const_reference;
        typedef O operator_type;

        void operator()( reference v, expression_const_reference e )
        {
            for( std::size_t i = 0; i != N; ++i ) 
                operator_type()( v( i ), e()( i ) );
        }
    };

    template< class T, std::size_t N1, bool I1, class A1, std::size_t N, bool I, class A, class E, class O, bool C >
    struct vector_assign< vector< vector< T,N1,I1,A1 >,N,I,A >,E,N,O,true,C >
    {
        typedef vector< vector< T,N1,I1,A1 >,N,I,A >& reference;
        typedef vector_expression< E,N > const& expression_const_reference;

        void operator()( reference v, expression_const_reference e )
        {
            for( std::size_t i = 0; i != N; ++i )
                e()( v( i ),i );
        }
    };

//--

    template< class T, class E, std::size_t N, class O >
    struct vector_assign< T,E,N,O,false,true >
    {
        typedef T& reference;
        typedef vector_expression< E,N > const& expression_const_reference;
        typedef O operator_type;

        void operator()( reference v, expression_const_reference e )
        {
            for( std::size_t i = 0; i != N; ++i )
                operator_type()( v( i ), e()( i ) );
        }
    };

//--
//--

    template< class E, std::size_t N, class O, bool L >
    class vector_unary_expression
        : public vector_expression< vector_unary_expression< E,N,O,L >,N >
    {
    public:

        typedef vector_unary_expression type;
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

        vector_unary_expression( E const& );

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
    vector_unary_expression< E,N,O,L >::vector_unary_expression( E const& e )
        : t( e )
    {}

    template< class E, std::size_t N, class O, bool L >
    typename vector_unary_expression< E,N,O,L >::expression_type const& 
        vector_unary_expression< E,N,O,L >::expression() const
    {
        return t;
    }

    template< class E, std::size_t N, class O, bool L >
    typename vector_unary_expression< E,N,O,L >::result_type const 
        vector_unary_expression< E,N,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t( s ) );
    }

    template< class E, std::size_t N, class O, bool L > template< class U >
    bool const vector_unary_expression< E,N,O,L >::references( scalar< U > const& s ) const
    {
        return ( t().references( s ) );
    }

    template< class E, std::size_t N, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const vector_unary_expression< E,N,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t().references( v ) );
    }

    template< class E, std::size_t N, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const vector_unary_expression< E,N,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t().references( m ) );
    }

//--

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_negate< E >,true >
    operator-( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_negate< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_sin< E >,true >
    sin( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_sin< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_cos< E >,true >
    cos( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_cos< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_tan< E >,true >
    tan( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_tan< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_cosec< E >,true >
    cosec( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_cosec< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_sec< E >,true >
    sec( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_sec< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_cot< E >,true >
    cot( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_cot< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_sinh< E >,true >
    sinh( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_sinh< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_cosh< E >,true >
    cosh( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_cosh< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_tanh< E >,true >
    tanh( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_tanh< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_cosech< E >,true >
    cosech( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_cosech< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_sech< E >,true >
    sech( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_sech< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_coth< E >,true >
    coth( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_coth< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_asin< E >,true >
    asin( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_asin< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_acos< E >,true >
    acos( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_acos< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_atan< E >,true >
    atan( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_atan< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_asinh< E >,true >
    asinh( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_asinh< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_acosh< E >,true >
    acosh( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_acosh< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_atanh< E >,true >
    atanh( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_atanh< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_exp< E >,true >
    exp( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_exp< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_log< E >,true >
    log( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_log< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_log10< E >,true >
    log10( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_log10< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_sqrt< E >,true >
    sqrt( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_sqrt< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_abs< E >,true >
    abs( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_abs< E >,true >( e() );
    }

    template< class E, std::size_t N >
    vector_unary_expression< E,N,scalar_fabs< E >,true >
    fabs( vector_expression< E,N > const& e )
    {
        return vector_unary_expression< E,N,scalar_fabs< E >,true >( e() );
    }

//--
//--

    template< class E, std::size_t N, class O, bool L >
    class vector_vector_expression
        : public vector_expression< vector_vector_expression< E,N,O,L >,N >
    {
    public:

        typedef vector_vector_expression type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
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

        vector_vector_expression();

        result_type const operator()( size_type ) const;

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    };

//--

    template< class E, std::size_t N, class O, bool L > 
    vector_vector_expression< E,N,O,L >::vector_vector_expression()
    {}

    template< class E, std::size_t N, class O, bool L >
    typename vector_vector_expression< E,N,O,L >::result_type const 
        vector_vector_expression< E,N,O,L >::operator()( size_type s ) const
    {
        return operator_type()( s );
    }

    template< class E, std::size_t N, class O, bool L > template< class U >
    bool const vector_vector_expression< E,N,O,L >::references( scalar< U > const& ) const
    {
        return false;
    }

    template< class E, std::size_t N, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const vector_vector_expression< E,N,O,L >::references( vector< U,Q,J,B > const& ) const
    {
        return false;
    }

    template< class E, std::size_t N, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const vector_vector_expression< E,N,O,L >::references( matrix< U,P,Q,J,B > const& ) const
    {
        return false;
    }

//--

    template< class T, std::size_t I >
    struct vector_standard_basis
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( size_type s )
        {
            return s == I ? result_type(1) : result_type(0);
        }
    };

//--

    // N = number of elements in (virtual) vector
    // I ( < N ) is the zero-based index of basis identity component
    template< class T, std::size_t N, std::size_t I >
    vector_vector_expression< vector< T,N >,N,vector_standard_basis< vector< T,N >,I >,true >
    standard_basis()
    {
        BOOST_STATIC_ASSERT( I < N );
        return vector_vector_expression< vector< T,N >,N, 
            vector_standard_basis< vector< T,N >,I >,true >();
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_MATH_VECTOR_VECTOR_HPP