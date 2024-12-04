#pragma once

#include <memory>
#include <vector>

#include "curve.hpp"

std::shared_ptr<MultiCurve> fit_curve_to_beziers(std::shared_ptr<Curve> curve,
                                double error_tolerance, int max_iterations, int num_bezier_curves);

std::shared_ptr<Bezier> fit_curve_to_bezier(std::shared_ptr<Curve> curve,
                                            int num_samples, int degree,
                                            double error_tolerance,
                                            int max_iterations);

double compute_curve_error(std::shared_ptr<Curve> a, std::shared_ptr<Curve> b,
                           int num_samples);