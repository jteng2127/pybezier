#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bezier.hpp"

namespace py = pybind11;

PYBIND11_MODULE(pybezier, m) {
  py::class_<Curve, std::shared_ptr<Curve>>(m, "Curve")
      .def("__call__", &Curve::operator());

  py::class_<Bezier, Curve, std::shared_ptr<Bezier>>(m, "Bezier")
      .def(py::init<std::vector<std::pair<double, double>>>())
      .def_property_readonly("control_points", &Bezier::getControlPoints)
      .def("__call__", &Bezier::operator());

  py::class_<UniformDistanceSampler, Curve, std::shared_ptr<UniformDistanceSampler>>(
      m, "UniformDistanceSampler")
      .def(py::init<Curve*, int>())
      .def_property_readonly("cumulative_distances",
                             &UniformDistanceSampler::getCumulativeDistances)
      .def_property("samples", &UniformDistanceSampler::getSamples,
                    &UniformDistanceSampler::setSamples)
      .def("__call__", &UniformDistanceSampler::operator());
}