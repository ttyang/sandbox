//////////////////////////////////////////////////////////////////////////////////
// distribution_toolkit::fwd_math::mean.hpp                                     //
//                                                                              //
//  (C) Copyright 2009 Erwann Rogard                                            //
//  Use, modification and distribution are subject to the                       //
//  Boost Software License, Version 1.0. (See accompanying file                 //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_DISTRIBUTION_TOOLKIT_DISTRIBUTIONS_FWD_MATH_MEAN_HPP_ER_2009
#define BOOST_DISTRIBUTION_TOOLKIT_DISTRIBUTIONS_FWD_MATH_MEAN_HPP_ER_2009
#include <boost/utility/enable_if.hpp>
#include <boost/statistics/detail/distribution_toolkit/meta/is_math_distribution.hpp>
#include <boost/statistics/detail/distribution_toolkit/meta/value.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution_toolkit{
    
    template<typename D>
    typename lazy_enable_if<
        meta::is_math_distribution<D>,
        meta::value<D>
    >::type
    mean(const D& dist)
    {        
        return boost::math::mean(dist);
    }


}// distribution_toolkit
}// detail
}// statistics
}// boost 


#endif