/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Fri 13 Dec 2013 12:35:59 CET
 *
 * @brief Bindings to activation functors
 */

#define XBOB_LEARN_ACTIVATION_MODULE
#include <xbob.learn.activation/api.h>

#ifdef NO_IMPORT_ARRAY
#undef NO_IMPORT_ARRAY
#endif
#include <xbob.blitz/capi.h>
#include <xbob.blitz/cleanup.h>
#include <xbob.io.base/api.h>

static PyMethodDef module_methods[] = {
    {0}  /* Sentinel */
};

PyDoc_STRVAR(module_docstr, "classes for activation functors");

#if PY_VERSION_HEX >= 0x03000000
static PyModuleDef module_definition = {
  PyModuleDef_HEAD_INIT,
  XBOB_EXT_MODULE_NAME,
  module_docstr,
  -1,
  module_methods,
  0, 0, 0, 0
};
#endif

int PyXbobLearnActivation_APIVersion = XBOB_LEARN_ACTIVATION_API_VERSION;

static PyObject* create_module (void) {

  PyBobLearnActivation_Type.tp_new = PyType_GenericNew;
  if (PyType_Ready(&PyBobLearnActivation_Type) < 0) return 0;

  PyBobLearnIdentityActivation_Type.tp_base = &PyBobLearnActivation_Type;
  if (PyType_Ready(&PyBobLearnIdentityActivation_Type) < 0) return 0;

  PyBobLearnLinearActivation_Type.tp_base = &PyBobLearnActivation_Type;
  if (PyType_Ready(&PyBobLearnLinearActivation_Type) < 0) return 0;

  PyBobLearnLogisticActivation_Type.tp_base = &PyBobLearnActivation_Type;
  if (PyType_Ready(&PyBobLearnLogisticActivation_Type) < 0) return 0;

  PyBobLearnHyperbolicTangentActivation_Type.tp_base =
    &PyBobLearnActivation_Type;
  if (PyType_Ready(&PyBobLearnHyperbolicTangentActivation_Type) < 0) return 0;

  PyBobLearnMultipliedHyperbolicTangentActivation_Type.tp_base =
    &PyBobLearnActivation_Type;
  if (PyType_Ready(&PyBobLearnMultipliedHyperbolicTangentActivation_Type) < 0)
    return 0;

# if PY_VERSION_HEX >= 0x03000000
  PyObject* m = PyModule_Create(&module_definition);
# else
  PyObject* m = Py_InitModule3(XBOB_EXT_MODULE_NAME, module_methods, module_docstr);
# endif
  if (!m) return 0;
  auto m_ = make_safe(m);

  /* register some constants */
  if (PyModule_AddIntConstant(m, "__api_version__", XBOB_LEARN_ACTIVATION_API_VERSION) < 0) return 0;
  if (PyModule_AddStringConstant(m, "__version__", XBOB_EXT_MODULE_VERSION) < 0) return 0;

  /* register the types to python */
  Py_INCREF(&PyBobLearnActivation_Type);
  if (PyModule_AddObject(m, "Activation", (PyObject *)&PyBobLearnActivation_Type) < 0) return 0;

  Py_INCREF(&PyBobLearnIdentityActivation_Type);
  if (PyModule_AddObject(m, "Identity", (PyObject *)&PyBobLearnIdentityActivation_Type) < 0) return 0;

  Py_INCREF(&PyBobLearnLinearActivation_Type);
  if (PyModule_AddObject(m, "Linear", (PyObject *)&PyBobLearnLinearActivation_Type) < 0) return 0;

  Py_INCREF(&PyBobLearnLogisticActivation_Type);
  if (PyModule_AddObject(m, "Logistic", (PyObject *)&PyBobLearnLogisticActivation_Type) < 0) return 0;

  Py_INCREF(&PyBobLearnHyperbolicTangentActivation_Type);
  if (PyModule_AddObject(m, "HyperbolicTangent", (PyObject *)&PyBobLearnHyperbolicTangentActivation_Type) < 0) return 0;

  Py_INCREF(&PyBobLearnMultipliedHyperbolicTangentActivation_Type);
  if (PyModule_AddObject(m, "MultipliedHyperbolicTangent", (PyObject *)&PyBobLearnMultipliedHyperbolicTangentActivation_Type) < 0) return 0;

  static void* PyXbobLearnActivation_API[PyXbobLearnActivation_API_pointers];

  /* exhaustive list of C APIs */

  /**************
   * Versioning *
   **************/

  PyXbobLearnActivation_API[PyXbobLearnActivation_APIVersion_NUM] = (void *)&PyXbobLearnActivation_APIVersion;

  /*************************************************
   * Bindings for xbob.learn.activation.Activation *
   *************************************************/

  PyXbobLearnActivation_API[PyBobLearnActivation_Type_NUM] = (void *)&PyBobLearnActivation_Type;

  PyXbobLearnActivation_API[PyBobLearnActivation_Check_NUM] = (void *)&PyBobLearnActivation_Check;

  PyXbobLearnActivation_API[PyBobLearnActivation_NewFromActivation_NUM] = (void *)&PyBobLearnActivation_NewFromActivation;

  /***********************************************
   * Bindings for xbob.learn.activation.Identity *
   ***********************************************/

  PyXbobLearnActivation_API[PyBobLearnIdentityActivation_Type_NUM] = (void *)&PyBobLearnIdentityActivation_Type;

  /*********************************************
   * Bindings for xbob.learn.activation.Linear *
   *********************************************/

  PyXbobLearnActivation_API[PyBobLearnLinearActivation_Type_NUM] = (void *)&PyBobLearnLinearActivation_Type;

  /***********************************************
   * Bindings for xbob.learn.activation.Logistic *
   ***********************************************/

  PyXbobLearnActivation_API[PyBobLearnLogisticActivation_Type_NUM] = (void *)&PyBobLearnLogisticActivation_Type;

  /********************************************************
   * Bindings for xbob.learn.activation.HyperbolicTangent *
   ********************************************************/

  PyXbobLearnActivation_API[PyBobLearnHyperbolicTangentActivation_Type_NUM] = (void *)&PyBobLearnHyperbolicTangentActivation_Type;

  /******************************************************************
   * Bindings for xbob.learn.activation.MultipliedHyperbolicTangent *
   ******************************************************************/

  PyXbobLearnActivation_API[PyBobLearnMultipliedHyperbolicTangentActivation_Type_NUM] = (void *)&PyBobLearnMultipliedHyperbolicTangentActivation_Type;

#if PY_VERSION_HEX >= 0x02070000

  /* defines the PyCapsule */

  PyObject* c_api_object = PyCapsule_New((void *)PyXbobLearnActivation_API,
      XBOB_EXT_MODULE_PREFIX "." XBOB_EXT_MODULE_NAME "._C_API", 0);

#else

  PyObject* c_api_object = PyCObject_FromVoidPtr((void *)PyXbobLearnActivation_API, 0);

#endif

  if (c_api_object) PyModule_AddObject(m, "_C_API", c_api_object);

  /* imports dependencies */
  if (import_xbob_blitz() < 0) {
    PyErr_Print();
    PyErr_Format(PyExc_ImportError, "cannot import `%s'", XBOB_EXT_MODULE_NAME);
    return 0;
  }

  if (import_xbob_io_base() < 0) {
    PyErr_Print();
    PyErr_Format(PyExc_ImportError, "cannot import `%s'", XBOB_EXT_MODULE_NAME);
    return 0;
  }

  Py_INCREF(m);
  return m;

}

PyMODINIT_FUNC XBOB_EXT_ENTRY_NAME (void) {
# if PY_VERSION_HEX >= 0x03000000
  return
# endif
    create_module();
}
