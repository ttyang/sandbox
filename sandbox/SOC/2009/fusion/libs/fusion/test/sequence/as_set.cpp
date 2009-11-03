/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/container/generation/make_list.hpp>
#include <boost/fusion/container/set/convert.hpp>
#include <boost/fusion/container/list/convert.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/sequence/io/out.hpp>
#include <boost/mpl/vector_c.hpp>

int
main()
{
    using namespace boost::fusion;

    std::cout << tuple_open('[');
    std::cout << tuple_close(']');
    std::cout << tuple_delimiter(", ");

    {
        vector<> empty;
        std::cout << as_set(make_list(1, 1.23, "harru")) << std::endl;
        std::cout << as_set(push_back(empty, 999)) << std::endl;
        
        BOOST_TEST(as_list(as_set(make_list(1, 1.23, "harru")))
            == make_list(1, 1.23, std::string("harru")));
        BOOST_TEST(as_list(as_set(push_back(empty, 999)))
            == push_back(empty, 999));
    }

    {
        result_of::as_set<list<int, double, std::string> >::type set(1, 1.23, "harru");
        std::cout << at_key<int>(set) << std::endl;
        BOOST_TEST(at_key<int>(set) == 1);
    }

    {
        std::cout << as_set(boost::mpl::vector_c<int, 1, 2, 3, 4, 5>()) << std::endl;
        BOOST_TEST((as_list(as_set(boost::mpl::vector_c<int, 1, 2, 3, 4, 5>()))
            == boost::mpl::vector_c<int, 1, 2, 3, 4, 5>()));
    }

    {
        // test conversion
        set<int, std::string> s(make_vector(123, "harru"));
        BOOST_TEST(as_vector(s) == make_vector(123, "harru"));
        s = (make_vector(235, "hola")); // test assign
        BOOST_TEST(as_vector(s) == make_vector(235, "hola"));
    }

    return boost::report_errors();
}

