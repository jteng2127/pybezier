cmake_minimum_required(VERSION 3.12)
project(pybezier)

add_subdirectory(pybind11)

add_subdirectory(pybezier)

add_custom_target(pytest
    COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_SOURCE_DIR}/pybezier/cpp python -m pytest ${CMAKE_SOURCE_DIR}/tests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running Python unit tests with pytest"
)