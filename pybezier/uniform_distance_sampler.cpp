#include <algorithm>
#include <exception>
#include <stdexcept>

#include "curve.hpp"

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