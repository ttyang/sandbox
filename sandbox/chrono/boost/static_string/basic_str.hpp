//  basic_str.hpp  --------------------------------------------------------------//

//  Copyright 2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


#ifndef BOOST_STATIC_STRING_BASIC_STR_HPP
#define BOOST_STATIC_STRING_BASIC_STR_HPP

#include <boost/mpl/vector/vector10_c.hpp>

namespace boost {
namespace static_string {

struct nil {};

template <char H1>
struct str_1 {
    typedef mpl::vector1_c<char, H1> type;
};

template <char H1, char H2>
struct str_2 {
    typedef mpl::vector2_c<char, H1, H2> type;
};

template <char H1, char H2, char H3>
struct str_3 {
    typedef mpl::vector3_c<char, H1, H2, H3> type;
};

template <char H1, char H2, char H3, char H4>
struct str_4 {
    typedef mpl::vector4_c<char, H1, H2, H3, H4> type;
};

template <char H1, char H2, char H3, char H4, char H5>
struct str_5 {
    typedef mpl::vector5_c<char, H1, H2, H3, H4, H5> type;
};

} // namespace static_string
} // namespace boost

#endif // BOOST_STATIC_STRING_BASIC_STR_HPP
