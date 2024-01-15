#pragma once
#include <stdexcept>

namespace cpp_library{

class Foo {
public:
    static void Init();
    static void Release();
};

void init();

}