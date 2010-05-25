// Copyright 2010 Jim Bosch.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PYTHON_CONST_AWARE_REGISTRY_HPP
#define BOOST_PYTHON_CONST_AWARE_REGISTRY_HPP

#include <boost/python.hpp>

namespace boost { namespace python { namespace const_aware { namespace registry {

BOOST_PYTHON_DECL PyTypeObject * query(PyTypeObject const * non_const);

BOOST_PYTHON_DECL void insert(PyTypeObject * non_const, PyTypeObject * const_);

}}}} // namespace boost::python::const_aware::registry

#endif // !BOOST_PYTHON_CONST_AWARE_REGISTRY_HPP
