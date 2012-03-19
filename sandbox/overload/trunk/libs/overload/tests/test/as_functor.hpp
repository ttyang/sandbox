
#ifndef _TEST_AS_FUNCTOR_HPP_
#define _TEST_AS_FUNCTOR_HPP_


void as_functor_test()
{
    typedef boost::overload<sig1_t, sig2_t, sig3_t> polymorfic1_t;
    typedef boost::overload<sig0_t, sig5_t, sig3_t, sig4_t> polymorfic2_t;
    typedef boost::overload<sig0_t, sig2_t, sig3_t, sig4_t> polymorfic3_t;
    typedef boost::overload<sig0_t, sig5_t, sig4_t> polymorfic4_t;


    BOOST_STATIC_ASSERT((
            is_same< ovdtl::get_function_tag<polymorfic1_t>::type,
                     ovdtl::function_obj_tag
            >::value
    ));

    BOOST_STATIC_ASSERT((
            ovdtl::functor_has_signature<polymorfic1_t, sig2_t>::value ));

    BOOST_STATIC_ASSERT((
            ovdtl::number_of_shared_signatures<polymorfic1_t, polymorfic2_t>
                    ::value == 1 ));

    BOOST_STATIC_ASSERT((
            ovdtl::have_any_shared_signature<polymorfic1_t, polymorfic2_t>::value ));

    BOOST_STATIC_ASSERT((
            ovdtl::number_of_shared_signatures<polymorfic1_t, polymorfic3_t>
                    ::value == 2 ));

    BOOST_STATIC_ASSERT((
            ovdtl::have_any_shared_signature<polymorfic1_t, polymorfic3_t>::value ));

    BOOST_STATIC_ASSERT((
            ovdtl::number_of_shared_signatures<polymorfic1_t, polymorfic4_t>
                    ::value == 0 ));

    BOOST_STATIC_ASSERT((
            !ovdtl::have_any_shared_signature<polymorfic1_t, polymorfic4_t>::value ));

    BOOST_STATIC_ASSERT((
            ovdtl::number_of_shared_signatures<polymorfic3_t, polymorfic4_t>
                    ::value == 2 ));

    BOOST_STATIC_ASSERT((
            ovdtl::have_any_shared_signature<polymorfic3_t, polymorfic4_t>::value ));


    polymorfic1_t f;
    f.set( &bar1::foo1 );
    f.set( &bar2::foo2 );
    f.set( &foo3 );
    BOOST_ASSERT( f("hello") == 'Y' );

    polymorfic2_t g;
    g.set( f );
    BOOST_ASSERT( g("hello") == 'Y' );
    BOOST_ASSERT( g.empty<0>() );
    BOOST_ASSERT( g.empty<1>() );
    BOOST_ASSERT( g.empty<3>() );

    polymorfic3_t h;
    h.set<sig2_t>( f );
    h.set<sig3_t>( f );
    BOOST_ASSERT( h.empty<0>() );
    BOOST_ASSERT( !h.empty<1>() );
    BOOST_ASSERT( !h.empty<2>() );
    BOOST_ASSERT( h.empty<3>() );
    BOOST_ASSERT( h("hello") == 'Y' );

    h.clear_all();
    BOOST_ASSERT( h.empty_all() );
    h.set<1>( f );
    h.set<2>( f );
    BOOST_ASSERT( h.empty<0>() );
    BOOST_ASSERT( !h.empty<1>() );
    BOOST_ASSERT( !h.empty<2>() );
    BOOST_ASSERT( h.empty<3>() );
    BOOST_ASSERT( h("hello") == 'Y' );


    // MSVC 7.1 doesn't succeed in deducing the signature of a multi-signature
    // function object
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    polymorfic3_t p;
    p.set_for_each_shared_signature( f );
    BOOST_ASSERT( p.empty<0>() );
    BOOST_ASSERT( !p.empty<1>() );
    BOOST_ASSERT( !p.empty<2>() );
    BOOST_ASSERT( p.empty<3>() );
    BOOST_ASSERT( p("hello") == 'Y' );
#endif

}




#endif /* _TEST_AS_FUNCTOR_HPP_ */
