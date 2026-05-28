"""
FastTS Demo — C++ vs NumPy vs Pandas benchmark
==============================================
Demonstrates the performance advantage of the C++ / NumPy-backed
fastts_demo functions over equivalent NumPy and pandas implementations.
"""

import time
import numpy as np
import pandas as pd
from fastts_demo import functions

# ---------------------------------------------------------------------------
# NumPy reference implementations
# ---------------------------------------------------------------------------

def np_rolling_mean(data: np.ndarray, window: int) -> np.ndarray:
    if window <= 0 or window > len(data):
        raise ValueError("Invalid window size")

    csum = np.cumsum(data, dtype=np.float64)
    csum = np.concatenate(([0.0], csum))
    return (csum[window:] - csum[:-window]) / window


def np_rolling_std(data: np.ndarray, window: int) -> np.ndarray:
    if window <= 0 or window > len(data):
        raise ValueError("Invalid window size")

    csum = np.cumsum(data, dtype=np.float64)
    csum2 = np.cumsum(data * data, dtype=np.float64)

    csum = np.concatenate(([0.0], csum))
    csum2 = np.concatenate(([0.0], csum2))

    sum_x = csum[window:] - csum[:-window]
    sum_x2 = csum2[window:] - csum2[:-window]

    mean = sum_x / window
    var = (sum_x2 / window) - (mean * mean)
    var = np.maximum(var, 0.0)

    return np.sqrt(var)


def np_rolling_zscore(data: np.ndarray, window: int) -> np.ndarray:
    if window <= 0 or window > len(data):
        raise ValueError("Invalid window size")

    csum = np.cumsum(data, dtype=np.float64)
    csum2 = np.cumsum(data * data, dtype=np.float64)

    csum = np.concatenate(([0.0], csum))
    csum2 = np.concatenate(([0.0], csum2))

    sum_x = csum[window:] - csum[:-window]
    sum_x2 = csum2[window:] - csum2[:-window]

    mean = sum_x / window
    var = (sum_x2 / window) - (mean * mean)
    var = np.maximum(var, 0.0)
    std = np.sqrt(var)

    last = data[window - 1 :]

    out = np.zeros_like(mean)
    mask = std != 0.0
    out[mask] = (last[mask] - mean[mask]) / std[mask]
    return out


def np_diff(data: np.ndarray) -> np.ndarray:
    return np.diff(data)


def np_pct_return(data: np.ndarray) -> np.ndarray:
    prev = data[:-1]
    curr = data[1:]
    out = np.zeros_like(prev)
    mask = prev != 0.0
    out[mask] = (curr[mask] - prev[mask]) / prev[mask] * 100.0
    return out


def np_bucket_mean(data: np.ndarray, bucket_size: int) -> np.ndarray:
    n_full = len(data) // bucket_size
    head = data[: n_full * bucket_size].reshape(n_full, bucket_size).mean(axis=1)

    if len(data) % bucket_size == 0:
        return head

    tail = np.array([data[n_full * bucket_size :].mean()])
    return np.concatenate([head, tail])


# ---------------------------------------------------------------------------
# Pandas reference implementations
# ---------------------------------------------------------------------------

def pd_rolling_mean(data: np.ndarray, window: int) -> np.ndarray:
    return pd.Series(data).rolling(window).mean().dropna().to_numpy()


def pd_rolling_std(data: np.ndarray, window: int) -> np.ndarray:
    return pd.Series(data).rolling(window).std(ddof=0).dropna().to_numpy()


def pd_rolling_zscore(data: np.ndarray, window: int) -> np.ndarray:
    series = pd.Series(data)
    mean = series.rolling(window).mean()
    std = series.rolling(window).std(ddof=0)
    zscore = ((series - mean) / std).replace([np.inf, -np.inf], 0.0)
    return zscore.iloc[window - 1 :].fillna(0.0).to_numpy()


def pd_diff(data: np.ndarray) -> np.ndarray:
    return pd.Series(data).diff().dropna().to_numpy()


def pd_pct_return(data: np.ndarray) -> np.ndarray:
    returns = pd.Series(data).pct_change().replace([np.inf, -np.inf], 0.0)
    return (returns.iloc[1:].fillna(0.0) * 100.0).to_numpy()


def pd_bucket_mean(data: np.ndarray, bucket_size: int) -> np.ndarray:
    group_ids = np.arange(len(data)) // bucket_size
    return pd.Series(data).groupby(group_ids).mean().to_numpy()


# ---------------------------------------------------------------------------
# Benchmark helper
# ---------------------------------------------------------------------------

def time_fn(fn, *args, runs: int = 10) -> float:
    times = []
    for _ in range(runs):
        t0 = time.perf_counter()
        fn(*args)
        times.append(time.perf_counter() - t0)
    return float(np.median(times))


def warm_up(fn, *args, runs: int = 3):
    for _ in range(runs):
        fn(*args)


def assert_close(name, a, b, atol: float = 1e-9, rtol: float = 1e-7):
    if not np.allclose(a, b, atol=atol, rtol=rtol, equal_nan=True):
        raise AssertionError(f"{name} outputs do not match")


def classify_vs_numpy(cpp_sec: float, np_sec: float) -> str:
    ratio = np_sec / cpp_sec
    if 0.95 <= ratio <= 1.05:
        return "tie with NumPy"
    if ratio > 1.05:
        return "C++ wins"
    return "NumPy wins"


def benchmark3(label: str, fn_cpp, fn_np, fn_pd, *args, runs: int = 10):
    warm_up(fn_cpp, *args)
    warm_up(fn_np, *args)
    warm_up(fn_pd, *args)

    cpp_out = fn_cpp(*args)
    np_out = fn_np(*args)
    pd_out = fn_pd(*args)

    assert_close(label, cpp_out, np_out)
    assert_close(label, cpp_out, pd_out)

    cpp_sec = time_fn(fn_cpp, *args, runs=runs)
    np_sec = time_fn(fn_np, *args, runs=runs)
    pd_sec = time_fn(fn_pd, *args, runs=runs)
    status = classify_vs_numpy(cpp_sec, np_sec)

    print(
        f"  {label:<16} C++: {cpp_sec*1000:8.3f} ms   "
        f"NumPy: {np_sec*1000:8.3f} ms   "
        f"Pandas: {pd_sec*1000:8.3f} ms   "
        f"C++/NumPy: {np_sec / cpp_sec:6.2f}x   "
        f"C++/Pandas: {pd_sec / cpp_sec:6.2f}x   "
        f"[{status}]"
    )


# ---------------------------------------------------------------------------
# Run demo
# ---------------------------------------------------------------------------

N      = 10_000_000
WINDOW = 1_000
BUCKET = 60

print(f"\n{'='*65}")
print(f"  FastTS benchmark  —  N={N:,}  window={WINDOW}  bucket={BUCKET}")
print(f"{'='*65}")
print("  Note: within +/-5% vs NumPy is labeled as a tie")
print(f"{'='*65}")

rng  = np.random.default_rng(42)
data = rng.standard_normal(N) * 10 + 100   # realistic price-like series
data = data.astype(np.float64)

benchmark3("rolling_mean",   lambda d, w: functions.rolling_mean(d, w),   np_rolling_mean,   pd_rolling_mean,   data, WINDOW)
benchmark3("rolling_std",    lambda d, w: functions.rolling_std(d, w),    np_rolling_std,    pd_rolling_std,    data, WINDOW)
benchmark3("rolling_zscore", lambda d, w: functions.rolling_zscore(d, w), np_rolling_zscore, pd_rolling_zscore, data, WINDOW)
benchmark3("diff",           lambda d, _: functions.diff(d),              lambda d, _: np_diff(d),       lambda d, _: pd_diff(d),       data, 0)
benchmark3("pct_return",     lambda d, _: functions.pct_return(d),        lambda d, _: np_pct_return(d), lambda d, _: pd_pct_return(d), data, 0)
benchmark3("bucket_mean",    lambda d, b: functions.bucket_mean(d, b),    np_bucket_mean,    pd_bucket_mean,    data, BUCKET)

print(f"{'='*65}\n")