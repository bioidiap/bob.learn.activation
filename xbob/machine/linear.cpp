/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Tue 14 Jan 2014 14:26:09 CET
 *
 * @brief Bindings for a LinearMachine
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#define XBOB_MACHINE_MODULE
#include "cleanup.h"
#include <xbob.io/api.h>
#include <xbob.machine/api.h>
#include <xbob.blitz/cppapi.h>
#include <structmember.h>

/**********************************************
 * Implementation of LinearMachine base class *
 **********************************************/

PyDoc_STRVAR(s_linear_str, XBOB_EXT_MODULE_PREFIX ".LinearMachine");

PyDoc_STRVAR(s_linear_doc,
"LinearMachine([input_size=0, [output_size=0]])\n\
LinearMachine(weights)\n\
LinearMachine(config)\n\
LinearMachine(other)\n\
\n\
A linear classifier. See C. M. Bishop, 'Pattern Recognition\n\
and Machine  Learning', chapter 4 for more details. The basic\n\
matrix operation performed for projecting the input to the\n\
output is: :math:`o = w \\times i` (with :math:`w` being the\n\
vector of machine weights and :math:`i` the input data vector).\n\
The weights matrix is therefore organized column-wise. In this\n\
scheme, each column of the weights matrix can be interpreted\n\
as vector to which the input is projected. The number of\n\
columns of the weights matrix determines the number of outputs\n\
this linear machine will have. The number of rows, the number\n\
of allowed inputs it can process.\n\
\n\
Input and output is always performed on 1D arrays with 64-bit\n\
floating point numbers.\n\
\n\
A linear machine can be constructed in different ways. In the\n\
first form, the user specifies optional input and output vector\n\
sizes. The machine is remains **uninitialized**. With the second\n\
form, the user passes a 2D array with 64-bit floats containing\n\
weight matrix to be used by the new machine. In the third form\n\
the user passes a pre-opened HDF5 file pointing to the machine\n\
information to be loaded in memory. Finally, in the last form\n\
(copy constructor), the user passes another\n\
:py:class:`LinearMachine` that will be fully copied.\n\
");

static int PyBobMachineLinear_init_sizes(PyBobMachineLinearObject* self,
    PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {"input_size", "output_size", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  Py_ssize_t input_size = 0;
  Py_ssize_t output_size = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|nn", kwlist,
        &input_size, &output_size)) return -1;

  try {
    self->machine = new bob::machine::LinearMachine(input_size, output_size);
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot create new object of type `%s' - unknown exception thrown", s_linear_str);
  }

  return 0;

}

static int PyBobMachineLinear_init_weights(PyBobMachineLinearObject* self,
    PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {"weights", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  PyBlitzArrayObject* weights = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&", kwlist,
        &weights, &PyBlitzArray_Converter)) return -1;

  if (weights->type_num != NPY_FLOAT64 || weights->ndim != 2) {
    PyErr_SetString(PyExc_TypeError, "LinearMachine only supports 64-bit floats 2D arrays for input vector `weights'");
    return -1;
  }

  try {
    self->machine = new bob::machine::LinearMachine
      (*PyBlitzArrayCxx_AsBlitz<double,2>(weights));
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot create new object of type `%s' - unknown exception thrown", s_linear_str);
  }

  return 0;

}

static int PyBobMachineLinear_init_hdf5(PyBobMachineLinearObject* self,
    PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {"config", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  PyObject* config = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist,
        &config)) return -1;

  if (!PyBobIoHDF5File_Check(config)) {
    PyErr_Format(PyExc_TypeError, "initialization with HDF5 files requires an object of type `HDF5File' for input, not `%s'", config->ob_type->tp_name);
    return -1;
  }

  auto h5f = reinterpret_cast<PyBobIoHDF5FileObject*>(config);

  try {
    self->machine = new bob::machine::LinearMachine(*(h5f->f));
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot create new object of type `%s' - unknown exception thrown", s_linear_str);
  }

  return 0;

}

static int PyBobMachineLinear_init_copy(PyBobMachineLinearObject* self,
    PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {"other", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  PyObject* other = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist,
        &other)) return -1;

  if (!PyBobMachineLinear_Check(other)) {
    PyErr_Format(PyExc_TypeError, "copy construction requires an object of type `%s' for input, not `%s'", self->ob_type->tp_name, other->ob_type->tp_name);
    return -1;
  }

  auto copy = reinterpret_cast<PyBobMachineLinearObject*>(other);

  try {
    self->machine = new bob::machine::LinearMachine(*(copy->machine));
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot create new object of type `%s' - unknown exception thrown", s_linear_str);
  }

  return 0;

}

static int PyBobMachineLinear_init(PyBobMachineLinearObject* self,
    PyObject* args, PyObject* kwds) {

  Py_ssize_t nargs = args?PyTuple_Size(args):0 + kwds?PyDict_Size(kwds):0;

  switch (nargs) {

    case 0: //default initializer
    case 2: //two sizes
      return PyBobMachineLinear_init_sizes(self, args, kwds);

    case 1:

      {

        PyObject* arg = 0; ///< borrowed (don't delete)
        if (PyTuple_Size(args)) arg = PyTuple_GET_ITEM(args, 0);
        else {
          PyObject* tmp = PyDict_Values(kwds);
          auto tmp_ = make_safe(tmp);
          arg = PyList_GET_ITEM(tmp, 0);
        }

        if (PyBobIoHDF5File_Check(arg)) {
          return PyBobMachineLinear_init_hdf5(self, args, kwds);
        }

        if (PyBlitzArray_Check(arg) || PyArray_Check(arg)) {
          return PyBobMachineLinear_init_weights(self, args, kwds);
        }

        if (PyNumber_Check(arg)) {
          return PyBobMachineLinear_init_sizes(self, args, kwds);
        }

        if (PyBobMachineActivation_Check(arg)) {
          return PyBobMachineLinear_init_copy(self, args, kwds);
        }

        PyErr_Format(PyExc_TypeError, "cannot initialize `%s' with `%s' (see help)", s_linear_str, arg->ob_type->tp_name);

      }

      break;

    default:

      PyErr_Format(PyExc_RuntimeError, "number of arguments mismatch - %s requires 0, 1 or 2 arguments, but you provided %" PY_FORMAT_SIZE_T "d (see help)", s_linear_str, nargs);

  }

  return -1;

}

static void PyBobMachineLinear_delete (PyBobMachineLinearObject* self) {

  delete self->machine;
  self->ob_type->tp_free((PyObject*)self);

}

PyTypeObject PyBobMachineLinear_Type = {
    PyObject_HEAD_INIT(0)
    0,                                           /* ob_size */
    s_linear_str,                                /* tp_name */
    sizeof(PyBobMachineLinearObject),            /* tp_basicsize */
    0,                                           /* tp_itemsize */
    (destructor)PyBobMachineLinear_delete,       /* tp_dealloc */
    0,                                           /* tp_print */
    0,                                           /* tp_getattr */
    0,                                           /* tp_setattr */
    0,                                           /* tp_compare */
    0,                                           /* tp_repr */
    0,                                           /* tp_as_number */
    0,                                           /* tp_as_sequence */
    0,                                           /* tp_as_mapping */
    0,                                           /* tp_hash */
    0, //(ternaryfunc)PyBobMachineLinear_call,        /* tp_call */
    0, //(reprfunc)PyBobMachineLinear_Str,            /* tp_str */
    0,                                           /* tp_getattro */
    0,                                           /* tp_setattro */
    0,                                           /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,    /* tp_flags */
    s_linear_doc,                                /* tp_doc */
    0,                                           /* tp_traverse */
    0,                                           /* tp_clear */
    0, //(richcmpfunc)PyBobMachineLinear_RichCompare, /* tp_richcompare */
    0,                                           /* tp_weaklistoffset */
    0,                                           /* tp_iter */
    0,                                           /* tp_iternext */
    0, //PyBobMachineLinear_methods,                  /* tp_methods */
    0,                                           /* tp_members */
    0,                                           /* tp_getset */
    0,                                           /* tp_base */
    0,                                           /* tp_dict */
    0,                                           /* tp_descr_get */
    0,                                           /* tp_descr_set */
    0,                                           /* tp_dictoffset */
    (initproc)PyBobMachineLinear_init,           /* tp_init */
    0,                                           /* tp_alloc */
    0,                                           /* tp_new */
};

/******
static object forward(const bob::machine::LinearMachine& m,
  bob::python::const_ndarray input)
{
  const bob::core::array::typeinfo& info = input.type();

  switch(info.nd) {
    case 1:
      {
        bob::python::ndarray output(bob::core::array::t_float64, m.outputSize());
        blitz::Array<double,1> output_ = output.bz<double,1>();
        m.forward(input.bz<double,1>(), output_);
        return output.self();
      }
    case 2:
      {
        bob::python::ndarray output(bob::core::array::t_float64, info.shape[0], m.outputSize());
        blitz::Array<double,2> input_ = input.bz<double,2>();
        blitz::Array<double,2> output_ = output.bz<double,2>();
        blitz::Range all = blitz::Range::all();
        for (size_t k=0; k<info.shape[0]; ++k) {
          blitz::Array<double,1> i_ = input_(k,all);
          blitz::Array<double,1> o_ = output_(k,all);
          m.forward(i_, o_);
        }
        return output.self();
      }
    default:
      PYTHON_ERROR(TypeError, "cannot forward arrays with "  SIZE_T_FMT " dimensions (only with 1 or 2 dimensions).", info.nd);
  }
}

static void forward2(const bob::machine::LinearMachine& m,
    bob::python::const_ndarray input, bob::python::ndarray output)
{
  const bob::core::array::typeinfo& info = input.type();

  switch(info.nd) {
    case 1:
      {
        blitz::Array<double,1> output_ = output.bz<double,1>();
        m.forward(input.bz<double,1>(), output_);
      }
      break;
    case 2:
      {
        blitz::Array<double,2> input_ = input.bz<double,2>();
        blitz::Array<double,2> output_ = output.bz<double,2>();
        blitz::Range all = blitz::Range::all();
        for (size_t k=0; k<info.shape[0]; ++k) {
          blitz::Array<double,1> i_ = input_(k,all);
          blitz::Array<double,1> o_ = output_(k,all);
          m.forward(i_, o_);
        }
      }
      break;
    default:
      PYTHON_ERROR(TypeError, "cannot forward arrays with "  SIZE_T_FMT " dimensions (only with 1 or 2 dimensions).", info.nd);
  }
}

static tuple get_shape(const bob::machine::LinearMachine& m) {
  return make_tuple(m.inputSize(), m.outputSize());
}

static void set_shape(bob::machine::LinearMachine& m,
    const blitz::TinyVector<int,2>& s) {
  m.resize(s(0), s(1));
}

static void set_input_sub(bob::machine::LinearMachine& m, object o) {
  extract<int> int_check(o);
  extract<double> float_check(o);
  if (int_check.check()) { //is int
    m.setInputSubtraction(int_check());
  }
  else if (float_check.check()) { //is float
    m.setInputSubtraction(float_check());
  }
  else {
    //try hard-core extraction - throws TypeError, if not possible
    extract<bob::python::const_ndarray> array_check(o);
    if (!array_check.check())
      PYTHON_ERROR(TypeError, "Cannot extract an array from this Python object");
    bob::python::const_ndarray ar = array_check();
    m.setInputSubtraction(ar.bz<double,1>());
  }
}

static void set_input_div(bob::machine::LinearMachine& m, object o) {
  extract<int> int_check(o);
  extract<double> float_check(o);
  if (int_check.check()) { //is int
    m.setInputDivision(int_check());
  }
  else if (float_check.check()) { //is float
    m.setInputDivision(float_check());
  }
  else {
    //try hard-core extraction - throws TypeError, if not possible
    extract<bob::python::const_ndarray> array_check(o);
    if (!array_check.check())
      PYTHON_ERROR(TypeError, "Cannot extract an array from this Python object");
    bob::python::const_ndarray ar = array_check();
    m.setInputDivision(ar.bz<double,1>());
  }
}

static void set_weight(bob::machine::LinearMachine& m, object o) {
  extract<int> int_check(o);
  extract<double> float_check(o);
  if (int_check.check()) { //is int
    m.setWeights(int_check());
  }
  else if (float_check.check()) { //is float
    m.setWeights(float_check());
  }
  else {
    //try hard-core extraction - throws TypeError, if not possible
    extract<bob::python::const_ndarray> array_check(o);
    if (!array_check.check())
      PYTHON_ERROR(TypeError, "Cannot extract an array from this Python object");
    bob::python::const_ndarray ar = array_check();
    m.setWeights(ar.bz<double,2>());
  }
}

static void set_bias(bob::machine::LinearMachine& m, object o) {
  extract<int> int_check(o);
  extract<double> float_check(o);
  if (int_check.check()) { //is int
    m.setBiases(int_check());
  }
  else if (float_check.check()) { //is float
    m.setBiases(float_check());
  }
  else {
    //try hard-core extraction - throws TypeError, if not possible
    extract<bob::python::const_ndarray> array_check(o);
    if (!array_check.check())
      PYTHON_ERROR(TypeError, "Cannot extract an array from this Python object");
    bob::python::const_ndarray ar = array_check();
    m.setBiases(ar.bz<double,1>());
  }
}
***/

/***
void bind_machine_linear() {
    .def(self == self)
    .def(self != self)
    .def("is_similar_to", &bob::machine::LinearMachine::is_similar_to, (arg("self"), arg("other"), arg("r_epsilon")=1e-5, arg("a_epsilon")=1e-8), "Compares this LinearMachine with the 'other' one to be approximately the same.")
    .def("load", &bob::machine::LinearMachine::load, (arg("self"), arg("config")), "Loads the weights and biases from a configuration file. Both weights and biases have their dimensionalities checked between each other for consistency.")
    .def("save", &bob::machine::LinearMachine::save, (arg("self"), arg("config")), "Saves the weights and biases to a configuration file.")
    .add_property("input_subtract", make_function(&bob::machine::LinearMachine::getInputSubtraction, return_value_policy<copy_const_reference>()), &set_input_sub, "Input subtraction factor, before feeding data through the weight matrix W. The subtraction is the first applied operation in the processing chain - by default, it is set to 0.0.")
    .add_property("input_divide", make_function(&bob::machine::LinearMachine::getInputDivision, return_value_policy<copy_const_reference>()), &set_input_div, "Input division factor, before feeding data through the weight matrix W. The division is applied just after subtraction - by default, it is set to 1.0")
    .add_property("weights", make_function(&bob::machine::LinearMachine::getWeights, return_value_policy<copy_const_reference>()), &set_weight, "Weight matrix W to which the input is projected to. The output of the project is fed subject to bias and activation before being output.")
    .add_property("biases", make_function(&bob::machine::LinearMachine::getBiases, return_value_policy<copy_const_reference>()), &set_bias, "Bias to the output units of this linear machine, to be added to the output before activation.")
    .add_property("activation", &bob::machine::LinearMachine::getActivation, &bob::machine::LinearMachine::setActivation, "The activation function - by default, the identity function. The output provided by the activation function is passed, unchanged, to the user.")
    .add_property("shape", &get_shape, &set_shape, "A tuple that represents the size of the input vector followed by the size of the output vector in the format ``(input, output)``.")
    .def("resize", &bob::machine::LinearMachine::resize, (arg("self"), arg("input"), arg("output")), "Resizes the machine. If either the input or output increases in size, the weights and other factors should be considered uninitialized. If the size is preserved or reduced, already initialized values will not be changed.\n\nTip: Use this method to force data compression. All will work out given most relevant factors to be preserved are organized on the top of the weight matrix. In this way, reducing the system size will supress less relevant projections.")
    .def("__call__", &forward2, (arg("self"), arg("input"), arg("output")), "Projects the input to the weights and biases and saves results on the output")
    .def("forward", &forward2, (arg("self"), arg("input"), arg("output")), "Projects the input to the weights and biases and saves results on the output")
    .def("__call__", &forward, (arg("self"), arg("input")), "Projects the input to the weights and biases and returns the output. This method implies in copying out the output data and is, therefore, less efficient as its counterpart that sets the output given as parameter. If you have to do a tight loop, consider using that variant instead of this one.")
    .def("forward", &forward, (arg("self"), arg("input")), "Projects the input to the weights and biases and returns the output. This method implies in copying out the output data and is, therefore, less efficient as its counterpart that sets the output given as parameter. If you have to do a tight loop, consider using that variant instead of this one.")
    ;
}
***/
