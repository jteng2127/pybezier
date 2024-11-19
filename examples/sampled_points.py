from pybezier import UniformDistanceSampler, SampledCurve
import numpy as np
import matplotlib.pyplot as plt

np.random.seed(2)
x = np.sort(np.random.rand(50) ** 3 * 10)
y = np.sin(x) + np.random.normal(0, 0.1, 50)
data_points = np.column_stack((x, y))

curve = SampledCurve(data_points)

uds = UniformDistanceSampler(curve, 1000)

uniform_points = [uds(t) for t in np.linspace(0, 1, 100)]
ux, uy = zip(*uniform_points)
# show points with line
plt.scatter(x, y, label="Data Points", color='red', zorder=-1, marker='x', s=50)
plt.plot(ux, uy, label="Uniform Distance Sampling", color='blue', marker='.', markersize=5)
plt.savefig('output/sampled_points.png')
