/*=================================---------------------------------------------
    Copyright 2007,2008 Stjepan Rajko
  
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/

#ifndef BOOST__DATAFLOW__TEST__GENERIC__MY_STATIC_VECTOR_HPP
#define BOOST__DATAFLOW__TEST__GENERIC__MY_STATIC_VECTOR_HPP


#include <boost/dataflow/generic/static_vector.hpp>
#include "my_framework.hpp"
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/at.hpp>

typedef df::static_vector_traits<boost::fusion::vector2<float, int>, my_framework> my_traits;

namespace df=boost::dataflow;

struct my_static_vector
{
    my_static_vector(float f, int i)
        : ports(f,i) {}
    
    typedef my_traits dataflow_traits;
    boost::fusion::vector2<float, int> ports;
};

namespace boost { namespace dataflow { namespace extension {

template<>
struct entities_impl<my_traits>
{
    typedef boost::fusion::vector2<float, int> & result_type;
    
    template<typename Entity>
    result_type operator()(Entity &e)
    {
        return e.ports;
    }
};

}}}

#endif