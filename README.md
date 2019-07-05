# sais-lite-lcp
This is an attempt at bringing to python the ad-hoc-implementation of the code described in ["Inducing the LCP-Array"](http://arxiv.org/abs/1101.3448) by [Johannes Fischer](http://ls11-www.cs.tu-dortmund.de/staff/fischer). It is based on Florian Kurpicz and Johannes Fischer's [sais-lite-lcp](https://github.com/kurpicz/sais-lite-lcp) which is itself based on Yuta Mori's [sais-lite 2.4.1](http://sites.google.com/site/yuta256), which is an implementation of the following paper:

Nong, G., Zhang, S., & Chan, W. H. (2011). Two efficient algorithms for linear time suffix array construction. Computers, *IEEE Transactions on, 60(10)*, 1471-1484.

In this repository we only aim at exposing a python function for computing sa and lcp arrays from an array of int. The C wrapper that enables interfacing with python is inspired by Alexey Gritsenko's [PySais](https://github.com/AlexeyG/PySAIS).

## installation

    ./setup.py build
    ./setup.py install

It seems that it is required that the last element of the input array must be strictly lexicographically smaller than all other int in the array.

## Example:
```python
import pyfischer
import numpy as np

mississipi = np.array([2, 1, 4, 4, 1, 4, 4, 1, 3, 3, 1, 0], dtype=np.int32)
sa, lcp = pyfischer.sais_lcp_int(mississipi, mississipi.max() + 1)
```

