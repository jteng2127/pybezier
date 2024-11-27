cmake_minimum_required(VERSION 3.12)
project(pybezier)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

pybind11_add_module(pybezier MODULE ${SOURCES})