#include "curve.hpp"
#include <stdexcept>
#include <cmath>

MultiCurve::MultiCurve(std::vector<std::shared_ptr<Curve>> curves) {
  if (curves.empty()) {
    throw std::invalid_argument("MultiCurve requires at least one curve.");
  }
  this->curves = curves;
}

const std::pair<double, double> MultiCurve::operator()(double t) {
  if (t < 0.0) t = 0.0;
  if (t > 1.0) t = 1.0;

  double segment_length = 1.0 / curves.size();
  size_t curve_index = static_cast<size_t>(t / segment_length);

  if (curve_index == curves.size()) {
    curve_index = curves.size() - 1;
  }

  double local_t = (t - curve_index * segment_length) / segment_length;

  return (*curves[curve_index])(local_t);
}

const std::vector<std::shared_ptr<Curve>>& MultiCurve::getCurves() {
  return curves;
}