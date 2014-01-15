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
#include <xbob.io/api.h>

static PyMethodDef library_methods[] = {
    {0}  /* Sentinel */
};

PyDoc_STRVAR(library_docstr, "classes for activation functors");

int PyXbobLearnActivation_APIVersion = XBOB_LEARN_ACTIVATION_API_VERSION;

PyMODINIT_FUNC XBOB_EXT_ENTRY_NAME (void) {

  PyBobLearnActivation_Type.tp_new = PyType_GenericNew;
  if (PyType_Ready(&PyBobLearnActivation_Type) < 0) return;

  PyBobLearnIdentityActivation_Type.tp_base = &PyBobLearnActivation_Type;
  if (PyType_Ready(&PyBobLearnIdentityActivation_Type) < 0) return;

  PyBobLearnLinearActivation_Type.tp_base = &PyBobLearnActivation_Type;
  if (PyType_Ready(&PyBobLearnLinearActivation_Type) < 0) return;

  PyBobLearnLogisticActivation_Type.tp_base = &PyBobLearnActivation_Type;
  if (PyType_Ready(&PyBobLearnLogisticActivation_Type) < 0) return;

  PyBobLearnHyperbolicTangentActivation_Type.tp_base =
    &PyBobLearnActivation_Type;
  if (PyType_Ready(&PyBobLearnHyperbolicTangentActivation_Type) < 0) return;

  PyBobLearnMultipliedHyperbolicTangentActivation_Type.tp_base =
    &PyBobLearnActivation_Type;
  if (PyType_Ready(&PyBobLearnMultipliedHyperbolicTangentActivation_Type) < 0)
    return;

  PyObject* m = Py_InitModule3(XBOB_EXT_MODULE_NAME, library_methods, library_docstr);

  /* register some constants */
  PyModule_AddIntConstant(m, "__api_version__",
      XBOB_LEARN_ACTIVATION_API_VERSION);
  PyModule_AddStringConstant(m, "__version__", XBOB_EXT_MODULE_VERSION);

  /* register the types to python */
  Py_INCREF(&PyBobLearnActivation_Type);
  PyModule_AddObject(m, "Activation", (PyObject *)&PyBobLearnActivation_Type);

  Py_INCREF(&PyBobLearnIdentityActivation_Type);
  PyModule_AddObject(m, "Identity", (PyObject *)&PyBobLearnIdentityActivation_Type);

  Py_INCREF(&PyBobLearnLinearActivation_Type);
  PyModule_AddObject(m, "Linear", (PyObject *)&PyBobLearnLinearActivation_Type);

  Py_INCREF(&PyBobLearnLogisticActivation_Type);
  PyModule_AddObject(m, "Logistic", (PyObject *)&PyBobLearnLogisticActivation_Type);

  Py_INCREF(&PyBobLearnHyperbolicTangentActivation_Type);
  PyModule_AddObject(m, "HyperbolicTangent", (PyObject *)&PyBobLearnHyperbolicTangentActivation_Type);

  Py_INCREF(&PyBobLearnMultipliedHyperbolicTangentActivation_Type);
  PyModule_AddObject(m, "MultipliedHyperbolicTangent", (PyObject *)&PyBobLearnMultipliedHyperbolicTangentActivation_Type);

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

  /* imports the NumPy C-API */
  import_array();

  /* imports xbob.blitz C-API */
  import_xbob_blitz();

  /* imports xbob.io C-API */
  import_xbob_io();

}
