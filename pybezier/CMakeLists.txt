cmake_minimum_required(VERSION 3.12)
project(pybezier)

pybind11_add_module(pybezier MODULE bezier.cpp pybind.cpp)