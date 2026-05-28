# FastTS

> **Speed Up Python With C++**
>
> FastTS demonstrates how computational bottlenecks in Python can be moved into optimized C++ libraries using pybind11 while keeping a familiar Python interface.

---

## 🎯 About This Project

FastTS is a performance-focused project and portfolio piece exploring high-performance C++/Python integration.

The goal is simple:

✔ Keep the Python interface  
✔ Move heavy computation into optimized C++  
✔ Reduce runtime significantly

The example in this repository focuses on time-series processing, but the same idea applies broadly:

- financial calculations
- feature engineering
- numerical processing
- signal processing
- large-scale datasets
- CPU-heavy Python workloads

This project demonstrates the workflow:

1. Identify bottlenecks
2. Move expensive computations into C++
3. Expose them through pybind11
4. Keep the Python API simple

---

## 🚀 Areas I Am Building In

I am currently building projects around:

- 🔧 C++ acceleration for Python applications
- ⚡ Performance optimization and profiling
- 🔌 pybind11 integrations
- 📊 Numerical and time-series processing
- 📈 Large-scale data pipelines

---

## 📋 Potential Use Cases

- Financial analysis
- Machine learning preprocessing
- Scientific computing
- Signal processing
- Large data transformations
- Any CPU-bound Python bottleneck

---

## ⚡ Performance Benchmark

The following benchmark compares FastTS (C++/pybind11) against equivalent implementations in NumPy and Pandas.

**Setup**

- Dataset size: `N = 5,000,000`
- Rolling window: `1000`
- Bucket size: `60`
- Timing: median of multiple runs

> Results within ±5% versus NumPy are considered a tie.

| Function | C++ (FastTS) | NumPy | Pandas | Speedup vs NumPy | Speedup vs Pandas |
|-----------|-------------:|-------:|--------:|-----------------:|------------------:|
| rolling_mean | 13.3 ms | 40.3 ms | 156.6 ms | 3.03× | 11.74× |
| rolling_std | 19.2 ms | 132.1 ms | 199.3 ms | 6.89× | 10.39× |
| rolling_zscore | 25.8 ms | 196.5 ms | 290.8 ms | 7.61× | 11.25× |
| diff | 8.6 ms | 8.8 ms | 73.6 ms | ~1.0× | 8.58× |
| pct_return | 11.0 ms | 67.2 ms | 56.3 ms | 6.10× | 5.10× |
| bucket_mean | 3.7 ms | 3.6 ms | 116.1 ms | ~1.0× | 31.18× |

---

## 🧠 Key Takeaways

- Rolling analytics are significantly faster than equivalent NumPy and Pandas implementations
- Simple vectorized operations are already highly optimized in NumPy
- Performance gains come from algorithm design and moving heavy computation into native C++

---

## 📧 Interested in Connecting?

I am currently exploring high-performance Python and C++ integration projects.

If you're working on performance-heavy workloads or want to discuss optimization approaches:

📧 Email: benedik.benedik500@gmail.com

💼 LinkedIn:
https://www.linkedin.com/in/gaber-benedik-b20a8028b/

🐙 GitHub:
github.com/gaber444

---

## 🔗 How It Works

1. Profile slow code
2. Rewrite bottlenecks in C++
3. Expose through pybind11
4. Keep Python API unchanged

---

## 📄 License

MIT