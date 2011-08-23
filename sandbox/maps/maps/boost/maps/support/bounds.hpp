//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_SUPPORT_BOUNDS_HPP )
#define BOOST_MAPS_SUPPORT_BOUNDS_HPP

#include <boost/maps/support/assigner.hpp>

#ifdef BOOST_MSVC
# pragma warning( push )
# pragma warning( disable : 4351 ) // new behavior: elements of array 'array' will be default initialized
#endif

namespace boost { namespace maps {

//--

    template< std::size_t N > class bounds;
    template< std::size_t N > struct bounds_assign;

//--

    template< std::size_t N >
    struct bounds_assigner
    {
        typedef assigner< bounds< N >,N-1 > type;
    };

    template<>
    struct bounds_assigner< 1 >
    {
        typedef bounds< 1 > type;
    };

//--

    template< std::size_t N >
    class bounds
    {
    public:

        typedef bounds type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef std::size_t size_type;
        typedef std::size_t element_type;
        typedef element_type value_type;
        typedef value_type const& const_reference;
        typedef value_type& reference;
        typedef value_type const* const_iterator;
        typedef value_type* iterator;
        typedef typename bounds_assigner< N >::type assigner;

        enum { size = N };

        bounds();
        explicit bounds( const_reference );

        assigner operator=( const_reference );

        const_reference operator[]( size_type ) const;
        reference operator[]( size_type );

        void fill( const_reference );

        const_iterator begin() const;
        iterator begin();
        const_iterator end() const;
        iterator end();

    protected:

        typedef typename detail::array_type_< std::size_t,1,N >::type data_type;

        data_type data;

    };

//--
//--

    template< std::size_t N >
    bounds< N >::bounds() : data() 
    {}

    template< std::size_t N >
    bounds< N >::bounds( const_reference s ) 
    {
        std::fill_n( data, N, s ); 
    }

    template< std::size_t N >
    typename bounds< N >::assigner bounds< N >::operator=( const_reference x ) 
    {
        return bounds_assign< N >()( *this, data, x );
    }

    template< std::size_t N >
    typename bounds< N >::const_reference bounds< N >::operator[]( size_type s ) const 
    {
        BOOST_ASSERT( s < N ); 
        return data[s]; 
    }

    template< std::size_t N >
    typename bounds< N >::reference bounds< N >::operator[]( size_type s ) 
    {
        BOOST_ASSERT( s < N ); 
        return data[s]; 
    }

    template< std::size_t N >
    void bounds< N >::fill( const_reference s )
    {
        std::fill_n( data, N, s );
    }

    template< std::size_t N >
    typename bounds< N >::const_iterator bounds< N >::begin() const 
    { 
        return data; 
    }

    template< std::size_t N >
    typename bounds< N >::iterator bounds< N >::begin() 
    { 
        return data; 
    }

    template< std::size_t N >
    typename bounds< N >::const_iterator bounds< N >::end() const 
    { 
        return data+N; 
    }

    template< std::size_t N >
    typename bounds< N >::iterator bounds< N >::end() 
    { 
        return data+N; 
    }

//--

    template<>
    class bounds< 0 >
    {
    public:

        typedef bounds< 0 > type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef std::size_t size_type;
        typedef void element_type;
        typedef element_type value_type;
        typedef value_type const_reference;
        typedef value_type reference;
        typedef value_type const* const_iterator;
        typedef value_type* iterator;

        enum { size = 0 };

    };

//--
//--

    template< std::size_t N >
    struct bounds_assign
    {
        typedef typename bounds< N >::assigner assigner;
        typedef typename bounds< N >::type_reference type_reference;
        typedef typename bounds< N >::iterator iterator;
        typedef typename bounds< N >::const_reference const_reference;

        assigner operator()( type_reference b, iterator i, const_reference x )
        {
            return assigner( b, i, x );
        }
    };

    template<>
    struct bounds_assign< 1 >
    {
        typedef bounds< 1 >::type_reference type_reference;
        typedef bounds< 1 >::iterator iterator;
        typedef bounds< 1 >::const_reference const_reference;

        type_reference operator()( type_reference b, iterator i, const_reference x )
        {
            *i = x; return b;
        }
    };

//--
//--

    template< std::size_t N >
    class dimensions
        : public bounds< N >
    {
    public:

        typedef dimensions type;
        typedef bounds< N > base_type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef std::size_t size_type;
        typedef std::size_t element_type;
        typedef element_type value_type;
        typedef value_type const& const_reference;
        typedef value_type& reference;
        typedef value_type const* const_iterator;
        typedef value_type* iterator;
        typedef typename bounds_assigner< N >::type assigner;

        dimensions();

        assigner operator=( const_reference );

    };

//--
//--

    template< std::size_t N >
    dimensions< N >::dimensions()
    {}

    template< std::size_t N >
    typename dimensions< N >::assigner dimensions< N >::operator=( const_reference x )
    {
        return base_type::operator=( x );
    }

//--

    template<>
    class dimensions< 0 >
        : public bounds< 0 >
    {};

//--
//--

    template< std::size_t N >
    class indexes
        : public bounds< N >
    {
    public:

        typedef indexes type;
        typedef bounds< N > base_type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef std::size_t size_type;
        typedef std::size_t element_type;
        typedef element_type value_type;
        typedef value_type const& const_reference;
        typedef value_type& reference;
        typedef value_type const* const_iterator;
        typedef value_type* iterator;
        typedef typename bounds_assigner< N >::type assigner;

        indexes();

        assigner operator=( const_reference );

    };

//--
//--

    template< std::size_t N >
    indexes< N >::indexes() 
    {}

    template< std::size_t N >
    typename indexes< N >::assigner indexes< N >::operator=( const_reference x )
    {
        return base_type::operator=( x );
    }

//--

    template<>
    class indexes< 0 >
        : public bounds< 0 >
    {};

//--
//--

    template< std::size_t N >
    bool operator==( bounds< N > const& x, bounds< N > const& y )
    {
        for( std::size_t i = 0; i != N; ++i ) 
            if( !( x[i] == y[i] ) ) return false;
        return true;
    }

    template< std::size_t N >
    bool operator<( bounds< N > const& x, bounds< N > const& y )
    {
        for( std::size_t i = 0; i != N; ++i ) 
            if( !( x[i] < y[i] ) ) return false;
        return true;
    }

    template< std::size_t N >
    bool operator!=( bounds< N > const& x, bounds< N > const& y )
    {
        return !( x == y );
    }

    template< std::size_t N >
    bool operator>( bounds< N > const& x, bounds< N > const& y )
    {
        return y < x;
    }

    template< std::size_t N >
    bool operator<=( bounds< N > const& x, bounds< N > const& y )
    {
        return !( y < x );
    }

    template< std::size_t N >
    bool operator>=( bounds< N > const& x, bounds< N > const& y )
    {
        return !( x < y );
    }

//--

}} // namespace boost, namespace maps

#ifdef BOOST_MSVC
# pragma warning( pop )
#endif

#endif // BOOST_MAPS_SUPPORT_BOUNDS_HPP
