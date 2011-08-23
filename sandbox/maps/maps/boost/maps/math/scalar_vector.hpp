//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_MATH_SCALAR_VECTOR_HPP )
#define BOOST_MAPS_MATH_SCALAR_VECTOR_HPP

#include <boost/maps/math/scalar_scalar.hpp>
#include <boost/maps/math/vector_vector.hpp>

namespace boost { namespace maps {

//--

    template< class E1, class E2, class O, bool L >
    class scalar_vector_binary_expression
        : public scalar_expression< scalar_vector_binary_expression< E1,E2,O,L > >
    {
    public:

        typedef scalar_vector_binary_expression type;
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

        using scalar_expression< type >::operator();

        enum { size = 1 };
        enum { linear = ( L & E1::linear & E2::linear ) };

        scalar_vector_binary_expression( E1 const&, E2 const& );
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

    template< class E1, class E2, class O, bool L >
    scalar_vector_binary_expression< E1,E2,O,L >::scalar_vector_binary_expression( E1 const& e1, E2 const& e2 )
        : t1( e1 ), t2( e2 )
    {}

    template< class E1, class E2, class O, bool L >
    typename scalar_vector_binary_expression< E1,E2,O,L >::type_reference
        scalar_vector_binary_expression< E1,E2,O,L >::operator=( type_const_reference e )
    {
        if( &e != this ) { t1 = e.t1; t2 = e.t2; }
        return *this;
    }

    template< class E1, class E2, class O, bool L >
    typename scalar_vector_binary_expression< E1,E2,O,L >::expression_type1 const& 
        scalar_vector_binary_expression< E1,E2,O,L >::expression1() const
    {
        return t1;
    }

    template< class E1, class E2, class O, bool L >
    typename scalar_vector_binary_expression< E1,E2,O,L >::expression_type2 const& 
        scalar_vector_binary_expression< E1,E2,O,L >::expression2() const
    {
        return t2;
    }

    template< class E1, class E2, class O, bool L >
    typename scalar_vector_binary_expression< E1,E2,O,L >::result_type const 
        scalar_vector_binary_expression< E1,E2,O,L >::operator()( size_type ) const
    {
        return operator_type()( t1, t2 );
    }

    template< class E1, class E2, class O, bool L > template< class U >
    bool const scalar_vector_binary_expression< E1,E2,O,L >::references( scalar< U > const& s ) const
    {
        return ( t1().references( s ) || t2().references( s ) );
    }

    template< class E1, class E2, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const scalar_vector_binary_expression< E1,E2,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t1().references( v ) || t2().references( v ) );
    }

    template< class E1, class E2, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const scalar_vector_binary_expression< E1,E2,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t1().references( m ) || t2().references( m ) );
    }

//--
//--

    template< class T1, class T2 >
    struct scalar_vector_inner_product
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::result_type result_type;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference1 type_const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::type_const_reference2 type_const_reference2;
        typedef typename expression_binary_traits< T1,T2 >::size_type size_type;

        result_type operator()( type_const_reference1 t1, type_const_reference2 t2 )
        {
            result_type r = result_type();
            for( size_type k = 0; k != t1.size; ++k )
                r += t1( k ) * t2( k );
            return r;
        }
    };

//--

    /*
        vector inner product
        < x,y > = sum( i = 1 to N ) x( i ).y( i )
        or < x,y > = ||x||.||y||.cos( t ), t = angle between x and y
        x, y orthogonal if < x,y > = 0
        < x,x > = 0 iff x = 0
    */

    template< class E1, class E2, std::size_t N >
    scalar_vector_binary_expression< E1,E2,scalar_vector_inner_product< E1,E2 >,true >
    inner_product( vector_expression< E1,N > const& e1, vector_expression< E2,N > const& e2 )
    {
        return scalar_vector_binary_expression< E1,E2, 
            scalar_vector_inner_product< E1,E2 >,true >( e1(), e2() );
    }

//--
//--

    template< class E, class O, bool L >
    class scalar_vector_unary_expression
        : public scalar_expression< scalar_vector_unary_expression< E,O,L > >
    {
    public:

        typedef scalar_vector_unary_expression type;
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

        scalar_vector_unary_expression( E const& );
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
    scalar_vector_unary_expression< E,O,L >::scalar_vector_unary_expression( E const& e )
        : t( e )
    {}

    template< class E, class O, bool L >
    typename scalar_vector_unary_expression< E,O,L >::type_reference
        scalar_vector_unary_expression< E,O,L >::operator=( type_const_reference e )
    {
        if( &e != this ) t = e.t;
        return *this;
    }

    template< class E, class O, bool L >
    typename scalar_vector_unary_expression< E,O,L >::expression_type const& 
        scalar_vector_unary_expression< E,O,L >::expression() const
    {
        return t;
    }

    template< class E, class O, bool L >
    typename scalar_vector_unary_expression< E,O,L >::result_type const 
        scalar_vector_unary_expression< E,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t );
    }

    template< class E, class O, bool L > template< class U >
    bool const scalar_vector_unary_expression< E,O,L >::references( scalar< U > const& s ) const
    {
        return ( t().references( s ) );
    }

    template< class E, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const scalar_vector_unary_expression< E,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t().references( v ) );
    }

    template< class E, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const scalar_vector_unary_expression< E,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t().references( m ) );
    }

//--
//--

    template< class T >
    struct scalar_vector_euclidean_norm
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;
        typedef typename expression_unary_traits< T >::size_type size_type;

        result_type operator()( type_const_reference t )
        {
            result_type r = result_type();
            for( size_type k = 0; k != t.size; ++k )
                r += t( k ) * t( k );
            return r;
        }
    };

    template< class T >
    struct scalar_vector_magnitude
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::type_const_reference type_const_reference;

        result_type operator()( type_const_reference t )
        {
            return std::sqrt( scalar_vector_euclidean_norm< T >()( t ) );
        }
    };

//--

    template< class E, std::size_t N >
    scalar_vector_unary_expression< E,scalar_vector_euclidean_norm< E >,false >
    euclidean_norm( vector_expression< E,N > const& e )
    {
        return scalar_vector_unary_expression< E,scalar_vector_euclidean_norm< E >,false >( e() );
    }

    template< class E, std::size_t N >
    scalar_vector_unary_expression< E,scalar_vector_magnitude< E >,false >
    magnitude( vector_expression< E,N > const& e )
    {
        return scalar_vector_unary_expression< E,scalar_vector_magnitude< E >,false >( e() );
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_MATH_SCALAR_VECTOR_HPP