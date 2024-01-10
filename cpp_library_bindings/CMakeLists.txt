project(_core)

set(HEADER_FILES
  # ${CMAKE_CURRENT_SOURCE_DIR}/_core/myheader.h
)

set(SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/_core/cpp_library.cpp
)

# file(GLOB_RECURSE PYXMOLPP_SOURCES
#         _core/**.cpp
#         _core/**.h
# )

# pybind11_add_module(${PROJECT_NAME} SHARED ${PYXMOLPP_SOURCES})
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/_core)
# target_link_libraries(${PROJECT_NAME} PRIVATE cpp_library)

SP3_add_python_module(
    TARGET       ${PROJECT_NAME}
    PACKAGE      Bindings.Foo
    MODULE       _core
    DESTINATION  Foo
    SOURCES      ${SOURCE_FILES}
    HEADERS      ${HEADER_FILES}
    DEPENDS      FooLib
)
