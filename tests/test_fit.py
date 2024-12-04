import pytest
from pybezier import Bezier, SampledCurve, fit_curve_to_bezier, fit_curve_to_beziers


def test_fit_curve_to_bezier():
    curve = SampledCurve([(0.0, 0.0), (1.0, 2.0), (2.0, 0.0)])
    bezier = fit_curve_to_bezier(curve)
    assert isinstance(bezier, Bezier), "fit_bezier_curve 應返回 Bezier 實例"


def test_fit_curve_to_beziers():
    curve = SampledCurve([(0.0, 0.0), (1.0, 2.0), (2.0, 0.0)])
    beziers = fit_curve_to_beziers(curve)
    assert all(
        isinstance(b, Bezier) for b in beziers
    ), "fit_bezier_curves 應返回 Bezier 實例列表"
