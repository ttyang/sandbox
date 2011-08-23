//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_SUPPORT_ASSIGNER_HPP )
#define BOOST_MAPS_SUPPORT_ASSIGNER_HPP

namespace boost { namespace maps {

//--

    template< class T, std::size_t N >
    class assigner 
    {
    public:

        typedef assigner type;
        typedef typename T::iterator iterator;
        typedef typename T::const_reference const_reference;

        assigner( T&, iterator, const_reference );

        assigner< T,N-1 > operator,( const_reference );

    private:

        friend class assigner< T,N+1 >;
        assigner( T&, iterator );
        type& operator=( type const& );

        iterator iter;
        T& t;

    };

    template< class T >
    class assigner< T,1 > 
    {
    public:

        typedef assigner type;
        typedef typename T::iterator iterator;
        typedef typename T::const_reference const_reference;

        assigner( T&, iterator, const_reference );

        T& operator,( const_reference );

    private:

        friend class assigner< T,2 >;
        assigner( T&, iterator );
        type& operator=( type const& );

        iterator iter;
        T& t;

    };


    template< class T >
    class assigner< T,0 > 
    {
    public:

        typedef assigner type;
        typedef typename T::iterator iterator;
        typedef typename T::const_reference const_reference;

        assigner( T&, iterator, const_reference );

        T& operator,( const_reference );

    private:

        friend class assigner< T,1 >;
        assigner( T&, iterator );

    };

//--
//--

    template< class T, std::size_t N >
    assigner< T,N >::assigner( T& t, iterator i, const_reference x ) 
        : t( t ), iter( i ) 
    {
        *iter++ = x;
    }

    template< class T, std::size_t N >
    assigner< T,N-1 > assigner< T,N >::operator,( const_reference x )
    {
        *iter = x; return assigner< T,N-1 >( t, ++iter );
    }

    template< class T, std::size_t N >
    assigner< T,N >::assigner( T& t, iterator i ) 
        : t( t ), iter( i )
    {}

//--

    template< class T >
    assigner< T,1 >::assigner( T& t, iterator i, const_reference x ) 
        : t( t ), iter( i )
    {
        *iter++ = x;
    }

    template< class T >
    T& assigner< T,1 >::operator,( const_reference x ) 
    {
        *iter = x; return t;
    }

    template< class T >
    assigner< T,1 >::assigner( T& t, iterator i ) 
        : t( t ), iter( i )
    {}

//--

    template< class T >
    assigner< T,0 >::assigner( T&, iterator i, const_reference x ) 
    {
        *i = x;
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_SUPPORT_ASSIGNER_HPP