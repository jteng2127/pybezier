import numpy as np
import matplotlib.pyplot as plt
from pybezier import Bezier, UniformDistanceSampler, fit_curve_to_beziers

plt.rcParams.update({'font.size': 20})

s = Bezier([(2, 0), (-1, 0), (1, 8), (2, -10), (3, 6), (4, 8), (-1, 3), (2, 2)])
s = UniformDistanceSampler(s, 1000)
b = fit_curve_to_beziers(s, num_bezier_curves=5, degree=3)

# b2 = Bezier([(0.03, 0), (1, 5.9), (2, -10), (2.95, 6)])
t_values = np.linspace(0, 1, 1000)

plt.figure(figsize=(9, 6))

curve_points = np.array([s(t) for t in t_values])
segements = 5
for i in range(segements):
    length = len(curve_points)
    segment_points = curve_points[length//segements*i:length//segements*(i+1)]
    x_vals, y_vals = segment_points[:, 0], segment_points[:, 1]
    plt.plot(x_vals, y_vals, label=f"Target Segment {i+1}", linewidth=8)

curve_points = np.array([b(t) for t in t_values])
x_vals, y_vals = curve_points[:, 0], curve_points[:, 1]
plt.plot(x_vals, y_vals, label="5 Cubic Bézier Curves", linestyle="--", color='pink', linewidth=5)

plt.legend()
plt.tight_layout()
plt.axis('off')
x_min, x_max = plt.xlim()
plt.xlim(x_min-1, x_max)
ax = plt.gca()
for spine in ax.spines.values():
    spine.set_visible(False)

plt.savefig('output/draw2.png')