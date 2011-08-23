//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_MATH_VECTOR_HPP )
#define BOOST_MAPS_MATH_VECTOR_HPP

#include <boost/maps/support/math.hpp>
#include <boost/maps/math/vector_vector.hpp>
#include <boost/maps/math/vector_matrix.hpp>
#include <boost/maps/math/vector_scalar.hpp>

namespace boost { namespace maps {

//--

    template< class T, std::size_t N, bool I, class A, std::size_t K >
    struct vector_equality
    {
        typedef typename vector< T,N,I,A >::const_iterator const_iterator;

        bool operator()( const_iterator x, const_iterator y )
        {
            if( *x != *y ) return false;
            else return vector_equality< T,N,I,A,K-1 >()( x+1, y+1 );
        }
    };

    template< class T, std::size_t N, bool I, class A >
    struct vector_equality< T,N,I,A,1 >
    {
        typedef typename vector< T,N,I,A >::const_iterator const_iterator;

        bool operator()( const_iterator x, const_iterator y )
        {
            if( *x != *y ) return false;
            else return true;
        }
    };

//--

    /*
        fixed size vector class template

        parameters

            required

                T - data type we wish to store
                    type: arbitrary type
                N - number of components
                    type: std::size_t

            optional

                I - initialization parameter 
                    type: bool 
                    default: true, data elements zero/default initialized
                A - allocator 
                    type: standard conforming allocator, or null::allocator
                    default: null::allocator, statically allocated array
    */

    template< class T, std::size_t N, bool I, class A >
    class vector
        : public vector_expression< vector< T,N,I,A >, N >
    {
    public:

        typedef vector type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef vector_expression< type,N > base_type;
        typedef typename vector_type< T,N,I,A >::type representation_type;
        typedef typename representation_type::value_type value_type;
        typedef typename representation_type::const_reference_type const_reference_type;
        typedef typename representation_type::reference_type reference_type;
        typedef typename representation_type::element_type element_type;
        typedef typename representation_type::const_reference const_reference;
        typedef typename representation_type::reference reference;
        typedef typename representation_type::size_type size_type;
        typedef typename representation_type::difference_type difference_type;
        typedef typename representation_type::const_iterator const_iterator;
        typedef typename representation_type::iterator iterator;
        typedef A allocator_type;
        typedef mpl::size_t< 1 > dimensionality;
        typedef mpl::bool_< I > initialize;

        using vector_expression< type,N >::operator();

        enum { size = N };
        enum { linear = true };

    protected:

        typedef assigner< type,N-1 > assigner_type;

    public:

        vector();

        vector( vector const& );
        template< class E > vector( vector_expression< E,N > const& );

        vector& operator=( vector const& );
        template< class E > vector& operator=( vector_expression< E,N > const& );
        assigner_type operator=( const_reference );

        ~vector() {}

        template< size_t B > size_type const bound() const;

        void swap( vector& );

        const_reference_type operator[]( size_type ) const;
        reference_type operator[]( size_type );

        const_reference operator()( reference, size_type ) const;
        reference operator()( reference, size_type );

        const_reference operator()( size_type ) const;
        reference operator()( size_type );

        const_iterator begin() const;
        iterator begin();
        const_iterator end() const;
        iterator end();

        vector& operator+=( vector const& );
        vector& operator-=( vector const& );
        vector& operator*=( T const& );
        vector& operator/=( T const& );

        template< class E > vector& operator+=( vector_expression< E,N > const& );
        template< class E > vector& operator-=( vector_expression< E,N > const& );
        template< class E > vector& operator*=( scalar_expression< E > const& );
        template< class E > vector& operator/=( scalar_expression< E > const& );

        bool const operator==( vector const& ) const;
        bool const operator!=( vector const& ) const;

        void normalize();
        void clear();

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    private:

        representation_type data;

    public:

        template< class T1, std::size_t N1, bool I1, class A1, class C, class CT >
        friend std::basic_ostream< C, CT >& operator<<( std::basic_ostream< C, CT >&, vector< T1,N1,I1,A1 > const& );

    };

//--

    template< class T, std::size_t N, bool I, class A >
    inline vector< T,N,I,A >::vector()
    {} // constructor

    template< class T, std::size_t N, bool I, class A >
    vector< T,N,I,A >::vector( vector const& v ) : data( v.data )
    {}

    template< class T, std::size_t N, bool I, class A > template< class E >
    vector< T,N,I,A >::vector( vector_expression< E,N > const& e )
    {
        vector_assign< type,E,N,vector_vector_assign< type,E >,E::linear,true >()( *this, e );
    }

    template< class T, std::size_t N, bool I, class A >
    vector< T,N,I,A >& vector< T,N,I,A >::operator=( vector const& v )
    {
        if( &v != this ) data = v.data;
        return *this;
    }

    template< class T, std::size_t N, bool I, class A > template< class E >
    vector< T,N,I,A >& vector< T,N,I,A >::operator=( vector_expression< E,N > const& e )
    {
        vector_assign< type,E,N,vector_vector_assign< type,E >,E::linear,false >()( *this, e );
        return *this;
    }

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::assigner_type vector< T,N,I,A >::operator=( const_reference t )
    {
        return assigner_type( *this, begin(), t );
    } // initializing assignment

    template< class T, std::size_t N, bool I, class A > template< size_t B > 
    typename vector< T,N,I,A >::size_type const vector< T,N,I,A >::bound() const
    {
        BOOST_STATIC_ASSERT( B == 0 );
        return N;
    } // bound

    template< class T, std::size_t N, bool I, class A >
    void vector< T,N,I,A >::swap( vector& o )
    {
        if( &o != this ) data.swap( o.data );
    } // swap

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::const_reference_type vector< T,N,I,A >::operator[]( size_type s ) const
    {
        BOOST_ASSERT( s < size );
        return data[s];
    } // operator[] const

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::reference_type vector< T,N,I,A >::operator[]( size_type s )
    {
        BOOST_ASSERT( s < size );
        return data[s];
    } // operator[]

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::const_reference vector< T,N,I,A >::operator()( reference, size_type s ) const
    {
        BOOST_ASSERT( s < size );
        return *( data+s );
    } // operator() const

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::reference vector< T,N,I,A >::operator()( reference, size_type s )
    {
        BOOST_ASSERT( s < size );
        return *( data+s );
    } // operator()

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::const_reference vector< T,N,I,A >::operator()( size_type s ) const
    {
        BOOST_ASSERT( s < size );
        return *( data+s );
    } // operator() const

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::reference vector< T,N,I,A >::operator()( size_type s )
    {
        BOOST_ASSERT( s < size );
        return *( data+s );
    } // operator()

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::const_iterator vector< T,N,I,A >::begin() const
    {
        return data.begin();
    } // begin const

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::iterator vector< T,N,I,A >::begin()
    {
        return data.begin();
    } // begin

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::const_iterator vector< T,N,I,A >::end() const
    {
        return data.end();
    } // end const

    template< class T, std::size_t N, bool I, class A >
    typename vector< T,N,I,A >::iterator vector< T,N,I,A >::end()
    {
        return data.end();
    } // end

    template< class T, std::size_t N, bool I, class A >
    vector< T,N,I,A >& vector< T,N,I,A >::operator+=( vector const& v )
    {
        for( std::size_t i = 0; i != N; ++i ) data[i] += v[i];
        return *this;
    } // operator += vector

    template< class T, std::size_t N, bool I, class A >
    vector< T,N,I,A >& vector< T,N,I,A >::operator-=( vector const& v )
    {
        for( std::size_t i = 0; i != N; ++i ) data[i] -= v[i];
        return *this;
    } // operator -= vector

    template< class T, std::size_t N, bool I, class A >
    vector< T,N,I,A >& vector< T,N,I,A >::operator*=( T const& t )
    {
        for( std::size_t i = 0; i != N; ++i ) data[i] *= t;
        return *this;
    } // operator *= scalar

    template< class T, std::size_t N, bool I, class A >
    vector< T,N,I,A >& vector< T,N,I,A >::operator/=( T const& t )
    {
        T x = t;
        BOOST_ASSERT( x != T(0) );
        for( std::size_t i = 0; i != N; ++i ) data[i] /= x;
        return *this;
    } // operator /= scalar

    template< class T, std::size_t N, bool I, class A > template< class E >
    vector< T,N,I,A >& vector< T,N,I,A >::operator+=( vector_expression< E,N > const& e )
    {
        for( std::size_t i = 0; i != N; ++i ) data[i] += e()( i );
        return *this;
    } // operator += vector_expression

    template< class T, std::size_t N, bool I, class A > template< class E >
    vector< T,N,I,A >& vector< T,N,I,A >::operator-=( vector_expression< E,N > const& e )
    {
        for( std::size_t i = 0; i != N; ++i ) data[i] -= e()( i );
        return *this;
    } // operator -= vector_expression

    template< class T, std::size_t N, bool I, class A > template< class E >
    vector< T,N,I,A >& vector< T,N,I,A >::operator*=( scalar_expression< E > const& e )
    {
        for( std::size_t i = 0; i != N; ++i ) data[i] *= e()( 0 );
        return *this;
    } // operator *= scalar_expression

    template< class T, std::size_t N, bool I, class A > template< class E >
    vector< T,N,I,A >& vector< T,N,I,A >::operator/=( scalar_expression< E > const& e )
    {
        T x = e()( 0 );
        BOOST_ASSERT( x != T(0) );
        for( std::size_t i = 0; i != N; ++i ) data[i] /= x;
        return *this;
    } // operator /= scalar_expression

    template< class T, std::size_t N, bool I, class A >
    inline bool const vector< T,N,I,A >::operator==( vector< T,N,I,A > const& o ) const
    {
        return vector_equality< T,N,I,A,N >()( begin(), o.begin() );
    } // operator ==

    template< class T, std::size_t N, bool I, class A >
    inline bool const vector< T,N,I,A >::operator!=( vector< T,N,I,A > const& o ) const
    {
        return !( vector_equality< T,N,I,A,N >()( begin(), o.begin() ) );
    } // operator !=

    template< class T, std::size_t N, bool I, class A > template< class U > 
    bool const vector< T,N,I,A >::references( scalar< U > const& s ) const
    {
        return false;
    }

    template< class T, std::size_t N, bool I, class A > template< class U, std::size_t Q, bool J, class B > 
    bool const vector< T,N,I,A >::references( vector< U,Q,J,B > const& v ) const
    {
        return ( reinterpret_cast< vector< T,N,I,A > const* >( &v ) == this );
    }

    template< class T, std::size_t N, bool I, class A > template< class U, std::size_t P, std::size_t Q, bool J, class B > 
    bool const vector< T,N,I,A >::references( matrix< U,P,Q,J,B > const& ) const
    {
        return false;
    }

    template< class T, std::size_t N, bool I, class A >
    void vector< T,N,I,A >::normalize()
    {
        T m = vector_magnitude( *this ), x;
        if( m != T(0) )
        {   x = T(1) / m;
            for( std::size_t i = 0; i != N; ++i ) data[i] *= x;
        }
    } // normalize

    template< class T, std::size_t N, bool I, class A >
    void vector< T,N,I,A >::clear()
    {
        T t = T();
        std::fill( begin(), end(), t );
    } // clear : set all elements to default

//--

    template< class T1, std::size_t N1, bool I1, class A1, class C, class CT >
    std::basic_ostream< C,CT >& operator<<( std::basic_ostream< C,CT >& o, vector< T1,N1,I1,A1 > const& v )
    {
        o << v.data;
        return o;
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_MATH_VECTOR_HPP
