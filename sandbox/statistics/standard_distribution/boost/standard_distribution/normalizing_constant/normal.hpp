//////////////////////////////////////////////////////////////////////////////
// standard_distribution::normalizing_cosntant::normal.hpp                  //
//                                                                          //
//  (C) Copyright 2009 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STANDARD_DISTRIBUTION_NORMALIZING_CONSTANT_NORMAL_HPP_ER_2009
#define BOOST_STANDARD_DISTRIBUTION_NORMALIZING_CONSTANT_NORMAL_HPP_ER_2009
#include <cmath>
#include <boost/math/constants/constants.hpp>

namespace boost{
namespace math{

template<typename T,typename P>
T normalizing_constant(const normal_distribution<T,P>& d){
    static T pi = boost::math::constants::pi<T>;
    static T two = static_cast<T>(2);
    return sqrt(two * pi) * d.scale();
}

}// math
}// boost

#endif