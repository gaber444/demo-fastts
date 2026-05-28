#include "functions.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace functions_bindings {
void bind_functions(py::module_ &m) {

  // Rolling statistics
  m.def("rolling_mean", &functions::rolling_mean,
        "Calculate rolling mean over a window", py::arg("data"),
        py::arg("window"));

  m.def("rolling_std", &functions::rolling_std,
        "Calculate rolling standard deviation over a window", py::arg("data"),
        py::arg("window"));

  m.def("rolling_zscore", &functions::rolling_zscore,
        "Calculate rolling z-score over a window", py::arg("data"),
        py::arg("window"));

  m.def("rolling_min", &functions::rolling_min,
        "Calculate rolling minimum over a window", py::arg("data"),
        py::arg("window"));

  m.def("rolling_max", &functions::rolling_max,
        "Calculate rolling maximum over a window", py::arg("data"),
        py::arg("window"));

  // Transformations
  m.def("diff", &functions::diff, "Calculate first-order differences",
        py::arg("data"));

  m.def("pct_return", &functions::pct_return, "Calculate percentage returns",
        py::arg("data"));

  // Aggregation
  m.def("bucket_mean", &functions::bucket_mean,
        "Calculate mean for each bucket (aggregation)", py::arg("data"),
        py::arg("bucket_size"));
}
} // namespace functions_bindings