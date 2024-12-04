#pragma once

#include <vector>
#include <memory>

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

class SampledCurve : public Curve {
 private:
  std::vector<std::pair<double, double>> sampled_points;

 public:
  SampledCurve(std::vector<std::pair<double, double>> sampled_points);
  SampledCurve(const SampledCurve& sampled_curve);
  const std::pair<double, double> operator()(double t) override;
  const std::vector<std::pair<double, double>>& getSampledPoints();
};

class UniformDistanceSampler : public Curve {
 private:
  std::shared_ptr<Curve> curve;
  int samples;
  std::vector<double> cumulative_distances;
  void compute_cumulative_distances();  // lazy evaluation
 public:
  UniformDistanceSampler(std::shared_ptr<Curve> curve, int samples);
  const std::pair<double, double> operator()(double t) override;
  const std::vector<double>& getCumulativeDistances();
  const int getSamples();
  void setSamples(int samples);
};

class MultiCurve : public Curve {
 private:
  std::vector<std::shared_ptr<Curve>> curves;

 public:
  MultiCurve(std::vector<std::shared_ptr<Curve>> curves);
  const std::pair<double, double> operator()(double t) override;
};