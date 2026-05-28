#pragma once

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <vector>

namespace py = pybind11;

namespace functions {

/**
 * @brief Alias for a 1-D, C-contiguous, double-precision NumPy array.
 *        pybind11 will forcecast any compatible array to this layout.
 */
using DoubleArray =
    py::array_t<double, py::array::c_style | py::array::forcecast>;

// ---------------------------------------------------------------------------
// Rolling statistics
// ---------------------------------------------------------------------------

/**
 * @brief Compute the rolling arithmetic mean.
 * @param data   1-D array of doubles (length N).
 * @param window Number of elements in the sliding window (must be >= 1).
 * @return 1-D array of length N - window + 1 containing window means.
 */
py::array_t<double> rolling_mean(DoubleArray data, std::size_t window);

/**
 * @brief Compute the rolling population standard deviation.
 * @param data   1-D array of doubles (length N).
 * @param window Number of elements in the sliding window (must be >= 1).
 * @return 1-D array of length N - window + 1 containing window std devs.
 */
py::array_t<double> rolling_std(DoubleArray data, std::size_t window);

/**
 * @brief Compute the rolling z-score of the last element in each window.
 * @details z = (x[i] - mean) / std.  Returns 0 when std == 0.
 * @param data   1-D array of doubles (length N).
 * @param window Number of elements in the sliding window (must be >= 1).
 * @return 1-D array of length N - window + 1 containing z-scores.
 */
py::array_t<double> rolling_zscore(DoubleArray data, std::size_t window);

/**
 * @brief Compute the rolling minimum.
 * @param data   1-D array of doubles (length N).
 * @param window Number of elements in the sliding window (must be >= 1).
 * @return 1-D array of length N - window + 1 containing window minima.
 */
py::array_t<double> rolling_min(DoubleArray data, std::size_t window);

/**
 * @brief Compute the rolling maximum.
 * @param data   1-D array of doubles (length N).
 * @param window Number of elements in the sliding window (must be >= 1).
 * @return 1-D array of length N - window + 1 containing window maxima.
 */
py::array_t<double> rolling_max(DoubleArray data, std::size_t window);

// ---------------------------------------------------------------------------
// Transformations
// ---------------------------------------------------------------------------

/**
 * @brief Compute first-order differences: out[i] = data[i+1] - data[i].
 * @param data 1-D array of doubles (length N).
 * @return 1-D array of length N - 1.
 */
py::array_t<double> diff(DoubleArray data);

/**
 * @brief Compute percentage returns: out[i] = (data[i+1] / data[i] - 1) * 100.
 * @details Returns 0 when data[i] == 0 to avoid division by zero.
 * @param data 1-D array of doubles (length N).
 * @return 1-D array of length N - 1.
 */
py::array_t<double> pct_return(DoubleArray data);

// ---------------------------------------------------------------------------
// Aggregation
// ---------------------------------------------------------------------------

/**
 * @brief Compute the mean of non-overlapping fixed-size buckets.
 * @details The last bucket may be smaller than @p bucket_size if N is not
 *          evenly divisible.
 * @param data        1-D array of doubles (length N).
 * @param bucket_size Number of elements per bucket (must be >= 1).
 * @return 1-D array of length ceil(N / bucket_size).
 */
py::array_t<double> bucket_mean(DoubleArray data, std::size_t bucket_size);

} // namespace functions