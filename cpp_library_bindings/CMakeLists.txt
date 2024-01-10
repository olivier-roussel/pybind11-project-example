file(GLOB_RECURSE PYXMOLPP_SOURCES
        _core/**.cpp
        _core/**.h
)
set(FOO_TARGET _core)

pybind11_add_module(${FOO_TARGET} SHARED ${PYXMOLPP_SOURCES})
target_include_directories(${FOO_TARGET} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/_core)
target_link_libraries(${FOO_TARGET} PRIVATE cpp_library)