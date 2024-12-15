import numpy as np
import matplotlib.pyplot as plt
from pybezier import Bezier

plt.rcParams.update({'font.size': 20})

b = Bezier([(0, 0), (1, 6), (2, -10), (3, 6)])
b2 = Bezier([(0.03, 0), (1, 5.9), (2, -10), (2.96, 6.1)])
t_values = np.linspace(0, 1, 100)

plt.figure(figsize=(8, 6))

curve_points = np.array([b(t) for t in t_values])
x_vals, y_vals = curve_points[:, 0], curve_points[:, 1]
plt.plot(x_vals, y_vals, label="Any Target Curve (100 sample points)", linewidth=8)

curve_points = np.array([b2(t) for t in t_values])
x_vals, y_vals = curve_points[:, 0], curve_points[:, 1]
plt.plot(x_vals, y_vals, label="Cubic Bézier Curve (4 points)", linestyle='--', color='pink', linewidth=5)

plt.legend()
plt.tight_layout()
plt.axis('off')
ax = plt.gca()
for spine in ax.spines.values():
    spine.set_visible(False)

plt.savefig('output/draw.png')