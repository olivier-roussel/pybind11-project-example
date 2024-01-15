#include "cpp_library/Foo.h"

#include <pybind11/pybind11.h>

// namespace with types that lacks pybind counterpart
namespace forgotten {

struct Unbound {};

enum Enum{
    ONE=1,
    TWO=2
};

}


namespace py = pybind11;

PYBIND11_MODULE(_core, m)
{
  auto pyFoo = py::class_<cpp_library::Foo>(m,"Foo");
  pyFoo
    .def(py::init<>())
    .def("Init",&cpp_library::Foo::Init);

  py::list foolist;
  foolist.append(cpp_library::Foo());
  foolist.append(cpp_library::Foo());

  m.attr("foolist") = foolist;
  m.attr("none") = py::none();
  {
      py::list li;
      li.append(py::none{});
      li.append(2);
      li.append(py::dict{});
      m.attr("list_with_none") = li;
  }
}