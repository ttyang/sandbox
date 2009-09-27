//////////////////////////////////////////////////////////////////////////////
// distribution_toolkit::data::generate_n_sample_cdf.hpp                    //
//                                                                          //
//  (C) Copyright 2009 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_TOOLKIT_DATA_GENERATE_N_SAMPLE_CDF_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_TOOLKIT_DATA_GENERATE_N_SAMPLE_CDF_HPP_ER_2009
#include <boost/utility/enable_if.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/statistics/detail/distribution_toolkit/meta/is_scalar_distribution.hpp>
#include <boost/statistics/detail/distribution_toolkit/data/sample_cdf.hpp>
#include <boost/statistics/detail/distribution_toolkit/fwd_math/cdf.hpp>
#include <boost/statistics/detail/distribution_toolkit/random/generator.hpp>

namespace boost{

        template<typename T,typename N,typename D,typename U>
        typename enable_if<
            statistics::detail::distribution_toolkit
                ::meta::is_scalar_distribution<D>,
                void
        >::type
        generate_n(
            statistics::detail::distribution_toolkit::sample_cdf<T>& sc,
            N n, 
            U& urng,
            const D& dist
        ){
            typedef statistics::detail::distribution_toolkit::sample_cdf<T> sc_;
            typedef typename sc_::size_type size_type;
            BOOST_AUTO(vg,boost::make_random_generator(urng,dist));
            size_type i = 0;
            T x, cdf;
            while(i<n){
                x = vg();
                cdf = statistics::detail::distribution_toolkit::cdf(dist,x);
                sc(x,cdf);
                ++i;
            };
            
        }

}

#endif