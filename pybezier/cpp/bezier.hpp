#pragma once

#include <vector>

class Curve {
 public:
  virtual const std::pair<double, double> operator()(double t) = 0;
};


class Bezier : public Curve {
 private:
  std::vector<std::pair<double, double>> control_points;
 public:
  Bezier(std::vector<std::pair<double, double>> control_points);
  Bezier(const Bezier& bezier);
  const std::pair<double, double> operator()(double t) override;
  const std::vector<std::pair<double, double>>& getControlPoints();
};

class UniformDistanceSampler : public Curve {
 private:
  Curve* curve;
  int samples;
  std::vector<double> cumulative_distances;
  void compute_cumulative_distances(); // lazy evaluation
 public:
  UniformDistanceSampler(Curve* curve, int samples);
  const std::pair<double, double> operator()(double t) override;
  const std::vector<double>& getCumulativeDistances();
  const int getSamples();
  void setSamples(int samples);
};