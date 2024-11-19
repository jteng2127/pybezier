#include "bezier.hpp"

#include <iostream>
#include <vector>

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

UniformDistanceSampler::UniformDistanceSampler(Curve* curve, int samples)
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

const std::pair<double, double> UniformDistanceSampler::operator()(double t) {
  if (t < 0 || t > 1) {
    throw std::runtime_error("t must be in [0, 1]");
  }
  double d = t;
  if (cumulative_distances.size() != samples) {
    compute_cumulative_distances();
  }
  auto it = std::upper_bound(cumulative_distances.begin(),
                             cumulative_distances.end(), t);
  if (it == cumulative_distances.begin()) {
    return (*curve)(0);
  }
  double t0 = (it - cumulative_distances.begin() - 1) / (samples - 1.0);
  double t1 = (it - cumulative_distances.begin()) / (samples - 1.0);
  double d0 = cumulative_distances[it - cumulative_distances.begin() - 1];
  double d1 = cumulative_distances[it - cumulative_distances.begin()];
  double alpha = (d - d0) / (d1 - d0);
  return (*curve)(t0 + alpha * (t1 - t0));
}

const std::vector<double>& UniformDistanceSampler::getCumulativeDistances() {
  if (cumulative_distances.size() != samples) {
    compute_cumulative_distances();
  }
  return cumulative_distances;
}

const int UniformDistanceSampler::getSamples() { return samples; }

void UniformDistanceSampler::setSamples(int samples) {
  this->samples = samples;
}