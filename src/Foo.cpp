#include "cpp_library/Foo.h"

#include <iostream>

#include <pybind11/embed.h>
#include <pybind11/eval.h>

namespace cpp_library
{

void Foo::Init()
{
  std::cout << "invoked Foo::Init()" << std::endl;
  std::string pythonVersion = Py_GetVersion();
  std::cout <<  "Initializing with python version " << pythonVersion << std::endl;
}

void Foo::Release()
{
  std::cout << "invoked Foo::Release()" << std::endl;
}

void init()
{
  std::cout << "invoked main init()" << std::endl;
  Foo::Init();
}

} // cpp_library