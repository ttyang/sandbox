// Module test_array_ext.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003-10-15   rmg     File creation from testlinear.cpp
// 2008-05-18   rmg     Rename indexing subdirectory to indexing_v2
//
// $Id$
//

#include "int_wrapper.hpp"

#include <boost/python/suite/indexing_v2/container_suite.hpp>
#include <boost/python/suite/indexing_v2/iterator_range.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

// More messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

boost::python::indexing_v2::iterator_range<int *> get_array_plain()
{
  static int array[] = { 8, 6, 4, 2, 1, 3, 5, 7, 0 };

  return BOOST_MAKE_ITERATOR_RANGE (array);
}

boost::python::indexing_v2::iterator_range<int_wrapper *> get_array_wrap()
{
  static int_wrapper array[] = {
    int_wrapper(8), int_wrapper(6), int_wrapper(4), int_wrapper(2),
    int_wrapper(1), int_wrapper(3), int_wrapper(5),
    int_wrapper(7), int_wrapper(0) };

  return BOOST_MAKE_ITERATOR_RANGE (array);
}

BOOST_PYTHON_MODULE(test_array_ext)
{
  namespace indexing_v2 = boost::python::indexing_v2;

  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper>("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", &int_wrapper::repr)
    .def ("__cmp__", compare)
    ;

  typedef indexing_v2::iterator_range<int *> Container1;
  typedef indexing_v2::iterator_range<int_wrapper *> Container2;

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  typedef indexing_v2::container_suite<Container1> Suite1;
  typedef indexing_v2::container_suite<Container2> Suite2;
#else
  typedef indexing_v2::iterator_range_suite<Container1> Suite1;
  typedef indexing_v2::iterator_range_suite<Container2> Suite2;
#endif

  boost::python::class_<Container1>
    ("Array", boost::python::init<int *, int *>())
    .def (Suite1());

  boost::python::def ("get_array_plain", get_array_plain);


  // reference_existing_object is safe in this case, because the array
  // is static, and we never manually destroy any array elements. There
  // is also no point in using return_internal_reference to extend the
  // life of the iterator_range object, since it has no influence on the
  // lifetimes of the array elements.
  boost::python::class_<Container2>
    ("Array_ref", boost::python::init<int_wrapper *, int_wrapper *>())
    .def (Suite2::with_policies(
        boost::python::return_value_policy<
            boost::python::reference_existing_object>()));

  boost::python::def ("get_array_wrap", get_array_wrap);
}