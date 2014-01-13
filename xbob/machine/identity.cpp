/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Mon 13 Jan 2014 17:25:32 CET
 *
 * @brief Implementation of the Identity Activation function
 */

#include <xbob.machine/api.h>

PyDoc_STRVAR(s_activationsubtype_str, XBOB_EXT_MODULE_PREFIX ".IdentityActivation");

PyDoc_STRVAR(s_activationsubtype_doc,
"IdentityActivation() -> new IdentityActivation\n\
\n\
Computes :math:`f(z) = z` as activation function.\n\
\n\
");

/* Type definition for PyBobMathLpInteriorPointObject */
typedef struct {
  PyBobMachineActivationObject parent;

  /* Type-specific fields go here. */
  bob::machine::IdentityActivation* base;

} PyBobMachineActivationSubtypeObject;

static int PyBobMachineActivationSubtype_init(PyBobMachineActivationSubtypeObject* self, PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "", kwlist)) return -1;

  try {
    self->base = new bob::machine::IdentityActivation();
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot create new object of type `%s' - unknown exception thrown", s_activationsubtype_str);
  }

  self->parent.base = self->base;

  if (PyErr_Occurred()) return -1;

  return 0;

}

static void PyBobMachineActivationSubtype_delete (PyBobMachineActivationSubtypeObject* self) {

  delete self->base;
  self->parent.base = 0;
  self->base = 0;
  self->parent.ob_type->tp_free((PyObject*)self);

}

PyTypeObject PyBobMachineActivationSubtype_Type = {
    PyObject_HEAD_INIT(0)
    0,                                                  /*ob_size*/
    0,                                                  /*tp_name*/
    sizeof(PyBobMachineActivationSubtypeObject),        /*tp_basicsize*/
    0,                                                  /*tp_itemsize*/
    (destructor)PyBobMachineActivationSubtype_delete,   /*tp_dealloc*/
    0,                                                  /*tp_print*/
    0,                                                  /*tp_getattr*/
    0,                                                  /*tp_setattr*/
    0,                                                  /*tp_compare*/
    0,                                                  /*tp_repr*/
    0,                                                  /*tp_as_number*/
    0,                                                  /*tp_as_sequence*/
    0,                                                  /*tp_as_mapping*/
    0,                                                  /*tp_hash */
    0,                                                  /*tp_call*/
    0,                                                  /*tp_str*/
    0,                                                  /*tp_getattro*/
    0,                                                  /*tp_setattro*/
    0,                                                  /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,           /*tp_flags*/
    s_activationsubtype_doc,                            /* tp_doc */
    0,		                                              /* tp_traverse */
    0,		                                              /* tp_clear */
    0,                                                  /* tp_richcompare */
    0,		                                              /* tp_weaklistoffset */
    0,		                                              /* tp_iter */
    0,		                                              /* tp_iternext */
    0,                                                  /* tp_methods */
    0,                                                  /* tp_members */
    0,                                                  /* tp_getset */
    0,                                                  /* tp_base */
    0,                                                  /* tp_dict */
    0,                                                  /* tp_descr_get */
    0,                                                  /* tp_descr_set */
    0,                                                  /* tp_dictoffset */
    (initproc)PyBobMachineActivationSubtype_init,       /* tp_init */
    0,                                                  /* tp_alloc */
    0,                                                  /* tp_new */
};
