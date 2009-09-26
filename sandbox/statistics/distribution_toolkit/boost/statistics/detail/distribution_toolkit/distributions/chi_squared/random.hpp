/////////////////////////////////////////////////////////////////////////////////
// distribution_toolkit::distributions::chi_squared::random.hpp                //
//                                                                             //
//  (C) Copyright 2009 Erwann Rogard                                           //
//  Use, modification and distribution are subject to the                      //
//  Boost Software License, Version 1.0. (See accompanying file                //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)           //
/////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_TOOLKIT_DISTRIBUTIONS_CHI_SQUARED_RANDOM_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_TOOLKIT_DISTRIBUTIONS_CHI_SQUARED_RANDOM_HPP_ER_2009
#include <boost/math/distributions/chi_squared.hpp>
#include <boost/random/chi_squared.hpp>
#include <boost/statistics/detail/distribution_toolkit/meta/random.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution_toolkit{
namespace meta{

    template<typename T,typename P>
    struct random< 
        boost::math::chi_squared_distribution<T,P> 
    >{
        typedef math::chi_squared_distribution<T> dist_;
        typedef boost::random::chi_squared_distribution<T> type;
        
        static type make(const dist_& d){ 
            return type(d.degrees_of_freedom()); 
        }
    };
    
}// meta
}// distribution_toolkit
}// detail
}// statistics
}// boost

#endif
