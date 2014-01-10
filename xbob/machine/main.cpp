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

  PyObject* m = Py_InitModule3(XBOB_EXT_MODULE_NAME, library_methods, library_docstr);

  /* register some constants */
  PyModule_AddIntConstant(m, "__api_version__", XBOB_MACHINE_API_VERSION);
  PyModule_AddStringConstant(m, "__version__", XBOB_EXT_MODULE_VERSION);

  /* register the types to python */
  Py_INCREF(&PyBobMachineActivation_Type);
  PyModule_AddObject(m, "Activation", (PyObject *)&PyBobMachineActivation_Type);

  static void* PyXbobMachine_API[PyXbobMachine_API_pointers];

  /* exhaustive list of C APIs */

  /**************
   * Versioning *
   **************/

  PyXbobMachine_API[PyXbobMachine_APIVersion_NUM] = (void *)&PyXbobMachine_APIVersion;

  /*****************************
   * Bindings for xbob.io.file *
   *****************************/

  PyXbobMachine_API[PyBobMachineActivation_Type_NUM] = (void *)&PyBobMachineActivation_Type;

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
