#include <vector>

#include "curve.hpp"

SampledCurve::SampledCurve(
    std::vector<std::pair<double, double>> sampled_points)
    : sampled_points(sampled_points) {}

SampledCurve::SampledCurve(const SampledCurve& sampled_curve)
    : sampled_points(sampled_curve.sampled_points) {}

const std::vector<std::pair<double, double>>& SampledCurve::getSampledPoints() {
  return sampled_points;
}

const std::pair<double, double> SampledCurve::operator()(double t) {
  if (sampled_points.size() == 0) {
    throw std::runtime_error("No sampled points");
  }
  if (t < 0 || t > 1) {
    throw std::runtime_error("t must be in [0, 1]");
  }
  int n = sampled_points.size();
  // 0~1 -> 0~n-1
  // t = 0 -> 0
  // t = 1 -> n-1
  double x = t * (n - 1);
  int i = static_cast<int>(x);
  if (i == n - 1) {
    return sampled_points.back();
  }
  double alpha = x - i;
  return std::make_pair((1 - alpha) * sampled_points[i].first +
                            alpha * sampled_points[i + 1].first,
                        (1 - alpha) * sampled_points[i].second +
                            alpha * sampled_points[i + 1].second);
}
