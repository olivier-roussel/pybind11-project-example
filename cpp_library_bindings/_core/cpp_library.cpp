#include "cpp_library/Foo.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(_core, m)
{
  auto pyFoo = pybind11::class_<cpp_library::Foo>(m,"Foo");
  pyFoo
    .def(pybind11::init<>())
    .def("f",&cpp_library::Foo::Init);
}