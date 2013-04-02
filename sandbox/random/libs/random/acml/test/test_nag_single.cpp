// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/random/acml/engine.hpp>
#include <boost/random/acml/boost/distributions.hpp>
#include <boost/random/acml/c++11/distributions.hpp>
#include <boost/random/acml/tr1/distributions.hpp>

#define ACML_TEST
#define BOOST_RANDOM_ACML_URNG boost::random::acml::engine<1,true,1>

#define ENGINE_SCOPE boost::random::acml

// test generator
#include "test_generator.ipp"

