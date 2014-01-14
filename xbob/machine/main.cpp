/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Fri 13 Dec 2013 12:35:59 CET
 *
 * @brief Bindings to bob::machine
 */

#define XBOB_MACHINE_MODULE
#include <xbob.machine/api.h>

#ifdef NO_IMPORT_ARRAY
#undef NO_IMPORT_ARRAY
#endif
#include <xbob.blitz/capi.h>
#include <xbob.io/api.h>

static PyMethodDef library_methods[] = {
    {0}  /* Sentinel */
};

PyDoc_STRVAR(library_docstr, "bob::machine classes and methods");

int PyXbobMachine_APIVersion = XBOB_MACHINE_API_VERSION;

PyMODINIT_FUNC XBOB_EXT_ENTRY_NAME (void) {

  PyBobMachineActivation_Type.tp_new = PyType_GenericNew;
  if (PyType_Ready(&PyBobMachineActivation_Type) < 0) return;

  PyBobMachineIdentityActivation_Type.tp_base = &PyBobMachineActivation_Type;
  if (PyType_Ready(&PyBobMachineIdentityActivation_Type) < 0) return;

  PyBobMachineLinearActivation_Type.tp_base = &PyBobMachineActivation_Type;
  if (PyType_Ready(&PyBobMachineLinearActivation_Type) < 0) return;

  PyBobMachineLogisticActivation_Type.tp_base = &PyBobMachineActivation_Type;
  if (PyType_Ready(&PyBobMachineLogisticActivation_Type) < 0) return;

  PyBobMachineHyperbolicTangentActivation_Type.tp_base =
    &PyBobMachineActivation_Type;
  if (PyType_Ready(&PyBobMachineHyperbolicTangentActivation_Type) < 0) return;

  PyBobMachineMultipliedHyperbolicTangentActivation_Type.tp_base =
    &PyBobMachineActivation_Type;
  if (PyType_Ready(&PyBobMachineMultipliedHyperbolicTangentActivation_Type) < 0)
    return;

  PyBobMachineLinear_Type.tp_new = PyType_GenericNew;
  if (PyType_Ready(&PyBobMachineLinear_Type) < 0) return;

  PyObject* m = Py_InitModule3(XBOB_EXT_MODULE_NAME, library_methods, library_docstr);

  /* register some constants */
  PyModule_AddIntConstant(m, "__api_version__", XBOB_MACHINE_API_VERSION);
  PyModule_AddStringConstant(m, "__version__", XBOB_EXT_MODULE_VERSION);

  /* register the types to python */
  Py_INCREF(&PyBobMachineActivation_Type);
  PyModule_AddObject(m, "Activation", (PyObject *)&PyBobMachineActivation_Type);

  Py_INCREF(&PyBobMachineIdentityActivation_Type);
  PyModule_AddObject(m, "IdentityActivation", (PyObject *)&PyBobMachineIdentityActivation_Type);

  Py_INCREF(&PyBobMachineLinearActivation_Type);
  PyModule_AddObject(m, "LinearActivation", (PyObject *)&PyBobMachineLinearActivation_Type);

  Py_INCREF(&PyBobMachineLogisticActivation_Type);
  PyModule_AddObject(m, "LogisticActivation", (PyObject *)&PyBobMachineLogisticActivation_Type);

  Py_INCREF(&PyBobMachineHyperbolicTangentActivation_Type);
  PyModule_AddObject(m, "HyperbolicTangentActivation", (PyObject *)&PyBobMachineHyperbolicTangentActivation_Type);

  Py_INCREF(&PyBobMachineMultipliedHyperbolicTangentActivation_Type);
  PyModule_AddObject(m, "MultipliedHyperbolicTangentActivation", (PyObject *)&PyBobMachineMultipliedHyperbolicTangentActivation_Type);

  Py_INCREF(&PyBobMachineLinear_Type);
  PyModule_AddObject(m, "LinearMachine", (PyObject *)&PyBobMachineLinear_Type);

  static void* PyXbobMachine_API[PyXbobMachine_API_pointers];

  /* exhaustive list of C APIs */

  /**************
   * Versioning *
   **************/

  PyXbobMachine_API[PyXbobMachine_APIVersion_NUM] = (void *)&PyXbobMachine_APIVersion;

  /****************************************
   * Bindings for xbob.machine.Activation *
   ****************************************/

  PyXbobMachine_API[PyBobMachineActivation_Type_NUM] = (void *)&PyBobMachineActivation_Type;

  PyXbobMachine_API[PyBobMachineActivation_Check_NUM] = (void *)&PyBobMachineActivation_Check;

  /************************************************
   * Bindings for xbob.machine.IdentityActivation *
   ************************************************/

  PyXbobMachine_API[PyBobMachineIdentityActivation_Type_NUM] = (void *)&PyBobMachineIdentityActivation_Type;

  /**********************************************
   * Bindings for xbob.machine.LinearActivation *
   **********************************************/

  PyXbobMachine_API[PyBobMachineLinearActivation_Type_NUM] = (void *)&PyBobMachineLinearActivation_Type;

  /************************************************
   * Bindings for xbob.machine.LogisticActivation *
   ************************************************/

  PyXbobMachine_API[PyBobMachineLogisticActivation_Type_NUM] = (void *)&PyBobMachineLogisticActivation_Type;

  /*********************************************************
   * Bindings for xbob.machine.HyperbolicTangentActivation *
   *********************************************************/

  PyXbobMachine_API[PyBobMachineHyperbolicTangentActivation_Type_NUM] = (void *)&PyBobMachineHyperbolicTangentActivation_Type;

  /*******************************************************************
   * Bindings for xbob.machine.MultipliedHyperbolicTangentActivation *
   *******************************************************************/

  PyXbobMachine_API[PyBobMachineMultipliedHyperbolicTangentActivation_Type_NUM] = (void *)&PyBobMachineMultipliedHyperbolicTangentActivation_Type;

  /************************************
   * Bindings for xbob.machine.Linear *
   ************************************/

  PyXbobMachine_API[PyBobMachineLinear_Type_NUM] = (void *)&PyBobMachineLinear_Type;

  PyXbobMachine_API[PyBobMachineLinear_Check_NUM] = (void *)&PyBobMachineLinear_Check;

#if PY_VERSION_HEX >= 0x02070000

  /* defines the PyCapsule */

  PyObject* c_api_object = PyCapsule_New((void *)PyXbobMachine_API,
      XBOB_EXT_MODULE_PREFIX "." XBOB_EXT_MODULE_NAME "._C_API", 0);

#else

  PyObject* c_api_object = PyCObject_FromVoidPtr((void *)PyXbobMachine_API, 0);

#endif

  if (c_api_object) PyModule_AddObject(m, "_C_API", c_api_object);

  /* imports the NumPy C-API */
  import_array();

  /* imports xbob.blitz C-API */
  import_xbob_blitz();

  /* imports xbob.io C-API */
  import_xbob_io();

}
