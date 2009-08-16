///////////////////////////////////////////////////////////////////////////////
// is::example::sampler.cpp                                                  //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <boost/bind.hpp>
#include <boost/random.hpp>
#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/random/normal_distribution.hpp>
// Must come before non_param/algorithm/sequential_kolmogorov_smirnov_distance:
#include <boost/standard_distribution/distributions/normal.hpp>
#include <boost/non_param/algorithm/sequential_kolmogorov_smirnov_distance.hpp>
#include <boost/scalar_dist/include.hpp>
#include <boost/importance_weights/algorithm/prepare_weights.hpp>
#include <boost/importance_sampling/include.hpp>

void example_sampler(std::ostream& out){
    out << "->example_sampler : \n";

    // We sample from N(x|mu,sigma^2)N(x|mu,sigma^2) = N(x|mu,sigma^2/2), 
    // using SIR with N(x|mu+sigma,sigma^2) as proposal density. 
    // The quality of the sample is assessed by a series of 
    // kolmorov-distances along the the sample size of the targets.    
    using namespace boost;
    typedef std::string                                 str_t;
    typedef double                                      val_;
    typedef std::vector<val_>                           vec_;
    typedef range_iterator<vec_>::type                  it_val_;
    typedef std::vector<vec_>                           mat_;
    typedef math::normal_distribution<val_>             mnd_;
    typedef math::meta_ratio_pdf<mnd_,mnd_>             meta_ratio_;
    typedef normal_distribution<val_>                   rd_;
    typedef mt19937                                     urng_;
    typedef variate_generator<urng_&, rd_>              gen_t;
    typedef function<val_(mnd_,val_)>                   pdf_fun_; 
    typedef importance_weights::prepare_weights<val_>   prepare_weights_;

    // Constants
    const unsigned n_p          = 5e3;  // Proposal sample size
    const unsigned n_t_pl       = 1e1;  // Target sample size per loop
    const unsigned n_ks         = 1e2;
    const val_ max_log          = 0.0;  
    const val_ mu               = 0.0;
    const val_ sigma            = 1.0;
    const val_ target_mu        = mu + sigma;
    const val_ target_sigma     = sigma/sqrt(2.0);

    // Initialization
    prepare_weights_ prepare_weights( max_log );
    mnd_ md_proposal( mu, sigma );               
    mnd_ md_target( target_mu, target_sigma );   
    rd_ rd( mu, sigma );

    urng_ urng;
    vec_ vec_ks; vec_ks.reserve(n_ks * n_t_pl);
    vec_ proposals;
    proposals.reserve(n_p);
    vec_ targets; 
    targets.reserve( n_ks * n_t_pl );
    vec_ is_weights;
    is_weights.reserve(n_p);
    gen_t gen(urng,rd);
    std::generate_n( std::back_inserter(proposals), n_p, gen );

    is_weights.clear();
    math::transform<math::fun_wrap::log_unnormalized_pdf_>(
        meta_ratio_::make(md_target,md_proposal),
        boost::begin(proposals),
        boost::end(proposals),
        std::back_inserter(is_weights)
    );

    prepare_weights(
        boost::begin(is_weights),
        boost::end(is_weights),
        boost::begin(proposals)
    );

    out << std::endl << "Initial sample : " << std::endl
        << prepare_weights_::header << std::endl
        << prepare_weights << std::endl;

    targets.clear();
    is::generate(
        urng,
        boost::begin(is_weights),
        boost::end(is_weights),
        boost::begin(proposals),
        std::back_inserter(targets),
        n_t_pl * n_ks
    );
    {
        // i       0       1        ...    n-1           
        // [b,e)  [0,m)    [m,2m)   ...    [(n-1)m,n m)
        boost::non_param::sequential_kolmogorov_smirnov_distance(
            md_target,
            boost::begin(targets),
            boost::end(targets),
            n_ks,
            std::back_inserter(vec_ks)  
        );
        
    }

    out << "kolmorov smirnov distance series :";
    std::copy(
        boost::begin(vec_ks),
        boost::end(vec_ks),
        std::ostream_iterator<val_>(out, ",")
    );
    
    std::cout << "<-" << std::endl;

}


