cmake_minimum_required(VERSION 3.12)
project(bezier_cpp)

# Find pybind11
find_package(pybind11 REQUIRED)

# Add the C++ source file
add_library(bezier MODULE bezier.cpp)

# Link pybind11
target_link_libraries(bezier PRIVATE pybind11::module)

# Set the output properties to ensure the module is output in the correct location
set_target_properties(bezier PROPERTIES 
    PREFIX "${PYTHON_MODULE_PREFIX}" 
    SUFFIX "${PYTHON_MODULE_EXTENSION}" 
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/pybezier/cpp"
)

