import numpy as np
from numpy.typing import NDArray

# Rolling statistics

def rolling_mean(data: NDArray[np.float64], window: int) -> NDArray[np.float64]:
    """Compute the rolling arithmetic mean.

    Args:
        data: 1-D array of doubles (length N).
        window: Number of elements in the sliding window (>= 1).

    Returns:
        1-D array of length N - window + 1 containing window means.
    """
    ...

def rolling_std(data: NDArray[np.float64], window: int) -> NDArray[np.float64]:
    """Compute the rolling population standard deviation.

    Args:
        data: 1-D array of doubles (length N).
        window: Number of elements in the sliding window (>= 1).

    Returns:
        1-D array of length N - window + 1 containing window std devs.
    """
    ...

def rolling_zscore(data: NDArray[np.float64], window: int) -> NDArray[np.float64]:
    """Compute the rolling z-score of the last element in each window.

    z = (x[i] - mean) / std. Returns 0 where std == 0.

    Args:
        data: 1-D array of doubles (length N).
        window: Number of elements in the sliding window (>= 1).

    Returns:
        1-D array of length N - window + 1 containing z-scores.
    """
    ...

def rolling_min(data: NDArray[np.float64], window: int) -> NDArray[np.float64]:
    """Compute the rolling minimum.

    Args:
        data: 1-D array of doubles (length N).
        window: Number of elements in the sliding window (>= 1).

    Returns:
        1-D array of length N - window + 1 containing window minima.
    """
    ...

def rolling_max(data: NDArray[np.float64], window: int) -> NDArray[np.float64]:
    """Compute the rolling maximum.

    Args:
        data: 1-D array of doubles (length N).
        window: Number of elements in the sliding window (>= 1).

    Returns:
        1-D array of length N - window + 1 containing window maxima.
    """
    ...

# Transformations

def diff(data: NDArray[np.float64]) -> NDArray[np.float64]:
    """Compute first-order differences: out[i] = data[i+1] - data[i].

    Args:
        data: 1-D array of doubles (length N).

    Returns:
        1-D array of length N - 1.
    """
    ...

def pct_return(data: NDArray[np.float64]) -> NDArray[np.float64]:
    """Compute percentage returns: out[i] = (data[i+1] / data[i] - 1) * 100.

    Returns 0 where data[i] == 0 to avoid division by zero.

    Args:
        data: 1-D array of doubles (length N).

    Returns:
        1-D array of length N - 1.
    """
    ...

# Aggregation

def bucket_mean(data: NDArray[np.float64], bucket_size: int) -> NDArray[np.float64]:
    """Compute the mean of non-overlapping fixed-size buckets.

    The last bucket may be smaller than bucket_size if N is not evenly divisible.

    Args:
        data: 1-D array of doubles (length N).
        bucket_size: Number of elements per bucket (>= 1).

    Returns:
        1-D array of length ceil(N / bucket_size).
    """
    ...
