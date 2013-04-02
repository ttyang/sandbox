// Copyright Fabian Bösch 2013
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/random/mkl/engine.hpp>
#include <boost/random/mkl/boost/distributions.hpp>
#include <boost/random/mkl/c++11/distributions.hpp>
#include <boost/random/mkl/tr1/distributions.hpp>

#define BOOST_RANDOM_ACML_URNG boost::random::mkl::wh

#define ENGINE_SCOPE boost::random::mkl

#define BOOST_RANDOM_ACML_NO_DISCARD

// test generator
#include "../../acml/test/test_generator.ipp"

