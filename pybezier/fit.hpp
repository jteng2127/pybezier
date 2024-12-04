#pragma once

#include <memory>
#include <vector>

#include "curve.hpp"

std::vector<std::shared_ptr<Bezier>> fit_curve_to_beziers(
    std::shared_ptr<Curve> curve, double error_tolerance, int max_iterations);

std::shared_ptr<Bezier> fit_curve_to_bezier(std::shared_ptr<Curve> curve,
                                            int num_samples, int degree,
                                            double error_tolerance,
                                            int max_iterations);

double compute_curve_error(std::shared_ptr<Curve> a, std::shared_ptr<Curve> b,
                           int num_samples);