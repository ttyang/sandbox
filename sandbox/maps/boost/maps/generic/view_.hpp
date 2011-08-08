//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_GENERIC_VIEW_HPP_ )
#define BOOST_MAPS_GENERIC_VIEW_HPP_

#include <boost/maps/support/preprocessor_ranges.hpp>

namespace boost { namespace maps {

//--

    template< class A, class R, std::size_t N, bool B >
    struct view_reset_
    {    
        typedef typename view_< A,R,B >::iterator_type view_iterator;
        typedef typename A::iterator_type array_iterator;
        typedef view_range< typename mpl::front< R >::type > range;
        typedef typename A::subarray_type::type P;
        typedef typename mpl::pop_front< R >::type Q;
  
        void operator()( view_iterator v, array_iterator a ) 
        {
            for( std::size_t i = 0, j = range::first::value; 
                j != range::last::value; ++i, j += range::step::value )
                view_reset_< P,Q,N-1,B >()( v[i], a[j] );
        }
    };

    template< class A, class R, bool B >
    struct view_reset_< A,R,1,B >
    {    
        typedef typename view_< A,R,B >::iterator_type view_iterator;
        typedef typename A::iterator_type array_iterator;
        typedef view_range< typename mpl::front< R >::type > range;

        void operator()( view_iterator v, array_iterator a )
        {
            for( std::size_t i = 0, j = range::first::value; 
                j != range::last::value; ++i, j += range::step::value ) v[i] = &a[j];
        }
    };

    template< class A, class R >
    struct view_reset_< A,R,1,false >
    {    
        typedef typename view_< A,R,false >::iterator_type view_iterator;
        typedef typename A::iterator_type array_iterator;
        typedef view_range< typename mpl::front< R >::type > range;

        void operator()( view_iterator v, array_iterator a )
        {
            for( std::size_t i = 0, j = range::first::value; 
                j != range::last::value; ++i, j += range::step::value ) v[i] = a[j];
        }
    };

//--

    template< class A1, class A, class R, std::size_t N, bool B >
    struct view_set_
    {    
        typedef typename A1::iterator_type array_iterator;
        typedef typename view_< A,R,B >::const_iterator_type view_iterator;
        typedef view_range< typename mpl::front< R >::type > range;
        typedef typename A1::subarray_type::type P1;
        typedef typename A::subarray_type::type P;
        typedef typename mpl::pop_front< R >::type Q;

        void operator()( array_iterator a, view_iterator v ) 
        {
            for( std::size_t i = 0, j = range::first::value; 
                j != range::last::value; ++i, j += range::step::value )
                view_set_< P1,P,Q,N-1,B >()( a[j], v[i] );
        }
    };

    template< class A1, class A, class R, bool B >
    struct view_set_< A1,A,R,1,B >
    {    
        typedef typename A1::iterator_type array_iterator;
        typedef typename view_< A,R,B >::const_iterator_type view_iterator;
        typedef view_range< typename mpl::front< R >::type > range;

        void operator()( array_iterator a, view_iterator v )
        {
            for( std::size_t i = 0, j = range::first::value; 
                j != range::last::value; ++i, j += range::step::value ) a[j] = *v[i];
        }
    };

    template< class A1, class A, class R >
    struct view_set_< A1,A,R,1,false >
    {    
        typedef typename A1::iterator_type array_iterator;
        typedef typename view_< A,R,false >::const_iterator_type view_iterator;
        typedef view_range< typename mpl::front< R >::type > range;

        void operator()( array_iterator a, view_iterator v )
        {
            for( std::size_t i = 0, j = range::first::value; 
                j != range::last::value; ++i, j += range::step::value ) a[j] = v[i];
        }
    };

//--

    template< class A, class R, std::size_t N, bool B >
    struct view_element_const_
    {
        typedef typename view_< A,R,B >::const_reference const_reference;
        typedef typename view_< A,R,B >::const_iterator_type iterator_type;
        typedef typename bounds< A::dimensionality >::const_iterator const_iterator;
        typedef typename view_range< typename mpl::front< R >::type >::bound bound;
        typedef typename A::subarray_type::type P;
        typedef typename mpl::pop_front< R >::type Q;

        const_reference operator()( iterator_type p, const_iterator i )
        {
            BOOST_ASSERT( *i < bound::value );
            return view_element_const_< P,Q,N-1,B >()( p[*i], i+1 );
        }
    };

    template< class A, class R, bool B >
    struct view_element_const_< A,R,1,B >
    {
        typedef typename view_< A,R,B >::const_reference const_reference;
        typedef typename view_< A,R,B >::const_iterator_type iterator_type;
        typedef typename bounds< A::dimensionality >::const_iterator const_iterator;
        typedef typename view_range< typename mpl::front< R >::type >::bound bound;

        const_reference operator()( iterator_type p, const_iterator i )
        {
            BOOST_ASSERT( *i < bound::value );
            return p[*i];
        }
    };

//--

    template< class A, class R, std::size_t N, bool B >
    struct view_element_
    {
        typedef typename view_< A,R,B >::reference reference;
        typedef typename view_< A,R,B >::iterator_type iterator_type;
        typedef typename bounds< A::dimensionality >::const_iterator const_iterator;
        typedef typename view_range< typename mpl::front< R >::type >::bound bound;
        typedef typename A::subarray_type::type P;
        typedef typename mpl::pop_front< R >::type Q;

        reference operator()( iterator_type p, const_iterator i )
        {
            BOOST_ASSERT( *i < bound::value );
            return view_element_< P,Q,N-1,B >()( p[*i], i+1 );
        }
    };

    template< class A, class R, bool B >
    struct view_element_< A,R,1,B >
    {
        typedef typename view_< A,R,B >::reference reference;
        typedef typename view_< A,R,B >::iterator_type iterator_type;
        typedef typename bounds< A::dimensionality >::const_iterator const_iterator;
        typedef typename view_range< typename mpl::front< R >::type >::bound bound;

        reference operator()( iterator_type p, const_iterator i )
        {
            BOOST_ASSERT( *i < bound::value );
            return p[*i];
        }
    };

//--

    template< class A, class R, std::size_t N, bool B >
    struct view_element_at_const_
    {
        typedef typename view_< A,R,B >::const_reference const_reference;
        typedef typename view_< A,R,B >::const_iterator_type iterator_type;
        typedef typename bounds< A::dimensionality >::const_iterator const_iterator;
        typedef typename view_range< typename mpl::front< R >::type >::bound bound;
        typedef typename A::subarray_type::type P;
        typedef typename mpl::pop_front< R >::type Q;

        const_reference operator()( iterator_type p, const_iterator i )
        {
            if( !( *i < bound::value ) ) 
                throw std::out_of_range( "view_<> access out of range" );
            return view_element_at_const_< P,Q,N-1,B >()( p[*i], i+1 );
        }
    };

    template< class A, class R, bool B >
    struct view_element_at_const_< A,R,1,B >
    {
        typedef typename view_< A,R,B >::const_reference const_reference;
        typedef typename view_< A,R,B >::const_iterator_type iterator_type;
        typedef typename bounds< A::dimensionality >::const_iterator const_iterator;
        typedef typename view_range< typename mpl::front< R >::type >::bound bound;

        const_reference operator()( iterator_type p, const_iterator i )
        {
            if( !( *i < bound::value ) ) 
                throw std::out_of_range( "view_<> access out of range" );
            return p[*i];
        }
    };

//--

    template< class A, class R, std::size_t N, bool B >
    struct view_element_at_
    {
        typedef typename view_< A,R,B >::reference reference;
        typedef typename view_< A,R,B >::iterator_type iterator_type;
        typedef typename bounds< A::dimensionality >::const_iterator const_iterator;
        typedef typename view_range< typename mpl::front< R >::type >::bound bound;
        typedef typename A::subarray_type::type P;
        typedef typename mpl::pop_front< R >::type Q;

        reference operator()( iterator_type p, const_iterator i )
        {
            if( !( *i < bound::value ) ) 
                throw std::out_of_range( "view_<> access out of range" );
            return view_element_at_< P,Q,N-1,B >()( p[*i], i+1 );
        }
    };

    template< class A, class R, bool B >
    struct view_element_at_< A,R,1,B >
    {
        typedef typename view_< A,R,B >::reference reference;
        typedef typename view_< A,R,B >::iterator_type iterator_type;
        typedef typename bounds< A::dimensionality >::const_iterator const_iterator;
        typedef typename view_range< typename mpl::front< R >::type >::bound bound;

        reference operator()( iterator_type p, const_iterator i )
        {
            if( !( *i < bound::value ) ) 
                throw std::out_of_range( "view_<> access out of range" );
            return p[*i];
        }
    };

//--

    template< class A, class R, std::size_t N, bool B, std::size_t S >
    struct view_empty_
    {
        typedef typename view_< A,R,B >::const_iterator_type iterator_type;
        typedef typename A::subarray_type::type P;
        typedef typename mpl::pop_front< R >::type Q;
        typedef typename view_range< typename mpl::front< Q >::type >::bound D;

        bool operator()( iterator_type v ) 
        {
            return view_empty_< P,Q,N-1,B,S*D::value >()( v[0] );
        }
    };

    template< class A, class R, std::size_t S >
    struct view_empty_< A,R,1,false,S >
    {
        typedef typename view_< A,R,false >::const_iterator_type iterator_type;

        bool operator()( iterator_type ) 
        {
            return false;
        }
    };

    template< class A, class R, bool B, std::size_t S >
    struct view_empty_< A,R,1,B,S >
    {
        typedef typename view_< A,R,B >::const_iterator_type iterator_type;
        typedef typename view_range< typename mpl::front< R >::type >::bound D;

        bool operator()( iterator_type v )
        {
            for( std::size_t i = 0; i != S * D::value; ++i ) 
                if( v[i] == 0 ) return true;
            return false;
        }
    };

//--

    template< class A1, class A, class R, std::size_t N, bool B, std::size_t S >
    struct view_to_
    {    
        typedef typename A1::iterator_type array_iterator;
        typedef typename view_< A,R,B >::const_iterator_type view_iterator;
        typedef typename mpl::front< typename A1::bounds >::type F;
        typedef typename A1::subarray_type::type P1;
        typedef typename A::subarray_type::type P;
        typedef typename mpl::pop_front< R >::type Q;

        void operator()( array_iterator a, view_iterator v ) 
        {
            view_to_< P1,P,Q,N-1,B,S*F::value >()( a[0], v[0] );
        }
    };

    template< class A1, class A, class R, bool B, std::size_t S >
    struct view_to_< A1,A,R,1,B,S >
    {
        typedef typename A1::iterator_type array_iterator;
        typedef typename view_< A,R,B >::const_iterator_type view_iterator;
        typedef typename mpl::front< typename A1::bounds >::type F;

        void operator()( array_iterator a, view_iterator v )
        {
            for( std::size_t i = 0; i != S * F::value; ++i ) a[i] = *v[i];
        }
    };

    template< class A1, class A, class R, std::size_t S >
    struct view_to_< A1,A,R,1,false,S >
    {
        typedef typename A1::iterator_type array_iterator;
        typedef typename view_< A,mpl::vector1< R >,false >::const_iterator_type view_iterator;
        typedef typename mpl::front< typename A1::bounds >::type F;

        void operator()( array_iterator a, view_iterator v )
        {
            for( std::size_t i = 0; i != S * F::value; ++i ) a[i] = v[i];
        }
    };

//--

    template< class A, class A1, class R, std::size_t N, bool B, std::size_t S >
    struct view_from_
    {    
        typedef typename view_< A,R,B >::iterator_type view_iterator;
        typedef typename A1::const_iterator_type array_iterator;
        typedef typename mpl::front< typename A1::bounds >::type F;
        typedef typename A::subarray_type::type P;
        typedef typename A1::subarray_type::type P1;
        typedef typename mpl::pop_front< R >::type Q;

        void operator()( view_iterator v, array_iterator a ) 
        {
            view_from_< P,P1,Q,N-1,B,S*F::value >()( v[0], a[0] );
        }
    };

    template< class A, class A1, class R, bool B, std::size_t S >
    struct view_from_< A,A1,R,1,B,S >
    {
        typedef typename view_< A,mpl::vector1< R >,B >::iterator_type view_iterator;
        typedef typename A1::const_iterator_type array_iterator;
        typedef typename mpl::front< typename A1::bounds >::type F;

        void operator()( view_iterator v, array_iterator a )
        {
            for( std::size_t i = 0; i != S * F::value; ++i ) *v[i] = a[i];
        }
    };

    template< class A, class A1, class R, std::size_t S >
    struct view_from_< A,A1,R,1,false,S >
    {
        typedef typename view_< A,mpl::vector1< R >,false >::iterator_type view_iterator;
        typedef typename A1::const_iterator_type array_iterator;
        typedef typename mpl::front< typename A1::bounds >::type F;

        void operator()( view_iterator v, array_iterator a )
        {
            for( std::size_t i = 0; i != S * F::value; ++i ) v[i] = a[i];
        }
    };

//--

    template< class A, class R, std::size_t N, bool B >
    struct view_begin_const_
    {    
        typedef typename view_< A,R,B >::const_iterator const_iterator;
        typedef typename view_< A,R,B >::const_iterator_type iterator_type;
        typedef typename A::subarray_type::type P;
        typedef typename mpl::pop_front< R >::type Q;

        const_iterator operator()( iterator_type p ) 
        {
            return view_begin_const_< P,Q,N-1,B >()( p[0] );
        }
    };

    template< class A, class R, bool B >
    struct view_begin_const_< A,R,1,B >
    {    
        typedef typename view_< A,R,B >::const_iterator const_iterator;
        typedef typename view_< A,R,B >::const_iterator_type iterator_type;

        const_iterator operator()( iterator_type p )
        {
            return p;
        }
    };

    template< class A, class R, std::size_t N, bool B >
    struct view_begin_
    {    
        typedef typename view_< A,R,B >::iterator iterator;
        typedef typename view_< A,R,B >::iterator_type iterator_type;
        typedef typename A::subarray_type::type P;
        typedef typename mpl::pop_front< R >::type Q;

        iterator operator()( iterator_type p ) 
        {
            return view_begin_< P,Q,N-1,B >()( p[0] );
        }
    };

    template< class A, class R, bool B >
    struct view_begin_< A,R,1,B >
    {    
        typedef typename view_< A,R,B >::iterator iterator;
        typedef typename view_< A,R,B >::iterator_type iterator_type;

        iterator operator()( iterator_type p )
        {
            return p;
        }
    };

//--
//--

    template< class A, class R, bool B >
    class view_
        : public expression< view_< A,R,B > >
    {
    public:

        typedef view_ type;
        typedef type const& type_const_reference;
        typedef type& type_reference;
        typedef type const* type_const_pointer;
        typedef type* type_pointer;
        typedef expression< type > base_type;
        typedef typename view_traits_< A,R,B >::value_type value_type;
        typedef typename view_traits_< A,R,B >::const_reference_type const_reference_type;
        typedef typename view_traits_< A,R,B >::reference_type reference_type;
        typedef typename view_traits_< A,R,B >::const_iterator_type const_iterator_type;
        typedef typename view_traits_< A,R,B >::iterator_type iterator_type;
        typedef typename view_traits_< A,R,B >::element_type element_type;
        typedef typename view_traits_< A,R,B >::const_iterator const_iterator;
        typedef typename view_traits_< A,R,B >::iterator iterator;
        typedef typename view_traits_< A,R,B >::const_reference const_reference;
        typedef typename view_traits_< A,R,B >::reference reference;
        typedef typename view_traits_< A,R,B >::allocator_type allocator_type;
        typedef typename view_traits_< A,R,B >::size_type size_type;
        typedef typename view_traits_< A,R,B >::difference_type difference_type;
        typedef typename view_traits_< A,R,B >::bounds_type bounds_type;
        typedef typename view_traits_< A,R,B >::bounds_const_reference bounds_const_reference;
        typedef typename view_traits_< A,R,B >::bounds bounds;
        typedef typename view_traits_< A,R,B >::ranges ranges;

        enum { dimensionality = A::dimensionality, size = view_size< R >::type::value };

        view_();
        explicit view_( A& );

        void reset( A& );
        template< class A1 > void set( A1& ) const;

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
        template< std::size_t U > size_type const bound() const;

        template< class A1 > void to( A1& );
        template< class A1 > void from( A1 const& );

        const_iterator begin() const;
        iterator begin();
        const_iterator end() const;
        iterator end();

    protected:

        typedef typename mpl::size< R >::type N;
        typedef typename view_traits_< A,R,B >::member_type member_type;

        member_type data;

    private:

        view_( type_const_reference ) {}
        type_reference operator=( type_const_reference ) {}

    };

//--
//--

    template< class A, class R, bool B >
    view_< A,R,B >::view_()
    {
        BOOST_MPL_ASSERT(( view_valid< A,R > ));
    }

    template< class A, class R, bool B >
    view_< A,R,B >::view_( A& a )
    {
        BOOST_MPL_ASSERT(( view_valid< A,R > ));
        view_reset_< A,R,N::value,B >()( data+0, a+0 );
    }

    // Set this view_ representation to contain the values or pointers 
    // to the values, determined by parameter B, contained in array a.
    template< class A, class R, bool B >
    void view_< A,R,B >::reset( A& a )
    {
        view_reset_< A,R,N::value,B >()( data+0, a+0 );
    }

    // Sets the values of a to the corresponding values of the array 
    // that this view_ represents.
    template< class A, class R, bool B > template< class A1 >
    void view_< A,R,B >::set( A1& a ) const
    {
        BOOST_MPL_ASSERT(( mpl::equal< typename A::bounds, typename A1::bounds > ));
        view_set_< A1,A,R,N::value,B >()( a+0, data+0 );
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::const_reference_type view_< A,R,B >::operator[]( size_type s ) const
    {
        return data[s];
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::reference_type view_< A,R,B >::operator[]( size_type s )
    {
        return data[s];
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::const_reference_type view_< A,R,B >::operator*() const
    {
        return *data;
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::reference_type view_< A,R,B >::operator*()
    {
        return *data;
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::const_iterator_type view_< A,R,B >::operator+( size_type s ) const
    {
        return data+s;
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::iterator_type view_< A,R,B >::operator+( size_type s )
    {
        return data+s;
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::const_reference view_< A,R,B >::operator[]( bounds_const_reference b ) const
    {
        return view_element_const_< A,R,N::value,B >()( data+0, b.begin() );
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::reference view_< A,R,B >::operator[]( bounds_const_reference b )
    {
        return view_element_< A,R,N::value,B >()( data+0, b.begin() );
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::const_reference view_< A,R,B >::at( bounds_const_reference b ) const
    {
        return view_element_at_const_< A,R,N::value,B >()( data+0, b.begin() );
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::reference view_< A,R,B >::at( bounds_const_reference b )
    {
        return view_element_at_< A,R,N::value,B >()( data+0, b.begin() );
    }

    template< class A, class R, bool B >
    bool const view_< A,R,B >::empty() const
    {
        return view_empty_< A,R,N::value,B,1 >()( data+0 );
    }

    template< class A, class R, bool B > template< std::size_t U > 
    typename view_< A,R,B >::size_type const view_< A,R,B >::bound() const
    {
        BOOST_STATIC_ASSERT( U < dimensionality );
        return mpl::at< bounds,mpl::size_t< U > >::type::value;
    }

    template< class A, class R, bool B > template< class A1 > 
    void view_< A,R,B >::to( A1& a )
    {
        BOOST_MPL_ASSERT(( mpl::equal< bounds, typename A1::bounds > ));
        view_to_< A1,A,R,N::value,B,1 >()( a+0, data+0 );
    }

    template< class A, class R, bool B > template< class A1 > 
    void view_< A,R,B >::from( A1 const& a )
    {
        BOOST_MPL_ASSERT(( mpl::equal< bounds, typename A1::bounds > ));
        view_from_< A,A1,R,N::value,B,1 >()( data+0, a+0 );
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::const_iterator view_< A,R,B >::begin() const
    {
        return view_begin_const_< A,R,N::value,B >()( data+0 );
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::iterator view_< A,R,B >::begin()
    {
        return view_begin_< A,R,N::value,B >()( data+0 );
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::const_iterator view_< A,R,B >::end() const
    {
        return begin()+size;
    }

    template< class A, class R, bool B >
    typename view_< A,R,B >::iterator view_< A,R,B >::end()
    {
        return begin()+size;
    }

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_GENERIC_VIEW_HPP_