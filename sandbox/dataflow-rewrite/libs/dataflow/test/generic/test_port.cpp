// Copyright Stjepan Rajko 2007, 2008. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/dataflow/generic/port/port.hpp>

#include <boost/dataflow/generic/framework_entity.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

namespace df=boost::dataflow;

struct my_framework : public df::framework_base
{};

struct my_port : public df::port<df::port_traits<df::ports::producer, my_framework> >
{};

struct my_entity : public df::framework_entity<df::traits<my_framework> >
{};

struct not_entity;

BOOST_AUTO_TEST_CASE( test ) 
{
    BOOST_CHECK((df::is_port<my_port>::value));
    BOOST_CHECK((!df::is_port<my_entity>::value));
    BOOST_CHECK((!df::is_port<not_entity>::value));
}