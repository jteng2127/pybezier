# from setuptools import setup, Extension
# import pybind11

# module = Extension('example', sources=['example.cpp'])

# setup(
#     name='example',
#     version='1.0',
#     ext_modules=[module],
#     include_dirs=[pybind11.get_include()],
# )
from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "pybezier.cpp.bezier",
        ["pybezier/cpp/bezier.cpython-312-darwin.so"],
    ),
]

setup(
    name="pybezier_library",
    version="0.1",
    packages=["pybezier"],
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)

