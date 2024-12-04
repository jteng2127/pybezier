import numpy as np
from PIL import Image
from scipy.optimize import least_squares
from pybezier import (
    Bezier,
    UniformDistanceSampler,
    SampledCurve,
    fit_curve_to_bezier,
    fit_curve_to_beziers,
)
import os


def png_to_gif(png_folder, gif_output, duration=500):
    """
    Convert a sequence of PNG images to a GIF.

    :param png_folder: Folder containing PNG images
    :param gif_output: Output file path for the GIF
    :param duration: Duration between frames in milliseconds
    """
    # Get all PNG files in the folder, sorted by name
    png_files = sorted(
        [
            os.path.join(png_folder, file)
            for file in os.listdir(png_folder)
            if file.endswith(".png")
        ]
    )

    # Open images
    images = [Image.open(png) for png in png_files]

    # Save as GIF
    if images:
        images[0].save(
            gif_output,
            save_all=True,
            append_images=images[1:],
            duration=duration,
            loop=0,
        )
        print(f"GIF created successfully at {gif_output}")
    else:
        print("No PNG files found in the specified folder.")


# Example data points that you want to fit
np.random.seed(2)
x = np.sort(np.random.rand(50) ** 3 * 10)
y = np.sin(x)  # + np.random.normal(0, 0.1, 50)
data_points = np.column_stack((x, y))


# fit
curve = SampledCurve(data_points)
for i in range(100, 101):
    print(f" ===== iteration {i} =====")
    bezier = fit_curve_to_bezier(UniformDistanceSampler(curve, 1000), max_iterations=i, degree=9)

    uniform_fitted_bezier = UniformDistanceSampler(bezier, 1000)
    print(bezier.control_points)

    # print(f"Evaluation: {evaluate(fitted_bezier, SampledCurve(data_points))}")

    # Plotting
    import matplotlib.pyplot as plt

    t_values = np.linspace(0, 1, 300)
    fitted_points = np.array([uniform_fitted_bezier(t) for t in t_values])
    control_points = np.array(bezier.control_points)

    plt.plot(data_points[:, 0], data_points[:, 1], label="Data Points", color="red")
    plt.plot(
        fitted_points[:, 0],
        fitted_points[:, 1],
        label="Fitted Bezier Curve",
        color="blue",
    )
    # plt.scatter(
    #     control_points[:, 0],
    #     control_points[:, 1],
    #     label="Control Points",
    #     color="green",
    # )
    # plt.scatter(optimized_control_points[:, 0], optimized_control_points[:, 1], label="Control Points", color='green')
    plt.title(f"Bezier Curve Fitting using Levenberg-Marquardt Algorithm {i}")
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.grid(True)
    plt.savefig(f"output/lm/lm{i:03d}.png")
    plt.close()

png_to_gif("output/lm", "output/lm.gif")
