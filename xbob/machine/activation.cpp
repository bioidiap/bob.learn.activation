/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Fri 10 Jan 2014 14:26:25 CET
 *
 * @brief Python bindings for the machine activation
 *
 * Copyright (C) 2011-2014 Idiap Research Institute, Martigny, Switzerland
 */

#include <cleanup.h>
#include <bob/machine/Activation.h>
#include <boost/function.hpp>
#include <structmember.h>

/*******************************************
 * Implementation of Activation base class *
 *******************************************/

PyDoc_STRVAR(s_activation_str, XBOB_EXT_MODULE_PREFIX ".Activation");

PyDoc_STRVAR(s_activation_doc,
"Base class for activation functions (actually, *functors*).\n\
\n\
.. warning::\n\
\n\
   You cannot instantiate an object of this type directly, you must\n\
   use it through one of the inherited types.\n\
\n\
.. warning::\n\
\n\
   You cannot create classes in Python that derive from this one and\n\
   expect them to work fine with the C++ code, as no hook is\n\
   implemented as of this time to allow for this. You must create\n\
   a class that inherits from the C++\n\
   :cpp:type:`bob::machine::Activation` in C++ and then bind it to\n\
   Python like we have done for the classes available in these\n\
   bindings.\n\
\n\
");

static int PyBobMachineActivation_init(PyBobMachineActivationObject* self, PyObject*, PyObject*) {

  PyErr_Format(PyExc_NotImplementedError, "cannot initialize object of base type `%s' - use one of the inherited classes", s_activation_str);
  return -1;

}

PyDoc_STRVAR(s_call_str, "f");
PyDoc_STRVAR(s_call_doc,
"o.f(z, [res]) -> array | scalar

Computes the activated value, given an input array or scalar\n\
``z``, placing results in ``res`` (and returning it).

If ``z`` is an array, then you can pass another array in ``res``\n\
to store the results and, in this case, we won't allocate a new\n\
one for that purpose. This can be a speed-up in certain scenarios.\n\
Note this does not work for scalars as it makes little sense to\n\
avoid scalar allocation at this level.\n\
\n\
If you decide to pass an array in ``res``, note this array should\n\
have the exact same dimensions as the input array ``z``. It is an
error otherwise.\n\
\n\
.. note::\n\
\n\
   This method only accepts 64-bit float arrays as input or\n\
   output.\n\
\n\
");

/**
 * Maps all elements of arr through function() into retval
 */
static int apply(boost::function<double (double)> function,
    PyBlitzArrayObject* z, PyBlitzArrayObject* res) {

  if (arr->ndim == 1) {
    blitz::Array<double,1>* z_ = PyBlitzArrayCxx_AsBlitz<double,1>(z);
    blitz::Array<double,1>* res_ = PyBlitzArrayCxx_AsBlitz<double,1>(res);
    for (int k=0; k<z_->extent(0); ++k)
      res_->operator()(k) = function(z_->operator()(k));
    return 1;
  }

  else if (array->ndim == 2) {
    blitz::Array<double,2>* z_ = PyBlitzArrayCxx_AsBlitz<double,2>(z);
    blitz::Array<double,2>* res_ = PyBlitzArrayCxx_AsBlitz<double,2>(res);
    for (int k=0; k<z_->extent(0); ++k)
      for (int l=0; l<z_->extent(1); ++l)
        res_->operator()(k,l) = function(z_->operator()(k,l));
    return 1;
  }

  else if (array->ndim == 3) {
    blitz::Array<double,3>* z_ = PyBlitzArrayCxx_AsBlitz<double,3>(z);
    blitz::Array<double,3>* res_ = PyBlitzArrayCxx_AsBlitz<double,3>(res);
    for (int k=0; k<z_->extent(0); ++k)
      for (int l=0; l<z_->extent(1); ++l)
        for (int m=0; m<z_->extent(2); ++m)
          res_->operator()(k,l,m) = function(z_->operator()(k,l,m));
    return 1;
  }

  else if (array->ndim == 4) {
    blitz::Array<double,4>* z_ = PyBlitzArrayCxx_AsBlitz<double,4>(z);
    blitz::Array<double,4>* res_ = PyBlitzArrayCxx_AsBlitz<double,4>(res);
    for (int k=0; k<z_->extent(0); ++k)
      for (int l=0; l<z_->extent(1); ++l)
        for (int m=0; m<z_->extent(2); ++m)
          for (int n=0; n<z_->extent(3); ++n)
            res_->operator()(k,l,m,n) = function(z_->operator()(k,l,m,n));
    return 1;
  }

  return 0;

}

static PyObject* PyBobMachineActivation_call1(PyBobMachineActivationObject* o,
    PyObject* args, PyObject* kwds) {

  PyObject* z = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist, &z)) return 0;

  //protects acquired resources through this scope
  auto z_ = make_safe(z);

  if (PyBlitzArray_Check(z) || PyArray_Check(z)) {

    PyBlitzArrayObject* z_converted = 0;
    PyBlitzArray_Converter(z, &z_converted);
    auto z_converted_ = make_safe(z_converted);

    if (z_converted->type_num != NPY_FLOAT64) {
      PyErr_SetString(PyExc_TypeError, "Activation function only supports 64-bit float arrays for input array `z'");
      return 0;
    }

    if (z_converted->ndim < 1 || z_converted->ndim > 4) {
      PyErr_Format(PyExc_TypeError, "Activation function only accepts 1, 2, 3 or 4-dimensional arrays (not %" PY_FORMAT_SIZE_T "dD arrays)", z_converted->ndim);
      return 0;
    }

    // creates output array
    PyObject* res = PyBlitzArray_SimpleNew(NPY_FLOAT64, z_converted->ndim,
        z_converted->shape);
    auto res_ = make_safe(res);

    // processes the data
    int ok = apply(boost::bind(&bob::machine::Activation::f, *(o->base), _1), z_converted, res);

    if (!ok) {
      PyErr_SetString(PyExc_RuntimeError, "unexpected error occurred applying C++ activation function to input array (DEBUG ME)");
      return 0;
    }

    Py_INCREF(res);
    return res;

  }

  else if (PyNumber_Check(z)) {

    PyObject* z_float = PyNumber_Float(z);
    auto z_float_ = make_safe(z_float);
    double res_c = o->base->f(PyFloat_AsDouble(z_float);
    return PyFloat_FromDouble(res_c);

  }

  PyErr_Format(PyExc_TypeError, "Activation function is not capable to process input objects of type `%s'", z->ob_type->tp_name);
  return 0;

}

static PyObject* PyBobMachineActivation_call2(PyBobMachineActivationObject* o,
    PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {"z", "res", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  PyBlitzArrayObject* z = 0;
  PyBlitzArrayObject* res = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&O&", kwlist,
        &PyBlitzArray_Converter, &z,
        &PyBlitzArray_OutputConverter, &res
        )) return 0;

  //protects acquired resources through this scope
  auto z_ = make_safe(z);
  auto res_ = make_safe(res);

  if (z->type_num != NPY_FLOAT64) {
    PyErr_SetString(PyExc_TypeError, "Activation function only supports 64-bit float arrays for input array `z'");
    return 0;
  }

  if (res->type_num != NPY_FLOAT64) {
    PyErr_SetString(PyExc_TypeError, "Activation function only supports 64-bit float arrays for output array `res'");
    return 0;
  }

  if (z->ndim < 1 || z->ndim > 4) {
    PyErr_Format(PyExc_TypeError, "Activation function only accepts 1, 2, 3 or 4-dimensional arrays (not %" PY_FORMAT_SIZE_T "dD arrays)", z->ndim);
    return 0;
  }

  if (z->ndim != res->ndim) {
    PyErr_Format(PyExc_RuntimeError, "Input and output arrays should have matching number of dimensions, but input array `z' has %" PY_FORMAT_SIZE_T "d dimensions while output array `res' has %" PY_FORMAT_SIZE_T "d dimensions", z->ndim, res->ndim);
    return 0;
  }

  for (Py_ssize_t i=0; i<z->ndim; ++i) {

    if (z->shape[i] != res->shape[i]) {
      PyErr_Format(PyExc_RuntimeError, "Input and output arrays should have matching sizes, but dimension %" PY_FORMAT_SIZE_T "d of input array `z' has %" PY_FORMAT_SIZE_T "d positions while output array `res' has %" PY_FORMAT_SIZE_T "d positions", z->shape[i], res->shape[i]);
      return 0;
    }

  }

  //at this point all checks are done, we can proceed into calling C++
  int ok = apply(boost::bind(&bob::machine::Activation::f, *(o->base), _1), z, res);

  if (!ok) {
    PyErr_SetString(PyExc_RuntimeError, "unexpected error occurred applying C++ activation function to input array (DEBUG ME)");
    return 0;
  }

  Py_INCREF(res);
  return res;

}

static PyObject* PyBobMachineActivation_call(PyBobMachineActivationObject* o,
  PyObject* args, PyObject* kwds) {

  Py_ssize_t nargs = args?PyTuple_Size(args):0 + kwds?PyDict_Size(kwds):0;

  switch (nargs) {

    case 1:
      return PyBobMachineActivation_call1(self, args, kwds);
      break;

    case 2:
      return PyBobMachineActivation_call2(self, args, kwds);
      break;

    default:

      PyErr_Format(PyExc_RuntimeError, "number of arguments mismatch - %s requires 1 or 2 arguments, but you provided %" PY_FORMAT_SIZE_T "d (see help)", s_call_str, nargs);

  }

  return 0;

}

static PyMethodDef PyBobMachineActivation_methods[] = {
  {
    s_call_str,
    (PyCFunction)PyBobMachineActivation_call,
    METH_VARARGS|METH_KEYWORDS,
    s_call_doc
  },
  {0} /* Sentinel */
}

static int PyBobMachineActivation_Check(PyObject* o) {
  return PyObject_IsInstance(o, reinterpret_cast<PyObject*>(&PyBobMachineActivation_Type));
}

static PyObject* PyBobMachineActivation_RichCompare (PyBobMachineActivationObject* self, PyObject* other, int op) {

  if (!PyBobMachineActivation_Check(other)) {
    PyErr_Format(PyExc_TypeError, "cannot compare `%s' with `%s'",
        s_activation_str, other->ob_type->tp_name);
    return 0;
  }

  PyBobMachineActivationObject* other_ = reinterpret_cast<PyBobMachineActivationObject*>(other);

  switch (op) {
    case Py_EQ:
      if (*(self->base) == *(other_->base)) Py_RETURN_TRUE;
      Py_RETURN_FALSE;
      break;
    case Py_NE:
      if (*(self->base) != *(other_->base)) Py_RETURN_TRUE;
      Py_RETURN_FALSE;
      break;
    default:
      Py_INCREF(Py_NotImplemented);
      return Py_NotImplemented;
  }

}

PyTypeObject PyBobMachineActivation_Type = {
    PyObject_HEAD_INIT(0)
    0,                                                 /* ob_size */
    s_activation_str,                                  /* tp_name */
    sizeof(PyBobMachineActivationObject),              /* tp_basicsize */
    0,                                                 /* tp_itemsize */
    0,                                                 /* tp_dealloc */
    0,                                                 /* tp_print */
    0,                                                 /* tp_getattr */
    0,                                                 /* tp_setattr */
    0,                                                 /* tp_compare */
    0,                                                 /* tp_repr */
    0,                                                 /* tp_as_number */
    0,                                                 /* tp_as_sequence */
    0,                                                 /* tp_as_mapping */
    0,                                                 /* tp_hash */
    0,                                                 /* tp_call */
    0,                                                 /* tp_str */
    0,                                                 /* tp_getattro */
    0,                                                 /* tp_setattro */
    0,                                                 /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,          /* tp_flags */
    s_activation_doc,                                  /* tp_doc */
    0,                                                 /* tp_traverse */
    0,                                                 /* tp_clear */
    (richcmpfunc)PyBobMachineActivation_RichCompare,   /* tp_richcompare */
    0,                                                 /* tp_weaklistoffset */
    0,                                                 /* tp_iter */
    0,                                                 /* tp_iternext */
    PyBobMachineActivation_methods,                    /* tp_methods */
    0,                                                 /* tp_members */
    0,                                                 /* tp_getset */
    0,                                                 /* tp_base */
    0,                                                 /* tp_dict */
    0,                                                 /* tp_descr_get */
    0,                                                 /* tp_descr_set */
    0,                                                 /* tp_dictoffset */
    (initproc)PyBobMachineActivation_init,             /* tp_init */
    0,                                                 /* tp_alloc */
    0,                                                 /* tp_new */
};

/**
    .def("__call__", &activation_f_ndarray_1, (arg("self"), arg("z"), arg("res")), "Computes the activated value, given an input array ``z``, placing results in ``res`` (and returning it)")
    .def("__call__", &activation_f_ndarray_2, (arg("self"), arg("z")), "Computes the activated value, given an input array ``z``. Returns a newly allocated array with the same size as ``z``")
    .def("__call__", &bob::machine::Activation::f, (arg("self"), arg("z")), "Computes the activated value, given an input ``z``")
    .def("f_prime", &activation_f_prime_ndarray_1, (arg("self"), arg("z"), arg("res")), "Computes the derivative of the activated value, placing results in ``res`` (and returning it)")
    .def("f_prime", &activation_f_prime_ndarray_2, (arg("self"), arg("z")), "Computes the derivative of the activated value, given an input array ``z``. Returns a newly allocated array with the same size as ``z``")
    .def("f_prime", &bob::machine::Activation::f_prime, (arg("self"), arg("z")), "Computes the derivative of the activated value.")
    .def("f_prime_from_f", &activation_f_prime_from_f_ndarray_1, (arg("self"), arg("a"), arg("res")), "Computes the derivative of the activated value, given **the activated value** ``a``, placing results in ``res`` (and returning it)")
    .def("f_prime_from_f", &activation_f_prime_from_f_ndarray_2, (arg("self"), arg("z")), "Computes the derivative of the activated value, given **the activated value** ``a``. Returns a newly allocated array with the same size as ``a`` with the answer.")
    .def("f_prime_from_f", &bob::machine::Activation::f_prime_from_f, (arg("self"), arg("a")), "Computes the derivative of the activation value, given **the activated value** ``a``.")
    .def("save", &bob::machine::Activation::save, (arg("self"), arg("h5f")),
       "Saves itself to a :py:class:`bob.io.HDF5File`")
    .def("load", &bob::machine::Activation::load, (arg("self"), arg("h5f")),
       "Loads itself from a :py:class:`bob.io.HDF5File`")
    .def("unique_identifier",
        &bob::machine::Activation::unique_identifier, (arg("self")),
        "Returns a unique identifier, used by this class in connection to the Activation registry.")
    .def("__str__", &bob::machine::Activation::str)
**/
