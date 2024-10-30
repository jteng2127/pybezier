cmake_minimum_required(VERSION 3.12)
project(_pybezier)

pybind11_add_module(_pybezier MODULE bezier.cpp pybind.cpp)