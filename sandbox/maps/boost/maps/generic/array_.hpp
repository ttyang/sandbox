//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_GENERIC_ARRAY_HPP_ )
#define BOOST_MAPS_GENERIC_ARRAY_HPP_

#include <boost/maps/support/includes.hpp>

namespace boost { namespace maps {

//--

    template< class T, std::size_t N, std::size_t D, std::size_t S, class A >
    struct array_allocate_
    {    
        typedef typename array_type_< T,N,D,A >::type type;
        typedef typename array_type_< T,N-1,D,A >::type value_type;
        typedef typename A::template rebind< value_type >::other allocator;

        void operator()( type& p ) 
        {    
            allocator a; 
            p = a.allocate( S );
        }
    };

//--

    template< class T, std::size_t N, std::size_t D, std::size_t S, class A >
    struct array_deallocate_
    {    
        typedef typename array_type_< T,N,D,A >::type type;
        typedef typename array_type_< T,N-1,D,A >::type value_type;
        typedef typename A::template rebind< value_type >::other allocator;

        void operator()( type& p ) 
        {    
            allocator a; 
            a.deallocate( p, S ); p = 0;
        }
    };

//--

    template< class T, std::size_t N, std::size_t D, std::size_t S, bool I, class A >
    struct array_construct_
    {    
        typedef typename array_type_< T,N,D,A >::type type;
        typedef typename array_type_< T,N-1,D,A >::type value_type;
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

    template< class T, std::size_t N, std::size_t D, std::size_t S, class A >
    struct array_construct_< T,N,D,S,false,A >
    {    
        typedef typename array_type_< T,N,D,A >::type type;

        void operator()( type& ) 
        {}
    };

//--

    template< class T, std::size_t N, std::size_t D, std::size_t S, bool P, class A >
    struct array_copy_assign_
    {    
        typedef typename array_type_< T,N,D,A >::type type;
        typedef typename array_type_< T,N-1,D,A >::type value_type;
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

    template< class T, std::size_t N, std::size_t D, std::size_t S, class A >
    struct array_copy_assign_< T,N,D,S,true,A >
    {    
        typedef typename array_type_< T,N,D,A >::type type;

        void operator()( type& p, type const& q ) 
        {
            memcpy( p, q, S * sizeof(T) ); 
        }
    };

//--

    template< class T, std::size_t N, std::size_t D, std::size_t S, bool I, class A >
    struct array_destroy_
    {    
        typedef typename array_type_< T,N,D,A >::type type;
        typedef typename array_type_< T,N-1,D,A >::type value_type;
        typedef typename A::template rebind< value_type >::other allocator;

        void operator()( type& p ) 
        {    
            allocator a; 
            for( std::size_t i = 0; i != S; ++i ) a.destroy( p+i );
        }
    };

    template< class T, std::size_t N, std::size_t D, std::size_t S, class A >
    struct array_destroy_< T,N,D,S,true,A >
    {    
        typedef typename array_type_< T,N,D,A >::type type;

        void operator()( type& ) 
        {}
    };

//--
//--

    template< class T, std::size_t N, std::size_t D, std::size_t S, bool I, class A >
    struct array_constructor_
    {
        typedef typename array_type_< T,N,D,A >::type type;

        void operator()( type& p ) 
        {    
            array_allocate_< T,N,D,S,A >()( p );
            try { array_constructor_< T,N-1,D,S*D,I,A >()( p[0] ); }
            catch( ... ) { array_deallocate_< T,N,D,S,A >()( p ); throw; }
            for( std::size_t j = 1, k = D; j != S; ++j ) p[j] = p[j-1] + k;
        }
    };

    template< class T, std::size_t D, std::size_t S, bool I, class A >
    struct array_constructor_< T,1,D,S,I,A >
    {
        typedef typename array_type_< T,1,D,A >::type type;

        void operator()( type& p )
        {
            array_allocate_< T,1,D,S,A >()( p );
            try { array_construct_< T,1,D,S,I,A >()( p ); }
            catch( ... ) { array_deallocate_< T,1,D,S,A >()( p ); throw; }
        }
    };

//--

    template< class T, std::size_t N, std::size_t D, std::size_t S, bool I, class A >
    struct array_destructor_
    {    
        typedef typename array_type_< T,N,D,A >::type type;

        void operator()( type& p )
        {    
            array_destructor_< T,N-1,D,S*D,I,A >()( p[0] );
            array_deallocate_< T,N,D,S,A >()( p );
        }
    };

    template< class T, std::size_t D, std::size_t S, bool I, class A >
    struct array_destructor_< T,1,D,S,I,A >
    {    
        typedef typename array_type_< T,1,D,A >::type type;

        void operator()( type& p ) 
        {    
            array_destroy_< T,1,D,S,I,A >()( p );
            array_deallocate_< T,1,D,S,A >()( p );
        }
    };

//--

    template< class T, std::size_t N, std::size_t D, std::size_t S, class A >
    struct array_copy_
    {    
        typedef typename array_type_< T,N,D,A >::type type;

        void operator()( type& p, type const& q ) 
        {    
            array_allocate_< T,N,D,S,A >()( p ); 
            try { array_copy_< T,N-1,D,S*D,A >()( p[0], q[0] ); }
            catch( ... ) { array_deallocate_< T,N,D,S,A >()( p ); throw; }
            for( std::size_t j = 1, k = D; j != S; ++j ) p[j] = p[j-1] + k;
        }
    };

    template< class T, std::size_t D, std::size_t S, class A >
    struct array_copy_< T,1,D,S,A >
    {    
        typedef typename array_type_< T,1,D,A >::type type;
        typedef typename boost::is_pod< T >::type P;

        void operator()( type& p, type const& q )
        {    
            array_allocate_< T,1,D,S,A >()( p );
            try { array_copy_assign_< T,1,D,S,P::value,A >()( p, q ); }
            catch( ... ) { array_deallocate_< T,1,D,S,A >()( p ); throw; }
        }
    };

//--

    template< class T, std::size_t N, std::size_t D, std::size_t S, bool I, class A >
    struct array_assign_
    {    
        typedef typename array_type_< T,N,D,A >::type type;

        void operator()( type& p, type const& q ) 
        {    
            array_assign_< T,N-1,D,S*D,I,A >()( p[0], q[0] );
        }
    };

    template< class T, std::size_t D, std::size_t S, bool I, class A >
    struct array_assign_< T,2,D,S,I,A >
    {    
        typedef typename array_type_< T,2,D,A >::type type;

        void operator()( type& p, type const& q ) 
        {    
            array_assign_< T,1,D,S*D,I,A >()( p[0], q[0] );
            for( std::size_t j = 0, k = 0; j != S; ++j, k += D ) p[j] = &p[0][k];
        }
    };

    template< class T, std::size_t D, std::size_t S, bool I, class A >
    struct array_assign_< T,1,D,S,I,A >
    {    
        typedef typename array_type_< T,1,D,A >::type type;
        typedef typename boost::is_pod< T >::type P;

        void operator()( type& p, type const& q )
        {    
            type t = 0; array_allocate_< T,1,D,S,A >()( t );
            try { array_copy_assign_< T,1,D,S,P::value,A >()( t, q ); }
            catch( ... ) { array_deallocate_< T,1,D,S,A >()( t ); throw; }
            type r = p; p = t; t = 0; array_destructor_< T,1,D,S,I,A >()( r );
        }
    };

//--

    template< class T, std::size_t N, std::size_t D, class A >
    struct array_swap_
    {
        typedef typename array_type_< T,N,D,A >::type type;

        void operator()( type& p, type& q ) 
        {
            std::swap( p, q );
        }
    };

//--
//--

    template< class T, std::size_t N, std::size_t D, std::size_t S, bool I >
    struct array_constructor_< T,N,D,S,I,null::allocator >
    {
        typedef typename array_type_< T,N,D,null::allocator >::type type;

        void operator()( type& a ) 
        {   
            memset( a, 0, S * sizeof(T) );
        }
    };

    template< class T, std::size_t D, std::size_t S, bool I >
    struct array_constructor_< T,1,D,S,I,null::allocator >
    {
        typedef typename array_type_< T,1,D,null::allocator >::type type;

        void operator()( type& a ) 
        {   
            memset( a, 0, S * sizeof(T) );
        }
    };

    template< class T, std::size_t N, std::size_t D, std::size_t S >
    struct array_constructor_< T,N,D,S,false,null::allocator >
    {
        typedef typename array_type_< T,N,D,null::allocator >::type type;

        void operator()( type& ) 
        {}
    };

    template< class T, std::size_t D, std::size_t S >
    struct array_constructor_< T,1,D,S,false,null::allocator >
    {
        typedef typename array_type_< T,1,D,null::allocator >::type type;

        void operator()( type& ) 
        {}
    };

//--

    template< class T, std::size_t N, std::size_t D >
    struct array_swap_< T,N,D,null::allocator >
    {
        typedef typename array_type_< T,N,D,null::allocator >::type type;

        void operator()( type& p, type& q ) 
        {
            for( std::size_t i = 0; i != D; ++i )
                array_swap_< T,N-1,D,null::allocator >()( p[i], q[i] );
        }
    };

    template< class T, std::size_t D >
    struct array_swap_< T,1,D,null::allocator >
    {
        typedef typename array_type_< T,1,D,null::allocator >::type type;

        void operator()( type& p, type& q )
        {
            for( std::size_t i = 0; i != D; ++i ) 
                std::swap( p[i], q[i] );
        }
    };

//--
//--

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    struct array_element_const_
    {
        typedef typename array_< T,N,D,I,A >::const_reference const_reference;
        typedef typename array_type_< T,N,D,A >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;

        const_reference operator()( type const& p, const_iterator i )
        {
            BOOST_ASSERT( *i < D );
            return array_element_const_< T,N-1,D,I,A >()( p[*i], i+1 );
        }
    };

    template< class T, std::size_t D, bool I, class A >
    struct array_element_const_< T,1,D,I,A >
    {
        typedef typename array_< T,1,D,I,A >::const_reference const_reference;
        typedef typename array_type_< T,1,D,A >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;

        const_reference operator()( type const& p, const_iterator i )
        {
            BOOST_ASSERT( *i < D );
            return p[*i];
        }
    };

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    struct array_element_
    {
        typedef typename array_< T,N,D,I,A >::reference reference;
        typedef typename array_type_< T,N,D,A >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;

        reference operator()( type& p, const_iterator i )
        {
            BOOST_ASSERT( *i < D );
            return array_element_< T,N-1,D,I,A >()( p[*i], i+1 );
        }
    };

    template< class T, std::size_t D, bool I, class A >
    struct array_element_< T,1,D,I,A >
    {
        typedef typename array_< T,1,D,I,A >::reference reference;
        typedef typename array_type_< T,1,D,A >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;

        reference operator()( type& p, const_iterator i )
        {
            BOOST_ASSERT( *i < D );
            return p[*i];
        }
    };

//--

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    struct array_element_at_const_
    {
        typedef typename array_< T,N,D,I,A >::const_reference const_reference;
        typedef typename array_type_< T,N,D,A >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;

        const_reference operator()( type const& p, const_iterator i )
        {
            if( !( *i < D ) ) 
                throw std::out_of_range( "array_<> access out of range" );
            return array_element_at_const_< T,N-1,D,I,A >()( p[*i], i+1 );
        }
    };

    template< class T, std::size_t D, bool I, class A >
    struct array_element_at_const_< T,1,D,I,A >
    {
        typedef typename array_< T,1,D,I,A >::const_reference const_reference;
        typedef typename array_type_< T,1,D,A >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;

        const_reference operator()( type const& p, const_iterator i )
        {
            if( !( *i < D ) )
                throw std::out_of_range( "array_<> access out of range" );
            return p[*i];
        }
    };

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    struct array_element_at_
    {
        typedef typename array_< T,N,D,I,A >::reference reference;
        typedef typename array_type_< T,N,D,A >::type type;
        typedef typename bounds< N >::const_iterator const_iterator;

        reference operator()( type& p, const_iterator i )
        {
            if( !( *i < D ) ) 
                throw std::out_of_range( "array_<> access out of range" );
            return array_element_at_< T,N-1,D,I,A >()( p[*i], i+1 );
        }
    };

    template< class T, std::size_t D, bool I, class A >
    struct array_element_at_< T,1,D,I,A >
    {
        typedef typename array_< T,1,D,I,A >::reference reference;
        typedef typename array_type_< T,1,D,A >::type type;
        typedef typename bounds< 1 >::const_iterator const_iterator;

        reference operator()( type& p, const_iterator i )
        {
            if( !( *i < D ) )
                throw std::out_of_range( "array_<> access out of range" );
            return p[*i];
        }
    };

//--

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    struct array_begin_const_
    {
        typedef typename array_< T,N,D,I,A >::const_iterator const_iterator;
        typedef typename array_type_< T,N,D,A >::type type;

        const_iterator operator()( type const& p ) 
        {
            return array_begin_const_< T,N-1,D,I,A >()( *p );
        }
    };

    template< class T, std::size_t D, bool I, class A >
    struct array_begin_const_< T,1,D,I,A >
    {    
        typedef typename array_< T,1,D,I,A >::const_iterator const_iterator;
        typedef typename array_type_< T,1,D,A >::type type;

        const_iterator operator()( type const& p )
        {
            return p;
        }
    };

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    struct array_begin_
    {    
        typedef typename array_< T,N,D,I,A >::iterator iterator;
        typedef typename array_type_< T,N,D,A >::type type;

        iterator operator()( type& p ) 
        {
            return array_begin_< T,N-1,D,I,A >()( *p );
        }
    };

    template< class T, std::size_t D, bool I, class A >
    struct array_begin_< T,1,D,I,A >
    {
        typedef typename array_< T,1,D,I,A >::iterator iterator;
        typedef typename array_type_< T,1,D,A >::type type;

        iterator operator()( type& p )
        {
            return p;
        }
    };

//--

    // Base type for dynamically allocated array_'s.
    template< class T, std::size_t N, std::size_t D, bool I, class A >
    class array_base_
        : public expression< array_< T,N,D,I,A > >
    {
    public:

        typedef array_< T,N,D,I,A > type;
        typedef type const& type_const_reference;
        typedef expression< type > base_type;
        typedef typename array_member_type_< T,N,D,A >::type member_type;
        
        enum { dimensionality = N, size = array_size_< N,D >::type::value };

        array_base_();

        array_base_( type_const_reference );
        template< bool I1, class A1 > array_base_( array_< T,N,D,I1,A1 > const& );

        void operator=( type_const_reference );
        template< bool I1, class A1 > void operator=( array_< T,N,D,I1,A1 > const& );

        ~array_base_();

    protected:

        typedef typename has_trivial_destructor< T >::type M;
        typedef typename array_initialize< T,I,A >::type C;

        member_type data;

        template< class T1, std::size_t N1, std::size_t D1, bool I1, class A1 > 
        friend class array_;
    };

//--
//--

    // Base type for statically allocated array_'s.
    template< class T, std::size_t N, std::size_t D, bool I >
    class array_base_< T,N,D,I,null::allocator >
        : public expression< array_< T,N,D,I,null::allocator > >
    {
    public:

        typedef array_< T,N,D,I,null::allocator > type;
        typedef expression< type > base_type;
        typedef typename array_member_type_< T,N,D,null::allocator >::type member_type;
        
        enum { dimensionality = N, size = array_size_< N,D >::type::value };

        array_base_();

    protected:

        typedef typename array_initialize< T,I,null::allocator >::type C;

        member_type data;

        template< class T1, std::size_t N1, std::size_t D1, bool I1, class A1 > 
        friend class array_;
    };

//--
//--

    /*
        array_ class template

        parameters

            required

                T - stored data type
                    type: arbitrary type
                N - number of dimensions 
                    type: std::size_t
                D - size of each dimension
                    type: std::size_t

            optional

                I - initialization parameter 
                    type: bool 
                    default: true, data elements zero/default initialized
                A - allocator 
                    type: standard conforming allocator, or null::allocator
                    default: null::allocator, statically allocated array
    */

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    class array_
        : public array_base_< T,N,D,I,A >
    {
    public:

        typedef array_ type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef array_base_< T,N,D,I,A > base_type;
        typedef sub_type< type > subarray_type;
        typedef typename base_type::member_type member_type;
        typedef typename array_value_type_< T,N,D,A >::type value_type;
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
        typedef mpl::bool_< I > initialize;
        typedef typename array_bounds_< N,D >::type bounds;
        typedef bounds limits_type;

        array_();

        array_( type_const_reference );
        template< bool I1, class A1 > array_( array_< T,N,D,I1,A1 > const& );

        type_reference operator=( type_const_reference );
        template< bool I1, class A1 > type_reference operator=( array_< T,N,D,I1,A1 > const& );
        assigner_type operator=( const_reference );

        ~array_();

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
        template< bool I1, class A1 > void swap( array_< T,N,D,I1,A1 >& );

        const_iterator begin() const;
        iterator begin();
        const_iterator end() const;
        iterator end();

    };

//--
//--

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    array_< T,N,D,I,A >::array_() : base_type()
    {} // constructor

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    array_< T,N,D,I,A >::array_( type_const_reference a ) : base_type( a )
    {} // copy constructor

    template< class T, std::size_t N, std::size_t D, bool I, class A > template< bool I1, class A1 >
    array_< T,N,D,I,A >::array_( array_< T,N,D,I1,A1 > const& a ) : base_type( a )
    {} // copy constructor

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::type_reference array_< T,N,D,I,A >::operator=( type_const_reference a )
    {
        if( &a != this ) base_type::operator=( a );
        return *this;
    } // ( copy ) assignment operator

    template< class T, std::size_t N, std::size_t D, bool I, class A > template< bool I1, class A1 >
    typename array_< T,N,D,I,A >::type_reference array_< T,N,D,I,A >::operator=( array_< T,N,D,I1,A1 > const& a )
    {
        base_type::operator=( a );
        return *this;
    } // ( copy ) assignment operator

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::assigner_type array_< T,N,D,I,A >::operator=( const_reference t )
    {
        return assigner_type( *this, begin(), t );
    } // assigner assignment

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    array_< T,N,D,I,A >::~array_()
    {} // destructor

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::const_reference_type array_< T,N,D,I,A >::operator[]( size_type s ) const
    {
        return this->data[s];
    } // operator[] const

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::reference_type array_< T,N,D,I,A >::operator[]( size_type s )
    {
        return this->data[s];
    } // operator[]

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::const_reference_type array_< T,N,D,I,A >::operator*() const
    {
        return *this->data;
    } // dereference

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::reference_type array_< T,N,D,I,A >::operator*()
    {
        return *this->data;
    } // dereference

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::const_iterator_type array_< T,N,D,I,A >::operator+( size_type s ) const
    {
        return this->data+s;
    } // operator+, enables explicit indirection expressions

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::iterator_type array_< T,N,D,I,A >::operator+( size_type s )
    {
        return this->data+s;
    } // operator+, enables explicit indirection expressions

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::const_reference array_< T,N,D,I,A >::operator[]( bounds_const_reference b ) const
    {
        return array_element_const_< T,N,D,I,A >()( this->data, b.begin() );
    } // operator[] const

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::reference array_< T,N,D,I,A >::operator[]( bounds_const_reference b )
    {
        return array_element_< T,N,D,I,A >()( this->data, b.begin() );
    } // operator[]

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::const_reference array_< T,N,D,I,A >::at( bounds_const_reference b ) const
    {
        return array_element_at_const_< T,N,D,I,A >()( this->data, b.begin() );
    } // at const

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::reference array_< T,N,D,I,A >::at( bounds_const_reference b )
    {
        return array_element_at_< T,N,D,I,A >()( this->data, b.begin() );
    } // at

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    bool const array_< T,N,D,I,A >::empty() const
    {    
        return false;
    } // empty

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::size_type const array_< T,N,D,I,A >::size() const
    {
        return base_type::size;
    } // size

    template< class T, std::size_t N, std::size_t D, bool I, class A > template< std::size_t U >
    typename array_< T,N,D,I,A >::size_type const array_< T,N,D,I,A >::bound() const
    {
        BOOST_STATIC_ASSERT( U < N );
        return D;
    } // bound

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    void array_< T,N,D,I,A >::swap( type_reference a )
    {
        if( &a != this ) array_swap_< T,N,D,A >()( this->data, a.data ); 
    } // swap

    template< class T, std::size_t N, std::size_t D, bool I, class A > template< bool I1, class A1 >
    void array_< T,N,D,I,A >::swap( array_< T,N,D,I1,A1 >& a )
    {
        array_swap_< T,N,D,A >()( this->data, a.data );
    } // swap

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::const_iterator array_< T,N,D,I,A >::begin() const
    {
        return array_begin_const_< T,N,D,I,A >()( this->data );
    } // begin const

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::iterator array_< T,N,D,I,A >::begin()
    {
        return array_begin_< T,N,D,I,A >()( this->data );
    } // begin

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::const_iterator array_< T,N,D,I,A >::end() const
    {
        return begin()+base_type::size;
    } // end const

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    typename array_< T,N,D,I,A >::iterator array_< T,N,D,I,A >::end()
    {
        return begin()+base_type::size;
    } // end

//--
//--

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    array_base_< T,N,D,I,A >::array_base_()
    {
        array_constructor_< T,N,D,D,C::value,A >()( data );
    } // constructor

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    array_base_< T,N,D,I,A >::array_base_( type_const_reference a )
    {
        array_copy_< T,N,D,D,A >()( data, a.data );
    } // copy constructor

    template< class T, std::size_t N, std::size_t D, bool I, class A > template< bool I1, class A1 >
    array_base_< T,N,D,I,A >::array_base_( array_< T,N,D,I1,A1 > const& a )
    {
        array_copy_< T,N,D,D,A >()( data, a.data );
    } // copy constructor

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    void array_base_< T,N,D,I,A >::operator=( type_const_reference a )
    {
        array_assign_< T,N,D,D,M::value,A >()( data, a.data );
    } // ( copy ) assignment operator

    template< class T, std::size_t N, std::size_t D, bool I, class A > template< bool I1, class A1 >
    void array_base_< T,N,D,I,A >::operator=( array_< T,N,D,I1,A1 > const& a )
    {
        array_assign_< T,N,D,D,M::value,A >()( data, a.data );
    } // ( copy ) assignment operator

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    array_base_< T,N,D,I,A >::~array_base_()
    {
        array_destructor_< T,N,D,D,M::value,A >()( data );
    }

//--
//--

    template< class T, std::size_t N, std::size_t D, bool I >
    array_base_< T,N,D,I,null::allocator >::array_base_()
    {
        array_constructor_< T,N,D,size,C::value,null::allocator >()( data );
    } // constructor

//--
//--

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    struct sub_type< array_< T,N,D,I,A > >
    {
        typedef array_< T,N-1,D,I,A > type;
    };

//--
//--

    template< class T, std::size_t N, std::size_t D, bool I, class A, class C, class CT >
    struct array_out_
    {
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;
        typedef typename array_< T,N,D,I,A >::const_iterator_type type;

        stream& operator()( stream& s, type const& a ) 
        {
            s << '(';
            for( std::size_t i = 0; i != D; ++i )
            {   array_out_< T,N-1,D,I,A,C,CT >()( s, a[i] );
                if( i != D - 1 ) s << ',';
            }
            s << ')';
            return s;
        }
    };

    template< class T, std::size_t D, bool I, class A, class C, class CT >
    struct array_out_< T,1,D,I,A,C,CT >
    {
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;
        typedef typename array_< T,1,D,I,A >::const_iterator_type type;

        stream& operator()( stream& s, type const& a ) 
        {
            s << '(';
            for( std::size_t i = 0; i != D - 1; ++i ) s << a[i] << ',';
            s << a[D-1] << ')';
            return s;
        }
    };

//--

    template< std::size_t N, std::size_t D, class C, class CT >
    struct array_out_size_
    {
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;

        void operator()( stream& s ) 
        {
            s << '[' << D << ']';
            array_out_size_< N-1,D,C,CT >()( s );
        }
    };

    template< std::size_t D, class C, class CT >
    struct array_out_size_< 1,D,C,CT >
    {
        typedef std::basic_ostringstream< C,CT,std::allocator< C > > stream;

        void operator()( stream& s ) 
        {
            s << '[' << D << ']';
        }
    };

//--

    template< class T, std::size_t N, std::size_t D, bool I, class A, class C, class CT >
    std::basic_ostream< C,CT >& operator<<( std::basic_ostream< C,CT >& o, array_< T,N,D,I,A > const& a )
    {
        std::basic_ostringstream< C,CT,std::allocator< C > > s;
        s.flags( o.flags() ); s.imbue( o.getloc() ); s.precision( o.precision() );
        array_out_size_< N,D,C,CT >()( s );
        return o << array_out_< T,N,D,I,A,C,CT >()( s, a+0 ).str().c_str();
    }

//--
//--

    template< class T, std::size_t N, bool I, class A >
    class array_< T,N,0,I,A >
    {
    public:

        typedef array_ type;
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
        typedef bounds< N > bounds_type;
        typedef bounds_type const& bounds_const_reference;
        typedef mpl::bool_< I > initialize;
        typedef mpl::vector0<> limits;

        enum { dimensionality = N, size = 0 };

    };

    template< class T, bool I, class A >
    class array_< T,0,0,I,A >
    {
    public:

        typedef array_ type;
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
        typedef mpl::vector0<> limits;

        enum { dimensionality = 0, size = 0 };

    };

    template< class T, std::size_t D, bool I, class A >
    class array_< T,0,D,I,A >
        : public array_< T,0,0,I,A >
    {};

//--
//--

    template< class T, std::size_t N, std::size_t D, bool I, class A, bool I1, class A1 >
    bool operator==( array_< T,N,D,I,A > const& x, array_< T,N,D,I1,A1 > const& y )
    {
        return std::equal( x.begin(), x.end(), y.begin() );
    }

    template< class T, std::size_t N, std::size_t D, bool I, class A, bool I1, class A1 >
    bool operator<( array_< T,N,D,I,A > const& x, array_< T,N,D,I1,A1 > const& y )
    {
        return std::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
    }

    template< class T, std::size_t N, std::size_t D, bool I, class A, bool I1, class A1 >
    bool operator!=( array_< T,N,D,I,A > const& x, array_< T,N,D,I1,A1 > const& y )
    {
        return !( x == y );
    }

    template< class T, std::size_t N, std::size_t D, bool I, class A, bool I1, class A1 >
    bool operator>( array_< T,N,D,I,A > const& x, array_< T,N,D,I1,A1 > const& y )
    {
        return y < x;
    }

    template< class T, std::size_t N, std::size_t D, bool I, class A, bool I1, class A1 >
    bool operator<=( array_< T,N,D,I,A > const& x, array_< T,N,D,I1,A1 > const& y )
    {
        return !( y < x );
    }

    template< class T, std::size_t N, std::size_t D, bool I, class A, bool I1, class A1 >
    bool operator>=( array_< T,N,D,I,A > const& x, array_< T,N,D,I1,A1 > const& y )
    {
        return !( x < y );
    }

//--

    template< class T, std::size_t N, std::size_t D, bool I, class A >
    void swap( array_< T,N,D,I,A >& x, array_< T,N,D,I,A >& y )
    {
        x.swap( y );
    } 

    template< class T, std::size_t N, std::size_t D, bool I, class A, bool I1, class A1 >
    void swap( array_< T,N,D,I,A >& x, array_< T,N,D,I1,A1 >& y )
    {
        x.swap( y );
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_GENERIC_ARRAY_HPP_
