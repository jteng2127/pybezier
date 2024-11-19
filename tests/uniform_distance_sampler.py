import pytest
from pybezier import Bezier, UniformDistanceSampler

def test_uniform_distance_sampler_initialization():
    # 初始化一個 Bezier 曲線
    control_points = [(0.0, 0.0), (1.0, 2.0), (2.0, 0.0)]
    bezier_curve = Bezier(control_points)
    
    # 初始化 UniformDistanceSampler
    sampler = UniformDistanceSampler(bezier_curve, 10)
    
    # 驗證樣本數
    assert sampler.samples == 10, "初始化的樣本數不正確"

def test_uniform_distance_sampler_samples_setter():
    # 初始化 Bezier 曲線
    control_points = [(0.0, 0.0), (1.0, 2.0), (2.0, 0.0)]
    bezier_curve = Bezier(control_points)
    
    # 初始化 UniformDistanceSampler 並設置樣本數
    sampler = UniformDistanceSampler(bezier_curve, 5)
    sampler.setSamples(15)
    
    # 驗證樣本數是否更新正確
    assert sampler.samples == 15, "樣本數 setter 不正確"

def test_uniform_distance_sampler_cumulative_distances():
    # 初始化 Bezier 曲線
    control_points = [(0.0, 0.0), (1.0, 2.0), (2.0, 0.0)]
    bezier_curve = Bezier(control_points)
    
    # 初始化 UniformDistanceSampler
    sampler = UniformDistanceSampler(bezier_curve, 10)
    cumulative_distances = sampler.getCumulativeDistances()
    
    # 檢查累積距離是否計算正確
    assert len(cumulative_distances) == 10, "累積距離數量不正確"
    assert all(isinstance(d, float) for d in cumulative_distances), "累積距離類型應為 float"

def test_uniform_distance_sampler_call():
    # 初始化 Bezier 曲線
    control_points = [(0.0, 0.0), (1.0, 2.0), (2.0, 0.0)]
    bezier_curve = Bezier(control_points)
    
    # 初始化 UniformDistanceSampler
    sampler = UniformDistanceSampler(bezier_curve, 10)
    
    # 測試 t=0, t=0.5, t=1 對應的點是否合理
    point_start = sampler(0.0)
    point_middle = sampler(0.5)
    point_end = sampler(1.0)
    
    # 驗證邊界點
    assert point_start == (0.0, 0.0), "t=0 時返回的點不正確"
    assert point_end == (2.0, 0.0), "t=1 時返回的點不正確"
    
    # 中間點可以進一步檢查是否合理
    assert isinstance(point_middle, tuple) and len(point_middle) == 2, "t=0.5 返回的點格式不正確"
