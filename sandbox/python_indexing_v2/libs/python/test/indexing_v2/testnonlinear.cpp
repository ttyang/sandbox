// Module testnonlinear.cpp
//
// Copyright (c) 2003, 2008 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003-09-29   rmg     File creation from testlinear.cpp
// 2008-05-18   rmg     Rename indexing subdirectory to indexing_v2
//
// $Id$
//

#include "int_wrapper.hpp"
#include <boost/python/suite/indexing_v2/container_suite.hpp>
#include <boost/python/suite/indexing_v2/map.hpp>
#include <boost/python/suite/indexing_v2/set.hpp>
#include <map>
#include <set>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

// More messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

BOOST_PYTHON_MODULE(testnonlinear)
{
  namespace indexing_v2 = boost::python::indexing_v2;

  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper> ("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", &int_wrapper::repr)
    .def ("__cmp__", compare)
    ;

  typedef std::map<std::string, int_wrapper> Container1;
  typedef std::set<std::string> Container2;

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  typedef indexing_v2::container_suite<Container1> Suite1;
  typedef indexing_v2::container_suite<Container2> Suite2;
#else
  typedef indexing_v2::map_suite<Container1> Suite1;
  typedef indexing_v2::set_suite<Container2> Suite2;
#endif

  boost::python::class_<Container1>("Map").def (Suite1());
  boost::python::class_<Container2>("Set").def (Suite2());
}
