// Copyright Stjepan Rajko 2007. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "my_producer_consumer.hpp"
#include "my_producer_consumer_operations.hpp"

#include <boost/dataflow/support/component_operation.hpp>
#include <boost/dataflow/support/fusion_component.hpp>
#include <boost/mpl/map.hpp>

#include <boost/test/included/test_exec_monitor.hpp>

using namespace boost;

namespace df=boost::dataflow;

bool invoked = false;

struct my_component_traits : public boost::dataflow::fusion_component_traits<
    boost::fusion::vector<
        my_producer &,
        my_consumer &
    >,
    mpl::map<
        mpl::pair<
            df::default_port_selector<df::args::left>,
            mpl::int_<0> >,
        mpl::pair<
            df::default_port_selector<dataflow::args::right>,
            mpl::int_<1> >
    >
>
{
    template<typename Component>
    static typename my_component_traits::fusion_ports get_ports(Component &c)
    {
        return typename my_component_traits::fusion_ports(c.p, c.c);
    }
};

struct my_component : public boost::dataflow::component<my_component_traits>
{
    my_producer p;
    my_consumer c;
};

namespace boost { namespace dataflow { namespace extension {

template<>
struct component_operation_impl<my_component_traits, operations::invoke>
{
    typedef void result_type;
    
    template<typename Component>
    void operator()(Component &)
    {
        invoked = true;
    }
};

}}}

namespace df = boost::dataflow;

int test_main(int, char* [])
{
    my_component c;
    
    invoke(c);
    BOOST_CHECK(invoked);
    
    BOOST_CHECK_EQUAL((&df::get_port<boost::mpl::int_<0> >(c)), &c.p);
    BOOST_CHECK_EQUAL((&df::get_port<boost::mpl::int_<1> >(c)), &c.c);
    BOOST_CHECK_EQUAL((&df::get_port_c<0>(c)), &c.p);
    BOOST_CHECK_EQUAL((&df::get_port_c<1>(c)), &c.c);

    my_component c2;
    
    df::binary_operation<df::operations::connect, df::default_mechanism, df::default_tag>(c, c2);
    BOOST_CHECK(connected);
    
    return 0;
} // int test_main(int, char* [])

