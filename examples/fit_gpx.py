import gpxpy
import gpxpy.gpx
import matplotlib.pyplot as plt
import numpy as np
from pybezier import (
    Bezier,
    UniformDistanceSampler,
    SampledCurve,
    compute_curve_error,
    fit_curve_to_bezier,
)

# perpare sampled curves, type is SampledCurve
sampled_curves: list[SampledCurve] = []

with open("data/2023-05-11_15-11-56_gpx測試.gpx", "r") as gpx_file:
    gpx = gpxpy.parse(gpx_file)

    for track in gpx.tracks:
        for segment in track.segments:
            points = [(point.longitude, point.latitude) for point in segment.points]
            sampled_curves.append(SampledCurve(points))
            # for point in segment.points:
            #     print(f'Point at ({point.latitude},{point.longitude}) -> {point.elevation}')

plt.figure(figsize=(10, 5))

for curve in sampled_curves:
    # Fitting
    bezier = fit_curve_to_bezier(curve, degree=400, max_iterations=100000)
    bezier_points = [bezier(t) for t in np.linspace(0, 1, 1000)]

    # Compute the error
    for num_samples in [100, 1000, 10000]:
        error = compute_curve_error(bezier, curve, num_samples=num_samples)
        print(f"Error with {num_samples} samples: {error}")

    # Plotting
    plt.plot(*zip(*curve.sampled_points), label="GPX Curve")
    plt.plot(*zip(*bezier_points), label="Fitted Bezier Curve")

ax = plt.gca()
ax.set_aspect("equal", adjustable="datalim")
ax.ticklabel_format(useOffset=False)
plt.tight_layout()
plt.legend()
plt.savefig(f"output/fit_gpx.png")
