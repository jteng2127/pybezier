import pytest
from pybezier import SampledCurve

def test_sampled_curve_initialization():
    # 測試 SampledCurve 類別是否正確初始化
    sampled_points = [(0.0, 0.0), (1.0, 1.0), (2.0, 0.0)]
    sampled_curve = SampledCurve(sampled_points)
    
    # 驗證取樣點數量
    assert len(sampled_curve.sampled_points) == 3, "取樣點數量不正確"
    
    # 驗證每個取樣點的值
    assert sampled_curve.sampled_points[0] == (0.0, 0.0), "第一個取樣點錯誤"
    assert sampled_curve.sampled_points[1] == (1.0, 1.0), "第二個取樣點錯誤"
    assert sampled_curve.sampled_points[2] == (2.0, 0.0), "第三個取樣點錯誤"

def test_sampled_curve_call():
    # 測試 SampledCurve 類別的 __call__ 方法
    sampled_points = [(0.0, 0.0), (1.0, 1.0), (2.0, 0.0)]
    sampled_curve = SampledCurve(sampled_points)
    
    # 測試 t=0, t=0.5, t=1 對應的點是否合理
    point_start = sampled_curve(0.0)
    point_middle = sampled_curve(0.5)
    point_end = sampled_curve(1.0)
    
    # 驗證邊界點
    assert point_start == (0.0, 0.0), "t=0 時返回的點不正確"
    assert point_end == (2.0, 0.0), "t=1 時返回的點不正確"
    
    # 中間點可以進一步檢查是否合理
    assert isinstance(point_middle, tuple) and len(point_middle) == 2, "t=0.5 返回的點格式不正確"
