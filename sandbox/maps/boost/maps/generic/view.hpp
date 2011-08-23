//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_GENERIC_VIEW_HPP )
#define BOOST_MAPS_GENERIC_VIEW_HPP

#include <boost/maps/generic/array.hpp>
#include <boost/maps/generic/pointer.hpp>

namespace boost { namespace maps {

//--

    template< class P, std::size_t N, std::size_t I, bool B, class L >
    struct construct_view
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::iterator iterator1;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator2;
        typedef typename view< P,B >::size_type size_type;
        typedef typename mpl::deref< L >::type S;
        typedef typename view< P,B >::element_type T;
        typedef typename view< P,B >::allocator_type A;
        typedef typename P::subarray_type::type R;
        typedef typename mpl::next< L >::type M;

        void operator()( type& v, iterator1 b, iterator2 r, size_type a ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= S::value || ( l - f ) % s != 0 || c > S::value )
                throw std::invalid_argument( "invalid view<> range" );
            pointer_allocate< T,N,A >()( v, a *= c ); *b = c;
            try { construct_view< R,N-1,I+1,B,M >()( v[0], b+1, r, a ); }
            catch( ... ) { pointer_deallocate< T,N,A >()( v, a ); *b = 0; throw; }
            for( std::size_t j = 1, k = *( b+1 ); j != a; ++j ) v[j] = v[j-1] + k;
        }
    };

    template< class P, std::size_t I, bool B, class L >
    struct construct_view< P,1,I,B,L >
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::iterator iterator1;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator2;
        typedef typename view< P,B >::size_type size_type;
        typedef typename mpl::deref< L >::type S;
        typedef typename view< P,B >::element_type T;
        typedef typename view< P,B >::allocator_type A;

        void operator()( type& v, iterator1 b, iterator2 r, size_type a )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= S::value || ( l - f ) % s != 0 || c > S::value )
                throw std::invalid_argument( "invalid view<> range" );
            pointer_allocate< T,1,A >()( v, a * c ); *b = c; 
        }
    };

    template< class P, std::size_t I, class L >
    struct construct_view< P,1,I,false,L >
    {
        typedef typename view< P,false >::member_type type;
        typedef typename view< P,false >::bounds_type::iterator iterator1;
        typedef typename view< P,false >::ranges_type::const_iterator_type iterator2;
        typedef typename view< P,false >::size_type size_type;
        typedef typename mpl::deref< L >::type S;
        typedef typename view< P,false >::element_type T;
        typedef typename has_trivial_constructor< T >::type C;
        typedef typename view< P,false >::allocator_type A;

        void operator()( type& v, iterator1 b, iterator2 r, size_type a )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= S::value || ( l - f ) % s != 0 || c > S::value )
                throw std::invalid_argument( "invalid view<> range" );
            pointer_allocate< T,1,A >()( v, a *= c ); 
            try { pointer_construct< T,1,!C::value,A >()( v, a ); }
            catch( ... ) { pointer_deallocate< T,1,A >()( v, a ); throw; }
            *b = c; 
        }
    };

//--

    template< class P, std::size_t N, std::size_t I, bool B >
    struct construct_view< P,N,I,B,bounds<N> >
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::iterator iterator1;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator2;
        typedef typename P::bounds_type::const_iterator iterator3;
        typedef typename view< P,B >::size_type size_type;
        typedef typename view< P,B >::element_type T;
        typedef typename view< P,B >::allocator_type A;
        typedef typename P::subarray_type::type R;

        void operator()( type& v, iterator1 b, iterator2 r, iterator3 i, size_type a ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= *i || ( l - f ) % s != 0 || c > *i )
                throw std::invalid_argument( "invalid view<> range" );
            pointer_allocate< T,N,A >()( v, a *= c ); *b = c;
            try { construct_view< R,N-1,I+1,B,bounds<N-1> >()( v[0], b+1, r, i+1, a ); }
            catch( ... ) { pointer_deallocate< T,N,A >()( v, a ); *b = 0; throw; }
            for( std::size_t j = 1, k = *( b+1 ); j != a; ++j ) v[j] = v[j-1] + k;
        }
    };

    template< class P, std::size_t I, bool B >
    struct construct_view< P,1,I,B,bounds<1> >
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::iterator iterator1;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator2;
        typedef typename P::bounds_type::const_iterator iterator3;
        typedef typename view< P,B >::size_type size_type;
        typedef typename view< P,B >::element_type T;
        typedef typename view< P,B >::allocator_type A;

        void operator()( type& v, iterator1 b, iterator2 r, iterator3 i, size_type a )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= *i || ( l - f ) % s != 0 || c > *i )
                throw std::invalid_argument( "invalid view<> range" );
            pointer_allocate< T,1,A >()( v, a * c ); *b = c; 
        }
    };

    template< class P, std::size_t I >
    struct construct_view< P,1,I,false,bounds<1> >
    {
        typedef typename view< P,false >::member_type type;
        typedef typename view< P,false >::bounds_type::iterator iterator1;
        typedef typename view< P,false >::ranges_type::const_iterator_type iterator2;
        typedef typename P::bounds_type::const_iterator iterator3;
        typedef typename view< P,false >::size_type size_type;
        typedef typename view< P,false >::element_type T;
        typedef typename has_trivial_constructor< T >::type C;
        typedef typename view< P,false >::allocator_type A;

        void operator()( type& v, iterator1 b, iterator2 r, iterator3 i, size_type a )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= *i || ( l - f ) % s != 0 || c > *i )
                throw std::invalid_argument( "invalid view<> range" );
            pointer_allocate< T,1,A >()( v, a *= c ); 
            try { pointer_construct< T,1,!C::value,A >()( v, a ); }
            catch( ... ) { pointer_deallocate< T,1,A >()( v, a ); throw; }
            *b = c; 
        }
    };
    
//--

    template< class P, std::size_t N, bool B, class L >
    struct view_constructor
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::iterator iterator1;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator2;
        
        void operator()( type& v, iterator1 b, iterator2 r, P const& p )
        {
            construct_view< P,N,0,B,typename mpl::begin< L >::type >()( v, b, r, 1 );
        }
    };

    template< class P, std::size_t N, bool B >
    struct view_constructor< P,N,B,bounds<N> >
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::iterator iterator1;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator2;
        
        void operator()( type& v, iterator1 b, iterator2 r, P const& p )
        {
            construct_view< P,N,0,B,bounds<N> >()( v, b, r, p.bounds().begin(), 1 );
        }
    };

//--

    template< class P, std::size_t N, std::size_t I, bool B, class L >
    struct resize_view
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator1;
        typedef typename view< P,B >::bounds_type::iterator iterator2;
        typedef typename view< P,B >::size_type size_type;
        typedef typename mpl::deref< L >::type S;
        typedef typename view< P,B >::element_type T;
        typedef typename view< P,B >::allocator_type A;
        typedef typename P::subarray_type::type R;
        typedef typename mpl::next< L >::type M;

        void operator()( type& v, iterator1 r, iterator2 b, size_type a, size_type n ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= S::value || ( l - f ) % s != 0 || c > S::value )
                throw std::invalid_argument( "invalid view<> range" );
            type t = 0; if( ( a *= *b ) != ( n *= c ) ) pointer_allocate< T,N,A >()( t, n );
            try { resize_view< R,N-1,I+1,B,M >()( v[0], r, b+1, a, n ); }
            catch( ... ) { if( t ) pointer_deallocate< T,N,A >()( t, n ); throw; }
            if( t )
            {   for( std::size_t j = 0, k = 0; j != n; ++j, k += *( b+1 ) ) t[j] = &v[0][k];
                type r = v; v = t; t = 0; pointer_deallocate< T,N,A >()( r, a );
            }else
                for( std::size_t j = 0, k = 0; j != a; ++j, k += *( b+1 ) ) v[j] = &v[0][k];
            *b = c;
        }
    };

    template< class P, std::size_t I, bool B, class L >
    struct resize_view< P,1,I,B,L >
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator1;
        typedef typename view< P,B >::bounds_type::iterator iterator2;
        typedef typename view< P,B >::size_type size_type;
        typedef typename mpl::deref< L >::type S;
        typedef typename view< P,B >::element_type T;
        typedef typename view< P,B >::allocator_type A;

        void operator()( type& v, iterator1 r, iterator2 b, size_type a, size_type n ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= S::value || ( l - f ) % s != 0 || c > S::value )
                throw std::invalid_argument( "invalid view<> range" );
            if( ( a *= *b ) != ( n *= c ) )
            {   type t = 0; pointer_allocate< T,1,A >()( t, n );
                type r = v; v = t; t = 0; pointer_deallocate< T,1,A >()( r, a );
            }
            *b = c;
        }
    };

    template< class P, std::size_t I, class L >
    struct resize_view< P,1,I,false,L >
    {
        typedef typename view< P,false >::member_type type;
        typedef typename view< P,false >::ranges_type::const_iterator_type iterator1;
        typedef typename view< P,false >::bounds_type::iterator iterator2;
        typedef typename P::bounds_type::const_iterator iterator3;
        typedef typename view< P,false >::size_type size_type;
        typedef typename mpl::deref< L >::type S;
        typedef typename view< P,false >::element_type T;
        typedef typename has_trivial_constructor< T >::type C;
        typedef typename has_trivial_destructor< T >::type D;
        typedef typename view< P,false >::allocator_type A;

        void operator()( type& v, iterator1 r, iterator2 b, size_type a, size_type n ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= S::value || ( l - f ) % s != 0 || c > S::value )
                throw std::invalid_argument( "invalid view<> range" );
            if( ( a *= *b ) != ( n *= c ) )
            {   type t = 0; pointer_allocate< T,1,A >()( t, n );
                try { pointer_construct< T,1,!C::value,A >()( t, n ); }
                catch( ... ) { pointer_deallocate< T,1,A >()( t, n ); throw; }
                type r = v; v = t; t = 0; pointer_destructor< T,1,D::value,A >()( r, b, a );
            }
            *b = c;
        }
    };

//--

    template< class P, std::size_t N, std::size_t I, bool B >
    struct resize_view< P,N,I,B,bounds<N> >
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator1;
        typedef typename view< P,B >::bounds_type::iterator iterator2;
        typedef typename P::bounds_type::const_iterator iterator3;
        typedef typename view< P,B >::size_type size_type;
        typedef typename view< P,B >::element_type T;
        typedef typename view< P,B >::allocator_type A;
        typedef typename P::subarray_type::type R;

        void operator()( type& v, iterator1 r, iterator2 b, iterator3 i, size_type a, size_type n ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= *i || ( l - f ) % s != 0 || c > *i )
                throw std::invalid_argument( "invalid view<> range" );
            type t = 0; if( ( a *= *b ) != ( n *= c ) ) pointer_allocate< T,N,A >()( t, n );
            try { resize_view< R,N-1,I+1,B,bounds<N-1> >()( v[0], r, b+1, i+1, a, n ); }
            catch( ... ) { if( t ) pointer_deallocate< T,N,A >()( t, n ); throw; }
            if( t )
            {   for( std::size_t j = 0, k = 0; j != n; ++j, k += *( b+1 ) ) t[j] = &v[0][k];
                type r = v; v = t; t = 0; pointer_deallocate< T,N,A >()( r, a );
            }else
                for( std::size_t j = 0, k = 0; j != a; ++j, k += *( b+1 ) ) v[j] = &v[0][k];
            *b = c;
        }
    };

    template< class P, std::size_t I, bool B >
    struct resize_view< P,1,I,B,bounds<1> >
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator1;
        typedef typename view< P,B >::bounds_type::iterator iterator2;
        typedef typename P::bounds_type::const_iterator iterator3;
        typedef typename view< P,B >::size_type size_type;
        typedef typename view< P,B >::element_type T;
        typedef typename view< P,B >::allocator_type A;

        void operator()( type& v, iterator1 r, iterator2 b, iterator3 i, size_type a, size_type n ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= *i || ( l - f ) % s != 0 || c > *i )
                throw std::invalid_argument( "invalid view<> range" );
            if( ( a *= *b ) != ( n *= c ) )
            {   type t = 0; pointer_allocate< T,1,A >()( t, n );
                type r = v; v = t; t = 0; pointer_deallocate< T,1,A >()( r, a );
            }
            *b = c;
        }
    };

    template< class P, std::size_t I >
    struct resize_view< P,1,I,false,bounds<1> >
    {
        typedef typename view< P,false >::member_type type;
        typedef typename view< P,false >::ranges_type::const_iterator_type iterator1;
        typedef typename view< P,false >::bounds_type::iterator iterator2;
        typedef typename P::bounds_type::const_iterator iterator3;
        typedef typename view< P,false >::size_type size_type;
        typedef typename view< P,false >::element_type T;
        typedef typename has_trivial_constructor< T >::type C;
        typedef typename has_trivial_destructor< T >::type D;
        typedef typename view< P,false >::allocator_type A;

        void operator()( type& v, iterator1 r, iterator2 b, iterator3 i, size_type a, size_type n ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2], c = ( l - f ) / s;
            if( s == 0 || f >= l || ( l - s ) >= *i || ( l - f ) % s != 0 || c > *i )
                throw std::invalid_argument( "invalid view<> range" );
            if( ( a *= *b ) != ( n *= c ) )
            {   type t = 0; pointer_allocate< T,1,A >()( t, n );
                try { pointer_construct< T,1,!C::value,A >()( t, n ); }
                catch( ... ) { pointer_deallocate< T,1,A >()( t, n ); throw; }
                type r = v; v = t; t = 0; pointer_destructor< T,1,D::value,A >()( r, b, a );
            }
            *b = c;
        }
    };

//--

    template< class P, std::size_t N, bool B, class L >
    struct view_resize
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator1;
        typedef typename view< P,B >::bounds_type::iterator iterator2;

        void operator()( type& v, iterator1 r, iterator2 b, P const& p )
        {
            resize_view< P,N,0,B,typename mpl::begin< L >::type >()( v, r, b, 1, 1 );
        }
    };

    template< class P, std::size_t N, bool B >
    struct view_resize< P,N,B,bounds<N> >
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator1;
        typedef typename view< P,B >::bounds_type::iterator iterator2;

        void operator()( type& v, iterator1 r, iterator2 b, P const& p )
        {
            resize_view< P,N,0,B,bounds<N> >()( v, r, b, p.bounds().begin(), 1, 1 );
        }
    };

//--

    template< class P, std::size_t N, std::size_t I, bool B >
    struct view_reset
    {
        typedef typename view< P,B >::iterator_type iterator1;
        typedef typename P::iterator_type iterator2;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator3;
        typedef typename view< P,B >::size_type size_type;
        typedef typename P::subarray_type::type R;

        void operator()( iterator1 v, iterator2 p, iterator3 r ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2];
            for( std::size_t i = 0, j = f; j != l; ++i, j += s )
                view_reset< R,N-1,I+1,B >()( v[i], p[j], r );
        }
    };

    template< class P, std::size_t I, bool B >
    struct view_reset< P,1,I,B >
    {
        typedef typename view< P,B >::iterator_type iterator1;
        typedef typename P::iterator_type iterator2;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator3;
        typedef typename view< P,B >::size_type size_type;

        void operator()( iterator1 v, iterator2 p, iterator3 r )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2];
            for( std::size_t i = 0, j = f; j != l; ++i, j += s ) v[i] = &p[j];
        }
    };

    template< class P, std::size_t I >
    struct view_reset< P,1,I,false >
    {
        typedef typename view< P,false >::iterator_type iterator1;
        typedef typename P::iterator_type iterator2;
        typedef typename view< P,false >::ranges_type::const_iterator_type iterator3;
        typedef typename view< P,false >::size_type size_type;

        void operator()( iterator1 v, iterator2 p, iterator3 r )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2];
            for( std::size_t i = 0, j = f; j != l; ++i, j += s ) v[i] = p[j];
        }
    };

//--

    template< class P, class P1, std::size_t N, std::size_t I, bool B, class L >
    struct validate_view
    {
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator;
        typedef typename view< P,B >::size_type size_type;
        typedef typename mpl::front< L >::type S;
        typedef typename mpl::pop_front< L >::type M;

        void operator()( iterator r ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2];
            if( s == 0 || f >= l || ( l - s ) >= S::value || ( l - f ) % s != 0 || ( l - f ) / s > S::value )
                throw std::invalid_argument( "invalid view<> range" );
            validate_view< P,P1,N-1,I+1,B,M >()( r );
        }
    };

    template< class P, class P1, std::size_t I, bool B, class L >
    struct validate_view< P,P1,1,I,B,L >
    {
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator;
        typedef typename view< P,B >::size_type size_type;
        typedef typename mpl::front< L >::type S;

        void operator()( iterator r )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2];
            if( s == 0 || f >= l || ( l - s ) >= S::value || ( l - f ) % s != 0 || ( l - f ) / s > S::value )
                throw std::invalid_argument( "invalid view<> range" );
        }
    };

//--

    template< class P, class P1, std::size_t N, std::size_t I, bool B >
    struct validate_view< P,P1,N,I,B,bounds<N> >
    {
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator1;
        typedef typename view< P,B >::size_type size_type;
        typedef typename P1::bounds_type::const_iterator iterator2;

        void operator()( iterator1 r, iterator2 i ) 
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2];
            if( s == 0 || f >= l || ( l - s ) >= *i || ( l - f ) % s != 0 || ( l - f ) / s > *i )
                throw std::invalid_argument( "invalid view<> range" );
            validate_view< P,P1,N-1,I+1,B,bounds<N-1> >()( r, i+1 );
        }
    };

    template< class P, class P1, std::size_t I, bool B >
    struct validate_view< P,P1,1,I,B,bounds<1> >
    {
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator1;
        typedef typename view< P,B >::size_type size_type;
        typedef typename P1::bounds_type::const_iterator iterator2;

        void operator()( iterator1 r, iterator2 i )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2];
            if( s == 0 || f >= l || ( l - s ) >= *i || ( l - f ) % s != 0 || ( l - f ) / s > *i )
                throw std::invalid_argument( "invalid view<> range" );
        }
    };

//--

    template< class P, class P1, std::size_t N, bool B, class L >
    struct view_validate
    {
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator1;
        
        void operator()( iterator1 r, P1 const& ) 
        {
            validate_view< P,P1,N,0,B,L >()( r );
        }
    };

    template< class P, class P1, std::size_t N, bool B >
    struct view_validate< P,P1,N,B,bounds<N> >
    {
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator1;
        
        void operator()( iterator1 r, P1 const& p ) 
        {
            validate_view< P,P1,N,0,B,bounds<N> >()( r, p.bounds().begin() );
        }
    };

//--

    template< class P1, class P, std::size_t N, std::size_t I, bool B >
    struct view_set
    {
        typedef typename P1::iterator_type iterator1;
        typedef typename view< P,B >::iterator_type iterator2;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator3;
        typedef typename view< P,B >::size_type size_type;
        typedef typename P1::subarray_type::type R1;
        typedef typename P::subarray_type::type R;

        void operator()( iterator1 p, iterator2 v, iterator3 r )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2];
            for( std::size_t i = 0, j = f; j != l; ++i, j += s )
                view_set< R1,R,N-1,I+1,B >()( p[j], v[i], r );
        }
    };

    template< class P1, class P, std::size_t I, bool B >
    struct view_set< P1,P,1,I,B >
    {
        typedef typename P1::iterator_type iterator1;
        typedef typename view< P,B >::iterator_type iterator2;
        typedef typename view< P,B >::ranges_type::const_iterator_type iterator3;
        typedef typename view< P,B >::size_type size_type;

        void operator()( iterator1 p, iterator2 v, iterator3 r )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2];
            for( std::size_t i = 0, j = f; j != l; ++i, j += s ) p[j] = *v[i];
        }
    };

    template< class P1, class P, std::size_t I >
    struct view_set< P1,P,1,I,false >
    {
        typedef typename P1::iterator_type iterator1;
        typedef typename view< P,false >::iterator_type iterator2;
        typedef typename view< P,false >::ranges_type::const_iterator_type iterator3;
        typedef typename view< P,false >::size_type size_type;

        void operator()( iterator1 p, iterator2 v, iterator3 r )
        {
            size_type f = r[I][0], l = r[I][1], s = r[I][2];
            for( std::size_t i = 0, j = f; j != l; ++i, j += s ) p[j] = v[i];
        }
    };

//--

    template< class P, std::size_t N, bool B >
    struct view_destructor
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::iterator iterator;
        typedef typename view< P,B >::size_type size_type;
        typedef typename view< P,B >::element_type T;
        typedef typename view< P,B >::allocator_type A;
        typedef typename P::subarray_type::type R;

        void operator()( type& v, iterator i, size_type s ) 
        {
            view_destructor< R,N-1,B >()( v[0], i+1, s * *( i+1 ) );
            pointer_deallocate< T,N,A >()( v, s ); *i = 0;
        }
    };

    template< class P, bool B >
    struct view_destructor< P,1,B >
    {
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::iterator iterator;
        typedef typename view< P,B >::size_type size_type;
        typedef typename view< P,B >::element_type T;
        typedef typename view< P,B >::allocator_type A;

        void operator()( type& v, iterator i, size_type s ) 
        {
            pointer_deallocate< T,1,A >()( v, s ); *i = 0;
        }
    };

    template< class P >
    struct view_destructor< P,1,false >
    {
        typedef typename view< P,false >::member_type type;
        typedef typename view< P,false >::bounds_type::iterator iterator;
        typedef typename view< P,false >::size_type size_type;
        typedef typename view< P,false >::element_type T;
        typedef typename has_trivial_destructor< T >::type D;
        typedef typename view< P,false >::allocator_type A;

        void operator()( type& v, iterator i, size_type s ) 
        {
            pointer_destroy< T,1,D::value,A >()( v, s );
            pointer_deallocate< T,1,A >()( v, s ); *i = 0;
        }
    };

    //--

    template< class P, std::size_t N, bool B >
    struct view_element_const
    {
        typedef typename view< P,B >::const_reference const_reference;
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::const_iterator const_iterator;
        typedef typename P::subarray_type::type R;

        const_reference operator()( type const& v, const_iterator d, const_iterator i ) 
        {
            BOOST_ASSERT( *i < *d );
            return view_element_const< R,N-1,B >()( v[*i], d+1, i+1 ); 
        }
    };

    template< class P, bool B >
    struct view_element_const< P,1,B >
    {
        typedef typename view< P,B >::const_reference const_reference;
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::const_iterator const_iterator;

        const_reference operator()( type const& v, const_iterator d, const_iterator i ) 
        {
            BOOST_ASSERT( *i < *d );
            return v[*i];
        }
    };

//--

    template< class P, std::size_t N, bool B >
    struct view_element
    {
        typedef typename view< P,B >::reference reference;
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::const_iterator const_iterator;
        typedef typename P::subarray_type::type R;

        reference operator()( type& v, const_iterator d, const_iterator i ) 
        {
            BOOST_ASSERT( *i < *d );
            return view_element< R,N-1,B >()( v[*i], d+1, i+1 ); 
        }
    };

    template< class P, bool B >
    struct view_element< P,1,B >
    {
        typedef typename view< P,B >::reference reference;
        typedef typename view< P,B >::member_type type;
        typedef typename view< P,B >::bounds_type::const_iterator const_iterator;

        reference operator()( type& v, const_iterator d, const_iterator i ) 
        {
            BOOST_ASSERT( *i < *d );
            return v[*i];
        }
    };

//--

    template< class P1, class P, std::size_t N, bool B, class L >
    struct view_bounds_equality
    {
        typedef typename view< P,B >::bounds_type::const_iterator const_iterator;
        typedef typename mpl::front< L >::type F;
        typedef typename mpl::pop_front< L >::type M;

        bool operator()( const_iterator b ) 
        {
            if( *b != F::value ) return false;
            return view_bounds_equality< P1,P,N-1,B,M >()( b+1 );
        }
    };

    template< class P1, class P, bool B, class L >
    struct view_bounds_equality< P1,P,1,B,L >
    {
        typedef typename view< P,B >::bounds_type::const_iterator const_iterator;
        typedef typename mpl::front< L >::type F;

        bool operator()( const_iterator b ) 
        {
            if( *b != F::value ) return false;
            return true;
        }
    };

//--

    template< class P1, class P, std::size_t N, bool B >
    struct view_bounds_equality< P1,P,N,B,bounds<N> >
    {
        typedef typename view< P,B >::bounds_const_reference const_reference1;
        typedef typename P1::bounds_const_reference const_reference2;

        bool operator()( const_reference1 b, const_reference2 p ) 
        {
            if( b != p ) return false;
            return true;
        }
    };

//--

    template< class P1, class P, std::size_t N, bool B, class L >
    struct view_bounds_equal
    {
        typedef typename view< P,B >::bounds_const_reference const_reference;
        
        bool operator()( const_reference b, P1 const& p ) 
        {
            return view_bounds_equality< P1,P,N,B,L >()( b.begin() );
        }
    };

    template< class P1, class P, std::size_t N, bool B >
    struct view_bounds_equal< P1,P,N,B,bounds<N> >
    {
        typedef typename view< P,B >::bounds_const_reference const_reference;

        bool operator()( const_reference b, P1 const& p ) 
        {
            return view_bounds_equality< P1,P,N,B,bounds<N> >()( b, p.bounds() );
        }
    };

//--

    template< class P1, class P, std::size_t N, bool B >
    struct view_to
    {
        typedef typename P1::iterator_type iterator1;
        typedef typename view< P,B >::const_iterator_type iterator2;
        typedef typename view< P,B >::bounds_type::const_iterator const_iterator;
        typedef typename view< P,B >::size_type size_type;
        typedef typename P1::subarray_type::type R1;
        typedef typename P::subarray_type::type R;

        void operator()( iterator1 p, iterator2 v, const_iterator c ) 
        {
            size_type s = *c;
            for( size_t i = 0; i != s; ++i )
                view_to< R1,R,N-1,B >()( p[i], v[i], c+1 );
        }
    };

    template< class P1, class P, bool B >
    struct view_to< P1,P,1,B >
    {
        typedef typename P1::iterator_type iterator1;
        typedef typename view< P,B >::const_iterator_type iterator2;
        typedef typename view< P,B >::bounds_type::const_iterator const_iterator;
        typedef typename view< P,B >::size_type size_type;

        void operator()( iterator1 p, iterator2 v, const_iterator c )
        {
            size_type s = *c;
            for( std::size_t i = 0; i != s; ++i ) p[i] = *v[i];
        }
    };

    template< class P1, class P >
    struct view_to< P1,P,1,false >
    {
        typedef typename P1::iterator_type iterator1;
        typedef typename view< P,false >::const_iterator_type iterator2;
        typedef typename view< P,false >::bounds_type::const_iterator const_iterator;
        typedef typename view< P,false >::size_type size_type;

        void operator()( iterator1 p, iterator2 v, const_iterator c )
        {
            size_type s = *c;
            for( std::size_t i = 0; i != s; ++i ) p[i] = v[i];
        }
    };

//--

    template< class P, class P1, std::size_t N, bool B >
    struct view_from
    {
        typedef typename view< P,B >::iterator_type iterator1;
        typedef typename P1::const_iterator_type iterator2;
        typedef typename view< P,B >::bounds_type::const_iterator const_iterator;
        typedef typename view< P,B >::size_type size_type;
        typedef typename P::subarray_type::type R;
        typedef typename P1::subarray_type::type R1;

        void operator()( iterator1 v, iterator2 p, const_iterator c ) 
        {
            size_type s = *c;
            for( size_t i = 0; i != s; ++i )
                view_from< R,R1,N-1,B >()( v[i], p[i], c+1 );
        }
    };

    template< class P, class P1, bool B >
    struct view_from< P,P1,1,B >
    {
        typedef typename view< P,B >::iterator_type iterator1;
        typedef typename P1::const_iterator_type iterator2;
        typedef typename view< P,B >::bounds_type::const_iterator const_iterator;
        typedef typename view< P,B >::size_type size_type;

        void operator()( iterator1 v, iterator2 p, const_iterator c )
        {
            size_type s = *c;
            for( std::size_t i = 0; i != s; ++i ) *v[i] = p[i];
        }
    };

    template< class P, class P1 >
    struct view_from< P,P1,1,false >
    {
        typedef typename view< P,false >::iterator_type iterator1;
        typedef typename P1::const_iterator_type iterator2;
        typedef typename view< P,false >::bounds_type::const_iterator const_iterator;
        typedef typename view< P,false >::size_type size_type;

        void operator()( iterator1 v, iterator2 p, const_iterator c )
        {
            size_type s = *c;
            for( std::size_t i = 0; i != s; ++i ) v[i] = p[i];
        }
    };

//--

    template< class P, std::size_t N, bool B >
    struct view_begin_const
    {
        typedef typename view< P,B >::const_iterator const_iterator;
        typedef typename view< P,B >::member_type type;
        typedef typename P::subarray_type::type R;

        const_iterator operator()( type const p )
        {
            return view_begin_const< R,N-1,B >()( *p );
        }
    };

    template< class P, bool B >
    struct view_begin_const< P,1,B >
    {
        typedef typename view< P,B >::const_iterator const_iterator;
        typedef typename view< P,B >::member_type type;

        const_iterator operator()( type const p )
        {
            return p;
        }
    };

//--

    template< class P, std::size_t N, bool B >
    struct view_begin
    {
        typedef typename view< P,B >::iterator iterator;
        typedef typename view< P,B >::member_type type;
        typedef typename P::subarray_type::type R;

        iterator operator()( type p )
        {
            return view_begin< R,N-1,B >()( *p );
        }
    };

    template< class P, bool B >
    struct view_begin< P,1,B >
    {
        typedef typename view< P,B >::iterator iterator;
        typedef typename view< P,B >::member_type type;

        iterator operator()( type p )
        {
            return p;
        }
    };

//--
//--

    template< class P, bool B >
    class view
        : public expression< view< P,B > >
    {
    public:

        typedef view type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef expression< type > base_type;
        typedef typename view_traits< P,B >::member_type member_type;
        typedef typename view_traits< P,B >::value_type value_type;
        typedef typename view_traits< P,B >::const_reference_type const_reference_type;
        typedef typename view_traits< P,B >::reference_type reference_type;
        typedef typename view_traits< P,B >::const_iterator_type const_iterator_type;
        typedef typename view_traits< P,B >::iterator_type iterator_type;
        typedef typename view_traits< P,B >::element_type element_type;
        typedef typename view_traits< P,B >::const_iterator const_iterator;
        typedef typename view_traits< P,B >::iterator iterator;
        typedef typename view_traits< P,B >::const_reference const_reference;
        typedef typename view_traits< P,B >::reference reference;
        typedef typename view_traits< P,B >::allocator_type allocator_type;
        typedef typename view_traits< P,B >::size_type size_type;
        typedef typename view_traits< P,B >::difference_type difference_type;
        typedef typename view_traits< P,B >::bounds_type bounds_type;
        typedef typename view_traits< P,B >::bounds_const_reference bounds_const_reference;
        typedef typename view_traits< P,B >::limits_type limits_type;
        typedef typename view_traits< P,B >::ranges ranges_type;
        typedef typename view_traits< P,B >::ranges_const_reference ranges_const_reference;

        enum { dimensionality = P::dimensionality };

        view();

        ~view();

        void reset( P& );
        template< class P1 > void set( P1& ) const;

        const_reference_type operator[]( size_type ) const;
        reference_type operator[]( size_type );

        const_reference_type operator*() const;
        reference_type operator*();

        const_iterator_type operator+( size_type ) const;
        iterator_type operator+( size_type );

        const_reference operator[]( bounds_const_reference ) const;
        reference operator[]( bounds_const_reference );

        const_reference at( bounds_const_reference ) const;
        reference at( bounds_const_reference );

        bool const empty() const;
        size_type const size() const;
        bounds_const_reference bounds() const;
        template< std::size_t U > size_type const bound() const;

        template< class P1 > void to( P1& );
        template< class P1 > void from( P1 const& );

        void clear();

        const_iterator begin() const;
        iterator begin();
        const_iterator end() const;
        iterator end();

        template< std::size_t R >
        class range
        {
        public:

            typedef range type;
            typedef type const& type_const_reference;
            typedef type& type_reference;
            typedef type const* type_const_pointer;
            typedef type* type_pointer;
            typedef std::size_t size_type;
            typedef std::size_t element_type;
            typedef typename ranges_type::value_type value_type;
            typedef value_type const& const_reference_type;
            typedef value_type& reference_type;
            typedef value_type const* const_iterator_type;
            typedef value_type* iterator_type;
            typedef size_type const& const_reference;
            typedef size_type& reference;
            typedef size_type const* const_iterator;
            typedef size_type* iterator;
            typedef assigner< type,2 > assigner_type;

            explicit range( view& );

            assigner_type operator=( const_reference );

            const_reference operator[]( size_type ) const;
            reference operator[]( size_type );

        protected:

            view& v;
        };

    protected:

        bounds_type limits;
        ranges_type ranges;
        member_type data;

    private:

        typedef typename mpl::size_t< dimensionality >::type N;
        typedef limits_type L;

        view( type_const_reference );
        type_reference operator=( type_const_reference );

    };

//--
//--

    template< class P, bool B >
    view< P,B >::view() : data( 0 )
    {}

    template< class P, bool B >
    view< P,B >::~view()
    {
        if( data ) view_destructor< P,N::value,B >()( data, limits.begin(), limits[0] );
    }

    template< class P, bool B >
    void view< P,B >::reset( P& p )
    {
        if( data ) view_resize< P,N::value,B,L >()( data, ranges+0, limits.begin(), p );
        else view_constructor< P,N::value,B,L >()( data, limits.begin(), ranges+0, p );
        view_reset< P,N::value,0,B >()( data, p+0, ranges+0 );
    }

    template< class P, bool B > template< class P1 >
    void view< P,B >::set( P1& p ) const
    {
        if( data )
        {   view_validate< P,P1,N::value,B,typename P1::limits_type >()( ranges+0, p );
            view_set< P1,P,N::value,0,B >()( p+0, data, ranges+0 );
        }
    }

    template< class P, bool B > 
    typename view< P,B >::const_reference_type view< P,B >::operator[]( size_type s ) const 
    {
        BOOST_ASSERT( data );
        return data[s]; 
    }

    template< class P, bool B >
    typename view< P,B >::reference_type view< P,B >::operator[]( size_type s ) 
    {
        BOOST_ASSERT( data );
        return data[s];
    }

    template< class P, bool B >
    typename view< P,B >::const_reference_type view< P,B >::operator*() const
    {
        BOOST_ASSERT( data );
        return *data;
    }

    template< class P, bool B >
    typename view< P,B >::reference_type view< P,B >::operator*()
    {
        BOOST_ASSERT( data );
        return *data;
    }

    template< class P, bool B >
    typename view< P,B >::const_iterator_type view< P,B >::operator+( size_type s ) const
    {
        BOOST_ASSERT( data );
        return data+s;
    }

    template< class P, bool B >
    typename view< P,B >::iterator_type view< P,B >::operator+( size_type s )
    {
        BOOST_ASSERT( data );
        return data+s;
    }

    template< class P, bool B >
    typename view< P,B >::const_reference view< P,B >::operator[]( bounds_const_reference b ) const
    {
        BOOST_ASSERT( data );
        return view_element_const< P,N::value,B >()( data, limits.begin(), b.begin() );
    }

    template< class P, bool B >
    typename view< P,B >::reference view< P,B >::operator[]( bounds_const_reference b )
    {
        BOOST_ASSERT( data );
        return view_element< P,N::value,B >()( data, limits.begin(), b.begin() );
    }

    template< class P, bool B >
    typename view< P,B >::const_reference view< P,B >::at( bounds_const_reference b ) const
    {
        if( !( b < limits ) )
            throw std::out_of_range( "view<> access out of range" );
        return view_element_const< P,N::value,B >()( data, limits.begin(), b.begin() );
    }

    template< class P, bool B >
    typename view< P,B >::reference view< P,B >::at( bounds_const_reference b )
    {
        if( !( b < limits ) )
            throw std::out_of_range( "view<> access out of range" );
        return view_element< P,N::value,B >()( data, limits.begin(), b.begin() );
    }

    template< class P, bool B >
    bool const view< P,B >::empty() const
    {
        return ( data == 0 );
    }

    template< class P, bool B >
    typename view< P,B >::size_type const view< P,B >::size() const
    {
        return pointer_size< N::value >()( limits.begin() );
    }

    template< class P, bool B >
    typename view< P,B >::bounds_const_reference view< P,B >::bounds() const
    {
        return limits;
    }

    template< class P, bool B > template< std::size_t U >
    typename view< P,B >::size_type const view< P,B >::bound() const
    {
        BOOST_STATIC_ASSERT( U < N::value ); 
        return limits[U];
    }

    template< class P, bool B > template< class P1 > 
    void view< P,B >::to( P1& p )
    {
        if( !view_bounds_equal< P1,P,N::value,B,typename P1::limits_type >()( limits, p ) )
            throw std::invalid_argument( "view<> 'to' invalid argument" );
        if( data ) view_to< P1,P,N::value,B >()( p+0, data, limits.begin() );
    }

    template< class P, bool B > template< class P1 > 
    void view< P,B >::from( P1 const& p )
    {
        if( !view_bounds_equal< P1,P,N::value,B,typename P1::limits_type >()( limits, p ) )
            throw std::invalid_argument( "view<> 'from' invalid argument" );
        if( data ) view_from< P,P1,N::value,B >()( data, p+0, limits.begin() );
    }

    template< class P, bool B >
    void view< P,B >::clear()
    {
        if( data ) view_destructor< P,N::value,B >()( data, limits.begin(), limits[0] );
    }

    template< class P, bool B > 
    typename view< P,B >::const_iterator view< P,B >::begin() const
    {
        if( data ) return view_begin_const< P,N::value,B >()( data );
        return 0;
    }

    template< class P, bool B >
    typename view< P,B >::iterator view< P,B >::begin()
    {
        if( data ) return view_begin< P,N::value,B >()( data );
        return 0;
    }

    template< class P, bool B >
    typename view< P,B >::const_iterator view< P,B >::end() const
    {
        if( data ) return begin()+size();
        return 0;
    }

    template< class P, bool B >
    typename view< P,B >::iterator view< P,B >::end()
    {
        if( data ) return begin()+size();
        return 0;
    }

    template< class P, bool B >
    view< P,B >::view( type_const_reference ) 
    {}

    template< class P, bool B >
    typename view< P,B >::type_reference view< P,B >::operator=( type_const_reference ) 
    {}

//--

    template< class P, bool B > template< std::size_t R >
    view< P,B >::range< R >::range( view& v ) : v( v )
    {
        BOOST_STATIC_ASSERT( R < dimensionality ); 
    }

    template< class P, bool B > template< std::size_t R >
    typename view< P,B >::template range< R >::assigner_type view< P,B >::range< R >::operator=( const_reference x ) 
    {
        return assigner_type( *this, v.ranges[R], x ); 
    }

    template< class P, bool B > template< std::size_t R >
    typename view< P,B >::template range< R >::const_reference view< P,B >::range< R >::operator[]( size_type s ) const 
    {
        BOOST_ASSERT( s < 3 );
        return v.ranges[R][s];
    }

    template< class P, bool B > template< std::size_t R >
    typename view< P,B >::template range< R >::reference view< P,B >::range< R >::operator[]( size_type s ) 
    {
        BOOST_ASSERT( s < 3 );
        return v.ranges[R][s];
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_GENERIC_VIEW_HPP