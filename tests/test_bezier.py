import pytest
from pybezier import Bezier

def test_bezier_initialization():
    # 測試 Bezier 類別是否正確初始化
    control_points = [(0.0, 0.0), (1.0, 2.0), (2.0, 0.0)]
    bezier = Bezier(control_points)
    
    # 驗證控制點數量
    assert len(bezier.control_points) == 3, "控制點數量不正確"
    
    # 驗證每個控制點的值
    assert bezier.control_points[0] == (0.0, 0.0), "第一個控制點錯誤"
    assert bezier.control_points[1] == (1.0, 2.0), "第二個控制點錯誤"
    assert bezier.control_points[2] == (2.0, 0.0), "第三個控制點錯誤"

def test_bezier_call():
    # 測試 Bezier 類別的 __call__ 方法
    control_points = [(0.0, 0.0), (1.0, 2.0), (2.0, 0.0)]
    bezier = Bezier(control_points)
    
    # 測試 t=0, t=0.5, t=1 對應的點是否合理
    point_start = bezier(0.0)
    point_middle = bezier(0.5)
    point_end = bezier(1.0)
    
    # 驗證邊界點
    assert point_start == (0.0, 0.0), "t=0 時返回的點不正確"
    assert point_end == (2.0, 0.0), "t=1 時返回的點不正確"
    
    # 中間點可以進一步檢查是否合理（依據具體計算）
    assert isinstance(point_middle, tuple) and len(point_middle) == 2, "t=0.5 返回的點格式不正確"
