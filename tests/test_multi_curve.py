import pytest
from pybezier import MultiCurve, SampledCurve


def test_multi_curve_call():
    curves = [
        SampledCurve([(0.0, 0.0), (1.0, 2.0), (2.0, 0.0)]),
        SampledCurve([(2.0, 0.0), (3.0, 2.0), (4.0, 0.0)]),
    ]
    multi_curve = MultiCurve(curves)

    point_start = multi_curve(0.0)
    point_middle = multi_curve(0.5)
    point_end = multi_curve(1.0)

    assert point_start == (0.0, 0.0), "t=0 時返回的點不正確"
    assert point_middle == (2.0, 0.0), "t=0.5 時返回的點不正確"
    assert point_end == (4.0, 0.0), "t=1 時返回的點不正確"
