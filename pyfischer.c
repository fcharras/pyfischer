#include <Python.h>
#include "sais.h"

#include <stdio.h>

#include <string.h>
#include "arrayobject.h"


/* C vector utility functions */
int *pyvector_to_Carrayptrs(PyArrayObject *arrayin);
int  not_intvector(PyArrayObject *vec);

/* Create 1D Carray from PyArray */
int *pyvector_to_Carrayptrs(PyArrayObject *arrayin)
{
    return (int *) arrayin->data;  /* pointer to arrayin data as double */
}

/* Check that PyArrayObject is an int type and a vector */
int  not_intvector(PyArrayObject *vec)
{
    if (vec->descr->type_num != NPY_INT || vec->nd != 1)
    {
        PyErr_SetString(PyExc_ValueError, "Array must be of type Int and 1 dimensional (n).");
        return 1;
    }
    return 0;
}


static PyObject *python_sais_int(PyObject *self, PyObject *args)
{
    PyArrayObject *T_np, *SA_np, *LCP_np;
    int *T, *SA, *LCP;
    int i, k;
    if (!PyArg_ParseTuple(args, "O!i", &PyArray_Type, &T_np, &k))
        return NULL;
    if (T_np == NULL)
    {
        PyErr_SetString(PyExc_StopIteration, "T cannot be None.");
        return NULL;
    }
    if (not_intvector(T_np))
        return NULL;
    if (k <= 0)
    {
        PyErr_SetString(PyExc_StopIteration, "Alphabet size k must be greater than 0.");
        return NULL;
    }
    T = pyvector_to_Carrayptrs(T_np);
    int n = T_np->dimensions[0];
    for (i = 0; i < n; i++)
        if (T[i] < 0 || T[i] >= k)
        {
            PyErr_SetString(PyExc_StopIteration, "Array elements must be >= 0 and < k (alphabet size).");
            return NULL;
        }
    npy_intp dims[2];
    dims[0] = n+1;  // +1 for computing LCP
    SA_np = (PyArrayObject *) PyArray_ZEROS(1, dims, NPY_INT, 0);
    dims[0] = n;
    LCP_np = (PyArrayObject *) PyArray_ZEROS(1, dims, NPY_INT, 0);
    SA = pyvector_to_Carrayptrs(SA_np);
    LCP = pyvector_to_Carrayptrs(LCP_np);
    int res = sais_lcp_int(T, SA, LCP, n, k);
    if (res < 0)
    {
        PyErr_SetString(PyExc_StopIteration, "Error occurred in SA-IS.");
        return NULL;
    }
    return Py_BuildValue("NN", SA_np, LCP_np);
}

static PyMethodDef ModuleMethods[] = {
    {"sais_lcp_int",  python_sais_int, METH_VARARGS, "Construct a Suffix Array and a LCP Array for a given NumPy integer array.\n:param ndarray T : int array for which SA should be constructed.\n:param k : alphabet size. All integers in T must be >= 0 and < k.\n:return ndarray SA : suffix array for T.\n:return ndarray LCP : lcp array for T."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


static struct PyModuleDef mod =
{
    PyModuleDef_HEAD_INIT,
    "pyfischer",
    "Suffix and LCP Array library using the Fischer algorithm",
    -1,
    ModuleMethods
};

PyMODINIT_FUNC PyInit_pyfischer(void)
{
    import_array(); // NumPy
    return PyModule_Create(&mod);
}
