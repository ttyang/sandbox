//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_MATH_MATRIX_HPP )
#define BOOST_MAPS_MATH_MATRIX_HPP

#include <boost/maps/support/math.hpp>
#include <boost/maps/math/matrix_matrix.hpp>
#include <boost/maps/math/matrix_scalar.hpp>
#include <boost/maps/math/matrix_vector.hpp>

namespace boost { namespace maps {

//--

    template< class T, std::size_t M, std::size_t N, bool I, class A, std::size_t K >
    struct matrix_equality
    {
        typedef typename matrix< T,M,N,I,A >::const_iterator const_iterator;

        bool operator()( const_iterator x, const_iterator y )
        {
            if( *x != *y ) return false;
            else return matrix_equality< T,M,N,I,A,K-1 >()( x+1, y+1 );
        }
    };

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    struct matrix_equality< T,M,N,I,A,1 >
    {
        typedef typename matrix< T,M,N,I,A >::const_iterator const_iterator;

        bool operator()( const_iterator x, const_iterator y )
        {
            if( *x != *y ) return false;
            else return true;
        }
    };

//--

    /*
        fixed size matrix class template

        parameters

            required

                T - data type we wish to store
                    type: arbitrary type
                M - number of rows
                    type: std::size_t
                N - number of columns
                    type: std::size_t

            optional

                I - initialization parameter 
                    type: bool 
                    default: true, data elements zero/default initialized
                A - allocator 
                    type: standard conforming allocator, or null::allocator
                    default: null::allocator, statically allocated array
    */

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    class matrix
        : public matrix_expression< matrix< T,M,N,I,A >,M,N >
    {
    public:

        typedef matrix type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef matrix_expression< type,M,N > base_type; 
        typedef typename matrix_type< T,M,N,I,A >::type representation_type;
        typedef typename representation_type::value_type value_type;
        typedef typename representation_type::const_reference_type const_reference_type;
        typedef typename representation_type::reference_type reference_type;
        typedef typename representation_type::const_iterator_type const_iterator_type;
        typedef typename representation_type::iterator_type iterator_type;
        typedef typename representation_type::element_type element_type;
        typedef typename representation_type::const_reference const_reference;
        typedef typename representation_type::reference reference;
        typedef typename representation_type::allocator_type allocator_type;
        typedef typename representation_type::size_type size_type;
        typedef typename representation_type::difference_type difference_type;
        typedef typename representation_type::const_iterator const_iterator;
        typedef typename representation_type::iterator iterator;
        typedef mpl::size_t< 2 > dimensionality;
        typedef mpl::bool_< I > initialize;

        using matrix_expression< type,M,N >::operator();

        enum { rows = M, cols = N, size = M * N };
        enum { linear = true };

    protected:

        typedef assigner< type,M*N-1 > assigner_type;

    public:

        matrix();

        matrix( matrix const& );
        template< class E > matrix( matrix_expression< E,M,N > const& );

        matrix& operator=( matrix const& );
        template< class E > matrix& operator=( matrix_expression< E,M,N > const& );
        assigner_type operator=( const_reference );

        ~matrix();

        template< size_t B > size_type const bound() const;

        void swap( matrix& );

        const_reference_type operator[]( size_type ) const;
        reference_type operator[]( size_type );

        const_reference operator()( reference, size_type, size_type ) const;
        reference operator()( reference, size_type, size_type );

        const_reference operator()( size_type, size_type ) const;
        reference operator()( size_type, size_type );

        const_reference operator()( size_type ) const;
        reference operator()( size_type );

        const_iterator begin() const;
        iterator begin();
        const_iterator end() const;
        iterator end();

        matrix& operator*=( matrix< T,N,N,I,A > const& );
        matrix& operator+=( matrix const& );
        matrix& operator-=( matrix const& );
        matrix& operator*=( T const& );
        matrix& operator/=( T const& );

        template< class E > matrix& operator*=( matrix_expression< E,N,N > const& );
        template< class E > matrix& operator+=( matrix_expression< E,M,N > const& );
        template< class E > matrix& operator-=( matrix_expression< E,M,N > const& );
        template< class E > matrix& operator*=( scalar_expression< E > const& );
        template< class E > matrix& operator/=( scalar_expression< E > const& );

        void clear();

        bool const operator==( matrix const& ) const;
        bool const operator!=( matrix const& ) const;

        template< class U > 
        bool const references( scalar< U > const& ) const;
        template< class U, std::size_t Q, bool J, class B > 
        bool const references( vector< U,Q,J,B > const& ) const;
        template< class U, std::size_t P, std::size_t Q, bool J, class B > 
        bool const references( matrix< U,P,Q,J,B > const& ) const;

    private:

        representation_type data;

    public:

        template< class T1, std::size_t M1, std::size_t N1, bool I1, class A1, class C, class CT >
        friend std::basic_ostream< C,CT >& operator<<( std::basic_ostream< C,CT >&, matrix< T1,M1,N1,I1,A1 > const& );
    };

//--

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    matrix< T,M,N,I,A >::matrix()
    {} // constructor

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    matrix< T,M,N,I,A >::matrix( matrix const& m ) : data( m.data )
    {}

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< class E >
    matrix< T,M,N,I,A >::matrix( matrix_expression< E,M,N > const& e )
    {
        matrix_assign< type,E,M,N,matrix_matrix_assign< type,E >,E::linear,true >()( *this, e );
    }

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator=( matrix const& m )
    {
        if( &m != this ) data = m.data;
        return *this;
    }

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< class E >
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator=( matrix_expression< E,M,N > const& e )
    {
        matrix_assign< type,E,M,N,matrix_matrix_assign< type,E >,E::linear,false >()( *this, e );
        return *this;
    }

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::assigner_type matrix< T,M,N,I,A >::operator=( const_reference t )
    {
        return assigner_type( *this, begin(), t );
    } // element assignment

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    matrix< T,M,N,I,A >::~matrix()
    {} // destructor

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< size_t B > 
    typename matrix< T,M,N,I,A >::size_type const matrix< T,M,N,I,A >::bound() const
    {
        BOOST_STATIC_ASSERT( B < 2 );
        return B == 0 ? M : N;
    } // bound

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    void matrix< T,M,N,I,A >::swap( matrix& m )
    {
        if( &m != this ) data.swap( m.data );
    } // swap

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::const_reference_type matrix< T,M,N,I,A >::operator[]( size_type s ) const
    {
        return data[s];
    } // operator[] const

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::reference_type matrix< T,M,N,I,A >::operator[]( size_type s )
    {
        return data[s];
    } // operator[]

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::const_reference matrix< T,M,N,I,A >::operator()( reference, size_type i, size_type j ) const
    {
        BOOST_ASSERT( i < M && j < N );
        return *(*( data+i)+j );
    } // operator() const

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::reference matrix< T,M,N,I,A >::operator()( reference, size_type i, size_type j )
    {
        BOOST_ASSERT( i < M && j < N );
        return *(*( data+i)+j );
    } // operator()

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::const_reference matrix< T,M,N,I,A >::operator()( size_type i, size_type j ) const
    {
        BOOST_ASSERT( i < M && j < N );
        return *(*( data+i)+j );
    } // operator() const

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::reference matrix< T,M,N,I,A >::operator()( size_type i, size_type j )
    {
        BOOST_ASSERT( i < M && j < N );
        return *(*( data+i)+j );
    } // operator()

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::const_reference matrix< T,M,N,I,A >::operator()( size_type s ) const
    {
        BOOST_ASSERT( s < size );
        return *( data.begin()+s );
    } // operator() const

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::reference matrix< T,M,N,I,A >::operator()( size_type s )
    {
        BOOST_ASSERT( s < size );
        return *( data.begin()+s );
    } // operator()

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::const_iterator matrix< T,M,N,I,A >::begin() const
    {
        return data.begin();
    } // begin const

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::iterator matrix< T,M,N,I,A >::begin()
    {
        return data.begin();
    } // begin

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::const_iterator matrix< T,M,N,I,A >::end() const
    {
        return data.end();
    } // end const

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    typename matrix< T,M,N,I,A >::iterator matrix< T,M,N,I,A >::end()
    {
        return data.end();
    } // end

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator*=( matrix< T,N,N,I,A > const& m )
    {
        *this = *this * m;
        return *this;
    } // operator*= matrix

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator+=( matrix const& m )
    {
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
            data[i][j] += m[i][j];
        return *this;
    } // operator+= matrix

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator-=( matrix const& m )
    {
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
            data[i][j] -= m[i][j];
        return *this;
    } // operator-= matrix

    template< class T, std::size_t M, std::size_t N, bool I, class A > 
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator*=( T const& t )
    {
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
            data[i][j] *= t;
        return *this;
    } // operator*= scalar

    template< class T, std::size_t M, std::size_t N, bool I, class A > 
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator/=( T const& t )
    {
        T s = t;
        BOOST_ASSERT( s != T(0) );
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
            data[i][j] /= s;
        return *this;
    } // operator/= scalar

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< class E > 
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator*=( matrix_expression< E,N,N > const& e )
    {
        *this = *this * e;
        return *this;
    } // operator*= matrix_expression

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< class E > 
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator+=( matrix_expression< E,M,N > const& e )
    {
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
            data[i][j] += e()( i,j );
        return *this;
    } // operator+= matrix_expression

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< class E >
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator-=( matrix_expression< E,M,N > const& e )
    {
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
            data[i][j] -= e()( i,j );
        return *this;
    } // operator-= matrix_expression

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< class E > 
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator*=( scalar_expression< E > const& e )
    {
        T s = e()( 0 );
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
            data[i][j] *= s;
        return *this;
    } // operator*= scalar_expression

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< class E > 
    matrix< T,M,N,I,A >& matrix< T,M,N,I,A >::operator/=( scalar_expression< E > const& e )
    {
        T s = e()( 0 );
        BOOST_ASSERT( s != T(0) );
        for( std::size_t i = 0; i != M; ++i )
        for( std::size_t j = 0; j != N; ++j )
            data[i][j] /= s;
        return *this;
    } // operator/= scalar_expression

    template< class T, std::size_t M, std::size_t N, bool I, class A > 
    void matrix< T,M,N,I,A >::clear()
    {
        T t = T(); std::fill( begin(), end(), t );
    } // clear : set all elements to default

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    bool const matrix< T,M,N,I,A >::operator==( matrix< T,M,N,I,A > const& m ) const
    {
        return matrix_equality< T,M,N,I,A,size >()( data.begin(), m.data.begin() );
    } // operator ==

    template< class T, std::size_t M, std::size_t N, bool I, class A >
    bool const matrix< T,M,N,I,A >::operator!=( matrix< T,M,N,I,A > const& m ) const
    {
        return !( matrix_equality< T,M,N,I,A,size >()( data.begin(), m.data.begin() ) );
    } // operator !=

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< class U > 
    bool const matrix< T,M,N,I,A >::references( scalar< U > const& ) const
    {
        return false;
    }

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< class U, std::size_t Q, bool J, class B > 
    bool const matrix< T,M,N,I,A >::references( vector< U,Q,J,B > const& ) const
    {
        return false;
    }

    template< class T, std::size_t M, std::size_t N, bool I, class A > template< class U, std::size_t P, std::size_t Q, bool J, class B > 
    bool const matrix< T,M,N,I,A >::references( matrix< U,P,Q,J,B > const& m ) const
    {
        return ( reinterpret_cast< matrix< T,M,N,I,A > const* >( &m ) == this );
    }

//--
//--

    template< class T1, std::size_t M1, std::size_t N1, bool I1, class A1, class C, class CT >
    std::basic_ostream< C,CT >& operator<<( std::basic_ostream< C,CT >& o, matrix< T1,M1,N1,I1,A1 > const& m )
    {
        o << m.data;
        return o;
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_MATH_MATRIX_HPP
