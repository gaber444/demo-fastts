#include "functions.h"
#include <algorithm>
#include <cmath>
#include <numeric>

namespace functions {

// Rolling statistics
py::array_t<double> rolling_mean(DoubleArray data, std::size_t window) {
  const size_t n = data.size();
  if (window == 0 || window > n)
    throw std::runtime_error("Invalid window size");

  auto result = py::array_t<double>(n - window + 1);
  const double *data_ptr = data.data();
  double *result_ptr = result.mutable_data();
  {
    py::gil_scoped_release release; // Release GIL for CPU-bound computation
    double window_sum = 0.0;
    const double inv_window = 1.0 / static_cast<double>(window);

    for (size_t i = 0; i < window; ++i) {
      window_sum += data_ptr[i];
    }
    result_ptr[0] = window_sum * inv_window;

    for (size_t i = window; i < n; ++i) {
      window_sum += data_ptr[i] - data_ptr[i - window];
      result_ptr[i - window + 1] = window_sum * inv_window;
    }
  }
  return result;
}

py::array_t<double> rolling_std(DoubleArray data, std::size_t window) {
  const size_t n = data.size();
  if (window == 0 || window > n)
    throw std::runtime_error("Invalid window size");

  auto result = py::array_t<double>(n - window + 1);
  const double *data_ptr = data.data();
  double *result_ptr = result.mutable_data();
  {
    py::gil_scoped_release release; // Release GIL for CPU-bound computation
    double window_sum = 0.0;
    double window_sum_sq = 0.0;
    const double inv_window = 1.0 / static_cast<double>(window);

    for (size_t i = 0; i < window; ++i) {
      const double v = data_ptr[i];
      window_sum += v;
      window_sum_sq += v * v;
    }

    for (size_t out = 0, i = window;; ++out, ++i) {
      const double mean = window_sum * inv_window;
      double variance = window_sum_sq * inv_window - mean * mean;
      if (variance < 0.0)
        variance = 0.0;
      result_ptr[out] = std::sqrt(variance);

      if (i == n)
        break;

      const double new_val = data_ptr[i];
      const double old_val = data_ptr[i - window];
      window_sum += new_val - old_val;
      window_sum_sq += new_val * new_val - old_val * old_val;
    }
  }

  return result;
}

py::array_t<double> rolling_zscore(DoubleArray data, std::size_t window) {
  const size_t n = data.size();
  if (window == 0 || window > n) {
    throw std::runtime_error("Invalid window size");
  }

  auto result = py::array_t<double>(n - window + 1);
  const double *data_ptr = data.data();
  double *result_ptr = result.mutable_data();

  {
    py::gil_scoped_release release; // Release GIL for CPU-bound computation
    double window_sum = 0.0;
    double window_sum_sq = 0.0;
    const double inv_window = 1.0 / static_cast<double>(window);

    for (size_t i = 0; i < window; ++i) {
      const double v = data_ptr[i];
      window_sum += v;
      window_sum_sq += v * v;
    }

    for (size_t out = 0, i = window;; ++out, ++i) {
      const double mean = window_sum * inv_window;
      double variance = window_sum_sq * inv_window - mean * mean;
      if (variance < 0.0)
        variance = 0.0;

      const double stddev = std::sqrt(variance);
      const double x = data_ptr[out + window - 1];
      result_ptr[out] = (stddev != 0.0) ? (x - mean) / stddev : 0.0;

      if (i == n)
        break;

      const double new_val = data_ptr[i];
      const double old_val = data_ptr[i - window];
      window_sum += new_val - old_val;
      window_sum_sq += new_val * new_val - old_val * old_val;
    }
  }
  return result;
}

py::array_t<double> rolling_min(DoubleArray data, std::size_t window) {
  const size_t n = data.size();
  if (window == 0 || window > n) {
    throw std::runtime_error("Invalid window size");
  }

  auto result = py::array_t<double>(n - window + 1);
  const double *in = data.data();
  double *out = result.mutable_data();
  {
    py::gil_scoped_release release; // Release GIL for CPU-bound computation
    std::deque<size_t> dq;

    for (size_t i = 0; i < n; ++i) {
      while (!dq.empty() && dq.front() + window <= i) {
        dq.pop_front();
      }

      while (!dq.empty() && in[dq.back()] >= in[i]) {
        dq.pop_back();
      }

      dq.push_back(i);

      if (i + 1 >= window) {
        out[i - window + 1] = in[dq.front()];
      }
    }
  }
  return result;
}

py::array_t<double> rolling_max(DoubleArray data, std::size_t window) {
  const size_t n = data.size();
  if (window == 0 || window > n) {
    throw std::runtime_error("Invalid window size");
  }

  auto result = py::array_t<double>(n - window + 1);
  const double *in = data.data();
  double *out = result.mutable_data();
  {
    py::gil_scoped_release release; // Release GIL for CPU-bound computation
    std::deque<size_t> dq;

    for (size_t i = 0; i < n; ++i) {
      while (!dq.empty() && dq.front() + window <= i) {
        dq.pop_front();
      }

      while (!dq.empty() && in[dq.back()] <= in[i]) {
        dq.pop_back();
      }

      dq.push_back(i);

      if (i + 1 >= window) {
        out[i - window + 1] = in[dq.front()];
      }
    }
  }
  return result;
}
// Transformations
py::array_t<double> diff(DoubleArray data) {
  const size_t n = data.size();
  if (n < 2) {
    return py::array_t<double>(0);
  }

  auto result = py::array_t<double>(n - 1);
  const double *in = data.data();
  double *out = result.mutable_data();
  {
    py::gil_scoped_release release; // Release GIL for CPU-bound computation

    for (size_t i = 0; i < n - 1; ++i) {
      out[i] = in[i + 1] - in[i];
    }
  }
  return result;
}

py::array_t<double> pct_return(DoubleArray data) {
  const size_t n = data.size();
  if (n < 2) {
    return py::array_t<double>(0);
  }

  auto result = py::array_t<double>(n - 1);
  const double *in = data.data();
  double *out = result.mutable_data();
  {
    py::gil_scoped_release release; // Release GIL for CPU-bound computation
    for (size_t i = 0; i < n - 1; ++i) {
      const double prev = in[i];
      out[i] = (prev != 0.0) ? ((in[i + 1] - prev) / prev) * 100.0 : 0.0;
    }
  }

  return result;
}
// Aggregation
py::array_t<double> bucket_mean(DoubleArray data, std::size_t bucket_size) {
  const size_t n = data.size();
  if (bucket_size == 0) {
    throw std::runtime_error("Invalid bucket size");
  }

  const size_t out_size = (n + bucket_size - 1) / bucket_size;
  auto result = py::array_t<double>(out_size);

  const double *in = data.data();
  double *out = result.mutable_data();
  {
    py::gil_scoped_release release; // Release GIL for CPU-bound computation
    const double inv_bucket = 1.0 / static_cast<double>(bucket_size);

    size_t out_idx = 0;
    size_t i = 0;

    for (; i + bucket_size <= n; i += bucket_size, ++out_idx) {
      double sum = 0.0;
      for (size_t j = 0; j < bucket_size; ++j) {
        sum += in[i + j];
      }
      out[out_idx] = sum * inv_bucket;
    }

    if (i < n) {
      double sum = 0.0;
      const size_t rem = n - i;
      for (size_t j = i; j < n; ++j) {
        sum += in[j];
      }
      out[out_idx] = sum / static_cast<double>(rem);
    }
  }
  return result;
}

} // namespace functions