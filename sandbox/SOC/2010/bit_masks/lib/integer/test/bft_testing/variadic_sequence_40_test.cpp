//  Copyright 2010 Brian Bartman.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)


#define BOOST_BFT_PARAM_COUNT 40
#include <boost/integer/bitfield_tuple.hpp>
#include <boost/detail/lightweight_test.hpp>


using namespace boost;
using namespace boost::bitfields;

struct red;
struct green;
struct pink;
struct blue;
struct salmon;

typedef bitfield_tuple<
    member<char,red,4>,
    member<unsigned char, green,5>,
    storage<std::size_t>,
    member<int, salmon, 16>,
    flag<blue>
>                                       test_tuple;

int main() {
    test_tuple temp;

    temp.get<blue>() = false;
    BOOST_TEST(( temp.get<blue>() == false ));
    return boost::report_errors();
}
