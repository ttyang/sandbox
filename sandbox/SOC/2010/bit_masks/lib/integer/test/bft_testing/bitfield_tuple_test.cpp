//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/integer/bitfield_tuple.hpp>
// #include "../test_type_list.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/begin.hpp>
using namespace boost;
using namespace boost::bitfields;



struct red { };
struct green { };
struct blue { };



int main() {
    // testing bitfield_element
    {
        // bitfield_element
        typedef bitfields::detail::bitfield_element<
            int, red, mpl::size_t<5>, mpl::size_t<4>
        > bft_element_test_1;
        BOOST_TEST(( is_same<bft_element_test_1::return_type, int>::value ));
        BOOST_TEST(( is_same<bft_element_test_1::name_type, red>::value ));
        BOOST_TEST(( bft_element_test_1::offset::value == 5 ));
        BOOST_TEST(( bft_element_test_1::field_width::value == 4 ));

    }

    // bitfield_tuple runtime tests.
    // additional tests preformed in the bft_testing folder.
    {
        // default constructor.
        typedef bitfield_tuple< storage<int>, member<int,red,3> > bft1;
        bft1 bft_test_1;
        BOOST_TEST(( bft_test_1.data() == 0 ));

        // value constructor
        bft1 bft_test_2(5);
        BOOST_TEST(( bft_test_2.data() == 5 ));

    }
    return boost::report_errors();
}
