// Copyright Stjepan Rajko 2007. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/dataflow/signals/support.hpp>

#include <boost/test/included/test_exec_monitor.hpp>

//[ test_connect

struct receiver
    : public boost::dataflow::port<boost::dataflow::signals::call_consumer<> >    
{
    receiver() : stored(0) {}
    
    void operator()(int x)
    {
        stored = x;
    }
    
    int stored;
};

int stored = 0;

void f_receiver(int x)
{
    stored = x;
};

int test_main(int, char* [])
{
    namespace df = boost::dataflow;
    
    boost::signal<void(int)> p;
    receiver r;

    connect(p, boost::function<void(int)>(f_receiver));
    connect(p, r);

    p(3);
    BOOST_CHECK_EQUAL(stored, 3);
    BOOST_CHECK_EQUAL(r.stored, 3);

    return 0;
}

//]