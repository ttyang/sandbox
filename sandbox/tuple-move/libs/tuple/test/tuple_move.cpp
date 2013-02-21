// Boost.Tuple
// Unit Test

// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/impl/execution_monitor.ipp>

#include <boost/tuple/tuple.hpp>

class cm
{
    BOOST_COPYABLE_AND_MOVABLE(cm)
public:
    enum state_type {def_ctor, copy_ctor, move_ctor, copy_assign, move_assign};
    
    cm() : last(def_ctor) {}
    cm(const cm & o) : last(copy_ctor) {}
    cm(BOOST_RV_REF(cm) o) : last(move_ctor) {}
    cm & operator=(BOOST_COPY_ASSIGN_REF(cm) o) { last = copy_assign; return *this; }
    cm & operator=(BOOST_RV_REF(cm) o) { last = move_assign; return *this; }

    state_type last_op() { return last; }

private:
    state_type last;
};

int test_main(int, char* [])
{
    using namespace boost;
    using namespace boost::tuples;

    cons<cm, cons<int, null_type> > ci;
    cons<cm, cons<float, null_type> > cf;
    const cons<cm, cons<int, null_type> > cci;
    const cons<cm, cons<float, null_type> > ccf;

    // tuples::cons ctor
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

    // tuples::cons assignment
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

    // tuple ctor taking tuples::cons
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

    tuple<cm, int> ti;
    tuple<cm, float> tf;
    const tuple<cm, int> cti;
    const tuple<cm, float> ctf;

    // tuple ctor taking tuple
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

    return 0;
}
