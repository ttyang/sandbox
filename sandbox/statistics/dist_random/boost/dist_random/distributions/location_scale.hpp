//////////////////////////////////////////////////////////////////////////////
// dist_random::distributions::location_scale.hpp                           //
//                                                                          //
//  (C) Copyright 2009 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_DIST_RANDOM_DISTRIBUTIONS_LOCATION_SCALE_HPP_ER_2009
#define BOOST_DIST_RANDOM_DISTRIBUTIONS_LOCATION_SCALE_HPP_ER_2009
#include <boost/standard_distribution/distributions/location_scale.hpp>
#include <boost/random/location_scale.hpp>
#include <boost/dist_random/meta/dist_random.hpp>
#include <boost/dist_random/functional/make_random.hpp>

namespace boost{

    template<typename Z>
    struct dist_random< 
        boost::math::location_scale_distribution<Z> 
    >{
        typedef boost::math::location_scale_distribution<Z> dist_;
        typedef typename dist_random<Z>::type z_;
        typedef boost::random::location_scale_distribution<z_> type;
        
        static type make(const dist_& d){ 
            return type(
                make_random(d.z()),
                d.mu(),
                d.sigma()
            ); 
        }
    };
    
}// boost

#endif