import matplotlib.pyplot as plt
from pybezier import compute_bezier

def plot_bezier(points, num_points=100):
    t_values = [i / (num_points - 1) for i in range(num_points)]
    curve_points = [compute_bezier(points, t) for t in t_values]
    x_vals, y_vals = zip(*curve_points)
    
    plt.plot(x_vals, y_vals, label="Bezier Curve")
    x_ctrl, y_ctrl = zip(*points)
    plt.scatter(x_ctrl, y_ctrl, color="red", label="Control Points")
    plt.legend()
    plt.show()

if __name__ == "__main__":
    control_points = [(0, 0), (1, 2), (3, 3)]
    plot_bezier(control_points)
