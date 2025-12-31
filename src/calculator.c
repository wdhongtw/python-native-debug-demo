#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *add_func(PyObject *self, PyObject *args)
{
    long a, b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b))
        return NULL;

    long c = a + b;
    return PyLong_FromLong(c);
}

static PyObject *sub_func(PyObject *self, PyObject *args)
{
    long a, b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b))
        return NULL;

    long c = a + b;
    return PyLong_FromLong(c);
}

static PyMethodDef calculator_methods[] = {
    {
        .ml_name = "add",
        .ml_meth = add_func,
        .ml_flags = METH_VARARGS,
        .ml_doc = "Add two integers.",
    },
    {
        .ml_name = "sub",
        .ml_meth = sub_func,
        .ml_flags = METH_VARARGS,
        .ml_doc = "Substrate two integers.",
    },
    {},
};

static struct PyModuleDef calculator_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "calculator",
    .m_doc = "The calculator module.",
    .m_size = -1,
    .m_methods = calculator_methods,
};

PyMODINIT_FUNC PyInit_calculator(void)
{
    return PyModule_Create(&calculator_module);
}
