# Import the C++ core module, defined in CMakeLists.txt as project(_zacetek_pybind LANGUAGES CXX)
from . import _fastts_demo as _core # change name

# Re-export the submodule so users can do:
# from zacetek_pybind import functions
functions = _core.functions

__all__ = ["functions"]