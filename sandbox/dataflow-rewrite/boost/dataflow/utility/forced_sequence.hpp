/*=================================---------------------------------------------
    Copyright 2007,2008 Stjepan Rajko
  
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/


#ifndef BOOST__DATAFLOW__UTILITY__FORCED_AS_SEQUENCE_HPP
#define BOOST__DATAFLOW__UTILITY__FORCED_AS_SEQUENCE_HPP


#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace dataflow {

namespace utility {

template<typename T, typename Enable=void>
struct forced_sequence
{
    typedef mpl::vector<T> type;
};

template<typename T>
struct forced_sequence<T, typename enable_if<mpl::is_sequence<T> >::type >
{
    typedef T type;
};

template<>
struct forced_sequence<void>
{
    typedef mpl::vector<> type;
};

}

} }

#endif // BOOST__DATAFLOW__UTILITY__FORCED_AS_SEQUENCE_HPP
