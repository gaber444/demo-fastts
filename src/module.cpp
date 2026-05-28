#include "functions.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

// Fallback in case someone builds without CMake/that define
#ifndef PY_MODULE_NAME
#define PY_MODULE_NAME _fastts_demo // change name
#endif

// Declaration of binding helpers
namespace functions_bindings {
void bind_functions(py::module_ &m);
}
/**
 * @brief Construct a new pybind11 module object, ime _zacetek_pybind
 * je pomemben mora biti enak kot ime knjižnice
 *
 */
PYBIND11_MODULE(PY_MODULE_NAME, m, py::mod_gil_not_used()) {
  m.doc() = "FastTS C++ core module: functions";

  // Submodule for functions
  auto functions = m.def_submodule("functions", "Functions related module");
  functions_bindings::bind_functions(functions);

  // Next submodule
}