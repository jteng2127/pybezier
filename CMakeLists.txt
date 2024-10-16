# execute_process(COMMAND python3 -m pybind11 --includes OUTPUT_VARIABLE PYBIND11_INCLUDE_DIRS)
# string(REPLACE " " ";" PYBIND11_INCLUDE_DIRS "${PYBIND11_INCLUDE_DIRS}")

# include_directories(${PYBIND11_INCLUDE_DIRS})
# cmake_minimum_required(VERSION 3.0)
# project(pybind11_example)

# # Find Python
# find_package(PythonLibs REQUIRED)
# include_directories(${PYTHON_INCLUDE_DIRS})

# # Find Pybind11
# find_package(pybind11 REQUIRED)

# # Add the example module
# pybind11_add_module(example example.cpp)

# # Link the module with Python
# target_link_libraries(example PRIVATE ${PYTHON_LIBRARIES})

cmake_minimum_required(VERSION 3.12)
project(pybezier_library)

# Add the cpp subdirectory where the C++ code is located
add_subdirectory(pybezier/cpp)
