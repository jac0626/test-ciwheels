#include <Python.h>

static PyObject* hello(PyObject* self, PyObject* args) {
    return Py_BuildValue("s", "Hello from C!");
}

static PyMethodDef module_methods[] = {
    {"hello", hello, METH_VARARGS, "Say hello"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module_definition = {
    PyModuleDef_HEAD_INIT,
    "_hello",
    "A minimal test module",
    -1,
    module_methods
};

PyMODINIT_FUNC PyInit__hello(void) {
    return PyModule_Create(&module_definition);
}
