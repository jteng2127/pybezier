import pytest
from pybezier import compute_bezier

def test_compute_bezier():
    points = [(0, 0), (1, 2), (3, 3)]
    result = compute_bezier(points, 0.5)
    assert isinstance(result, tuple)
    assert len(result) == 2
    # Additional assertions can be added based on expected values

