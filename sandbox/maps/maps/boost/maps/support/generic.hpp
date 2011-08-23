//--
// Copyright (c) 2010-2011 Brian Smith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/maps for documentation.
//--
#if !defined( BOOST_MAPS_SUPPORT_GENERIC_HPP )
#define BOOST_MAPS_SUPPORT_GENERIC_HPP

#include <boost/maps/support/preprocessor_bounds.hpp>

#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/type_traits/is_pod.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/modulus.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/assert.hpp>

namespace boost { namespace maps {

//--

    namespace null { 

    struct allocator 
    {
        template< class T >
        struct rebind { typedef allocator other; };

        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
    };

    } // namespace null

//--

    template< class T, std::size_t N >
    struct pointer_type
    {
        typedef typename pointer_type<
            typename add_pointer< T >::type,N-1
                >::type type;
    };

    template< class T >
    struct pointer_type< T,0 >
    {
        typedef T type;
    };

//--
//--

    namespace detail {

    template< class T, std::size_t N, class I >
    struct array_type
    {
        typedef typename array_type< 
            T,N-1,typename mpl::next< I >::type
                >::type type[ mpl::deref< I >::type::value ];
    };

    template< class T, class I >
    struct array_type< T,0,I >
    {
        typedef T type;
    };

//--

    template< class T, std::size_t N, class I >
    struct array_transverse_type
    {
        typedef typename array_transverse_type< 
            T[ mpl::deref< I >::type::value ],N-1,typename mpl::next< I >::type
                >::type type;
    };

    template< class T, class I >
    struct array_transverse_type< T,0,I >
    {
        typedef T type;
    };

//--

    template< std::size_t N, class I >
    struct array_size
    {
        typedef mpl::size_t< 
            mpl::deref< I >::type::value * 
                array_size< N-1,typename mpl::next< I >::type >::type::value 
                    > type;
    };

    template< class I >
    struct array_size< 1,I >
    {
        typedef mpl::size_t< 
            mpl::deref< I >::type::value 
                > type;
    };

    } // namespace detail

//--
//--

    template< class T, std::size_t N, class B, class A >
    struct array_type
    {
        typedef typename pointer_type< T,N >::type type;
    };

    template< class T, std::size_t N, class B >
    struct array_type< T,N,B,null::allocator >
    {
        typedef typename detail::array_type< T,N,B >::type type;
    };

//--

    template< class T, class B, class A >
    struct array_member_type
    {
        typedef typename array_type< 
            T,mpl::size< B >::type::value,typename mpl::begin< B >::type,A 
                >::type type;
    };

//--

    template< class T, class B, class A >
    struct array_value_type
    {
        typedef typename array_type< 
            T,mpl::size< B >::type::value-1,typename mpl::next< typename mpl::begin< B >::type >::type,A 
                >::type type;
    };

//--

    template< class B >
    struct array_size
    {
        typedef typename detail::array_size< 
            mpl::size< B >::type::value,typename mpl::begin< B >::type 
                >::type type;
    };

//--

    template< class T, bool I, class A >
    struct array_initialize
    {
        typedef typename mpl::or_< 
            mpl::not_< has_trivial_constructor< T > >,mpl::bool_< I > 
                >::type type;
    };

    template< class T, bool I >
    struct array_initialize< T,I,null::allocator >
    {
        typedef typename mpl::if_<  
            has_trivial_constructor< T >,mpl::bool_< I >,mpl::bool_< false >
                >::type type;
    };

//--
//--

    namespace detail {

    template< class T, std::size_t N, std::size_t D >
    struct array_type_
    {
        typedef typename array_type_< 
            T[D],N-1,D 
                >::type type;
    };

    template< class T, std::size_t D >
    struct array_type_< T,0,D >
    {
        typedef T type;
    };

//--

    template< std::size_t N, std::size_t D >
    struct array_size_
    {
        typedef mpl::size_t< 
            D * array_size_< N-1,D >::type::value
                > type;
    };

    template< std::size_t D >
    struct array_size_< 1, D >
    {
        typedef mpl::size_t< D > type;
    };

//--

    template< class B, std::size_t N, std::size_t D >
    struct array_bounds_
    {
        typedef typename array_bounds_< 
            typename mpl::push_back< B,mpl::integral_c< std::size_t,D > >::type,N-1,D 
                >::type type;
    };

    template< class B, std::size_t D >
    struct array_bounds_< B,0,D >
    {
        typedef B type;
    };

    } // namespace detail

//--

    template< class T, std::size_t N, std::size_t D, class A >
    struct array_type_
    {
        typedef typename pointer_type< T,N >::type type;
    };

    template< class T, std::size_t N, std::size_t D >
    struct array_type_< T,N,D,null::allocator >
    {
        typedef typename detail::array_type_< T,N,D >::type type;
    };

//--

    template< class T, std::size_t N, std::size_t D, class A >
    struct array_member_type_
    {
        typedef typename array_type_< T,N,D,A >::type type;
    };

//--

    template< class T, std::size_t N, std::size_t D, class A >
    struct array_value_type_
    {
        typedef typename array_type_< T,N-1,D,A >::type type;
    };

//--

    template< std::size_t N, std::size_t D >
    struct array_size_
    {
        typedef typename detail::array_size_< N,D >::type type;
    };

//--

    template< std::size_t N, std::size_t D >
    struct array_bounds_
    {
        typedef typename detail::array_bounds_< 
            mpl::vector0<>,N,D 
                >::type type;
    };

//--
//--

    template< class T, std::size_t N, bool I = false, class A = std::allocator< T > > class pointer;
    template< class T, class B, bool I = true, class A = null::allocator > class array;
    template< class T, std::size_t N, std::size_t D, bool I = true, class A = null::allocator > class array_;

//--

    template< class A >
    struct sub_type
    {};

//--
//--

// views

    template< std::size_t F, std::size_t L, std::size_t S = 1 >
    struct range
        : bounds3< F,L,S >
    {};

    template< std::size_t F, std::size_t L >
    struct range< F,L,0 >
        : bounds0
    {};

    template< std::size_t F, std::size_t S >
    struct range< F,F,S >
        : bounds0
    {};

//--
//--

// view_

    template< class R >
    class view_range
    {
        typedef typename mpl::deref< R >::type D;
        typedef typename mpl::begin< D >::type R1;
        typedef typename mpl::next< R1 >::type R2;
        typedef typename mpl::next< R2 >::type R3;

    public:

        typedef mpl::integral_c< std::size_t,mpl::deref< R1 >::type::value > first;
        typedef mpl::integral_c< std::size_t,mpl::deref< R2 >::type::value > last;
        typedef mpl::integral_c< std::size_t,mpl::deref< R3 >::type::value > step;

        typedef typename mpl::minus< last,first >::type range;
        typedef typename mpl::minus< last,step >::type last_index;

        typedef typename mpl::eval_if< 
            mpl::equal_to< mpl::modulus< range,step >,mpl::size_t< 0 > >, 
            mpl::integral_c< std::size_t,mpl::divides< range,step >::value >, 
            mpl::integral_c< std::size_t,0 >
        >::type bound;

    };

//--

    template< class B, class I, class E, bool S >
    struct view_validate_
    {
        typedef typename mpl::and_< 
            typename mpl::less_equal< 
                typename view_range< I >::bound, 
                typename mpl::front< B >::type
            >::type,
            typename mpl::less< 
                typename view_range< I >::last_index, 
                typename mpl::front< B >::type
            >::type,
            typename mpl::less< 
                typename view_range< I >::first, 
                typename view_range< I >::last
            >::type,
            typename view_validate_< 
                typename mpl::pop_front< B >::type, 
                typename mpl::next< I >::type, 
                E,
                S
            >::type
        >::type type;
    };

    template< class B, class E, bool S >
    struct view_validate_< B,E,E,S >
    {
        typedef mpl::bool_< true > type;
    };

    template< class B, class I, class E >
    struct view_validate_< B,I,E,false >
    {
        typedef mpl::bool_< false > type;
    };

    template< class A, class R >
    struct view_valid
    {
        typedef typename view_validate_< 
            typename A::limits_type,
            typename mpl::begin< R >::type,
            typename mpl::end< R >::type,
            mpl::equal< mpl::size< typename A::limits_type >,mpl::size< R > >::type::value 
        >::type type;
    };

//--
    
    namespace detail {

    template< class B, class I, class E >
    struct view_bounds
    {
        typedef typename view_bounds< 
            typename mpl::push_back< 
                B, 
                typename view_range< typename mpl::deref< I >::type >::bound 
            >::type, 
            typename mpl::next< I >::type, 
            E 
        >::type type;
    };

    template< class B, class E >
    struct view_bounds< B,E,E >
    {
        typedef B type;
    };
    
    } // namespace detail

    template< class B, class R >
    struct view_bounds
    {
        typedef typename detail::view_bounds< 
            B,typename mpl::begin< R >::type,typename mpl::end< R >::type
                >::type type;
    };

//--

    template< std::size_t N, class R >
    struct view_ranges
    {
        typedef R type;
    };

    template< class R >
    struct view_ranges< 1,R >
    {
        typedef mpl::vector1< typename mpl::front< R >::type > type;
    };

//--

    namespace detail {

    template< class R, class B, class E >
    struct view_size
    {
        typedef typename mpl::size_t< 
            view_range< typename mpl::front< R >::type >::bound::value * 
                view_size< typename mpl::pop_front< R >::type,typename mpl::next< B >::type,E >::type::value 
                    >::type type;
    };

    template< class R, class E >
    struct view_size< R,E,E >
    {
        typedef mpl::size_t< 1 > type;
    };
    
    } // namespace detail

    template< class R >
    struct view_size
    {
        typedef typename detail::view_size< 
            R,typename mpl::begin< R >::type,typename mpl::end< R >::type 
                >::type type;
    };

//--

    template< class A, class R, bool P > struct view_traits_base_ {};
    template< class A, class R, bool P > struct view_traits_ {};

//--

    template< class T, class B, bool I, class A, class R, bool P >
    struct view_traits_base_< array< T,B,I,A >,R,P >
    {
        typedef typename view_bounds< mpl::vector0<>,R >::type bounds;
        typedef array< T*,bounds,false,A > array_type;
    };

    template< class T, class B, bool I, class A, class R >
    struct view_traits_base_< array< T,B,I,A >,R,false >
    {
        typedef typename view_bounds< mpl::vector0<>,R >::type bounds;
        typedef array< T,bounds,false,A > array_type;
    };

//--

    template< class T, class B, bool I, class A, class R, bool P >
    struct view_traits_< array< T,B,I,A >,R,P >
        : view_traits_base_< array< T,B,I,A >,R,P >
    {
        typedef view_traits_base_< array< T,B,I,A >,R,P > base_type;
        typedef typename base_type::array_type::member_type member_type;
        typedef typename base_type::array_type::value_type value_type;
        typedef typename base_type::array_type::const_reference_type const_reference_type;
        typedef typename base_type::array_type::reference_type reference_type;
        typedef typename base_type::array_type::const_iterator_type const_iterator_type;
        typedef typename base_type::array_type::iterator_type iterator_type;
        typedef typename base_type::array_type::element_type element_type;
        typedef typename base_type::array_type::const_iterator const_iterator;
        typedef typename base_type::array_type::iterator iterator;
        typedef typename base_type::array_type::const_reference const_reference;
        typedef typename base_type::array_type::reference reference;
        typedef typename base_type::array_type::allocator_type allocator_type;
        typedef typename base_type::array_type::size_type size_type;
        typedef typename base_type::array_type::difference_type difference_type;
        typedef typename base_type::array_type::bounds_type bounds_type;
        typedef typename base_type::array_type::bounds_const_reference bounds_const_reference;
        typedef typename base_type::bounds bounds;
        typedef typename view_ranges< base_type::array_type::dimensionality,R >::type ranges;

    };

//--

    template< class T, std::size_t N, std::size_t D, bool I, class A, class R, bool P >
    struct view_traits_< array_< T,N,D,I,A >,R,P >
        : view_traits_< array< T,typename array_bounds_< N,D >::type,I,A >,R,P >
    {};

//--

    template< class A, class R, bool B = true > class view_;

//--
//--

// view

    template< class T, class A > 
    struct view_allocator_type
    {
        typedef typename A::template rebind< T >::other type;
    };

    template< class T > 
    struct view_allocator_type< T,null::allocator >
    {
        typedef std::allocator< T > type;
    };

//--

    template< class P, bool B > 
    struct view_traits_base 
    {
        typedef typename P::element_type* T;
        typedef typename view_allocator_type< T,typename P::allocator_type >::type A;
        typedef pointer< T,P::dimensionality,P::initialize::value,A > pointer_type;
    };

    template< class P > 
    struct view_traits_base< P,false > 
    {
        typedef typename P::element_type T;
        typedef typename view_allocator_type< T,typename P::allocator_type >::type A;
        typedef pointer< T,P::dimensionality,P::initialize::value,A > pointer_type;
    };

//--

    template< class P, bool B >
    struct view_traits
        : view_traits_base< P,B >
    {
        typedef view_traits_base< P,B > base_type;
        typedef typename base_type::pointer_type::member_type member_type;
        typedef typename base_type::pointer_type::value_type value_type;
        typedef typename base_type::pointer_type::const_reference_type const_reference_type;
        typedef typename base_type::pointer_type::reference_type reference_type;
        typedef typename base_type::pointer_type::const_iterator_type const_iterator_type;
        typedef typename base_type::pointer_type::iterator_type iterator_type;
        typedef typename base_type::pointer_type::element_type element_type;
        typedef typename base_type::pointer_type::const_iterator const_iterator;
        typedef typename base_type::pointer_type::iterator iterator;
        typedef typename base_type::pointer_type::const_reference const_reference;
        typedef typename base_type::pointer_type::reference reference;
        typedef typename base_type::pointer_type::allocator_type allocator_type;
        typedef typename base_type::pointer_type::size_type size_type;
        typedef typename base_type::pointer_type::difference_type difference_type;
        typedef typename base_type::pointer_type::bounds_type bounds_type;
        typedef typename base_type::pointer_type::bounds_const_reference bounds_const_reference;
        typedef typename P::limits_type limits_type;
        typedef array< std::size_t, bounds2< P::dimensionality,3 > > ranges;
        typedef ranges const& ranges_const_reference;

    };

//--

    template< class P, bool B = true > class view;

//--

}} // namespace boost, namespace maps

#endif // BOOST_MAPS_SUPPORT_GENERIC_HPP
