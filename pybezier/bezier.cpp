#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

#include "curve.hpp"

Bezier::Bezier(std::vector<std::pair<double, double>> control_points)
    : control_points(control_points) {}

Bezier::Bezier(const Bezier& bezier) : control_points(bezier.control_points) {}

const std::vector<std::pair<double, double>>& Bezier::getControlPoints() {
  return control_points;
}

const std::pair<double, double> Bezier::operator()(double t) {
  if (control_points.size() == 0) {
    throw std::runtime_error("No control points");
  }
  if (t < 0 || t > 1) {
    throw std::runtime_error("t must be in [0, 1]");
  }
  std::vector<std::pair<double, double>> tmp = control_points;
  while (tmp.size() > 1) {
    std::vector<std::pair<double, double>> next(tmp.size() - 1);
    for (size_t i = 0; i < tmp.size() - 1; ++i) {
      double x = (1 - t) * tmp[i].first + t * tmp[i + 1].first;
      double y = (1 - t) * tmp[i].second + t * tmp[i + 1].second;
      next[i] = std::make_pair(x, y);
    }
    tmp = next;
  }
  return tmp[0];
}

UniformDistanceSampler::UniformDistanceSampler(std::shared_ptr<Curve> curve,
                                               int samples)
    : curve(curve), samples(samples) {}

void UniformDistanceSampler::compute_cumulative_distances() {
  cumulative_distances.resize(samples);
  cumulative_distances[0] = 0;
  std::pair<double, double> current = (*curve)(0);
  for (int i = 1; i < samples; ++i) {
    double t = i / (samples - 1.0);
    std::pair<double, double> next = (*curve)(t);
    cumulative_distances[i] =
        cumulative_distances[i - 1] +
        std::hypot(next.first - current.first, next.second - current.second);
    current = next;
  }
  for (int i = 0; i < samples; ++i) {
    cumulative_distances[i] /= cumulative_distances.back();
  }
}
