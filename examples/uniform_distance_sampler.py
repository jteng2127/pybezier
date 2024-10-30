import matplotlib.pyplot as plt
from _pybezier import Bezier, UniformDistanceSampler

fig, ax = plt.subplots(2, 4, figsize=(16, 8))
plt.tight_layout(rect=[0, 0, 1, 0.9])
ax = ax.flatten()

control_points = [(1, 0), (3, -10), (0, -10), (3, 6)]
bezier = Bezier(control_points)
uds = UniformDistanceSampler(bezier, 2000)

samples = 70

sample_points = [bezier(t) for t in [i / (samples - 1) for i in range(samples)]]
x, y= zip(*sample_points)
ax[0].scatter(x, y, marker="o", s=3, color="red")
ax[0].title.set_text("Naive samples by t")

uds.samples = 5
sample_points = [uds(t) for t in [i / (samples - 1) for i in range(samples)]]
x, y= zip(*sample_points)
ax[1].scatter(x, y, marker="o", s=3, color="red")
# naive samples
sample_points = [bezier(t) for t in [i / (uds.samples - 1) for i in range(uds.samples)]]
x, y= zip(*sample_points)
ax[1].scatter(x, y, marker="o", s=10, color="blue", zorder=0)
# hist
ax[5].hist(uds.cumulative_distances, bins=len(uds.cumulative_distances), density=True, cumulative=True, alpha=0.6, color='blue', rwidth=1.0)
ax[1].title.set_text("Uniform distance samples\nby 5 naive samples")

uds.samples = 20
sample_points = [uds(t) for t in [i / (samples - 1) for i in range(samples)]]
x, y= zip(*sample_points)
ax[2].scatter(x, y, marker="o", s=3, color="red")
# naive samples
sample_points = [bezier(t) for t in [i / (uds.samples - 1) for i in range(uds.samples)]]
x, y= zip(*sample_points)
ax[2].scatter(x, y, marker="o", s=10, color="blue", zorder=0)
# hist
ax[6].hist(uds.cumulative_distances, bins=len(uds.cumulative_distances), density=True, cumulative=True, alpha=0.6, color='blue', rwidth=1.0)
ax[2].title.set_text("Uniform distance samples\nby 20 naive samples")

uds.samples = 10000
sample_points = [uds(t) for t in [i / (samples - 1) for i in range(samples)]]
x, y= zip(*sample_points)
ax[3].scatter(x, y, marker="o", s=3, color="red")
# naive samples
sample_points = [bezier(t) for t in [i / (uds.samples - 1) for i in range(uds.samples)]]
x, y= zip(*sample_points)
ax[3].scatter(x, y, marker="o", s=10, color="blue", zorder=0)
# hist
ax[7].hist(uds.cumulative_distances, bins=len(uds.cumulative_distances), density=True, cumulative=True, alpha=0.6, color='blue', rwidth=1.0)
ax[3].title.set_text("Uniform distance samples\nby 10000 naive samples")

plt.savefig("output/test.png")
print("Output saved to output/test.png")
