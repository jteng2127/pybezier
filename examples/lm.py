import numpy as np
from scipy.optimize import least_squares
from pybezier import Bezier, UniformDistanceSampler, SampledCurve

# Example data points that you want to fit
np.random.seed(2)
x = np.sort(np.random.rand(50) ** 3 * 10)
y = np.sin(x)# + np.random.normal(0, 0.1, 50)
data_points = np.column_stack((x, y))


# Function to compute residuals
def residuals(control_points, data_points):
    # Create Bezier curve with current control points
    # bezier = Bezier(control_points.reshape(-1, 2))
    # t_values = np.linspace(0, 1, len(data_points))  # Generate uniform t values
    # bezier_points = np.array([bezier(t) for t in t_values])
    # target_points = data_points

    # sample some points
    sampled_curve = SampledCurve(data_points)
    bezier = Bezier(control_points.reshape(-1, 2))
    target_curve = UniformDistanceSampler(sampled_curve, 1000)
    bezier_curve = UniformDistanceSampler(bezier, 1000)
    bezier_points = [bezier_curve(t) for t in np.linspace(0, 1, len(data_points))]
    bezier_points = np.array(bezier_points)
    target_points = [target_curve(t) for t in np.linspace(0, 1, len(data_points))]
    target_points = np.array(target_points)

    return (bezier_points - target_points).ravel()


def evaluate(bezier_curve, sampled_curve):
    u_bezier_curve = UniformDistanceSampler(bezier_curve, 10000)
    u_sampled_curve = UniformDistanceSampler(sampled_curve, 10000)
    t_values = np.linspace(0, 1, 1000)
    bezier_points = np.array([u_bezier_curve(t) for t in t_values])
    target_points = np.array([u_sampled_curve(t) for t in t_values])
    return np.linalg.norm(bezier_points - target_points)


# Initial guess for control points
initial_control_points = np.array(
    [
        [0.0, 0.0],
        [1.0, 1.0],
        [2.0, 2.0],
        [3.0, 3.0],
        [4.0, 4.0],
        [5.0, 5.0],
        [6.0, 6.0],
        [7.0, 7.0],
        [8.0, 8.0],
        [9.0, 9.0],
        [10.0, 10.0],
    ]
).ravel()

# Use Levenberg-Marquardt algorithm to optimize control points
result = least_squares(
    residuals,
    initial_control_points,
    args=(data_points,),
    method="lm",
    # verbose=1,
)

# Extract optimized control points
optimized_control_points = result.x.reshape(-1, 2)

# Create the fitted Bezier curve
fitted_bezier = Bezier(optimized_control_points)
uniform_fitted_bezier = UniformDistanceSampler(fitted_bezier, 1000)

print(f"Evaluation: {evaluate(fitted_bezier, SampledCurve(data_points))}")

# Plotting
import matplotlib.pyplot as plt

t_values = np.linspace(0, 1, 300)
fitted_points = np.array([uniform_fitted_bezier(t) for t in t_values])

plt.plot(data_points[:, 0], data_points[:, 1], label="Data Points", color="red")
plt.plot(
    fitted_points[:, 0], fitted_points[:, 1], label="Fitted Bezier Curve", color="blue"
)
# plt.scatter(optimized_control_points[:, 0], optimized_control_points[:, 1], label="Control Points", color='green')
plt.legend()
plt.title("Bezier Curve Fitting using Levenberg-Marquardt Algorithm")
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.grid(True)
plt.savefig("output/lm4.png")
