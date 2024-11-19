import numpy as np
import matplotlib.pyplot as plt
from pybezier import Bezier

def rdp(points, epsilon):
    """
    Ramer-Douglas-Peucker algorithm to simplify a polyline.
    :param points: List of points (2D coordinates).
    :param epsilon: Distance threshold.
    :return: Simplified polyline as a list of points.
    """
    # Find the point with the maximum distance from the line connecting the endpoints
    dmax = 0.0
    index = 0
    start, end = points[0], points[-1]
    for i in range(1, len(points) - 1):
        d = np.abs(np.cross(end - start, points[i] - start) / np.linalg.norm(end - start))
        if d > dmax:
            index, dmax = i, d

    # If the max distance is greater than epsilon, recursively simplify
    if dmax > epsilon:
        # Recursive call
        results1 = rdp(points[:index + 1], epsilon)
        results2 = rdp(points[index:], epsilon)
        # Combine the results
        return np.vstack((results1[:-1], results2))
    else:
        return np.array([start, end])

# Generate some random 2D points
np.random.seed(0)
x = np.sort(np.random.rand(50) * 10)
y = np.sin(x) + np.random.normal(0, 0.1, 50)
points = np.column_stack((x, y))

# Simplify the points using the Ramer-Douglas-Peucker algorithm
epsilon = 0.2
simplified_points = rdp(points, epsilon)

bezier = Bezier(simplified_points)
samples = 100
sample_points = [bezier(t) for t in np.linspace(0, 1, samples)]
bx, by = zip(*sample_points)

# Plot and save the figure
plt.figure(figsize=(10, 5))
plt.plot(points[:, 0], points[:, 1], 'b-', label="Original Points")
plt.plot(simplified_points[:, 0], simplified_points[:, 1], 'r-', label="Simplified Points", linewidth=2)
plt.plot(bx, by, 'g-', label="Bezier Curve", linewidth=2)
plt.scatter(points[:, 0], points[:, 1], c='blue', s=10)
plt.scatter(simplified_points[:, 0], simplified_points[:, 1], c='red', s=30)
plt.legend()
plt.title("Ramer-Douglas-Peucker Algorithm")
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.grid(True)
plt.savefig('rdp_simplification.png')
