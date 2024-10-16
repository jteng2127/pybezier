import pybezier.cpp.bezier as bezier_cpp

def compute_bezier(points, t):
    """
    Compute a Bezier curve point using the C++ implementation.

    Args:
        points (list of tuple): List of control points [(x1, y1), (x2, y2), ...].
        t (float): Parameter (0 <= t <= 1) for the curve.

    Returns:
        tuple: The point on the Bezier curve at parameter t.
    """
    return bezier_cpp.compute_bezier(points, t)
