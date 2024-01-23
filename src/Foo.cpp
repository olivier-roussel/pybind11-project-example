#include "cpp_library/Foo.h"

#include <iostream>

namespace cpp_library
{

void Foo::Init()
{
  std::cout << "invoked Foo::Init()" << std::endl;
}

void init()
{
  std::cout << "invoked main init()" << std::endl;
  Foo::Init();
}

} // cpp_library
