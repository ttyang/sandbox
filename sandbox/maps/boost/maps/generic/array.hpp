//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_GENERIC_ARRAY_HPP )
#define BOOST_MAPS_GENERIC_ARRAY_HPP

#include <boost/maps/support/preprocessor_bounds.hpp>
#include <boost/maps/support/includes.hpp>

namespace boost { namespace maps {

//--

    template< class T, std::size_t N, class B, class C, std::size_t S, class A >
    struct array_allocate
    {    
        typedef typename array_type< T,N,B,A >::type type;
        typedef typename array_type< T,N-1,C,A >::type value_type;
        typedef typename A::template rebind< value_type >::other allocator;

        void operator()( type& p ) 
        {    
            allocator a; 
            p = a.allocate( S );
        }
    };

//--

    template< class T, std::size_t N, class B, class C, std::size_t S, class A >
    struct array_deallocate
    {    
        typedef typename array_type< T,N,B,A >::type type;
        typedef typename array_type< T,N-1,C,A >::type value_type;
        typedef typename A::template rebind< value_type >::other allocator;

        void operator()( type& p ) 
        {    
            allocator a; 
            a.deallocate( p, S ); p = 0;
        }
    };

//--

    template< class T, std::size_t N, class B, class C, std::size_t S, bool I, class A >
    struct array_construct
    {    
        typedef typename array_type< T,N,B,A >::type type;
        typedef typename array_type< T,N-1,C,A >::type value_type;
        typedef typename A::template rebind< value_type >::other allocator;

        void operator()( type& p ) 
        {    
            type f = p, l = p+S;
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

    template< class T, std::size_t N, class B, class C, std::size_t S, class A >
    struct array_construct< T,N,B,C,S,false,A >
    {    
        typedef typename array_type< T,N,B,A >::type type;

        void operator()( type& ) 
        {}
    };

//--

    template< class T, std::size_t N, class B, class C, std::size_t S, bool P, class A >
    struct array_copy_assign
    {    
        typedef typename array_type< T,N,B,A >::type type;
        typedef typename array_type< T,N-1,C,A >::type value_type;
        typedef typename A::template rebind< value_type >::other allocator;

        void operator()( type& p, type const& q ) 
        {    
            type f = p, l = p+S, r = q;
            allocator a;
            try
            {   for (; f != l; ++f, ++r) a.construct(f, *r);
            }catch( ... )
            {   type n = p;
                for (; n != r; ++n) a.destroy(n);
                throw;
            }
        }
    };

    template< class T, std::size_t N, class B, class C, std::size_t S, class A >
    struct array_copy_assign< T,N,B,C,S,true,A >
    {    
        typedef typename array_type< T,N,B,A >::type type;

        void operator()( type& p, type const& q ) 
        {
            memcpy( p, q, S * sizeof(T) ); 
        }
    };

//--

    template< class T, std::size_t N, class B, class C, std::size_t S, bool I, class A >
    struct array_destroy
    {    
        typedef typename array_type< T,N,B,A >::type type;
        typedef typename array_type< T,N-1,C,A >::type value_type;
        typedef typename A::template rebind< value_type >::other allocator;

        void operator()( type& p ) 
        {    
            allocator a; 
            for( std::size_t i = 0; i != S; ++i ) a.destroy( p+i );
        }
    };

    template< class T, std::size_t N, class B, class C, std::size_t S, class A >
    struct array_destroy< T,N,B,C,S,true,A >
    {    
        typedef typename array_type< T,N,B,A >::type type;

        void operator()( type& ) 
        {}
    };

//--

    template< class T, std::size_t N, class B, std::size_t S, bool I, class A >
    struct array_constructor
    {
        typedef typename array_type< T,N,B,A >::type type;
        typedef typename mpl::next< B >::type C;
        typedef typename mpl::deref< C >::type D;

        void operator()( type& p ) 
        {   
            if( S == 0 ) throw std::invalid_argument( "invalid array<> dimension" );
            array_allocate< T,N,B,C,S,A >()( p );
            try { array_constructor< T,N-1,C,S*D::value,I,A >()( p[0] ); }
            catch( ... ) { array_deallocate< T,N,B,C,S,A >()( p ); throw; }
            for( std::size_t j = 1, k = D::value; j != S; ++j ) p[j] = p[j-1] + k;
        }
    };

    template< class T, class B, std::size_t S, bool I, class A >
    struct array_constructor< T,1,B,S,I,A >
    {
        typedef typename array_type< T,1,B,A >::type type;
        typedef typename mpl::next< B >::type C;

        void operator()( type& p )
        {
            if( S == 0 ) throw std::invalid_argument( "invalid array<> dimension" );
            array_allocate< T,1,B,C,S,A >()( p );
            try { array_construct< T,1,B,C,S,I,A >()( p ); }
            catch( ... ) { array_deallocate< T,1,B,C,S,A >()( p ); throw; }
        }
    };

//--

    template< class T, std::size_t N, class B, std::size_t S, bool I, class A >
    struct array_destructor
    {    
        typedef typename array_type< T,N,B,A >::type type;
        typedef typename mpl::next< B >::type C;
        typedef typename mpl::deref< C >::type D;

        void operator()( type& p )
        {    
            array_destructor< T,N-1,C,S*D::value,I,A >()( p[0] );
            array_deallocate< T,N,B,C,S,A >()( p );
        }
    };

    template< class T, class B, std::size_t S, bool I, class A >
    struct array_destructor< T,1,B,S,I,A >
    {    
        typedef typename array_type< T,1,B,A >::type type;
        typedef typename mpl::next< B >::type C;
        
        void operator()( type& p ) 
        {    
            array_destroy< T,1,B,C,S,I,A >()( p );
            array_deallocate< T,1,B,C,S,A >()( p );
        }
    };

//--

    template< class T, std::size_t N, class B, std::size_t S, class A >
    struct array_copy
    {    
        typedef typename array_type< T,N,B,A >::type type;
        typedef typename mpl::next< B >::type C;
        typedef typename mpl::deref< C >::type D;
        
        void operator()( type& p, type const& q ) 
        {    
            array_allocate< T,N,B,C,S,A >()( p ); 
            try { array_copy< T,N-1,C,S*D::value,A >()( p[0], q[0] ); }
            catch( ... ) { array_deallocate< T,N,B,C,S,A >()( p ); throw; }
            for( std::size_t j = 1, k = D::value; j != S; ++j ) p[j] = p[j-1] + k;
        }
    };

    template< class T, class B, std::size_t S, class A >
    struct array_copy< T,1,B,S,A >
    {    
        typedef typename array_type< T,1,B,A >::type type;
        typedef typename mpl::next< B >::type C;
        typedef typename boost::is_pod< T >::type P;

        void operator()( type& p, type const& q )
        {    
            array_allocate< T,1,B,C,S,A >()( p );
            try { array_copy_assign< T,1,B,C,S,P::value,A >()( p, q ); }
            catch( ... ) { array_deallocate< T,1,B,C,S,A >()( p ); throw; }
        }
    };

//--

    template< class T, std::size_t N, class B, std::size_t S, bool I, class A >
    struct array_assign
    {    
        typedef typename array_type< T,N,B,A >::type type;
        typedef typename mpl::next< B >::type C;
        typedef typename mpl::deref< C >::type D;

        void operator()( type& p, type const& q ) 
        {    
            array_assign< T,N-1,C,S*D::value,I,A >()( p[0], q[0] );
        }
    };

    template< class T, class B, std::size_t S, bool I, class A >
    struct array_assign< T,2,B,S,I,A >
    {    
        typedef typename array_type< T,2,B,A >::type type;
        typedef typename mpl::next< B >::type C;
        typedef typename mpl::deref< C >::type D;

        void operator()( type& p, type const& q ) 
        {    
            array_assign< T,1,C,S*D::value,I,A >()( p[0], q[0] );
            for( std::size_t j = 0, k = 0; j != S; ++j, k += D::value ) p[j] = &p[0][k];
        }
    };

    template< class T, class B, std::size_t S, bool I, class A >
    struct array_assign< T,1,B,S,I,A >
    {    
        typedef typename array_type< T,1,B,A >::type type;
        typedef typename mpl::next< B >::type C;
        typedef typename boost::is_pod< T >::type P;

        void operator()( type& p, type const& q )
        {    
            type t = 0; array_allocate< T,1,B,C,S,A >()( t );
            try { array_copy_assign< T,1,B,C,S,P::value,A >()( t, q ); }
            catch( ... ) { array_deallocate< T,1,B,C,S,A >()( t ); throw; }
            type r = p; p = t; t = 0; array_destructor< T,1,B,S,I,A >()( r );
        }
    };

//--

    template< class T, std::size_t N, class F, class A >
    struct array_swap
    {
        typedef typename array_type< T,N,F,A >::type type;

        void operator()( type& p, type& q ) 
        {
            std::swap( p, q );
        }
    };

//--
//--

    template< class T, std::size_t N, class B, std::size_t S, bool I >
    struct array_constructor< T,N,B,S,I,null::allocator >
    {
        typedef typename array_type< T,N,B,null::allocator >::type type;

        void operator()( type& a ) 
        {   
            memset( a, 0, S * sizeof(T) );
        }
    };

    template< class T, class B, std::size_t S, bool I >
    struct array_constructor< T,1,B,S,I,null::allocator >
    {
        typedef typename array_type< T,1,B,null::allocator >::type type;

        void operator()( type& a ) 
        {   
            memset( a, 0, S * sizeof(T) );
        }
    };

    template< class T, std::size_t N, class B, std::size_t S >
    struct array_constructor< T,N,B,S,false,null::allocator >
    {
        typedef typename array_type< T,N,B,null::allocator >::type type;

        void operator()( type& ) 
        {}
    };

    template< class T, class B, std::size_t S >
    struct array_constructor< T,1,B,S,false,null::allocator >
    {
        typedef typename array_type< T,1,B,null::allocator >::type type;

        void operator()( type& ) 
        {}
    };

//--

    template< class T, std::size_t N, class F >
    struct array_swap< T,N,F,null::allocator >
    {
        typedef typename array_type< T,N,F,null::allocator >::type type;
        typedef typename mpl::deref< F >::type D;
        typedef typename mpl::next< F >::type G;

        void operator()( type& p, type& q ) 
        {
            for( std::size_t i = 0; i != D::value; ++i )
                array_swap< T,N-1,G,null::allocator >()( p[i], q[i] );
        }
    };

    template< class T, class F >
    struct array_swap< T,1,F,null::allocator >
    {
        typedef typename array_type< T,1,F,null::allocator >::type type;
        typedef typename mpl::deref< F >::type D;

        void operator()( type& p, type& q )
        {
            for( std::size_t i = 0; i != D::value; ++i ) 
                std::swap( p[i], q[i] );
        }
    };

//--
//--

    template< class T, class B, std::size_t N, class F, bool I, class A >
    struct array_element_const
    {
        typedef typename array< T,B,I,A >::const_reference const_reference;
        typedef typename array_type< T,N,F,A >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename mpl::deref< F >::type D;
        typedef typename mpl::next< F >::type G;

        const_reference operator()( type const& p, const_iterator i )
        {
            BOOST_ASSERT( *i < D::value );
            return array_element_const< T,B,N-1,G,I,A >()( p[*i], i+1 );
        }
    };

    template< class T, class B, class F, bool I, class A >
    struct array_element_const< T,B,1,F,I,A >
    {
        typedef typename array< T,B,I,A >::const_reference const_reference;
        typedef typename array_type< T,1,F,A >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename mpl::deref< F >::type D;

        const_reference operator()( type const& p, const_iterator i )
        {
            BOOST_ASSERT( *i < D::value );
            return p[*i];
        }
    };

    template< class T, class B, std::size_t N, class F, bool I, class A >
    struct array_element
    {
        typedef typename array< T,B,I,A >::reference reference;
        typedef typename array_type< T,N,F,A >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename mpl::deref< F >::type D;
        typedef typename mpl::next< F >::type G;

        reference operator()( type& p, const_iterator i )
        {
            BOOST_ASSERT( *i < D::value );
            return array_element< T,B,N-1,G,I,A >()( p[*i], i+1 );
        }
    };

    template< class T, class B, class F, bool I, class A >
    struct array_element< T,B,1,F,I,A >
    {
        typedef typename array< T,B,I,A >::reference reference;
        typedef typename array_type< T,1,F,A >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename mpl::deref< F >::type D;

        reference operator()( type& p, const_iterator i )
        {
            BOOST_ASSERT( *i < D::value );
            return p[*i];
        }
    };

//--

    template< class T, class B, std::size_t N, class F, bool I, class A >
    struct array_element_at_const
    {
        typedef typename array< T,B,I,A >::const_reference const_reference;
        typedef typename array_type< T,N,F,A >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename mpl::deref< F >::type D;
        typedef typename mpl::next< F >::type G;

        const_reference operator()( type const& p, const_iterator i )
        {
            if( !( *i < D::value ) ) 
                throw std::out_of_range( "array<> access out of range" );
            return array_element_at_const< T,B,N-1,G,I,A >()( p[*i], i+1 );
        }
    };

    template< class T, class B, class F, bool I, class A >
    struct array_element_at_const< T,B,1,F,I,A >
    {
        typedef typename array< T,B,I,A >::const_reference const_reference;
        typedef typename array_type< T,1,F,A >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename mpl::deref< F >::type D;

        const_reference operator()( type const& p, const_iterator i )
        {
            if( !( *i < D::value ) )
                throw std::out_of_range( "array<> access out of range" );
            return p[*i];
        }
    };

    template< class T, class B, std::size_t N, class F, bool I, class A >
    struct array_element_at
    {
        typedef typename array< T,B,I,A >::reference reference;
        typedef typename array_type< T,N,F,A >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;
        typedef typename mpl::deref< F >::type D;
        typedef typename mpl::next< F >::type G;

        reference operator()( type& p, const_iterator i )
        {
            if( !( *i < D::value ) ) 
                throw std::out_of_range( "array<> access out of range" );
            return array_element_at< T,B,N-1,G,I,A >()( p[*i], i+1 );
        }
    };

    template< class T, class B, class F, bool I, class A >
    struct array_element_at< T,B,1,F,I,A >
    {
        typedef typename array< T,B,I,A >::reference reference;
        typedef typename array_type< T,1,F,A >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;
        typedef typename mpl::deref< F >::type D;

        reference operator()( type& p, const_iterator i )
        {
            if( !( *i < D::value ) )
                throw std::out_of_range( "array<> access out of range" );
            return p[*i];
        }
    };

//--

    template< class T, class B, std::size_t N, class F, bool I, class A >
    struct array_begin_const
    {
        typedef typename array< T,B,I,A >::const_iterator const_iterator;
        typedef typename array_type< T,N,F,A >::type type;
        typedef typename mpl::next< F >::type G;

        const_iterator operator()( type const& p ) 
        {
            return array_begin_const< T,B,N-1,G,I,A >()( *p );
        }
    };

    template< class T, class B, class F, bool I, class A >
    struct array_begin_const< T,B,1,F,I,A >
    {
        typedef typename array< T,B,I,A >::const_iterator const_iterator;
        typedef typename array_type< T,1,F,A >::type type;

        const_iterator operator()( type const& p )
        {
            return p;
        }
    };

    template< class T, class B, std::size_t N, class F, bool I, class A >
    struct array_begin
    {
        typedef typename array< T,B,I,A >::iterator iterator;
        typedef typename array_type< T,N,F,A >::type type;
        typedef typename mpl::next< F >::type G;

        iterator operator()( type& p ) 
        {
            return array_begin< T,B,N-1,G,I,A >()( *p );
        }
    };

    template< class T, class B, class F, bool I, class A >
    struct array_begin< T,B,1,F,I,A >
    {
        typedef typename array< T,B,I,A >::iterator iterator;
        typedef typename array_type< T,1,F,A >::type type;

        iterator operator()( type& p )
        {
            return p;
        }
    };

//--

    // Base type for dynamically allocated array's. 
    template< class T, class B, bool I, class A >
    class array_base
        : public expression< array< T,B,I,A > >
    {
    public:

        typedef array< T,B,I,A > type;
        typedef type const& type_const_reference;
        typedef expression< type > base_type;
        typedef typename array_member_type< T,B,A >::type member_type;
        typedef mpl::bool_< I > initialize;

        enum { dimensionality = mpl::size< B >::type::value, 
            size = array_size< B >::type::value };

        array_base();

        array_base( type_const_reference );
        template< bool I1, class A1 > array_base( array< T,B,I1,A1 > const& );

        void operator=( type_const_reference );
        template< bool I1, class A1 > void operator=( array< T,B,I1,A1 > const& );

        ~array_base();

    protected:

        typedef typename has_trivial_destructor< T >::type M;
        typedef typename array_initialize< T,I,A >::type C;
        typedef typename mpl::size< B >::type N;
        typedef typename mpl::begin< B >::type F;
        typedef typename mpl::deref< F >::type D;

        member_type data;

        template< class T1, class B1, bool I1, class A1 > 
        friend class array;
    };

//--
//--

    // Base type for statically allocated array's.
    template< class T, class B, bool I >
    class array_base< T,B,I,null::allocator >
        : public expression< array< T,B,I,null::allocator > >
    {
    public:

        typedef array< T,B,I,null::allocator > type;
        typedef expression< type > base_type;
        typedef typename array_member_type< T,B,null::allocator >::type member_type;
        typedef mpl::bool_< I > initialize;

        enum { dimensionality = mpl::size< B >::type::value, 
            size = array_size< B >::type::value };
        
        array_base();

    protected:

        typedef typename has_trivial_destructor< T >::type M;
        typedef typename array_initialize< T,I,null::allocator >::type C;
        typedef typename mpl::size< B >::type N;
        typedef typename mpl::begin< B >::type F;
        typedef typename mpl::deref< F >::type D;

        member_type data;

        template< class T1, class B1, bool I1, class A1 > 
        friend class array;
    };

//--
//--

    /*
        array class template

        parameters

            required

                T - stored data type
                    type: arbitrary type
                B - array bounds
                    type: boundsN< ... > : mpl vectorN_c< std::size_t, ... > 
                          sequence containing size of each of N dimensions
            
            optional

                I - initialization parameter 
                    type: bool 
                    default: true, data elements zero/default initialized
                A - allocator 
                    type: standard conforming allocator, or null::allocator
                    default: null::allocator, statically allocated array
    */

    template< class T, class B, bool I, class A >
    class array
        : public array_base< T,B,I,A >
    {
    public:

        typedef array type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef array_base< T,B,I,A > base_type;
        typedef sub_type< type > subarray_type;
        typedef typename base_type::member_type member_type;
        typedef typename array_value_type< T,B,A >::type value_type;
        typedef value_type const& const_reference_type;
        typedef value_type& reference_type;
        typedef value_type const* const_iterator_type;
        typedef value_type* iterator_type;
        typedef T element_type;
        typedef T const& const_reference;
        typedef T& reference;
        typedef T const* const_iterator;
        typedef T* iterator;
        typedef typename A::template rebind< value_type >::other allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef bounds< base_type::dimensionality > bounds_type;
        typedef bounds_type const& bounds_const_reference;
        typedef assigner< type,base_type::size-1 > assigner_type; 
        typedef typename base_type::initialize initialize;
        typedef B bounds;
        typedef bounds limits_type;

        array();

        array( type_const_reference );
        template< bool I1, class A1 > array( array< T,B,I1,A1 > const& );

        type_reference operator=( type_const_reference );
        template< bool I1, class A1 > type_reference operator=( array< T,B,I1,A1 > const& );
        assigner_type operator=( const_reference );

        ~array();

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
        template< std::size_t U > size_type const bound() const;

        void swap( type_reference );
        template< bool I1, class A1 > void swap( array< T,B,I1,A1 >& );

        const_iterator begin() const;
        iterator begin();
        const_iterator end() const;
        iterator end();

    };

//--
//--

    template< class T, class B, bool I, class A >
    array< T,B,I,A >::array() : base_type()
    {} // constructor

    template< class T, class B, bool I, class A >
    array< T,B,I,A >::array( type_const_reference a ) : base_type( a )
    {} // copy constructor

    template< class T, class B, bool I, class A > template< bool I1, class A1 >
    array< T,B,I,A >::array( array< T,B,I1,A1 > const& a ) : base_type( a )
    {} // copy constructor

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::type_reference array< T,B,I,A >::operator=( type_const_reference a )
    {
        if( &a != this ) base_type::operator=( a );
        return *this;
    } // ( copy ) assignment operator

    template< class T, class B, bool I, class A > template< bool I1, class A1 >
    typename array< T,B,I,A >::type_reference array< T,B,I,A >::operator=( array< T,B,I1,A1 > const& a )
    {
        base_type::operator=( a );
        return *this;
    } // ( copy ) assignment operator

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::assigner_type array< T,B,I,A >::operator=( const_reference t )
    {
        return assigner_type( *this, begin(), t );
    } // assigner assignment

    template< class T, class B, bool I, class A >
    array< T,B,I,A >::~array()
    {} // destructor

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::const_reference_type array< T,B,I,A >::operator[]( size_type s ) const
    {
        return this->data[s];
    } // operator[] const

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::reference_type array< T,B,I,A >::operator[]( size_type s )
    {
        return this->data[s];
    } // operator[]

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::const_reference_type array< T,B,I,A >::operator*() const
    {
        return *this->data;
    } // dereference

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::reference_type array< T,B,I,A >::operator*()
    {
        return *this->data;
    } // dereference

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::const_iterator_type array< T,B,I,A >::operator+( size_type s ) const
    {
        return this->data+s;
    } // operator+, enables explicit indirection expressions

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::iterator_type array< T,B,I,A >::operator+( size_type s )
    {
        return this->data+s;
    } // operator+, enables explicit indirection expressions

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::const_reference array< T,B,I,A >::operator[]( bounds_const_reference b ) const
    {
        return array_element_const< T,B,base_type::N::value,typename base_type::F,I,A >()( this->data, b.begin() );
    } // operator[] const

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::reference array< T,B,I,A >::operator[]( bounds_const_reference b )
    {
        return array_element< T,B,base_type::N::value,typename base_type::F,I,A >()( this->data, b.begin() );
    } // operator[]

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::const_reference array< T,B,I,A >::at( bounds_const_reference b ) const
    {
        return array_element_at_const< T,B,base_type::N::value,typename base_type::F,I,A >()( this->data, b.begin() );
    } // at const

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::reference array< T,B,I,A >::at( bounds_const_reference b )
    {
        return array_element_at< T,B,base_type::N::value,typename base_type::F,I,A >()( this->data, b.begin() );
    } // at

    template< class T, class B, bool I, class A >
    bool const array< T,B,I,A >::empty() const
    {    
        return false;
    } // empty

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::size_type const array< T,B,I,A >::size() const
    {
        return base_type::size;
    } // size

    template< class T, class B, bool I, class A > template< std::size_t U >
    typename array< T,B,I,A >::size_type const array< T,B,I,A >::bound() const
    {
        BOOST_STATIC_ASSERT( U < base_type::dimensionality );
        return mpl::at< B, mpl::size_t< U > >::type::value;
    } // bound

    template< class T, class B, bool I, class A >
    void array< T,B,I,A >::swap( type_reference a )
    {
        if( &a != this ) array_swap< T,base_type::N::value,typename base_type::F,A >()( this->data, a.data ); 
    } // swap

    template< class T, class B, bool I, class A > template< bool I1, class A1 >
    void array< T,B,I,A >::swap( array< T,B,I1,A1 >& a )
    {
        array_swap< T,base_type::N::value,typename base_type::F,A >()( this->data, a.data ); 
    } // swap

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::const_iterator array< T,B,I,A >::begin() const
    {
        return array_begin_const< T,B,base_type::N::value,typename base_type::F,I,A >()( this->data );
    } // begin const

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::iterator array< T,B,I,A >::begin()
    {
        return array_begin< T,B,base_type::N::value,typename base_type::F,I,A >()( this->data );
    } // begin

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::const_iterator array< T,B,I,A >::end() const
    {
        return begin()+base_type::size;
    } // end const

    template< class T, class B, bool I, class A >
    typename array< T,B,I,A >::iterator array< T,B,I,A >::end()
    {
        return begin()+base_type::size;
    } // end

//--
//--

    template< class T, class B, bool I, class A >
    array_base< T,B,I,A >::array_base()
    {
        array_constructor< T,N::value,F,D::value,C::value,A >()( data );
    } // constructor

    template< class T, class B, bool I, class A >
    array_base< T,B,I,A >::array_base( type_const_reference a )
    {
        array_copy< T,N::value,F,D::value,A >()( data, a.data );
    } // copy constructor

    template< class T, class B, bool I, class A > template< bool I1, class A1 >
    array_base< T,B,I,A >::array_base( array< T,B,I1,A1 > const& a )
    {
        array_copy< T,N::value,F,D::value,A >()( data, a.data );
    } // copy constructor

    template< class T, class B, bool I, class A >
    void array_base< T,B,I,A >::operator=( type_const_reference a )
    {
        array_assign< T,N::value,F,D::value,M::value,A >()( data, a.data );
    } // ( copy ) assignment operator

    template< class T, class B, bool I, class A > template< bool I1, class A1 >
    void array_base< T,B,I,A >::operator=( array< T,B,I1,A1 > const& a )
    {
        array_assign< T,N::value,F,D::value,M::value,A >()( data, a.data );
    } // ( copy ) assignment operator

    template< class T, class B, bool I, class A >
    array_base< T,B,I,A >::~array_base()
    {
        array_destructor< T,N::value,F,D::value,M::value,A >()( data );
    }

//--
//--

    template< class T, class B, bool I >
    array_base< T,B,I,null::allocator >::array_base()
    {
        array_constructor< T,N::value,F,size,C::value,null::allocator >()( data );
    } // constructor

//--
//--

    template< class T, class B, bool I, class A >
    struct sub_type< array< T,B,I,A > >
    {
        typedef array< T,typename mpl::pop_front< B >::type,I,A > type;
    };

//--
//--

    template< class T, class B, std::size_t N, class F, bool I, class A, class C, class CT >
    struct array_out
    {
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;
        typedef typename array< T,B,I,A >::const_iterator_type type;
        typedef typename mpl::pop_front< B >::type P;
        typedef typename mpl::deref< F >::type D;
        typedef typename mpl::next< F >::type G;

        stream& operator()( stream& s, type const& a ) 
        {
            s << '(';
            for( std::size_t i = 0; i != D::value; ++i )
            {   array_out< T,P,N-1,G,I,A,C,CT >()( s, a[i] );
                if( i != D::value - 1 ) s << ',';
            }
            s << ')';
            return s;
        }
    };

    template< class T, class B, class F, bool I, class A, class C, class CT >
    struct array_out< T,B,1,F,I,A,C,CT >
    {
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;
        typedef typename array< T,B,I,A >::const_iterator_type type;
        typedef typename mpl::deref< F >::type D;

        stream& operator()( stream& s, type const& a ) 
        {
            s << '(';
            for( std::size_t i = 0; i != D::value - 1; ++i ) s << a[i] << ',';
            s << a[D::value-1] << ')';
            return s;
        }
    };

//--

    template< std::size_t N, class F, class C, class CT >
    struct array_out_size
    {
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;
        typedef typename mpl::deref< F >::type D;
        typedef typename mpl::next< F >::type G;

        void operator()( stream& s ) 
        {
            s << '[' << D::value << ']';
            array_out_size< N-1,G,C,CT >()( s );
        }
    };

    template< class F, class C, class CT >
    struct array_out_size< 1,F,C,CT >
    {
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;
        typedef typename mpl::deref< F >::type D;

        void operator()( stream& s ) 
        {
            s << '[' << D::value << ']';
        }
    };

//--

    template< class T, class B, bool I, class A, class C, class CT >
    std::basic_ostream< C,CT >& operator<<( std::basic_ostream< C,CT >& o, array< T,B,I,A > const& a )
    {
        typedef typename mpl::size< B >::type N; typedef typename mpl::begin< B >::type F;

        std::basic_ostringstream< C,CT,std::allocator< C > > s;
        s.flags( o.flags() ); s.imbue( o.getloc() ); s.precision( o.precision() );
        array_out_size< N::value,F,C,CT >()( s );
        return o << array_out< T,B,N::value,F,I,A,C,CT >()( s, a+0 ).str().c_str();
    }

//--
//--

    template< class T, bool I, class A >
    class array< T,bounds0,I,A >
    {
    public:

        typedef array type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef bounds0 subarray_type;
        typedef bounds0 member_type;
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
        typedef bounds0 limits;

        enum { dimensionality = 0, size = 0 };

    };

    template< class T, bool I, class A >
    class array< T,mpl::vector0<>,I,A >
        : public array< T,bounds0,I,A >
    {};

//--
//--

    template< class T, class B, bool I, class A, bool I1, class A1 >
    bool operator==( array< T,B,I,A > const& x, array< T,B,I1,A1 > const& y )
    {
        return std::equal( x.begin(), x.end(), y.begin() );
    }

    template< class T, class B, bool I, class A, bool I1, class A1 >
    bool operator<( array< T,B,I,A > const& x, array< T,B,I1,A1 > const& y )
    {
        return std::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
    }

    template< class T, class B, bool I, class A, bool I1, class A1 >
    bool operator!=( array< T,B,I,A > const& x, array< T,B,I1,A1 > const& y )
    {
        return !( x == y );
    }

    template< class T, class B, bool I, class A, bool I1, class A1 >
    bool operator>( array< T,B,I,A > const& x, array< T,B,I1,A1 > const& y )
    {
        return y < x;
    }

    template< class T, class B, bool I, class A, bool I1, class A1 >
    bool operator<=( array< T,B,I,A > const& x, array< T,B,I1,A1 > const& y )
    {
        return !( y < x );
    }

    template< class T, class B, bool I, class A, bool I1, class A1 >
    bool operator>=( array< T,B,I,A > const& x, array< T,B,I1,A1 > const& y )
    {
        return !( x < y );
    }

//--

    template< class T, class B, bool I, class A >
    void swap( array< T,B,I,A >& x, array< T,B,I,A >& y )
    {
        x.swap( y );
    }

    template< class T, class B, bool I, class A, bool I1, class A1 >
    void swap( array< T,B,I,A >& x, array< T,B,I1,A1 >& y )
    {
        x.swap( y );
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_GENERIC_ARRAY_HPP
