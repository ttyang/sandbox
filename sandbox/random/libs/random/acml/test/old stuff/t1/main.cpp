// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/random/acml/engine.hpp>
//#include <boost/random/variate_generator.hpp>
//#include <boost/random/acml/variate_generator_specialization_0x_distributions.hpp>
//#include <random>
//#include <vector>

int main()
{

	// instantiate generators

	//boost::random::acml::engine<-1,false,0> engine_1;   // must not compile
	//boost::random::acml::engine<0,false,0>  engine0;    // must not compile
	//boost::random::acml::engine<5,false,0>  engine5;    // must not compile
	
	boost::random::acml::engine<1,false,0> engine1f0;   // single precision linear congruential
	boost::random::acml::engine<1,false,1> engine1f1;   // single precision linear congruential (behavoiur equivalent to engine1f0)
	boost::random::acml::engine<1,true,0>  engine1t0;   // double precision linear congruential
	boost::random::acml::engine<1,true,1>  engine1t1;   // double precision linear congruential (behavoiur equivalent to engine1t0)

	boost::random::acml::engine<3,false,0> engine3f0;   // single precision Mersenne Twister
	boost::random::acml::engine<3,false,1> engine3f1;   // single precision Mersenne Twister (behavoiur equivalent to engine3f0)
	boost::random::acml::engine<3,true,0>  engine3t0;   // double precision Mersenne Twister
	boost::random::acml::engine<3,true,1>  engine3t1;   // double precision Mersenne Twister (behavoiur equivalent to engine3t0)

	boost::random::acml::engine<4,false,0> engine4f0;   // single precision combined multiple recursive
	boost::random::acml::engine<4,false,1> engine4f1;   // single precision combined multiple recursive (behavoiur equivalent to engine4f0)
	boost::random::acml::engine<4,true,0>  engine4t0;   // double precision combined multiple recursive
	boost::random::acml::engine<4,true,1>  engine4t1;   // double precision combined multiple recursive (behavoiur equivalent to engine4t0)

	//boost::random::acml::engine<2,false,0>   engine2f0;   // must not compile
	boost::random::acml::engine<2,false,1>   engine2f1;     // single precision Wichmann-Hill combined multiplicative congruential
	boost::random::acml::engine<2,false,2>   engine2f2;     // single precision Wichmann-Hill combined multiplicative congruential
	boost::random::acml::engine<2,false,100> engine2f100;   // single precision Wichmann-Hill combined multiplicative congruential
	boost::random::acml::engine<2,false,273> engine2f273;   // single precision Wichmann-Hill combined multiplicative congruential
	//boost::random::acml::engine<2,false,274> engine2f274; // must not compile
	//boost::random::acml::engine<2,true,0>    engine2t0;   // must not compile
	boost::random::acml::engine<2,true,1>   engine2t1;      // double precision Wichmann-Hill combined multiplicative congruential
	boost::random::acml::engine<2,true,2>   engine2t2;      // double precision Wichmann-Hill combined multiplicative congruential
	boost::random::acml::engine<2,true,100> engine2t100;    // double precision Wichmann-Hill combined multiplicative congruential
	boost::random::acml::engine<2,true,273> engine2t273;    // double precision Wichmann-Hill combined multiplicative congruential
	//boost::random::acml::engine<2,true,274> engine2t274;  // must not compile


	return 0;
}

