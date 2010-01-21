//////////////////////////////////////////////////////////////////////////////
// distribution::toolkit::example::random2.cpp                               //
//                                                                          //
//  (C) Copyright 2009 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <boost/typeof/typeof.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/chi_squared/include.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/exponential/include.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/gamma/include.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/normal/include.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/poisson/include.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/students_t/include.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/location_scale/include.hpp>
#include <boost/statistics/detail/distribution_common/distributions/reference/include.hpp>
#include <boost/statistics/detail/distribution_common/meta/random/generator.hpp>
#include <boost/statistics/detail/non_parametric/kolmogorov_smirnov/check_convergence.hpp>

#include <libs/statistics/detail/distribution_toolkit/example/random.h>

void example_random(std::ostream& os)
{
    // Checks convergence of sample generated by make_random_generator(urng,d)
    // to distribution b, by the kolmogorov-smirnov

    os << "-> test_random2 " << std::endl;

	namespace ks = boost::statistics::detail::kolmogorov_smirnov;

    using namespace boost;
    using namespace boost::statistics;
    namespace stat = statistics::detail;
	namespace dist = stat::distribution;
	typedef int int_;
    typedef double val_;
	typedef boost::mt19937 urng_;
	typedef ks::check_convergence<val_> check_;

    const unsigned n_loops = 6;
    const unsigned n1 = 1e1;
    const unsigned n2 = 1e1;
    	
    urng_ urng;
    check_ check;
    
    {
        typedef math::chi_squared_distribution<val_> dist_;
        const val_ df = 10;
        dist_ d( df );
        os << d << std::endl;
        BOOST_AUTO(
        	vg,
            dist::make_random_generator(urng,d)
        );
        check(n_loops,n1,n2,d,vg,os);
    }
    {
        typedef math::exponential_distribution<val_>     dist_;
        const val_ lambda = 1.0;
        dist_ d( lambda );
        os << d << std::endl;
        BOOST_AUTO(
        	vg,
            dist::make_random_generator(urng,d)
        );
        check(n_loops,n1,n2,d,vg,os);
    }
    { 
        typedef math::gamma_distribution<val_>            dist_;
        const val_ shape = 2.0;
        const val_ scale = 3.0;
        dist_ d( shape, scale );
        os << d << std::endl;
            
        BOOST_AUTO(
        	vg,
            dist::make_random_generator(urng,d)
        );
        check(n_loops,n1,n2,d,vg,os);
    }
    {
        typedef math::normal_distribution<val_>            dist_;
        const val_ m = 1.0;
        const val_ s = 2.0;
        dist_ d( m, s );
        os << d << std::endl;
            
        BOOST_AUTO(
        	vg,
            dist::make_random_generator(urng,d)
        );
        check(n_loops,n1,n2,d,vg,os);

    }
    {
        typedef boost::math::poisson_distribution<val_>            dist_;
        const val_ m = 10.0;
        dist_ d( m );
        os << d << std::endl;
            
        BOOST_AUTO(
        	vg,
            dist::make_random_generator(urng,d)
        );
        check(n_loops,n1,n2,d,vg,os);

    }
    {
        typedef math::students_t_distribution<val_>        dist_;
        const val_ df = 4.0;
        dist_ d( df );
        os << d << std::endl;

        BOOST_AUTO(
        	vg,
            dist::make_random_generator(urng,d)
        );
        check(n_loops,n1,n2,d,vg,os);
    }
    {
        typedef math::students_t_distribution<val_> dist_z_;
        typedef dist::toolkit::location_scale_distribution<dist_z_> dist_; 
        const val_ df = 4.0;
        const val_ m = 1.0;
        const val_ s = 2.0;
        dist_z_ dist_z( df );
        dist_ d(m, s, dist_z);
        os << d << std::endl;

        BOOST_AUTO(
        	vg,
            dist::make_random_generator(urng,d)
        );
        check(n_loops,n1,n2,d,vg,os);
    }
    {
        typedef math::students_t_distribution<val_>         d0_;
        typedef dist::reference_wrapper<d0_>                dist_; 
        const val_ df = 4.0;
        d0_ d0( df );
        dist_ d(d0);
        os << d << std::endl;
            
        BOOST_AUTO(
        	vg,
            dist::make_random_generator(urng,d)
        );
        check(n_loops,n1,n2,d,vg,os);
    }

    os << "<-" << std::endl;
}