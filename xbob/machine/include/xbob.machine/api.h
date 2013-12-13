/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Tue  5 Nov 12:22:48 2013
 *
 * @brief C/C++ API for bob::io
 */

#ifndef XBOB_MACHINE_H
#define XBOB_MACHINE_H

#include <Python.h>
#include <xbob.machine/config.h>
#include <bob/config.h>
#include <bob/machine/Activation.h>

#define XBOB_MACHINE_MODULE_PREFIX xbob.machine
#define XBOB_MACHINE_MODULE_NAME _library

/*******************
 * C API functions *
 *******************/

/**************
 * Versioning *
 **************/

#define PyXbobMachine_APIVersion_NUM 0
#define PyXbobMachine_APIVersion_TYPE int

/***********************************
 * Bindings for xbob.io.Activation *
 ***********************************/

/* Type definition for PyBobIoFileObject */
typedef struct {
  PyObject_HEAD

  /* Type-specific fields go here. */
  boost::shared_ptr<bob::machine::Activation> o;

} PyBobMachineActivation;

#define PyBobMachineActivation_Type_NUM 1
#define PyBobMachineActivation_Type_TYPE PyTypeObject

/* Total number of C API pointers */
#define PyXbobMachine_API_pointers 2

#ifdef XBOB_MACHINE_MODULE

  /* This section is used when compiling `xbob.core.random' itself */

  /**************
   * Versioning *
   **************/

  extern int PyXbobMachine_APIVersion;

  /****************************************
   * Bindings for xbob.machine.Activation *
   ****************************************/

  extern PyBobMachineActivation_Type_TYPE PyBobMachineActivation_Type;

#else

  /* This section is used in modules that use `blitz.array's' C-API */

/************************************************************************
 * Macros to avoid symbol collision and allow for separate compilation. *
 * We pig-back on symbols already defined for NumPy and apply the same  *
 * set of rules here, creating our own API symbol names.                *
 ************************************************************************/

#  if defined(PY_ARRAY_UNIQUE_SYMBOL)
#    define XBOB_MACHINE_MAKE_API_NAME_INNER(a) XBOB_MACHINE_ ## a
#    define XBOB_MACHINE_MAKE_API_NAME(a) XBOB_MACHINE_MAKE_API_NAME_INNER(a)
#    define PyXbobMachine_API XBOB_MACHINE_MAKE_API_NAME(PY_ARRAY_UNIQUE_SYMBOL)
#  endif

#  if defined(NO_IMPORT_ARRAY)
  extern void **PyXbobMachine_API;
#  else
#    if defined(PY_ARRAY_UNIQUE_SYMBOL)
  void **PyXbobMachine_API;
#    else
  static void **PyXbobMachine_API=NULL;
#    endif
#  endif

  static void **PyXbobMachine_API;

  /**************
   * Versioning *
   **************/

# define PyXbobMachine_APIVersion (*(PyXbobMachine_APIVersion_TYPE *)PyXbobMachine_API[PyXbobMachine_APIVersion_NUM])

  /****************************************
   * Bindings for xbob.machine.Activation *
   ****************************************/

# if !defined(NO_IMPORT_ARRAY)

  /**
   * Returns -1 on error, 0 on success. PyCapsule_Import will set an exception
   * if there's an error.
   */
  static int import_xbob_io(void) {

    PyObject *c_api_object;
    PyObject *module;

    module = PyImport_ImportModule(BOOST_PP_STRINGIZE(XBOB_MACHINE_MODULE_PREFIX) "." BOOST_PP_STRINGIZE(XBOB_MACHINE_MODULE_NAME));

    if (module == NULL) return -1;

    c_api_object = PyObject_GetAttrString(module, "_C_API");

    if (c_api_object == NULL) {
      Py_DECREF(module);
      return -1;
    }

#   if PY_VERSION_HEX >= 0x02070000
    if (PyCapsule_CheckExact(c_api_object)) {
      PyXbobMachine_API = (void **)PyCapsule_GetPointer(c_api_object,
          PyCapsule_GetName(c_api_object));
    }
#   else
    if (PyCObject_Check(c_api_object)) {
      XbobMachine_API = (void **)PyCObject_AsVoidPtr(c_api_object);
    }
#   endif

    Py_DECREF(c_api_object);
    Py_DECREF(module);

    if (!XbobMachine_API) {
      PyErr_Format(PyExc_ImportError,
#   if PY_VERSION_HEX >= 0x02070000
          "cannot find C/C++ API capsule at `%s.%s._C_API'",
#   else
          "cannot find C/C++ API cobject at `%s.%s._C_API'",
#   endif
          BOOST_PP_STRINGIZE(XBOB_MACHINE_MODULE_PREFIX),
          BOOST_PP_STRINGIZE(XBOB_MACHINE_MODULE_NAME));
      return -1;
    }

    /* Checks that the imported version matches the compiled version */
    int imported_version = *(int*)PyXbobMachine_API[PyXbobMachine_APIVersion_NUM];

    if (XBOB_MACHINE_API_VERSION != imported_version) {
      PyErr_Format(PyExc_ImportError, "%s.%s import error: you compiled against API version 0x%04x, but are now importing an API with version 0x%04x which is not compatible - check your Python runtime environment for errors", BOOST_PP_STRINGIZE(XBOB_MACHINE_MODULE_PREFIX), BOOST_PP_STRINGIZE(XBOB_MACHINE_MODULE_NAME), XBOB_MACHINE_API_VERSION, imported_version);
      return -1;
    }

    /* If you get to this point, all is good */
    return 0;

  }

# endif //!defined(NO_IMPORT_ARRAY)

#endif /* XBOB_MACHINE_MODULE */

#endif /* XBOB_MACHINE_H */
