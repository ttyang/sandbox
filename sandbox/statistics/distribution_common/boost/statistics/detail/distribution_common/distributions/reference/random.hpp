/////////////////////////////////////////////////////////////////////////////////
// distribution::common::distributions::reference::random.hpp                  //
//                                                                             //
//  (C) Copyright 2009 Erwann Rogard                                           //
//  Use, modification and distribution are subject to the                      //
//  Boost Software License, Version 1.0. (See accompanying file                //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)           //
/////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_COMMON_DISTRIBUTIONS_REFERENCE_RANDOM_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_COMMON_DISTRIBUTIONS_REFERENCE_RANDOM_HPP_ER_2009
#include <boost/math/distributions/exponential.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/statistics/detail/distribution_common/meta/random/distribution.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace meta{

    template<typename D>
    struct random_distribution< reference_wrapper<D> >
    {
        typedef typename reference_wrapper<D>::distribution_type dist_;
        typedef random_distribution<dist_> inner_; 
        typedef typename inner_::type type;
        
        static type call(const reference_wrapper<D>& d){ 
        	return inner_::call(d.distribution());
        }
    };
    
}// meta
}// distribution
}// detail
}// statistics
}// boost

#endif