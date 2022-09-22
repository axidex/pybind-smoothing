cmake_minimum_required(VERSION 3.16)
project("pybind-smoothing")
#set(ENGINE_PROJECT_NAME smoothingmodule)

set(CMAKE_CXX_STANDARD 20)

set(MODULE_SOURCE "${PROJECT_SOURCE_DIR}/source/module")
set(EXTERNALS "${PROJECT_SOURCE_DIR}/externals")

# pybind11
add_subdirectory(${EXTERNALS}/pybind11)

include_directories(${PYTHON_INCLUDE_DIRS} ${_numpy_include_dirs})
message("Python libs: ${PYTHON_LIBRARIES}")

#module

pybind11_add_module (
    smoothingmodule
    ${MODULE_SOURCE}/module.cpp
    ${MODULE_SOURCE}/smoothing.cpp
)

target_include_directories (
    smoothingmodule
    PRIVATE ${MODULE_SOURCE}
)

FIND_PACKAGE(Python3 COMPONENTS Interpreter Development)

# opencv

find_package(OpenCV REQUIRED)
set(OpenCV_STATIC ON)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(smoothingmodule PRIVATE ${OpenCV_LIBS} pybind11::embed Python3::Python -static)

