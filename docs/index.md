# FastTS

> **Speed Up Python With C++**
>
> FastTS is a demo project showing how Python bottlenecks can be accelerated with optimized C++ and pybind11.

## Performance

- Rolling statistics: 3–7× faster than NumPy
- Up to 10–12× faster than Pandas
- Python-style API
- C++ backend

## Downloads

Prebuilt demo wheels are available here:

[Download FastTS releases](https://github.com/gaber444/FastTS/releases)

## Example

```python
import numpy as np
from fastts_demo import functions

x = np.random.random(1_000_000)

mean = functions.rolling_mean(x, 1000)
std = functions.rolling_std(x, 1000)
```

## Contact

If you'd like to discuss the project, performance optimization, or collaboration:

- Email: benedik.benedik500@gmail.com
- GitHub: [gaber444](https://github.com/gaber444)
- LinkedIn: [linkedin.com/in/gaber444](https://linkedin.com/in/gaber444)

---

[Downloads](downloads.md)
