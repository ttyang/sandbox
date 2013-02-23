// Boost.Tuple
// Unit Test

// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>    // see "Header Implementation Option"

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <boost/tuple/tuple.hpp>

class cm
{
    BOOST_COPYABLE_AND_MOVABLE(cm)
public:
    enum state_type {def_ctor, copy_ctor, move_ctor, copy_assign, move_assign};
    
    cm() : last(def_ctor) {}
    cm(const cm &) : last(copy_ctor) {}
    cm(BOOST_RV_REF(cm)) : last(move_ctor) {}
    cm & operator=(BOOST_COPY_ASSIGN_REF(cm)) { last = copy_assign; return *this; }
    cm & operator=(BOOST_RV_REF(cm)) { last = move_assign; return *this; }

    state_type last_op() { return last; }

private:
    state_type last;
};

template <typename T>
struct foo
{
    T t;
};

int test_main(int, char* [])
{
    using namespace boost;
    using namespace boost::tuples;

    std::pair<cm, int> pi;
    std::pair<cm, float> pf;
    const std::pair<cm, int> cpi;
    const std::pair<cm, float> cpf;
    cons<cm, cons<int, null_type> > ci;
    cons<cm, cons<float, null_type> > cf;
    const cons<cm, cons<int, null_type> > cci;
    const cons<cm, cons<float, null_type> > ccf;
    tuple<cm, int> ti;
    tuple<cm, float> tf;
    const tuple<cm, int> cti;
    const tuple<cm, float> ctf;

    bool pi_move_enabled =
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        !boost::enable_move_utility_emulation< std::pair<cm, int> >::value ||
        boost::has_move_emulation_enabled< std::pair<cm, int> >::value;
#else
        true;
#endif
    bool pf_move_enabled =
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        !boost::enable_move_utility_emulation< std::pair<cm, float> >::value ||
        boost::has_move_emulation_enabled< std::pair<cm, float> >::value;
#else
        true;
#endif

    // tuples::cons( tuples::cons )
    cons<cm, cons<int, null_type> > cc1(ci);
    BOOST_CHECK(get<0>(cc1).last_op() == cm::copy_ctor);
    cons<cm, cons<int, null_type> > cc2(boost::move(ci));
    BOOST_CHECK(get<0>(cc2).last_op() == cm::move_ctor);
    cons<cm, cons<int, null_type> > cc3(cf);
    BOOST_CHECK(get<0>(cc3).last_op() == cm::copy_ctor);
    cons<cm, cons<int, null_type> > cc4(boost::move(cf));
    BOOST_CHECK(get<0>(cc4).last_op() == cm::move_ctor);
    cons<cm, cons<int, null_type> > cc5(cci);
    BOOST_CHECK(get<0>(cc5).last_op() == cm::copy_ctor);
    cons<cm, cons<int, null_type> > cc6(boost::move(cci));
    BOOST_CHECK(get<0>(cc6).last_op() == cm::copy_ctor);
    cons<cm, cons<int, null_type> > cc7(ccf);
    BOOST_CHECK(get<0>(cc7).last_op() == cm::copy_ctor);
    cons<cm, cons<int, null_type> > cc8(boost::move(ccf));
    BOOST_CHECK(get<0>(cc8).last_op() == cm::copy_ctor);

    // tuples::cons = tuples::cons
    ci = ci;
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = boost::move(ci);
    BOOST_CHECK(get<0>(ci).last_op() == cm::move_assign);
    ci = cf;
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = boost::move(cf);
    BOOST_CHECK(get<0>(ci).last_op() == cm::move_assign);
    ci = cci;
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = boost::move(cci);
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = ccf;
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = boost::move(ccf);
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);

    // tuples::cons = std::pair
    ci = pi;
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = boost::move(pi);
    if ( pi_move_enabled )
        BOOST_CHECK(get<0>(ci).last_op() == cm::move_assign);
    else
        BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = pf;
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = boost::move(pf);
    if ( pf_move_enabled )
        BOOST_CHECK(get<0>(ci).last_op() == cm::move_assign);
    else
        BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = cpi;
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = boost::move(cpi);
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = cpf;
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);
    ci = boost::move(cpf);
    BOOST_CHECK(get<0>(ci).last_op() == cm::copy_assign);

    // tuple( tuples::cons )
    tuple<cm, int> tt1(ci);
    BOOST_CHECK(get<0>(tt1).last_op() == cm::copy_ctor);
    tuple<cm, int> tt2(move(ci));
    BOOST_CHECK(get<0>(tt2).last_op() == cm::move_ctor);
    tuple<cm, int> tt3(cf);
    BOOST_CHECK(get<0>(tt3).last_op() == cm::copy_ctor);
    tuple<cm, int> tt4(move(cf));
    BOOST_CHECK(get<0>(tt4).last_op() == cm::move_ctor);
    tuple<cm, int> tt5(cci);
    BOOST_CHECK(get<0>(tt5).last_op() == cm::copy_ctor);
    tuple<cm, int> tt6(move(cci));
    BOOST_CHECK(get<0>(tt6).last_op() == cm::copy_ctor);
    tuple<cm, int> tt7(ccf);
    BOOST_CHECK(get<0>(tt7).last_op() == cm::copy_ctor);
    tuple<cm, int> tt8(move(ccf));
    BOOST_CHECK(get<0>(tt8).last_op() == cm::copy_ctor);

    // tuple( tuple )
    tuple<cm, int> tt9(ti);
    BOOST_CHECK(get<0>(tt9).last_op() == cm::copy_ctor);
    tuple<cm, int> tt10(move(ti));
    BOOST_CHECK(get<0>(tt10).last_op() == cm::move_ctor);
    tuple<cm, int> tt11(tf);
    BOOST_CHECK(get<0>(tt11).last_op() == cm::copy_ctor);
    tuple<cm, int> tt12(move(tf));
    BOOST_CHECK(get<0>(tt12).last_op() == cm::move_ctor);
    tuple<cm, int> tt13(cti);
    BOOST_CHECK(get<0>(tt13).last_op() == cm::copy_ctor);
    tuple<cm, int> tt14(move(cti));
    BOOST_CHECK(get<0>(tt14).last_op() == cm::copy_ctor);
    tuple<cm, int> tt15(ctf);
    BOOST_CHECK(get<0>(tt15).last_op() == cm::copy_ctor);
    tuple<cm, int> tt16(move(ctf));
    BOOST_CHECK(get<0>(tt16).last_op() == cm::copy_ctor);

    // tuple = tuple
    ti = ti;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(ti);
    BOOST_CHECK(get<0>(ti).last_op() == cm::move_assign);
    ti = tf;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(tf);
    BOOST_CHECK(get<0>(ti).last_op() == cm::move_assign);
    ti = cti;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(cti);
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = ctf;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(ctf);
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);

    // tuple = tuples::cons
    ti = ci;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(ci);
    BOOST_CHECK(get<0>(ti).last_op() == cm::move_assign);
    ti = cf;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(cf);
    BOOST_CHECK(get<0>(ti).last_op() == cm::move_assign);
    ti = cci;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(cci);
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = ccf;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(ccf);
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);

    // tuple = std::pair
    ti = pi;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(pi);
    if ( pi_move_enabled )
        BOOST_CHECK(get<0>(ti).last_op() == cm::move_assign);
    else
        BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = pf;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(pf);
    if ( pf_move_enabled )
        BOOST_CHECK(get<0>(ti).last_op() == cm::move_assign);
    else
        BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = cpi;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(cpi);
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = cpf;
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    ti = boost::move(cpf);
    BOOST_CHECK(get<0>(ti).last_op() == cm::copy_assign);
    
    {
        foo< boost::tuple<cm> > a, b;
        a = b;
        BOOST_CHECK(get<0>(a.t).last_op() == cm::copy_assign);
        a = boost::move(b);
//#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
//        BOOST_CHECK(get<0>(a.t).last_op() == cm::copy_assign);
//#else
//        BOOST_CHECK(get<0>(a.t).last_op() == cm::move_assign);
//#endif
        a = foo< boost::tuple<cm> >();
//#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
//        BOOST_CHECK(get<0>(a.t).last_op() == cm::copy_assign);
//#else
//        BOOST_CHECK(get<0>(a.t).last_op() == cm::move_assign);
//#endif
    }
    
    {
        foo< cons<cm, cons<int, null_type> > > a, b;
        cm & cm_ref = boost::tuples::get<0>(a.t);
        a = b;
        BOOST_CHECK(cm_ref.last_op() == cm::copy_assign);
        a = boost::move(b);
//#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
//        BOOST_CHECK(cm_ref.last_op() == cm::copy_assign);
//#else
//        BOOST_CHECK(cm_ref.last_op() == cm::move_assign);
//#endif
        a = foo< cons<cm, cons<int, null_type> > >();
//#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
//        BOOST_CHECK(cm_ref.last_op() == cm::copy_assign);
//#else
//        BOOST_CHECK(cm_ref.last_op() == cm::move_assign);
//#endif
    }

    {
        int dummy_t = 10;
        int dummy_c = 20;

        cons<int, cons<int&, null_type> > cir( cons<int, cons<int&, null_type> >(0, dummy_c) );
        BOOST_CHECK(&boost::tuples::get<1>(cir) == &dummy_c);
        
        tuple<int, int&> tir = tuple<int, int&>(0, dummy_t);
        BOOST_CHECK(&boost::get<1>(tir) == &dummy_t);

        cir = cons<int, cons<int&, null_type> >(0, dummy_c);
        BOOST_CHECK(&boost::tuples::get<1>(cir) == &dummy_c);

        tir = tuple<int, int&>(0, dummy_t);
        BOOST_CHECK(&boost::get<1>(tir) == &dummy_t);

        cir = cir;
        cir = boost::move(cir);
        tir = boost::move(cir);
        BOOST_CHECK(dummy_t = dummy_c);
        tir = boost::move(tir);
        tir = tir;        
    }

    {
        int dummy_t = 10;
        int dummy_c = 20;

        cons<int, cons<int&, null_type> > cir( cons<float, cons<int&, null_type> >(0.0f, dummy_c) );
        BOOST_CHECK(&boost::tuples::get<1>(cir) == &dummy_c);

        tuple<int, int&> tir = tuple<float, int&>(0.0f, dummy_t);
        BOOST_CHECK(&boost::get<1>(tir) == &dummy_t);

        cir = cons<float, cons<int&, null_type> >(0.0f, dummy_c);
        BOOST_CHECK(&boost::tuples::get<1>(cir) == &dummy_c);

        tir = tuple<float, int&>(0.0f, dummy_t);
        BOOST_CHECK(&boost::get<1>(tir) == &dummy_t);

        cons<float, cons<int&, null_type> > cir2(0.0f, dummy_c);
        tuple<float, int&> tir2(0.0f, dummy_t);
        cir = cir2;
        cir = boost::move(cir2);
        tir = boost::move(cir2);
        BOOST_CHECK(dummy_t == dummy_c);
        tir = boost::move(tir2);
        tir = tir2;
    }

    {
        int dummy_t = 10;
        int dummy_c = 20;

        cons<int&, cons<int, null_type> > cir( cons<int&, cons<float, null_type> >(dummy_c, 0.0f) );
        BOOST_CHECK(&boost::tuples::get<0>(cir) == &dummy_c);

        tuple<int&, int> tir = tuple<int&, float>(dummy_t, 0.0f);
        BOOST_CHECK(&boost::get<0>(tir) == &dummy_t);

        cir = cons<int&, cons<float, null_type> >(dummy_c, 0.0f);
        BOOST_CHECK(&boost::tuples::get<0>(cir) == &dummy_c);

        tir = tuple<int&, float>(dummy_t, 0.0f);
        BOOST_CHECK(&boost::get<0>(tir) == &dummy_t);

        cons<int&, cons<float, null_type> > cir2(dummy_c, 0.0f);
        tuple<int&, float> tir2(dummy_t, 0.0f);
        cir = cir2;
        cir = boost::move(cir2);
        tir = boost::move(cir2);
        BOOST_CHECK(dummy_t == dummy_c);
        tir = boost::move(tir2);
        tir = tir2;
    }

    return 0;
}

#else // #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

int test_main(int, char* [])
{
    return 0;
}

#endif // #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
