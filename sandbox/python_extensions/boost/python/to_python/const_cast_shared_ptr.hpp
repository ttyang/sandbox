// Copyright 2010 Jim Bosch.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PYTHON_TO_PYTHON_CONST_CAST_SHARED_PTR_HPP
#define BOOST_PYTHON_TO_PYTHON_CONST_CAST_SHARED_PTR_HPP

#include <boost/python.hpp>

namespace boost {
namespace python {

/**
 *  @brief A to-python converter that enables converting shared_ptr<Value const> to Python by
 *         casting away constness.
 *
 *  A shared_ptr<Value> to-Python converter must be registered for this converter to work
 *  (this is typically done with register_ptr_to_python).
 *
 *  This converter is particularly useful when a wrapped class is immutable in Python.
 */
template <typename Value>
struct const_cast_shared_ptr_to_python {
    typedef typename boost::python::copy_const_reference::apply<shared_ptr<Value> const &>::type Converter;

    static PyObject * convert(shared_ptr<Value const> const & source) {
        Converter converter;
        shared_ptr<Value> target = boost::const_pointer_cast<Value>(source);
        return converter(target);
    }
    
    static PyTypeObject const * get_pytype() {
        Converter converter;
        return converter.get_pytype();
    }

    const_cast_shared_ptr_to_python() {
        boost::python::to_python_converter<shared_ptr<Value const>,const_cast_shared_ptr_to_python,true>();
    }

};

} // namespace boost::python
} // namespace boost

#endif // !BOOST_PYTHON_TO_PYTHON_CONST_CAST_SHARED_PTR_HPP
