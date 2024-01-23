set(TARGET _core)

pybind11_add_module(${TARGET} SHARED _core/cpp_library.cpp)
target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/_core)
target_link_libraries(${TARGET} PRIVATE cpp_library)