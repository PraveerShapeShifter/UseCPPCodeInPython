import os

from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

# Set SHAPESHIFTER_DEBUG=1 to build the extensions with C++ debug symbols and
# optimizations off, so they can be stepped through at source level:
#
#   $env:SHAPESHIFTER_DEBUG = "1"
#   python setup.py build_ext --inplace --force
#
# Do NOT use `build_ext --debug` on Windows: it defines _DEBUG and links
# against python314_d.lib, which requires a debug build of Python itself.
DEBUG = os.environ.get("SHAPESHIFTER_DEBUG") == "1"

# Settings shared by every extension module. UNICODE/_UNICODE match the
# character set of the MFC/ATL code this project wraps (CString == CStringW).
COMMON = dict(
    include_dirs=["cpp/vendor", "cpp/inc"],
    define_macros=[("UNICODE", None), ("_UNICODE", None)],
    extra_compile_args=["/Zi", "/Od", "/FS"] if DEBUG else [],
    extra_link_args=["/DEBUG"] if DEBUG else [],
)

ext_modules = [
    Pybind11Extension(
        "shapeshifter.maths",
        ["cpp/bindings/maths_bindings.cpp",
         "cpp/vendor/Maths.cpp"],
        **COMMON,
    ),
    Pybind11Extension(
        "shapeshifter.fabric",
        ["cpp/bindings/fabric_bindings.cpp",
         "cpp/vendor/Fabric.cpp"],
        **COMMON,
    ),
]

setup(
    packages=["shapeshifter"],
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
