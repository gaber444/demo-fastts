# FastTS

> **Speed Up Python With C++**
>
> FastTS demonstrates how computational bottlenecks in Python can be accelerated using optimized C++ and pybind11 while keeping a familiar Python interface.

---

## 🚀 What Is FastTS?

FastTS is a performance-focused demo project exploring high-performance C++/Python integration.

The goal is simple:

✔ Keep the Python interface
✔ Move heavy computation into optimized C++
✔ Reduce runtime significantly

The project focuses on time-series processing, but the same approach applies broadly to:

* financial calculations
* feature engineering
* signal processing
* numerical workloads
* CPU-heavy Python applications

This repository demonstrates the workflow:

1. Identify bottlenecks
2. Rewrite expensive operations in optimized C++
3. Expose them through pybind11
4. Keep the Python API simple

---

## ⚡ Performance Benchmark

The following benchmark compares FastTS (C++/pybind11) against equivalent implementations in NumPy and Pandas.

### Setup

* Dataset size: `N = 5,000,000`
* Rolling window: `1000`
* Bucket size: `60`
* Timing: median of multiple runs

> Results within ±5% versus NumPy are considered a tie.

| Function       | C++ (FastTS) |    NumPy |   Pandas | Speedup vs NumPy | Speedup vs Pandas |
| -------------- | -----------: | -------: | -------: | ---------------: | ----------------: |
| rolling_mean   |      13.3 ms |  40.3 ms | 156.6 ms |            3.03× |            11.74× |
| rolling_std    |      19.2 ms | 132.1 ms | 199.3 ms |            6.89× |            10.39× |
| rolling_zscore |      25.8 ms | 196.5 ms | 290.8 ms |            7.61× |            11.25× |
| diff           |       8.6 ms |   8.8 ms |  73.6 ms |            ~1.0× |             8.58× |
| pct_return     |      11.0 ms |  67.2 ms |  56.3 ms |            6.10× |             5.10× |
| bucket_mean    |       3.7 ms |   3.6 ms | 116.1 ms |            ~1.0× |            31.18× |

---

## 🧠 Key Takeaways

* Rolling analytics are significantly faster than equivalent NumPy and Pandas implementations
* Performance gains come from optimized algorithms and native C++ execution
* Python API remains simple and familiar

---

## 📦 Downloads

Prebuilt demo wheels are available here:

[Download FastTS Releases](https://github.com/gaber444/demo-fastts/releases)

Supported platforms:

* macOS
* Windows
* Ubuntu

---

## 🔬 Example

```python
import numpy as np
from fastts_demo import functions

x = np.random.random(1_000_000)

mean = functions.rolling_mean(x, 1000)
std = functions.rolling_std(x, 1000)
zscore = functions.rolling_zscore(x, 1000)

returns = functions.pct_return(x)
diff = functions.diff(x)
```

---

## 📧 Contact

If you'd like to discuss the project, optimization approaches, or collaboration:

* Email: [benedik.benedik500@gmail.com](mailto:benedik.benedik500@gmail.com)
* GitHub: https://github.com/gaber444
* LinkedIn: https://www.linkedin.com/in/gaber-benedik-b20a8028b/

---

## 🔗 How It Works

1. Profile slow Python code
2. Rewrite bottlenecks in optimized C++
3. Expose through pybind11
4. Keep the Python API unchanged

---

## 📄 License

MIT
