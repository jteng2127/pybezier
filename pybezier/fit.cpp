#include "fit.hpp"

#include <Eigen/Dense>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "curve.hpp"

// double calculateL2Norm(const std::vector<std::pair<double, double>>& curve1,
//                        const std::vector<std::pair<double, double>>& curve2)
//                        {
//   double error = 0.0;
//   for (size_t i = 0; i < curve1.size(); ++i) {
//     double dx = curve1[i].first - curve2[i].first;
//     double dy = curve1[i].second - curve2[i].second;
//     error += dx * dx + dy * dy;
//   }
//   return std::sqrt(error / curve1.size());
// }

// void print_points(const std::vector<std::pair<double, double>>& points, const
// std::string& prefix = "") {
//   std::cout << prefix;
//   for (size_t i = 0; i < points.size(); ++i) {
//     std::cout << "(" << points[i].first << ", " << points[i].second << ") ";
//   }
//   std::cout << std::endl;
// }

// // double bernstein_derivative(int i, int n, double t) {
// //   if (i < 0 || i > n) return 0.0;

// //   double binomial = 1.0;
// //   for (int k = 0; k < i; ++k) binomial *= (n - k) / static_cast<double>(k
// + 1);

// //   double term1 =
// //       (i > 0) ? binomial * std::pow(t, i - 1) * std::pow(1 - t, n - i) :
// 0.0;
// //   double term2 = binomial * std::pow(t, i) * std::pow(1 - t, n - i - 1);

// //   return n * (term1 - term2);
// // }

// // 計算二項式係數
// int binomial_coeff(int n, int k) {
//   if (k < 0 || k > n) return 0;
//   if (k == 0 || k == n) return 1;
//   int c = 1;
//   for (int i = 0; i < k; ++i) {
//     c *= (n - i);
//     c /= (i + 1);
//   }
//   return c;
// }

// // 計算 Bernstein 多項式的導數
// double bernstein_derivative(int n, int j, double t) {
//   if (j < 0 || j > n) return 0.0;

//   double term1 = (j > 0) ? n * binomial_coeff(n - 1, j - 1) * std::pow(t, j -
//   1) * std::pow(1 - t, n - j) : 0.0; double term2 = (j < n) ? n *
//   binomial_coeff(n - 1, j) * std::pow(t, j) * std::pow(1 - t, n - j - 1) :
//   0.0;

//   return term1 - term2;
// }

// std::shared_ptr<Bezier> fit_curve_to_bezier(std::shared_ptr<Curve> curve,
//                                             double error_tolerance,
//                                             int max_iterations) {
//   std::cout << std::fixed << std::setprecision(10);
//   int samples = 5;
//   UniformDistanceSampler sampler(curve, samples);

//   std::vector<std::pair<double, double>> sampled_points;
//   for (int i = 0; i < samples; ++i) {
//     double t = static_cast<double>(i) / (samples - 1);
//     sampled_points.push_back(sampler(t));
//   }
//   print_points(sampled_points, "Sampled points: ");

//   // Initialize control points with sampled points
//   int control_points_count = 4;
//   std::vector<std::pair<double, double>>
//   control_points(control_points_count); for (int i = 0; i <
//   control_points_count; ++i) {
//     double t = static_cast<double>(i) / (control_points_count - 1);
//     control_points[i] = sampler(t);
//   }

//   // LM algorithm
//   double lambda = 1e-3;  // Initial damping factor
//   const double lambda_max = 1e6;
//   const double lambda_min = 1e-6;
//   double prev_error = std::numeric_limits<double>::max();

//   for (int iter = 0; iter < max_iterations; ++iter) {
//     std::cout << "i=" << iter << std::endl;
//     print_points(control_points, "Control points: ");
//     Bezier bezier(control_points);
//     // Calculate Bezier points
//     std::vector<std::pair<double, double>> bezier_points;
//     for (int i = 0; i < samples; ++i) {
//       double t = static_cast<double>(i) / (samples - 1);
//       bezier_points.push_back(bezier(t));
//     }
//     print_points(bezier_points, "Bezier points: ");

//     // Calculate L2 norm
//     double error = calculateL2Norm(bezier_points, sampled_points);
//     std::cout << "error: " << error << std::endl;
//     if (error < error_tolerance || std::abs(prev_error - error) < 1e-6) {
//       break;
//     }

//     // 構造 Jacobian 矩陣
//     Eigen::MatrixXd J(samples * 2, control_points_count * 2);
//     Eigen::VectorXd residuals(samples * 2);
//     J.setZero();
//     residuals.setZero();

//     for (int i = 0; i < samples; ++i) {
//       double t = static_cast<double>(i) / (samples - 1);

//       // 計算對每個控制點的導數
//       for (size_t j = 0; j < control_points_count; ++j) {
//         double basis = bernstein_derivative(control_points_count - 1, j, t);
//         J(2 * i, 2 * j) = basis;          // 對 x 的偏導
//         J(2 * i + 1, 2 * j + 1) = basis;  // 對 y 的偏導
//       }

//       residuals(2 * i) = sampled_points[i].first - bezier_points[i].first;
//       residuals(2 * i + 1) = sampled_points[i].second -
//       bezier_points[i].second;
//     }
//     std::cout << "J: \n" << J << std::endl;
//     std::cout << "residuals: \n" << residuals << std::endl;

//     // LM 更新
//     Eigen::MatrixXd JTJ = J.transpose() * J;
//     Eigen::VectorXd JTr = J.transpose() * residuals;
//     Eigen::MatrixXd damping =
//         lambda * Eigen::MatrixXd::Identity(JTJ.rows(), JTJ.cols());
//     Eigen::VectorXd delta = -(JTJ).ldlt().solve(JTr);
//     std::cout << "delta: \n" << delta << std::endl;

//     // 更新控制點
//     for (size_t j = 0; j < control_points.size(); ++j) {
//       control_points[j].first += delta(2 * j);
//       control_points[j].second += delta(2 * j + 1);
//     }

//     // 檢查是否收斂
//     double new_error = calculateL2Norm(bezier_points, sampled_points);
//     if (new_error < prev_error) {
//       lambda = std::max(lambda * 0.1, lambda_min);
//       prev_error = new_error;
//     } else {
//       lambda = std::min(lambda * 10, lambda_max);
//     }
//   }

//   return std::make_shared<Bezier>(control_points);
//   return std::make_shared<Bezier>(std::vector<std::pair<double, double>>());
// }

// std::shared_ptr<Curve> fit_curve_to_bezier(std::shared_ptr<Curve> curve,
//                                            double error_tolerance,
//                                            int max_iterations) {
//   return std::make_shared<Bezier>(std::vector<std::pair<double, double>>());
// }

// Compute binomial coefficients
std::vector<double> compute_binomial_coefficients(int n) {
  std::vector<double> coeffs(n + 1, 1.0);
  for (int k = 1; k <= n; ++k) {
    coeffs[k] = coeffs[k - 1] * (n - k + 1) / k;
  }
  return coeffs;
}

// Sample points uniformly along a curve
void sample_curve(std::shared_ptr<Curve> curve, int num_samples,
                  std::vector<std::pair<double, double>>& sampled_points,
                  std::vector<double>& t_values) {
  UniformDistanceSampler sampler(curve, num_samples);
  sampled_points.clear();
  t_values.clear();

  for (int i = 0; i < num_samples; ++i) {
    double t = static_cast<double>(i) / (num_samples - 1);
    sampled_points.push_back(sampler(t));
    t_values.push_back(t);
  }
}

// Initialize control points
void initialize_control_points(
    const std::vector<std::pair<double, double>>& sampled_points,
    int control_points_count,
    std::vector<std::pair<double, double>>& control_points) {
  int n = sampled_points.size();
  control_points.resize(control_points_count);
  for (int i = 0; i < control_points_count; ++i) {
    double t = static_cast<double>(i) / (control_points_count - 1);
    int idx = static_cast<int>(t * (n - 1));
    control_points[i] = sampled_points[idx];
  }
}

// Compute total squared error
double compute_total_error(Bezier& bezier,
                           const std::vector<std::pair<double, double>>& points,
                           const std::vector<double>& t_values) {
  double total_error = 0.0;
  for (size_t i = 0; i < points.size(); ++i) {
    auto bezier_point = bezier(t_values[i]);
    double dx = bezier_point.first - points[i].first;
    double dy = bezier_point.second - points[i].second;
    double error = dx * dx + dy * dy;
    total_error += error;
  }
  return total_error;
}

// Fit a Bezier curve using the LM algorithm
std::shared_ptr<Bezier> fit_bezier_curve(
    const std::vector<std::pair<double, double>>& sampled_points,
    const std::vector<double>& t_values, int control_points_count,
    double error_tolerance, int max_iterations) {
  int n = sampled_points.size();
  int degree = control_points_count - 1;

  // Compute binomial coefficients
  std::vector<double> binomial_coeffs = compute_binomial_coefficients(degree);

  // Initialize control points
  std::vector<std::pair<double, double>> control_points;
  initialize_control_points(sampled_points, control_points_count,
                            control_points);

  // Flatten control points into parameter vector
  Eigen::VectorXd params(2 * control_points_count);
  for (int i = 0; i < control_points_count; ++i) {
    params(2 * i) = control_points[i].first;
    params(2 * i + 1) = control_points[i].second;
  }

  double lambda = 1e-3;
  int iter = 0;
  double prev_error = std::numeric_limits<double>::max();

  while (iter < max_iterations) {
    // Create Bezier object using current parameters
    for (int i = 0; i < control_points_count; ++i) {
      control_points[i].first = params(2 * i);
      control_points[i].second = params(2 * i + 1);
    }
    Bezier bezier(control_points);

    Eigen::VectorXd r(2 * n);
    Eigen::MatrixXd J(2 * n, 2 * control_points_count);

    // Compute residuals and Jacobian matrix
    for (int i = 0; i < n; ++i) {
      double t = t_values[i];

      // Compute Bernstein basis functions
      std::vector<double> bernstein_basis(control_points_count);
      double one_minus_t = 1.0 - t;
      for (int j = 0; j <= degree; ++j) {
        bernstein_basis[j] = binomial_coeffs[j] *
                             std::pow(one_minus_t, degree - j) * std::pow(t, j);
      }

      // Compute Bezier curve point at t
      auto bezier_point = bezier(t);

      // Compute residuals
      r(2 * i) = bezier_point.first - sampled_points[i].first;
      r(2 * i + 1) = bezier_point.second - sampled_points[i].second;

      // Fill Jacobian matrix
      for (int j = 0; j < control_points_count; ++j) {
        // Partial derivative with respect to x
        J(2 * i, 2 * j) = bernstein_basis[j];
        J(2 * i, 2 * j + 1) = 0;
        // Partial derivative with respect to y
        J(2 * i + 1, 2 * j) = 0;
        J(2 * i + 1, 2 * j + 1) = bernstein_basis[j];
      }
    }

    // Compute Hessian approximation and parameter update
    Eigen::MatrixXd H =
        J.transpose() * J +
        lambda * Eigen::MatrixXd::Identity(2 * control_points_count,
                                           2 * control_points_count);
    Eigen::VectorXd dp = -H.ldlt().solve(J.transpose() * r);

    if (dp.norm() < 1e-6) {
      break;  // Convergence achieved
    }

    Eigen::VectorXd new_params = params + dp;

    // Compute error with new parameters
    std::vector<std::pair<double, double>> new_control_points(
        control_points_count);
    for (int i = 0; i < control_points_count; ++i) {
      new_control_points[i].first = new_params(2 * i);
      new_control_points[i].second = new_params(2 * i + 1);
    }
    Bezier new_bezier(new_control_points);

    double new_error =
        compute_total_error(new_bezier, sampled_points, t_values);

    if (new_error < prev_error) {
      // Accept update and reduce lambda
      params = new_params;
      prev_error = new_error;
      lambda *= 0.8;
    } else {
      // Reject update and increase lambda
      lambda *= 2.0;
    }

    // Check if error tolerance is reached
    if (std::sqrt(new_error / n) < error_tolerance) {
      break;
    }

    ++iter;
  }

  // Create final Bezier object with optimized parameters
  for (int i = 0; i < control_points_count; ++i) {
    control_points[i].first = params(2 * i);
    control_points[i].second = params(2 * i + 1);
  }
  auto final_bezier = std::make_shared<Bezier>(control_points);

  return final_bezier;
}

// Main function: Fit a curve to a single Bezier curve
std::shared_ptr<Bezier> fit_curve_to_bezier(std::shared_ptr<Curve> curve,
                                            int num_samples, int degree,
                                            double error_tolerance,
                                            int max_iterations) {
  int num_control_points = degree + 1;
  // Sample the curve
  std::vector<std::pair<double, double>> sampled_points;
  std::vector<double> t_values;
  sample_curve(curve, num_samples, sampled_points, t_values);

  // Fit Bezier curve using LM algorithm
  auto bezier = fit_bezier_curve(sampled_points, t_values, num_control_points,
                                 error_tolerance, max_iterations);

  return bezier;
}

// Compute error between two curves
double compute_curve_error(std::shared_ptr<Curve> a, std::shared_ptr<Curve> b,
                           int num_samples) {
  std::vector<std::pair<double, double>> sampled_points_a;
  std::vector<std::pair<double, double>> sampled_points_b;
  std::vector<double> t_values;

  sample_curve(a, num_samples, sampled_points_a, t_values);
  sample_curve(b, num_samples, sampled_points_b, t_values);

  double total_error = 0.0;
  for (size_t i = 0; i < sampled_points_a.size(); ++i) {
    double dx = sampled_points_a[i].first - sampled_points_b[i].first;
    double dy = sampled_points_a[i].second - sampled_points_b[i].second;
    total_error += dx * dx + dy * dy;
  }

  return std::sqrt(total_error / sampled_points_a.size());
}

std::vector<std::shared_ptr<Bezier>> fit_curve_to_beziers(
    std::shared_ptr<Curve> curve, double error_tolerance, int max_iterations) {
  return std::vector<std::shared_ptr<Bezier>>();
}