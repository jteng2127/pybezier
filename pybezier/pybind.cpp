#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "curve.hpp"
#include "fit.hpp"

namespace py = pybind11;

PYBIND11_MODULE(pybezier, m) {
  py::class_<Curve, std::shared_ptr<Curve>>(m, "Curve")
      .def("__call__", &Curve::operator());

  py::class_<Bezier, Curve, std::shared_ptr<Bezier>>(m, "Bezier")
      .def(py::init<std::vector<std::pair<double, double>>>())
      .def_property_readonly("control_points", &Bezier::getControlPoints)
      .def("__call__", &Bezier::operator());

  py::class_<SampledCurve, Curve, std::shared_ptr<SampledCurve>>(m,
                                                                 "SampledCurve")
      .def(py::init<std::vector<std::pair<double, double>>>())
      .def_property_readonly("sampled_points", &SampledCurve::getSampledPoints)
      .def("__call__", &SampledCurve::operator());

  py::class_<UniformDistanceSampler, Curve,
             std::shared_ptr<UniformDistanceSampler>>(m,
                                                      "UniformDistanceSampler")
      .def(py::init<std::shared_ptr<Curve>, int>())
      .def_property_readonly("cumulative_distances",
                             &UniformDistanceSampler::getCumulativeDistances)
      .def_property("samples", &UniformDistanceSampler::getSamples,
                    &UniformDistanceSampler::setSamples)
      .def("__call__", &UniformDistanceSampler::operator());

  py::class_<MultiCurve, Curve, std::shared_ptr<MultiCurve>>(m, "MultiCurve")
      .def(py::init<std::vector<std::shared_ptr<Curve>>>())
      .def("__call__", &MultiCurve::operator())
      .def_property_readonly("curves", &MultiCurve::getCurves);

  m.def("fit_curve_to_bezier", &fit_curve_to_bezier, py::arg("curve"),
        py::arg("num_samples") = 100, py::arg("degree") = 3,
        py::arg("error_tolerance") = 0.01, py::arg("max_iterations") = 1000);
  m.def("fit_curve_to_beziers", &fit_curve_to_beziers, py::arg("curve"),
        py::arg("error_tolerance") = 0.01, py::arg("max_iterations") = 1000,
        py::arg("num_bezier_curves") = 1, py::arg("degree") = 3);
  m.def("compute_curve_error", &compute_curve_error, py::arg("a"), py::arg("b"),
        py::arg("num_samples") = 100);
}