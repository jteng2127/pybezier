# PyBezier

`PyBezier` is a Python library for calculating Bezier curves.

This library provides an easy-to-use Python interface while leveraging C++ for computational efficiency.

## Problem to Solve

In the fields of Aerodynamics, Fluid mechanics, and Modeling, it's often essential to describe complex curves accurately. One approach involves the use of Bezier curves, which are widely applied in computer graphics because of their smoothness and intuitive control.

The goal is to use multiple third-order (or higher order) Bezier curves to fit the following types of curves:

1. A fourth-order Bezier curve
2. A [NACA 4-digit airfoil](https://zh.wikipedia.org/zh-tw/NACA%E7%BF%BC%E5%9E%8B)
3. Any discretely sampled curve (e.g., [Contour line](https://en.wikipedia.org/wiki/Contour_line))
4. Any curve that can be expressed by a formula (e.g., [Superformula](https://en.wikipedia.org/wiki/Superformula) curve)

## Features

- **Bezier curve calculations**: Compute points on Bezier curves with any number of control points.
- **High-performance**: C++ backend to speed up calculations.
- **Python-friendly**: Simple Python interface that abstracts the complexity of C++.

## Installation

### Prerequisites

- Python 3.x
- `pybind11`
- C++11 compatible compiler
- CMake 3.12 or newer

### Build Instructions

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/pybezier.git
    cd pybezier
    ```
2. Create and navigate to the build directory:
    ```bash
    mkdir build
    cd build
    ```
3. Build the C++ extension:
    ```bash
    cmake ..
    make
    ```

This will build the C++ extension and place it in the correct location for Python to access.

## Usage

Once the C++ extension is built, you can use the library in Python to compute Bezier curves:

```python
from pybezier import compute_bezier

# Define control points
points = [(0, 0), (1, 2), (3, 3)]

# Compute the point on the Bezier curve for t = 0.5
result = compute_bezier(points, 0.5)
print(result)
```

## Testing

This project uses `pytest` for testing. To run the tests:

1. Install `pytest` if you haven't already:
    ```bash
    pip install pytest
    ```

2. Run the tests:
    ```bash
    pytest tests/
    ```