//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_MATH_SCALAR_SCALAR_HPP )
#define BOOST_MAPS_MATH_SCALAR_SCALAR_HPP

#include <boost/maps/support/expression.hpp>

#include <boost/math/complex.hpp>

namespace boost { namespace maps {

//--

    template< class E >
    class scalar_expression
        : expression< scalar_expression< E > >
    {
    public:

        typedef scalar_expression type;
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

    template< class E1, class E2, class O, bool L >
    class scalar_binary_expression
        : public scalar_expression< scalar_binary_expression< E1,E2,O,L > >
    {
    public:

        typedef scalar_binary_expression type;
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

        enum { size = E1::size };
        enum { linear = ( L & E1::linear & E2::linear ) };

        scalar_binary_expression( E1 const&, E2 const& );
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
    scalar_binary_expression< E1,E2,O,L >::scalar_binary_expression( E1 const& e1, E2 const& e2 )
        : t1( e1 ), t2( e2 )
    {}

    template< class E1, class E2, class O, bool L >
    typename scalar_binary_expression< E1,E2,O,L >::type_reference
        scalar_binary_expression< E1,E2,O,L >::operator=( type_const_reference e )
    {
        if( &e != this ) { t1 = e.t1; t2 = e.t2; }
        return *this;
    }

    template< class E1, class E2, class O, bool L >
    typename scalar_binary_expression< E1,E2,O,L >::expression_type1 const& 
        scalar_binary_expression< E1,E2,O,L >::expression1() const
    {
        return t1;
    }

    template< class E1, class E2, class O, bool L >
    typename scalar_binary_expression< E1,E2,O,L >::expression_type2 const& 
        scalar_binary_expression< E1,E2,O,L >::expression2() const
    {
        return t2;
    }

    template< class E1, class E2, class O, bool L >
    typename scalar_binary_expression< E1,E2,O,L >::result_type const 
        scalar_binary_expression< E1,E2,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t1( s ), t2( s ) );
    }

    template< class E1, class E2, class O, bool L > template< class U >
    bool const scalar_binary_expression< E1,E2,O,L >::references( scalar< U > const& s ) const
    {
        return ( t1().references( s ) || t2().references( s ) );
    }

    template< class E1, class E2, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const scalar_binary_expression< E1,E2,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t1().references( v ) || t2().references( v ) );
    }

    template< class E1, class E2, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const scalar_binary_expression< E1,E2,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t1().references( m ) || t2().references( m ) );
    }

//--
//--

    template< class T1, class T2 >
    struct scalar_scalar_product
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::result_type result_type;
        typedef typename expression_binary_traits< T1,T2 >::const_reference1 const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::const_reference2 const_reference2;

        result_type operator()( const_reference1 t1, const_reference2 t2 )
        {
            return t1 * t2;
        }
    };

    template< class T1, class T2 >
    struct scalar_scalar_division
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::result_type result_type;
        typedef typename expression_binary_traits< T1,T2 >::const_reference1 const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::const_reference2 const_reference2;

        result_type operator()( const_reference1 t1, const_reference2 t2 )
        {
            return t1 / t2;
        }
    };

    template< class T1, class T2 >
    struct scalar_scalar_addition
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::result_type result_type;
        typedef typename expression_binary_traits< T1,T2 >::const_reference1 const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::const_reference2 const_reference2;

        result_type operator()( const_reference1 t1, const_reference2 t2 )
        {
            return t1 + t2;
        }
    };

    template< class T1, class T2 >
    struct scalar_scalar_subtraction
        : expression_binary_traits< T1,T2 >
    {
        typedef typename expression_binary_traits< T1,T2 >::result_type result_type;
        typedef typename expression_binary_traits< T1,T2 >::const_reference1 const_reference1;
        typedef typename expression_binary_traits< T1,T2 >::const_reference2 const_reference2;

        result_type operator()( const_reference1 t1, const_reference2 t2 )
        {
            return t1 - t2;
        }
    };

//--

    template< class E1, class E2 >
    scalar_binary_expression< E1,E2,scalar_scalar_product< E1,E2 >,true >
    operator*( scalar_expression< E1 > const& e1, scalar_expression< E2 > const& e2 )
    {
        return scalar_binary_expression< E1,E2, 
            scalar_scalar_product< E1,E2 >,true >( e1(), e2() );
    }

    template< class E1, class E2 >
    scalar_binary_expression< E1,E2,scalar_scalar_division< E1,E2 >,true >
    operator/( scalar_expression< E1 > const& e1, scalar_expression< E2 > const& e2 )
    {
        return scalar_binary_expression< E1,E2, 
            scalar_scalar_division< E1,E2 >,true >( e1(), e2() );
    }

    template< class E1, class E2 >
    scalar_binary_expression< E1,E2,scalar_scalar_addition< E1,E2 >,true >
    operator+( scalar_expression< E1 > const& e1, scalar_expression< E2 > const& e2 )
    {
        return scalar_binary_expression< E1,E2, 
            scalar_scalar_addition< E1,E2 >,true >( e1(), e2() );
    }

    template< class E1, class E2 >
    scalar_binary_expression< E1,E2,scalar_scalar_subtraction< E1,E2 >,true >
    operator-( scalar_expression< E1 > const& e1, scalar_expression< E2 > const& e2 )
    {
        return scalar_binary_expression< E1,E2, 
            scalar_scalar_subtraction< E1,E2 >,true >( e1(), e2() );
    }

//--

    template< class T1, class T2 >
    struct scalar_scalar_assign
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

    template< class T, class E, class O, bool L >
    struct scalar_assign
    {
        typedef T& reference;
        typedef scalar_expression< E > const& expression_const_reference;
        typedef O operator_type;

        void operator()( reference s, expression_const_reference e )
        {
            operator_type()( s( 0 ), e()( 0 ) );
        }
    };

//--
//--

    template< class E, class O, bool L >
    class scalar_unary_expression
        : public scalar_expression< scalar_unary_expression< E,O,L > >
    {
    public:

        typedef scalar_unary_expression type;
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

        enum { size = E::size };
        enum { linear = ( L & E::linear ) };

        scalar_unary_expression( E const& );

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
    scalar_unary_expression< E,O,L >::scalar_unary_expression( E const& e )
        : t( e )
    {}

    template< class E, class O, bool L >
    typename scalar_unary_expression< E,O,L >::expression_type const& 
        scalar_unary_expression< E,O,L >::expression() const
    {
        return t;
    }

    template< class E, class O, bool L >
    typename scalar_unary_expression< E,O,L >::result_type const 
        scalar_unary_expression< E,O,L >::operator()( size_type s ) const
    {
        return operator_type()( t( s ) );
    }

    template< class E, class O, bool L > template< class U >
    bool const scalar_unary_expression< E,O,L >::references( scalar< U > const& s ) const
    {
        return ( t().references( s ) );
    }

    template< class E, class O, bool L > template< class U, std::size_t Q, bool J, class B >
    bool const scalar_unary_expression< E,O,L >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( t().references( v ) );
    }

    template< class E, class O, bool L > template< class U, std::size_t P, std::size_t Q, bool J, class B >
    bool const scalar_unary_expression< E,O,L >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( t().references( m ) );
    }

//--
//--

    template< class T >
    struct scalar_negate
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return -t;
        }
    };

    template< class T >
    struct scalar_sin
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::sin( t );
        }
    };

    template< class T >
    struct scalar_cos
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::cos( t );
        }
    };

    template< class T >
    struct scalar_tan
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::tan( t );
        }
    };

    template< class T >
    struct scalar_cosec
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return T(1) / std::sin( t );
        }
    };

    template< class T >
    struct scalar_sec
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return T(1) / std::cos( t );
        }
    };

    template< class T >
    struct scalar_cot
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return T(1) / std::tan( t );
        }
    };

    template< class T >
    struct scalar_sinh
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::sinh( t );
        }
    };

    template< class T >
    struct scalar_cosh
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::cosh( t );
        }
    };

    template< class T >
    struct scalar_tanh
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::tanh( t );
        }
    };

    template< class T >
    struct scalar_cosech
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return T(1) / std::sinh( t );
        }
    };

    template< class T >
    struct scalar_sech
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return T(1) / std::cosh( t );
        }
    };

    template< class T >
    struct scalar_coth
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return T(1) / std::tanh( t );
        }
    };

    template< class T >
    struct scalar_asin
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::asin( t );
        }
    };

    template< class T >
    struct scalar_asin< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return math::asin( t );
        }
    };

    template< class T >
    struct scalar_acos
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::acos( t );
        }
    };

    template< class T >
    struct scalar_acos< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return math::acos( t );
        }
    };

    template< class T >
    struct scalar_atan
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::atan( t );
        }
    };

    template< class T >
    struct scalar_atan< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return math::atan( t );
        }
    };

    template< class T >
    struct scalar_asinh
        : expression_unary_traits< T >
    {};

    template< class T >
    struct scalar_acosh
        : expression_unary_traits< T >
    {};

    template< class T >
    struct scalar_atanh
        : expression_unary_traits< T >
    {};

    template< class T >
    struct scalar_asinh< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return math::asinh( t );
        }
    };

    template< class T >
    struct scalar_acosh< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return math::acosh( t );
        }
    };

    template< class T >
    struct scalar_atanh< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return math::atanh( t );
        }
    };

    template< class T >
    struct scalar_exp
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::exp( t );
        }
    };

    template< class T >
    struct scalar_log
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::log( t );
        }
    };

    template< class T >
    struct scalar_log10
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::log10( t );
        }
    };

    template< class T >
    struct scalar_sqrt
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::sqrt( t );
        }
    };

    template< class T >
    struct scalar_sqr
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return t * t;
        }
    };

    template< class T >
    struct scalar_abs
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::abs( t );
        }
    };

    template< class T >
    struct scalar_fabs
        : expression_unary_traits< T >
    {
        typedef typename expression_unary_traits< T >::result_type result_type;
        typedef typename expression_unary_traits< T >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return std::fabs( t );
        }
    };

    template< class T >
    struct scalar_fabs< std::complex< T > >
        : expression_unary_traits< std::complex< T > >
    {
        typedef typename expression_unary_traits< std::complex< T > >::result_type result_type;
        typedef typename expression_unary_traits< std::complex< T > >::const_reference const_reference;

        result_type operator()( const_reference t )
        {
            return math::fabs( t );
        }
    };

//--
//--

    template< class E >
    scalar_unary_expression< E,scalar_negate< E >,true >
    operator-( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_negate< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_sin< E >,true >
    sin( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_sin< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_cos< E >,true >
    cos( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_cos< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_tan< E >,true >
    tan( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_tan< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_cosec< E >,true >
    cosec( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_cosec< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_sec< E >,true >
    sec( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_sec< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_cot< E >,true >
    cot( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_cot< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_sinh< E >,true >
    sinh( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_sinh< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_cosh< E >,true >
    cosh( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_cosh< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_tanh< E >,true >
    tanh( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_tanh< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_cosech< E >,true >
    cosech( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_cosech< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_sech< E >,true >
    sech( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_sech< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_coth< E >,true >
    coth( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_coth< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_asin< E >,true >
    asin( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_asin< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_acos< E >,true >
    acos( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_acos< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_atan< E >,true >
    atan( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_atan< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_asinh< E >,true >
    asinh( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_asinh< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_acosh< E >,true >
    acosh( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_acosh< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_atanh< E >,true >
    atanh( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_atanh< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_exp< E >,true >
    exp( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_exp< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_log< E >,true >
    log( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_log< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_log10< E >,true >
    log10( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_log10< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_sqrt< E >,true >
    sqrt( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_sqrt< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_sqr< E >,true >
    sqr( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_sqr< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_abs< E >,true >
    abs( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_abs< E >,true >( e() );
    }

    template< class E >
    scalar_unary_expression< E,scalar_fabs< E >,true >
    fabs( scalar_expression< E > const& e )
    {
        return scalar_unary_expression< E,scalar_fabs< E >,true >( e() );
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_MATH_SCALAR_SCALAR_HPP