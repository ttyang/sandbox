// Copyright 2010 Jim Bosch
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/python.hpp>
#include <boost/python/const_aware/registry.hpp>
#include <boost/python/const_aware/proxy_class.hpp>
#include <boost/python/const_aware/as_const.hpp>

#include <map>

namespace boost { namespace python { namespace const_aware { namespace registry {

namespace {

typedef std::map<PyTypeObject*,PyTypeObject*> registry_t;
registry_t & entries() {
    static registry_t result;
    return result;
}

}

PyTypeObject * query(PyTypeObject const * non_const) {
    registry_t::const_iterator iter = entries().find(const_cast<PyTypeObject*>(non_const));
    if (iter != entries().end()) return iter->second;
    return 0;
}

void insert(PyTypeObject * non_const, PyTypeObject * const_) {
    entries().insert(registry_t::value_type(non_const, const_));
}

}}}} // namespace boost::python::const_aware::registry
