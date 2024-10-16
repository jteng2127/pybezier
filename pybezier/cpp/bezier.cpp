#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

namespace py = pybind11;

std::pair<double, double> compute_bezier(const std::vector<std::pair<double, double>>& points, double t) {
    std::vector<std::pair<double, double>> tmp = points;
    while (tmp.size() > 1) {
        std::vector<std::pair<double, double>> next;
        for (size_t i = 0; i < tmp.size() - 1; ++i) {
            double x = (1 - t) * tmp[i].first + t * tmp[i + 1].first;
            double y = (1 - t) * tmp[i].second + t * tmp[i + 1].second;
            next.emplace_back(x, y);
        }
        tmp = next;
    }
    return tmp[0];
}

PYBIND11_MODULE(bezier, m) {
    m.def("compute_bezier", &compute_bezier, "Compute a Bezier curve point");
}
