cmake_minimum_required(VERSION 3.8)
project(pybind11_project_example)

set(SP3_COMPILED_AS_SUBPROJECT 1)
set(PLUGIN_SOFAPYTHON3 1)
# CMAKE TOOLS
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
include(SofaPython3Tools)

# OPTIONS
include(CMakeDependentOption)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable use of folder for IDE like VS
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set the minimum python version to 3.7
set(PYBIND11_PYTHON_VERSION 3.7)

# Find Python3
# find_package(Python ${PYBIND11_PYTHON_VERSION} COMPONENTS Interpreter Development REQUIRED)

# find_package(PythonInterp REQUIRED)
# find_package(PythonLibs "${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}" REQUIRED )
# if (PYTHONLIBS_FOUND)
#     include_directories(${PYTHON_INCLUDE_DIRS})
#     message("Using default python version: " ${PYTHONLIBS_VERSION_STRING})
# endif()


# Save PYTHON_* vars
# set(PYTHON_VERSION_RESET "${PYTHON_VERSION}")
# set(PYTHON_EXECUTABLE_RESET "${PYTHON_EXECUTABLE}")
# set(PYTHON_LIBRARIES_RESET "${PYTHON_LIBRARIES}")
# set(PYTHON_INCLUDE_DIRS_RESET "${PYTHON_INCLUDE_DIRS}")
# set(PYTHON_LIBRARY_RESET "${PYTHON_LIBRARY}")
# set(PYTHON_INCLUDE_DIR_RESET "${PYTHON_INCLUDE_DIR}")

# Change PYTHON_* vars before pybind11 find_package
# to be sure that pybind11 relies on the right Python version
# set(PYTHON_VERSION "${Python_VERSION}" CACHE STRING "" FORCE)
# set(PYTHON_EXECUTABLE "${Python_EXECUTABLE}" CACHE FILEPATH "" FORCE)
# set(PYTHON_LIBRARIES "${Python_LIBRARIES}" CACHE STRING "" FORCE)
# set(PYTHON_INCLUDE_DIRS "${Python_INCLUDE_DIRS}" CACHE STRING "" FORCE)
# if(EXISTS "${Python_LIBRARY}")
#     set(PYTHON_LIBRARY "${Python_LIBRARY}" CACHE INTERNAL "" FORCE)
# elseif(EXISTS "${Python_LIBRARIES}")
#     set(PYTHON_LIBRARY "${Python_LIBRARIES}" CACHE INTERNAL "" FORCE)
# endif()
# if(EXISTS "${Python_INCLUDE_DIR}")
#     set(PYTHON_INCLUDE_DIR "${Python_INCLUDE_DIR}" CACHE INTERNAL "" FORCE)
# elseif(EXISTS "${Python_INCLUDE_DIRS}")
#     set(PYTHON_INCLUDE_DIR "${Python_INCLUDE_DIRS}" CACHE INTERNAL "" FORCE)
# endif()

# Set the minimum pybind11 version to 2.3 (before that the pybind11::embed target did not exist)
find_package(pybind11 2.3 CONFIG QUIET REQUIRED)

set(SP3_PYTHON_PACKAGES_DIRECTORY
    "python3/site-packages"
    CACHE STRING
    "Directory name where the python packages will be built and installed.
    This will be prepend to LIBRARY_OUTPUT_DIRECTORY (default to site-packages)"
)

# Get the Python's user site packages directory, or FALSE if not found
SP3_get_python_user_site()

# Add an option to automatically create links towards the python packages of SP3
# into the python's user site packages directory.
option(
    SP3_LINK_TO_USER_SITE
    "Install python packages to python's user site directory. The directory path can be changed by setting SP3_PYTHON_PACKAGES_LINK_DIRECTORY."
    OFF
)

set(SP3_PYTHON_PACKAGES_LINK_DIRECTORY
    "${PYTHON_USER_SITE}"
    CACHE PATH
    "Path to the directory where the python packages will be installed (with symbolic links).
    (default to $(python3 -m site --user-site))"
)

message(STATUS "Python:
    Version: ${Python_VERSION}
    Executable: ${Python_EXECUTABLE}
    Headers: ${Python_INCLUDE_DIRS}
    Libraries: ${Python_LIBRARIES}
    User site: ${PYTHON_USER_SITE}"
)
message(STATUS "pybind11:
    Version: ${pybind11_VERSION}
    Config: ${pybind11_CONFIG}"
)


# When using python3 from XCode on MacOS, the RPath is wrongly set to XCode frameworks directory:
#   LC_LOAD_DYLIB   @rpath/Python3.framework/Versions/3.7/Python3
#   LC_RPATH        /Applications/Xcode.app/Contents/Developer/Library/Frameworks/Python3.framework/Versions/3.7/lib
# Hence LC_RPATH/LC_LOAD_DYLIB does not exists.
# Until this is fixed (not sure if it comes from pybind11, cmake or XCode), we can add another path to RPATH:
#   LC_LOAD_DYLIB   @rpath/Python3.framework/Versions/3.7/Python3
#   LC_RPATH        /Applications/Xcode.app/Contents/Developer/Library/Frameworks/Python3.framework/Versions/3.7/lib
#                   /Applications/Xcode.app/Contents/Developer/Library/Frameworks  <----- ADDED
# And now one combination of  LC_RPATH/LC_LOAD_DYLIB will be valid.
# This should't change anything for those that use other python libs than XCode (homebrew for example) since the
# LC_LOAD_DYLIB from XCode is quite unique.
# if (APPLE)
#     set(CMAKE_INSTALL_RPATH "/Applications/Xcode.app/Contents/Developer/Library/Frameworks")
#     set(CMAKE_BUILD_RPATH "/Applications/Xcode.app/Contents/Developer/Library/Frameworks")
# endif()



# add_subdirectory(Plugin)
# add_subdirectory(bindings)
# add_subdirectory(examples)
# add_subdirectory(docs)
# if (SP3_BUILD_TEST)
#     add_subdirectory(Testing)
# endif()

# SP3_add_python_package(
#     SOURCE_DIRECTORY
#         ${CMAKE_CURRENT_SOURCE_DIR}/constants
#     TARGET_DIRECTORY
#         Sofa/constants
# )

## This is only to warn users that splib is now relocated in its own repository
# it just contains a __init__.py rising an exception indicating to where to find the plugin.
# If splib is available, then splib/__init__.py will be overriden by the one from the real splib.
# SP3_add_python_package(
#     SOURCE_DIRECTORY
#         ${CMAKE_CURRENT_SOURCE_DIR}/splib
#     TARGET_DIRECTORY
#         splib
# )

# sofa_create_package(
#     PACKAGE_NAME ${PROJECT_NAME}
#     PACKAGE_VERSION ${PROJECT_VERSION}
#     RELOCATABLE "plugins"
#     )

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/CMake/SofaPython3Tools.cmake" "${CMAKE_BINARY_DIR}/lib/cmake/SofaPython3Tools.cmake" COPYONLY)
install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/SofaPython3Tools.cmake"
    DESTINATION lib/cmake/Foo
    COMPONENT headers
)

# if (SP3_LINK_TO_USER_SITE AND SP3_PYTHON_PACKAGES_LINK_DIRECTORY)
#     set(SP3_SITE_PACKAGES_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${SP3_PYTHON_PACKAGES_DIRECTORY}")

#     file(GLOB directories RELATIVE "${SP3_SITE_PACKAGES_OUTPUT_DIRECTORY}" "${SP3_SITE_PACKAGES_OUTPUT_DIRECTORY}/*")
    
#     # Create the site-package link directory if it doesn't exists yet
#     install(DIRECTORY DESTINATION ${SP3_PYTHON_PACKAGES_LINK_DIRECTORY})
#     foreach(directory ${directories})
#         if(SP3_COMPILED_AS_SOFA_SUBPROJECT)
#             set(LINK_SOURCE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/plugins/SofaPython3/lib/${SP3_PYTHON_PACKAGES_DIRECTORY}/${directory})
#         else()
#             set(LINK_SOURCE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib/${SP3_PYTHON_PACKAGES_DIRECTORY}/${directory})
#         endif()
#         if(IS_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${SP3_PYTHON_PACKAGES_DIRECTORY}/${directory})
#             if(WIN32)
#                 install(CODE "\
#                 execute_process( \
#                     COMMAND ${CMAKE_COMMAND} -E copy_directory \
#                     ${LINK_SOURCE_DIRECTORY}/ \
#                     ${SP3_PYTHON_PACKAGES_LINK_DIRECTORY}/${directory}   \
#                 )"
#             )
#             else()
#                 install(CODE "\
#                     execute_process( \
#                         COMMAND ${CMAKE_COMMAND} -E create_symlink \
#                         ${LINK_SOURCE_DIRECTORY}/ \
#                         ${SP3_PYTHON_PACKAGES_LINK_DIRECTORY}/${directory}   \
#                     )"
#                 )
#             endif()
#         endif()
#     endforeach()
# endif()

# Reset PYTHON_* vars
# set(PYTHON_VERSION "${PYTHON_VERSION_RESET}" CACHE STRING "" FORCE)
# set(PYTHON_EXECUTABLE "${PYTHON_EXECUTABLE_RESET}" CACHE FILEPATH "" FORCE)
# set(PYTHON_LIBRARIES "${PYTHON_LIBRARIES_RESET}" CACHE STRING "" FORCE)
# set(PYTHON_INCLUDE_DIRS "${PYTHON_INCLUDE_DIRS_RESET}" CACHE STRING "" FORCE)
# set(PYTHON_LIBRARY "${PYTHON_LIBRARY_RESET}" CACHE INTERNAL "" FORCE)
# set(PYTHON_INCLUDE_DIR "${PYTHON_INCLUDE_DIR_RESET}" CACHE INTERNAL "" FORCE)


# --- specific ----
# find_package(Eigen3 REQUIRED)

file(GLOB_RECURSE LIB_SOURCES src/**.cpp)
add_library(FooLib SHARED ${LIB_SOURCES})
target_include_directories(FooLib PUBLIC ./include)
# target_link_libraries(FooLib Eigen3::Eigen)

add_subdirectory(cpp_library_bindings)