#pragma once
#ifndef stradex_PYBIND_UTILS_H
#define stradex_PYBIND_UTILS_H

#include <vector>
#include <boost/python.hpp>

namespace py = boost::python;

template <class T>
py::list vector_to_py_list(const T& v) {
    py::object get_iter = py::iterator<T>();
    py::object iter = get_iter(v);
    py::list l(iter);
    return l;
}

template <class T>
T python_list_to_vector(py::list pylist) {
    size_t total = py::len(pylist);
    T result(total);
    for (size_t i = 0; i < total; i++) {
        result[i] = py::extract<typename T::value_type>(pylist[i])();
    }
    return result;
}

#endif  