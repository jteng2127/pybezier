import matplotlib.pyplot as plt
import numpy as np
from pybezier import MultiCurve, SampledCurve


curves = []
for i in range(0, 30, 2):
    curves += [
        SampledCurve([(i, 0), (i + 1, 2), (i + 2, 0)])
    ]
multi_curve = MultiCurve(curves)

# draw
t = np.linspace(0, 1, 10000)
points = np.array([multi_curve(ti) for ti in t])
plt.plot(points[:, 0], points[:, 1])
plt.savefig('output/multi_curve.png')