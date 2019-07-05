#! /usr/bin/env python
from setuptools import setup, Extension
import numpy as np

pyfischer = Extension(
    'pyfischer',
    sources=['sais.c', 'pyfischer.c'],
    extra_compile_args=['-Wall', '-DNDEBUG', '-ffast-math', '-O9', '-funroll-loops'],
    include_dirs=[np.get_include() + '/numpy']
)

setup(
    name='pyfischer',
    version='0.1',
    description='A Python module wrapper for the SA-IS LCP algorithm by Johannes Fischer.',
    author='Franck Charras',
    author_email='franck@sancare.fr',
    long_description='A Python module wrapper for the SA-IS LCP algorithm implementation by Johannes Fischer based on Yuta Mori work.',
    ext_modules=[pyfischer],
)
