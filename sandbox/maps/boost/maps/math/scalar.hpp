//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_MATH_SCALAR_HPP )
#define BOOST_MAPS_MATH_SCALAR_HPP

#include <boost/maps/support/math.hpp>
#include <boost/maps/math/scalar_scalar.hpp>
#include <boost/maps/math/scalar_vector.hpp>

namespace boost { namespace maps {

    /*
        scalar class template

        parameters

            required

                T - data type we wish to store
                    type: arbitrary type
    */

    template< class T >
    class scalar
        : public scalar_expression< scalar< T > >
    {
    public:

        typedef scalar type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef scalar_expression< type > base_type;
        typedef T representation_type;
        typedef T value_type;
        typedef T const& const_reference_type;
        typedef T& reference_type;
        typedef T element_type;
        typedef T const& const_reference;
        typedef T& reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T const* const_iterator;
        typedef T* iterator;
        typedef null::allocator allocator_type;
        typedef mpl::size_t< 0 > dimensionality;

        using scalar_expression< type >::operator();

        enum { size = 1 };
        enum { linear = true };

        scalar();

        scalar( scalar const& );
        scalar( T const& );
        template< class E > scalar( scalar_expression< E > const& );

        scalar& operator=( scalar const& );
        scalar& operator=( T const& );
        template< class E > scalar& operator=( scalar_expression< E > const& );

        ~scalar() {}

        template< size_t B >size_type const bound() const;

        void swap( scalar& );

        const_reference operator[]( size_type ) const; 
        reference operator[]( size_type );

        const_reference operator()( size_type ) const; 
        reference operator()( size_type );

        operator T() const;

        scalar& operator*=( T const& );
        scalar& operator/=( T const& );
        scalar& operator+=( T const& );
        scalar& operator-=( T const& );

        scalar& operator*=( scalar const& );
        scalar& operator/=( scalar const& );
        scalar& operator+=( scalar const& );
        scalar& operator-=( scalar const& );

        template< class E > scalar& operator*=( scalar_expression< E > const& );
        template< class E > scalar& operator/=( scalar_expression< E > const& );
        template< class E > scalar& operator+=( scalar_expression< E > const& );
        template< class E > scalar& operator-=( scalar_expression< E > const& );

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    private:

        representation_type data;

    public:

        template< class T1, class C, class CT >
        friend std::basic_ostream< C,CT >& operator<<( std::basic_ostream< C,CT >& o, scalar< T1 > const& );

    };

//--

    template< class T >
    scalar< T >::scalar() : data( T() )
    {}

    template< class T >
    scalar< T >::scalar( scalar const& t ) : data( t.data )
    {}

    template< class T >
    scalar< T >::scalar( T const& t ) : data( t )
    {}

    template< class T > template< class E >
    scalar< T >::scalar( scalar_expression< E > const& e )
    {
        scalar_assign< type,E,scalar_scalar_assign< type,E >,E::linear >()( *this, e );
    }

    template< class T >
    scalar< T >& scalar< T >::operator=( T const& t )
    {
        data = t;
        return *this;
    }

    template< class T >
    scalar< T >& scalar< T >::operator=( scalar const& t )
    {
        if( &t != this ) data = t.data;
        return *this;
    }

    template< class T > template< class E >
    scalar< T >& scalar< T >::operator=( scalar_expression< E > const& e )
    {
        scalar_assign< type,E,scalar_scalar_assign< type,E >,E::linear >()( *this, e );
        return *this;
    }

    template< class T > template< size_t B > 
    typename scalar< T >::size_type const scalar< T >::bound() const
    {
        BOOST_STATIC_ASSERT( B == 0 );
        return 1;
    } // bound

    template< class T >
    void scalar< T >::swap( scalar& o )
    {
        if( &o != this ) { T t = o.data; o.data = data; data = t; }
    } // swap

    template< class T >
    typename scalar< T >::const_reference scalar< T >::operator[]( size_type s ) const
    {
        BOOST_ASSERT( s == 0 );
        return data;
    } // operator() const

    template< class T >
    typename scalar< T >::reference scalar< T >::operator[]( size_type s )
    {
        BOOST_ASSERT( s == 0 );
        return data;
    } // operator()

    template< class T >
    typename scalar< T >::const_reference scalar< T >::operator()( size_type s ) const
    {
        BOOST_ASSERT( s == 0 );
        return data;
    } // operator() const

    template< class T >
    typename scalar< T >::reference scalar< T >::operator()( size_type s )
    {
        BOOST_ASSERT( s == 0 );
        return data;
    } // operator()

    template< class T >
    scalar< T >::operator T() const
    {
        return data;
    }

    template< class T > 
    scalar< T >& scalar< T >::operator*=( T const& t )
    {
        data *= t;
        return *this;
    } // operator*=

    template< class T > 
    scalar< T >& scalar< T >::operator/=( T const& t )
    {
        data /= t;
        return *this;
    } // operator/=

    template< class T >
    scalar< T >& scalar< T >::operator+=( T const& t )
    {
        data += t;
        return *this;
    } // operator+=

    template< class T >
    scalar< T >& scalar< T >::operator-=( T const& t )
    {
        data -= t;
        return *this;
    } // operator-=

    template< class T > 
    scalar< T >& scalar< T >::operator*=( scalar const& s )
    {
        data *= s.data;
        return *this;
    } // operator*=

    template< class T > 
    scalar< T >& scalar< T >::operator/=( scalar const& s )
    {
        data /= s.data;
        return *this;
    } // operator/=

    template< class T >
    scalar< T >& scalar< T >::operator+=( scalar const& s )
    {
        data += s.data;
        return *this;
    } // operator+=

    template< class T >
    scalar< T >& scalar< T >::operator-=( scalar const& s )
    {
        data -= s.data;
        return *this;
    } // operator-=

    template< class T > template< class E > 
    scalar< T >& scalar< T >::operator*=( scalar_expression< E > const& e )
    {
        data *= e()( 0 );
        return *this;
    } // operator*=

    template< class T > template< class E > 
    scalar< T >& scalar< T >::operator/=( scalar_expression< E > const& e )
    {
        data /= e()( 0 );
        return *this;
    } // operator/=

    template< class T > template< class E >
    scalar< T >& scalar< T >::operator+=( scalar_expression< E > const& e )
    {
        data += e()( 0 );
        return *this;
    } // operator+=

    template< class T > template< class E >
    scalar< T >& scalar< T >::operator-=( scalar_expression< E > const& e )
    {
        data -= e()( 0 );
        return *this;
    } // operator-=

    template< class T > template< class U > 
    bool const scalar< T >::references( scalar< U > const& s ) const
    {
        return ( reinterpret_cast< scalar< T > const* >( &s ) == this );
    }

    template< class T > template< class U, std::size_t Q, bool J, class B > 
    bool const scalar< T >::references( vector< U,Q,J,B > const& ) const
    {
        return false;
    }

    template< class T > template< class U, std::size_t P, std::size_t Q, bool J, class B > 
    bool const scalar< T >::references( matrix< U,P,Q,J,B > const& ) const
    {
        return false;
    }

//--
//--

    template< class T1, class C, class CT >
    std::basic_ostream< C,CT >& operator<<( std::basic_ostream< C,CT >& o, scalar< T1 > const& s )
    {
        o << s.data;
        return o;
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_MATH_SCALAR_HPP
