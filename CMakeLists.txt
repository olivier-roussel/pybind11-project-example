cmake_minimum_required(VERSION 3.8)
project(pybind11_project_example)

find_package(pybind11 REQUIRED)

add_library(cpp_library SHARED src/Foo.cpp)
target_include_directories(cpp_library PUBLIC ./include)
target_link_libraries(cpp_library PRIVATE pybind11::embed)

add_subdirectory(cpp_library_bindings)