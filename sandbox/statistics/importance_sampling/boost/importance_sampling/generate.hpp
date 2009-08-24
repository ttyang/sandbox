///////////////////////////////////////////////////////////////////////////////
// is::generate.hpp                                                          //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_IMPORTANCE_SAMPLING_GENERATE_HPP_ER_2009
#define BOOST_IMPORTANCE_SAMPLING_GENERATE_HPP_ER_2009
#include <iterator>
#include <functional>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/utility.hpp>
#include <boost/non_param/algorithm/proportion_less_than.hpp>
#include <boost/importance_sampling/sampler.hpp>
#include <boost/random/ref_distribution.hpp>

namespace boost{
namespace is{

    template<typename U,typename ItW,typename ItP,typename ItT>
    ItT generate(
        U& urng,
        ItW b_w,        // unnormalized weights
        ItW e_w,        // unnormalized weights
        ItP b_p,        // proposal values
        ItT b_t,        // target values (output)
        std::size_t n   // sample size
    );

    // Implementation

    template<typename U,typename ItW,typename ItP,typename ItT>
    ItT generate(
        U& urng,
        ItW b_w, 
        ItW e_w, 
        ItP b_p, 
        ItT b_t, 
        std::size_t n 
    ){
        typedef boost::iterator_range<ItW>                  range_w_;
        typedef boost::iterator_range<ItP>                  range_p_;
        typedef typename boost::iterator_value<ItW>::type   w_;
        typedef boost::is::sampler<range_p_,w_>             iss_;
        typedef boost::random::ref_distribution<iss_&>      ref_iss_;
        typedef boost::variate_generator<U&,ref_iss_>       gen_iss_;
        
        range_w_    range_w(b_w,e_w);
        range_p_    range_p(
            b_p,
            boost::next(
                b_p,
                std::distance(
                    b_w,
                    e_w
                )
            )
        );

        iss_        iss( range_w, range_p );
        ref_iss_    ref_iss( iss );
        gen_iss_    gen_iss( urng, iss );
        
        return std::generate_n(
            b_t,
            n,
            gen_iss
        );
    }
    
}// is
}// boost

#endif