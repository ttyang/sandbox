//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_GENERIC_POINTER_HPP )
#define BOOST_MAPS_GENERIC_POINTER_HPP

#include <boost/maps/support/includes.hpp>

#ifdef BOOST_MSVC
# pragma warning( disable : 4996 ) // std::copy and its relatives deprecated by microsoft
#endif

namespace boost { namespace maps {

//--

    template< class T, std::size_t N, class A >
    struct pointer_allocate
    {    
        typedef typename pointer_type< T,N >::type type;
        typedef typename A::template rebind< typename pointer_type< T,N-1 >::type >::other allocator;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type& p, size_type s ) 
        {    
            allocator a; 
            p = a.allocate( s );
        }
    };

//--

    template< class T, std::size_t N, class A >
    struct pointer_deallocate
    {    
        typedef typename pointer_type< T,N >::type type;
        typedef typename A::template rebind< typename pointer_type< T,N-1 >::type >::other allocator;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type& p, size_type s ) 
        {    
            allocator a; 
            a.deallocate( p, s ); p = 0;
        }
    };

//--

    template< class T, std::size_t N, bool I, class A >
    struct pointer_construct
    {    
        typedef typename pointer_type< T,N >::type type;
        typedef typename A::template rebind< typename pointer_type< T,N-1 >::type >::other allocator;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type& p, size_type s ) 
        {    
            type f = p, l = p+s;
            allocator a;
            try
            {   T t = T();
                while( f != l ) { a.construct( f, t ); ++f; }
            }catch( ... )
            {   type n = p;
                while( n != f ) { a.destroy( n ); ++n; }
                throw;
            }
        }
    };

    template< class T, std::size_t N, class A >
    struct pointer_construct< T,N,false,A >
    {    
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type&, size_type ) 
        {}
    };

//--

    template< class T, std::size_t N, bool D, class A >
    struct pointer_destroy
    {    
        typedef typename pointer_type< T,N >::type type;
        typedef typename A::template rebind< typename pointer_type< T,N-1 >::type >::other allocator;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type& p, size_type s ) 
        {    
            allocator a; 
            for( std::size_t i = 0; i != s; ++i ) a.destroy( p+i );
        }
    };

    template< class T, std::size_t N, class A >
    struct pointer_destroy< T,N,true,A >
    {    
        typedef typename pointer_type< T,N >::type type;
        typedef typename A::template rebind< typename pointer_type< T,N-1 >::type >::other allocator;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type&, size_type ) 
        {}
    };

//--

    template< class T, std::size_t N, bool I, class A >
    struct pointer_constructor
    {
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::iterator iterator;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type& p, iterator i, const_iterator c, size_type s ) 
        {    
            if( s == 0 ) throw std::invalid_argument( "invalid pointer<> dimension" );
            pointer_allocate< T,N,A >()( p, s ); *i = *c;
            try { pointer_constructor< T,N-1,I,A >()( p[0], i+1, c+1, s * *( c+1 ) ); }
            catch( ... ) { pointer_deallocate< T,N,A >()( p, s ); *i = 0; throw; }
            for( std::size_t j = 1, k = *( c+1 ); j != s; ++j ) p[j] = p[j-1] + k;
        }
    };

    template< class T, bool I, class A >
    struct pointer_constructor< T,1,I,A >
    {
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::iterator iterator;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename bounds< 1 >::size_type size_type;

        void operator()( type& p, iterator i, const_iterator c, size_type s )
        {
            if( s == 0 ) throw std::invalid_argument( "invalid pointer<> dimension" );
            pointer_allocate< T,1,A >()( p, s );
            try { pointer_construct< T,1,I,A >()( p, s ); }
            catch( ... ) { pointer_deallocate< T,1,A >()( p, s ); throw; }
            *i = *c;
        }
    };

//--

    template< class T, std::size_t N, bool D, class A >
    struct pointer_destructor
    {    
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::iterator iterator;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type& p, iterator i, size_type s )
        {    
            pointer_destructor< T,N-1,D,A >()( p[0], i+1, s * *( i+1 ) );
            pointer_deallocate< T,N,A >()( p, s ); *i = 0;
        }
    };

    template< class T, bool D, class A >
    struct pointer_destructor< T,1,D,A >
    {    
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::iterator iterator;
        typedef typename bounds< 1 >::size_type size_type;

        void operator()( type& p, iterator i, size_type s ) 
        {    
            pointer_destroy< T,1,D,A >()( p, s );
            pointer_deallocate< T,1,A >()( p, s ); *i = 0;
        }
    };

//--

    template< class T, std::size_t N, class A >
    struct pointer_copy
    {    
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::iterator iterator;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type& p, iterator i, type const& q, const_iterator c, size_type s ) 
        {    
            pointer_allocate< T,N,A >()( p, s ); *i = *c; 
            try { pointer_copy< T,N-1,A >()( p[0], i+1, q[0], c+1, s * *( c+1 ) ); }
            catch( ... ) { pointer_deallocate< T,N,A >()( p, s ); *i = 0; throw; }
            for( std::size_t j = 1, k = *( c+1 ); j != s; ++j ) p[j] = p[j-1] + k;
        }
    };

    template< class T, class A >
    struct pointer_copy< T,1,A >
    {    
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::iterator iterator;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename bounds< 1 >::size_type size_type;

        void operator()( type& p, iterator i, type const& q, const_iterator c, size_type s )
        {    
            pointer_allocate< T,1,A >()( p, s );
            try { std::uninitialized_copy( q, q+s, p ); }
            catch( ... ) { pointer_deallocate< T,1,A >()( p, s ); throw; }
            *i = *c;
        }
    };

//--

    template< class T, std::size_t N, bool D, class A >
    struct pointer_assign
    {    
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::iterator iterator;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type& p, iterator i, size_type s, type const& q, const_iterator c, size_type n ) 
        {    
            type t = 0; if( n != s ) pointer_allocate< T,N,A >()( t, n );
            try { pointer_assign< T,N-1,D,A >()( p[0], i+1, s * *( i+1 ), q[0], c+1, n * *( c+1 ) ); }
            catch( ... ) { if( t ) pointer_deallocate< T,N,A >()( t, n ); throw; }
            if( t )
            {   for( std::size_t j = 0, k = 0; j != n; ++j, k += *( c+1 ) ) t[j] = &p[0][k];
                type r = p; p = t; t = 0; pointer_deallocate< T,N,A >()( r, s );
            }else
                for( std::size_t j = 0, k = 0; j != n; ++j, k += *( c+1 ) ) p[j] = &p[0][k];
            *i = *c;
        }
    };

    template< class T, bool D, class A >
    struct pointer_assign< T,1,D,A >
    {    
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::iterator iterator;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename bounds< 1 >::size_type size_type;
        
        void operator()( type& p, iterator i, size_type s, type const& q, const_iterator c, size_type n )
        {    
            type t = 0; pointer_allocate< T,1,A >()( t, n );
            try { std::uninitialized_copy( q, q+n, t ); }
            catch( ... ) { pointer_deallocate< T,1,A >()( t, n ); throw; }
            type r = p; p = t; t = 0; pointer_destructor< T,1,D,A >()( r, i, s );
            *i = *c;
        }
    };

//--

    template< class T, std::size_t N, bool I, bool D, class A, bool P >
    struct pointer_resize
    {    
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::iterator iterator;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename bounds< N >::size_type size_type;

        void operator()( type& p, iterator i, size_type s, const_iterator c, size_type n ) 
        {    
            if( n == 0 ) throw std::invalid_argument( "invalid pointer<> dimension" );
            type t = 0; if( n != s ) pointer_allocate< T,N,A >()( t, n );
            try { pointer_resize< T,N-1,I,D,A,P >()( p[0], i+1, s * *( i+1 ), c+1, n * *( c+1 ) ); }
            catch( ... ) { if( t ) pointer_deallocate< T,N,A >()( t, n ); throw; }
            if( t )
            {   for( std::size_t j = 0, k = 0; j != n; ++j, k += *( c+1 ) ) t[j] = &p[0][k];
                type r = p; p = t; t = 0; pointer_deallocate< T,N,A >()( r, s );
            }else
                for( std::size_t j = 0, k = 0; j != n; ++j, k += *( c+1 ) ) p[j] = &p[0][k];
            *i = *c;
        }
    };

    template< class T, bool I, bool D, class A, bool P > 
    struct pointer_resize< T,1,I,D,A,P >
    {    
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::iterator iterator;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename bounds< 1 >::size_type size_type;

        void operator()( type& p, iterator i, size_type s, const_iterator c, size_type n )
        {    
            if( n == 0 ) throw std::invalid_argument( "invalid pointer<> dimension" );
            type t = 0; pointer_allocate< T,1,A >()( t, n );
            try { pointer_construct< T,1,I,A >()( t, n ); }
            catch( ... ) { pointer_deallocate< T,1,A >()( t, n ); throw; }
            type r = p; p = t; t = 0; pointer_destructor< T,1,D,A >()( r, i, s );
            *i = *c;
        }
    };

    template< class T, bool I, bool D, class A > 
    struct pointer_resize< T,1,I,D,A,true >
    {    
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::iterator iterator;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename bounds< 1 >::size_type size_type;

        void operator()( type& p, iterator i, size_type s, const_iterator c, size_type n )
        {   
            if( n == 0 ) throw std::invalid_argument( "invalid pointer<> bound" );
            if( n != s )
            {   type t = 0; pointer_allocate< T,1,A >()( t, n );
                if( n < s )
                {   try{ std::uninitialized_copy( p, p+n, t ); }
                    catch( ... ) { pointer_deallocate< T,1,A >()( t, n ); throw; }
                }else
                {   try { std::uninitialized_copy( p, p+s, t ); }
                    catch( ... ) { pointer_deallocate< T,1,A >()( t, n ); throw; }
                    try{ T d = T(); std::uninitialized_fill( t+s, t+n, d ); }
                    catch( ... ) 
                    {   pointer_destroy< T,1,D,A >()( t, s );
                        pointer_deallocate< T,1,A >()( t, n ); throw;
                    }
                }
                type r = p; p = t; t = 0; pointer_destructor< T,1,D,A >()( r, i, s );
            }
            *i = *c;
        }
    };

//--

    template< class T, std::size_t N, bool I, class A >
    struct pointer_element_const
    {
        typedef typename pointer< T,N,I,A >::const_reference const_reference;
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;

        const_reference operator()( type const& p, const_iterator d, const_iterator i ) 
        {    
            BOOST_ASSERT( *i < *d );
            return pointer_element_const< T,N-1,I,A >()( p[*i], d+1, i+1 ); 
        }
    };

    template< class T, bool I, class A >
    struct pointer_element_const< T,1,I,A >
    {    
        typedef typename pointer< T,1,I,A >::const_reference const_reference;
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;

        const_reference operator()( type const& p, const_iterator d, const_iterator i ) 
        {    
            BOOST_ASSERT( *i < *d );
            return p[*i];
        }
    };

    template< class T, std::size_t N, bool I, class A >
    struct pointer_element
    {
        typedef typename pointer< T,N,I,A >::reference reference;
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;

        reference operator()( type& p, const_iterator d, const_iterator i ) 
        {    
            BOOST_ASSERT( *i < *d );
            return pointer_element< T,N-1,I,A >()( p[*i], d+1, i+1 ); 
        }
    };

    template< class T, bool I, class A >
    struct pointer_element< T,1,I,A >
    {    
        typedef typename pointer< T,1,I,A >::reference reference;
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;

        reference operator()( type& p, const_iterator d, const_iterator i ) 
        {    
            BOOST_ASSERT( *i < *d );
            return p[*i];
        }
    };

//--

    template< class T, std::size_t N, bool D, class A >
    struct pointer_reconstruct
    {   
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename bounds< N >::size_type size_type;

        bool operator()( type& p, const_iterator i, size_type s ) 
        {   
            type t = 0; 
            try { pointer_allocate< T,N,A >()( t, s ); }
            catch( ... ) { pointer_deallocate< T,N,A >()( t, s ); return false; }
            if( pointer_reconstruct< T,N-1,D,A >()( p[0], i+1, s * *( i+1 ) ) )
            {   for( std::size_t j = 0, k = 0; j != s; ++j, k += *( i+1 ) ) t[j] = &p[0][k];
                type r = p; p = t; t = 0; pointer_deallocate< T,N,A >()( r, s );
                return true;
            }else return false;
        }
    };

    template< class T, bool D, class A >
    struct pointer_reconstruct< T,1,D,A >
    {    
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename bounds< 1 >::size_type size_type;

        bool operator()( type& p, const_iterator, size_type s )
        {    
            type t = 0;
            try 
            {   pointer_allocate< T,1,A >()( t, s );
                std::uninitialized_copy( p, p+s, t ); 
            }catch( ... ) { pointer_deallocate< T,1,A >()( t, s ); return false; }
            type r = p; p = t; t = 0; pointer_destructor< T,1,D,A >()( r, &s, s );
            return true;
        }
    };

//--

    template< class T, std::size_t N, bool I, bool D, class A >
    struct pointer_reset
    {   
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename bounds< N >::size_type size_type;

        bool operator()( type& p, const_iterator i, size_type s ) 
        {   
            if( pointer_reset< T,N-1,I,D,A >()( p[0], i+1, s * *( i+1 ) ) ) 
                return true;
            else return false;
        }
    };

    template< class T, bool I, bool D, class A >
    struct pointer_reset< T,2,I,D,A >
    {   
        typedef typename pointer_type< T,2 >::type type;
        typedef typename bounds< 2 >::const_iterator const_iterator;
        typedef typename bounds< 2 >::size_type size_type;

        bool operator()( type& p, const_iterator i, size_type s ) 
        {   
            if( pointer_reset< T,1,I,D,A >()( p[0], i+1, s * *( i+1 ) ) ) 
            {   for( std::size_t j = 0, k = 0; j != s; ++j, k += *( i+1 ) ) p[j] = &p[0][k];
                return true;
            }else return false;
        }
    };

    template< class T, bool I, bool D, class A >
    struct pointer_reset< T,1,I,D,A >
    {    
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename bounds< 1 >::size_type size_type;

        bool operator()( type& p, const_iterator, size_type s )
        {    
            type t = 0;
            try 
            {   pointer_allocate< T,1,A >()( t, s );
                pointer_construct< T,1,I,A >()( t, s ); 
            }catch( ... ) { pointer_deallocate< T,1,A >()( t, s ); return false; }
            type r = p; p = t; t = 0; pointer_destructor< T,1,D,A >()( r, &s, s );
            return true;
        }
    };

//--

    template< class T, std::size_t N, bool I, class A >
    struct pointer_begin_const
    {    
        typedef typename pointer< T,N,I,A >::const_iterator const_iterator;
        typedef typename pointer_type< T,N >::type type;

        const_iterator operator()( type const p ) 
        {    
            return pointer_begin_const< T,N-1,I,A >()( *p );
        }
    };

    template< class T, bool I, class A >
    struct pointer_begin_const< T,1,I,A >
    {    
        typedef typename pointer< T,1,I,A >::const_iterator const_iterator;
        typedef typename pointer_type< T,1 >::type type;

        const_iterator operator()( type const p )
        {    
            return p;
        }
    };

    template< class T, std::size_t N, bool I, class A >
    struct pointer_begin
    {    
        typedef typename pointer< T,N,I,A >::iterator iterator;
        typedef typename pointer_type< T,N >::type type;

        iterator operator()( type p ) 
        {    
            return pointer_begin< T,N-1,I,A >()( *p );
        }
    };

    template< class T, bool I, class A >
    struct pointer_begin< T,1,I,A >
    {    
        typedef typename pointer< T,1,I,A >::iterator iterator;
        typedef typename pointer_type< T,1 >::type type;

        iterator operator()( type p )
        {    
            return p;
        }
    };

//--

    template< class T, std::size_t N, bool I, class A >
    struct pointer_end_const
    {    
        typedef typename pointer< T,N,I,A >::const_iterator output_iterator;
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::const_iterator input_iterator;
        typedef typename bounds< N >::size_type size_type;

        output_iterator operator()( type const p, input_iterator i, size_type s ) 
        {    
            return pointer_end_const< T,N-1,I,A >()( *p, i+1, s * *( i+1 ) );
        }
    };

    template< class T, bool I, class A >
    struct pointer_end_const< T,1,I,A >
    {    
        typedef typename pointer< T,1,I,A >::const_iterator output_iterator;
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::const_iterator input_iterator;
        typedef typename bounds< 1 >::size_type size_type;

        output_iterator operator()( type const p, input_iterator, size_type s )
        {    
            return p+s;
        }
    };

    template< class T, std::size_t N, bool I, class A >
    struct pointer_end
    {    
        typedef typename pointer< T,N,I,A >::iterator iterator;
        typedef typename pointer_type< T,N >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename bounds< N >::size_type size_type;

        iterator operator()( type p, const_iterator i, size_type s ) 
        {    
            return pointer_end< T,N-1,I,A >()( *p, i+1, s * *( i+1 ) );
        }
    };

    template< class T, bool I, class A >
    struct pointer_end< T,1,I,A >
    {    
        typedef typename pointer< T,1,I,A >::iterator iterator;
        typedef typename pointer_type< T,1 >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename bounds< 1 >::size_type size_type;

        iterator operator()( type p, const_iterator, size_type s )
        {    
            return p+s;
        }
    };

//--

    template< std::size_t N >
    struct pointer_size
    {    
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename bounds< N >::size_type size_type;

        size_type operator()( const_iterator c )
        {    
            return *c * pointer_size< N-1 >()( c+1 );
        }
    };

    template<>
    struct pointer_size< 1 >
    {    
        typedef bounds< 1 >::const_iterator const_iterator;
        typedef bounds< 1 >::size_type size_type;

        size_type operator()( const_iterator c )
        {    
            return *c;
        }
    };

//--

    template< std::size_t N >
    struct pointer_bounds
    {
        typedef bounds< N > bounds_type;
    };

//--

    /*
        pointer class template

        parameters

            required

                T - data type we wish to store 
                    type: arbitrary type
                N - number of dimensions 
                    type: std::size_t

            optional

                I - default initialization parameter 
                    type: bool, default = false
                A - allocator 
                    type: standard conforming allocator, default std::allocator<T>
    */

    template< class T, std::size_t N, bool I, class A >
    class pointer
        : public expression< pointer< T,N,I,A > >
    {
    public:

        typedef pointer type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef expression< type > base_type;
        typedef sub_type< type > subarray_type;
        typedef typename pointer_type< T,N >::type member_type;
        typedef typename pointer_type< T,N-1 >::type value_type;
        typedef value_type const& const_reference_type;
        typedef value_type& reference_type;
        typedef value_type const* const_iterator_type;
        typedef value_type* iterator_type;
        typedef T element_type;
        typedef T const& const_reference;
        typedef T& reference;
        typedef T const* const_iterator;
        typedef T* iterator;
        typedef typename A::template rebind< T >::other allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename pointer_bounds< N >::bounds_type bounds_type;
        typedef bounds_type const& bounds_const_reference;
        typedef mpl::bool_< I > initialize;
        typedef bounds_type limits_type;

        enum { dimensionality = N };

        pointer();
        explicit pointer( bounds_const_reference );

        pointer( type_const_reference );
        template< bool I1, class A1 > 
        pointer( pointer< T,N,I1,A1 > const& );

        type_reference operator=( type_const_reference );
        template< bool I1, class A1 > 
        type_reference operator=( pointer< T,N,I1,A1 > const& );

        ~pointer();

        template< bool P > void resize( bounds_const_reference );

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

        void swap( type_reference );
        template< bool I1, class A1 > void swap( pointer< T,N,I1,A1 >& );
   
        bool reconstruct();
        bool reset();
        void clear();

        const_iterator begin() const;
        iterator begin();
        const_iterator end() const;
        iterator end();

    protected:

        typedef typename has_trivial_destructor< T >::type M;
        typedef typename array_initialize< T,I,A >::type C;

        bounds_type limits;
        member_type data;

        template< class T1, std::size_t N1, bool I1, class A1 > 
        friend class pointer;
    };

//--
//--

    template< class T, std::size_t N, bool I, class A >
    pointer< T,N,I,A >::pointer() : data( 0 )
    {} // constructor

    template< class T, std::size_t N, bool I, class A >
    pointer< T,N,I,A >::pointer( bounds_const_reference b ) : data( 0 )
    {    
        pointer_constructor< T,N,C::value,A >()( data, limits.begin(), b.begin(), b[0] );
    } // constructor

    template< class T, std::size_t N, bool I, class A >
    pointer< T,N,I,A >::pointer( type_const_reference p ) : data( 0 )
    {
        if( p.data ) pointer_copy< T,N,A >()( data, limits.begin(), p.data, p.limits.begin(), p.limits[0] );
    } // copy constructor

    template< class T, std::size_t N, bool I, class A > template< bool I1, class A1 >
    pointer< T,N,I,A >::pointer( pointer< T,N,I1,A1 > const& p ) : data( 0 )
    {
        if( p.data ) pointer_copy< T,N,A >()( data, limits.begin(), p.data, p.limits.begin(), p.limits[0] );
    } // copy constructor

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::type_reference pointer< T,N,I,A >::operator=( type_const_reference p )
    {    
        if( &p != this )
        {   if( p.data )
            {   if( data ) pointer_assign< T,N,M::value,A >()( data, limits.begin(), limits[0], p.data, p.limits.begin(), p.limits[0] );
                else pointer_copy< T,N,A >()( data, limits.begin(), p.data, p.limits.begin(), p.limits[0] );
            }else
            {   if( data ) pointer_destructor< T,N,M::value,A >()( data, limits.begin(), limits[0] );
            }
        }
        return *this;
    } // ( copy ) assignment operator

    template< class T, std::size_t N, bool I, class A > template< bool I1, class A1 >
    typename pointer< T,N,I,A >::type_reference pointer< T,N,I,A >::operator=( pointer< T,N,I1,A1 > const& p )
    {    
        if( p.data )
        {   if( data ) pointer_assign< T,N,M::value,A >()( data, limits.begin(), limits[0], p.data, p.limits.begin(), p.limits[0] );
            else pointer_copy< T,N,A >()( data, limits.begin(), p.data, p.limits.begin(), p.limits[0] );
        }else
        {   if( data ) pointer_destructor< T,N,M::value,A >()( data, limits.begin(), limits[0] );
        }
        return *this;
    } // ( copy ) assignment operator

    template< class T, std::size_t N, bool I, class A >
    pointer< T,N,I,A >::~pointer()
    {    
        if( data ) pointer_destructor< T,N,M::value,A >()( data, limits.begin(), limits[0] );
    } // destructor

    template< class T, std::size_t N, bool I, class A > template< bool P >
    void pointer< T,N,I,A >::resize( bounds_const_reference b )
    {    
        if( data ) pointer_resize< T,N,C::value,M::value,A,P >()( data, limits.begin(), limits[0], b.begin(), b[0] );
        else pointer_constructor< T,N,C::value,A >()( data, limits.begin(), b.begin(), b[0] );
    } // resize

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::const_reference_type pointer< T,N,I,A >::operator[]( size_type s ) const
    {    
        BOOST_ASSERT( data );
        return data[s];
    } // operator[] const

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::reference_type pointer< T,N,I,A >::operator[]( size_type s )
    {    
        BOOST_ASSERT( data );
        return data[s];
    } // operator[]

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::const_reference_type pointer< T,N,I,A >::operator*() const
    {
        BOOST_ASSERT( data );
        return *data;
    } // dereference const

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::reference_type pointer< T,N,I,A >::operator*()
    {
        BOOST_ASSERT( data );
        return *data;
    } // dereference

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::const_iterator_type pointer< T,N,I,A >::operator+( size_type s ) const
    {
        BOOST_ASSERT( data );
        return data+s;
    } // operator+ const

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::iterator_type pointer< T,N,I,A >::operator+( size_type s )
    {
        BOOST_ASSERT( data );
        return data+s;
    } // operator+

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::const_reference pointer< T,N,I,A >::operator[]( bounds_const_reference b ) const
    {   
        BOOST_ASSERT( data );
        return pointer_element_const< T,N,I,A >()( data, limits.begin(), b.begin() );
    } // operator[] const

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::reference pointer< T,N,I,A >::operator[]( bounds_const_reference b )
    {   
        BOOST_ASSERT( data );
        return pointer_element< T,N,I,A >()( data, limits.begin(), b.begin() );
    } // operator[]

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::const_reference pointer< T,N,I,A >::at( bounds_const_reference b ) const
    {
        if( !( b < limits ) )
            throw std::out_of_range( "pointer<> access out of range" );
        return pointer_element_const< T,N,I,A >()( data, limits.begin(), b.begin() );
    } // at const

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::reference pointer< T,N,I,A >::at( bounds_const_reference b )
    {    
        if( !( b < limits ) )
            throw std::out_of_range( "pointer<> access out of range" );
        return pointer_element< T,N,I,A >()( data, limits.begin(), b.begin() );
    } // at

    template< class T, std::size_t N, bool I, class A >
    bool const pointer< T,N,I,A >::empty() const
    {    
        return ( data == 0 );
    } // empty

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::size_type const pointer< T,N,I,A >::size() const
    {    
        return pointer_size< N >()( limits.begin() );
    } // size

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::bounds_const_reference pointer< T,N,I,A >::bounds() const
    {    
        return limits;
    } // bounds

    template< class T, std::size_t N, bool I, class A > template< std::size_t U >
    typename pointer< T,N,I,A >::size_type const pointer< T,N,I,A >::bound() const
    {    
        BOOST_STATIC_ASSERT( U < N );
        return limits[U];
    } // bound

    template< class T, std::size_t N, bool I, class A >
    void pointer< T,N,I,A >::swap( type_reference p )
    {    
        if( &p != this ) { std::swap( data, p.data ); std::swap( limits, p.limits ); }
    } // swap

    template< class T, std::size_t N, bool I, class A > template< bool I1, class A1 >
    void pointer< T,N,I,A >::swap( pointer< T,N,I1,A1 >& p )
    {
        std::swap( data, p.data ); std::swap( limits, p.limits );
    } // swap

    template< class T, std::size_t N, bool I, class A >
    bool pointer< T,N,I,A >::reconstruct()
    {    
        if( data ) return pointer_reconstruct< T,N,M::value,A >()( data, limits.begin(), limits[0] );
        return true;
    } // reconstruct

    template< class T, std::size_t N, bool I, class A >
    bool pointer< T,N,I,A >::reset()
    {    
        if( data ) return pointer_reset< T,N,C::value,M::value,A >()( data, limits.begin(), limits[0] );
        return true;
    } // reset

    template< class T, std::size_t N, bool I, class A >
    void pointer< T,N,I,A >::clear()
    {    
        if( data ) pointer_destructor< T,N,M::value,A >()( data, limits.begin(), limits[0] );
    } // clear

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::const_iterator pointer< T,N,I,A >::begin() const
    {    
        if( data ) return pointer_begin_const< T,N,I,A >()( data );
        return 0;
    } // begin const

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::iterator pointer< T,N,I,A >::begin()
    {    
        if( data ) return pointer_begin< T,N,I,A >()( data );
        return 0;
    } // begin

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::const_iterator pointer< T,N,I,A >::end() const
    {    
        if( data ) return pointer_end_const< T,N,I,A >()( data, limits.begin(), limits[0] );
        return 0;
    } // end const

    template< class T, std::size_t N, bool I, class A >
    typename pointer< T,N,I,A >::iterator pointer< T,N,I,A >::end()
    {    
        if( data ) return pointer_end< T,N,I,A >()( data, limits.begin(), limits[0] );
        return 0;
    } // end

//--
//--

    template< class T, std::size_t N, bool I, class A >
    struct sub_type< pointer< T,N,I,A > >
    {
        typedef pointer< T,N-1,I,A > type;
    };

//--
//--

    template< class T, std::size_t N, bool I, class A, class C, class CT >
    struct pointer_out
    {    
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;
        typedef typename pointer< T,N,I,A >::const_iterator_type type;
        typedef typename bounds< N >::const_iterator const_iterator;

        stream& operator()( stream& s, type const& p, const_iterator d ) 
        {    
            s << '(';
            for( std::size_t i = 0; i != *d; ++i )
            {   pointer_out< T,N-1,I,A,C,CT >()( s, p[i], d+1 );
                if( i != *d - 1 ) s << ',';
            }
            s << ')';
            return s;
        }
    };

    template< class T, bool I, class A, class C, class CT >
    struct pointer_out< T,1,I,A,C,CT >
    {    
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;
        typedef typename pointer< T,1,I,A >::const_iterator_type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;

        stream& operator()( stream& s, type const& p, const_iterator d ) 
        {    
            s << '(';
            for( std::size_t i = 0; i != *d - 1; ++i ) s << p[i] << ',';
            s << p[*d-1] << ')';
            return s;
        }
    };

//--

    template< std::size_t N, class C, class CT >
    struct pointer_out_size
    {    
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;
        typedef typename bounds< N >::const_iterator const_iterator;

        void operator()( stream& s, const_iterator d ) 
        {    
            s << '[' << *d << ']';
            pointer_out_size< N-1,C,CT >()( s, d+1 );
        }
    };

    template< class C, class CT >
    struct pointer_out_size< 1,C,CT >
    {    
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;
        typedef typename bounds< 1 >::const_iterator const_iterator;

        void operator()( stream& s, const_iterator d ) 
        {    
            s << '[' << *d << ']';
        }
    };

//--

    template< class T, std::size_t N, bool I, class A, class C, class CT >
    std::basic_ostream< C,CT >& operator<<( std::basic_ostream< C,CT >& o, pointer< T,N,I,A > const& p )
    {
        std::basic_ostringstream< C,CT,std::allocator< C > > s;
        s.flags( o.flags() ); s.imbue( o.getloc() ); s.precision( o.precision() );
        pointer_out_size< N,C,CT >()( s, p.bounds().begin() );
        return o << pointer_out< T,N,I,A,C,CT >()( s, p+0, p.bounds().begin() ).str().c_str();
    }

//--
//--

    template< class T, bool I, class A >
    class pointer< T,0,I,A >
    {
    public:

        typedef pointer type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef T value_type;
        typedef value_type const& const_reference_type;
        typedef value_type& reference_type;
        typedef value_type const* const_iterator_type;
        typedef value_type* iterator_type;
        typedef T element_type;
        typedef T const& const_reference;
        typedef T& reference;
        typedef T const* const_iterator;
        typedef T* iterator;
        typedef typename A::template rebind< T >::other allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef bounds< 0 > bounds_type;
        typedef bounds_type const& bounds_const_reference;
        typedef mpl::bool_< I > initialize;

        enum { dimensionality = 0 };

    };

//--

    template< class T, std::size_t N, bool I, class A, bool I1, class A1  >
    bool operator==( pointer< T,N,I,A > const& x, pointer< T,N,I1,A1 > const& y )
    {    
        return std::equal( x.begin(), x.end(), y.begin() );
    }

    template< class T, std::size_t N, bool I, class A, bool I1, class A1  >
    bool operator<( pointer< T,N,I,A > const& x, pointer< T,N,I1,A1 > const& y )
    {    
        return std::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
    }

    template< class T, std::size_t N, bool I, class A, bool I1, class A1  >
    bool operator!=( pointer< T,N,I,A > const& x, pointer< T,N,I1,A1 > const& y )
    {    
        return !( x == y );
    }

    template< class T, std::size_t N, bool I, class A, bool I1, class A1  >
    bool operator>( pointer< T,N,I,A > const& x, pointer< T,N,I1,A1 > const& y )
    {    
        return y < x;
    }

    template< class T, std::size_t N, bool I, class A, bool I1, class A1  >
    bool operator<=( pointer< T,N,I,A > const& x, pointer< T,N,I1,A1 > const& y )
    {    
        return !( y < x );
    }

    template< class T, std::size_t N, bool I, class A, bool I1, class A1  >
    bool operator>=( pointer< T,N,I,A > const& x, pointer< T,N,I1,A1 > const& y )
    {    
        return !( x < y );
    }

//--

    template< class T, std::size_t N, bool I, class A >
    void swap( pointer< T,N,I,A >& x, pointer< T,N,I,A >& y )
    {    
        x.swap( y );
    }

    template< class T, std::size_t N, bool I, class A, bool I1, class A1  >
    void swap( pointer< T,N,I,A >& x, pointer< T,N,I1,A1 >& y )
    {    
        x.swap( y );
    }

//--

}} // namespace boost, namespace maps

#ifdef BOOST_MSVC
# pragma warning( default : 4996 )
#endif

#endif // BOOST_MAPS_GENERIC_POINTER_HPP