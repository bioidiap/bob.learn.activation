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

/* Type definition for PyBobMachineActivationObject */
typedef struct {
  PyObject_HEAD

  /* Type-specific fields go here. */
  bob::machine::Activation* base;

} PyBobMachineActivationObject;

#define PyBobMachineActivation_Type_NUM 1
#define PyBobMachineActivation_Type_TYPE PyTypeObject

#define PyBobMachineActivation_Check_NUM 2
#define PyBobMachineActivation_Check_RET int
#define PyBobMachineActivation_Check_PROTO (PyObject* o)

/*******************************************
 * Bindings for xbob.io.IdentityActivation *
 *******************************************/

/* Type definition for PyBobMachineIdentityActivationObject */
typedef struct {
  PyBobMachineActivationObject parent;

  /* Type-specific fields go here. */
  bob::machine::IdentityActivation* base;

} PyBobMachineIdentityActivationObject;

#define PyBobMachineIdentityActivation_Type_NUM 3
#define PyBobMachineIdentityActivation_Type_TYPE PyTypeObject

/*****************************************
 * Bindings for xbob.io.LinearActivation *
 *****************************************/

/* Type definition for PyBobMachineLinearActivationObject */
typedef struct {
  PyBobMachineActivationObject parent;

  /* Type-specific fields go here. */
  bob::machine::LinearActivation* base;

} PyBobMachineLinearActivationObject;

#define PyBobMachineLinearActivation_Type_NUM 4
#define PyBobMachineLinearActivation_Type_TYPE PyTypeObject

/*******************************************
 * Bindings for xbob.io.LogisticActivation *
 *******************************************/

/* Type definition for PyBobMachineLogisticActivationObject */
typedef struct {
  PyBobMachineActivationObject parent;

  /* Type-specific fields go here. */
  bob::machine::LogisticActivation* base;

} PyBobMachineLogisticActivationObject;

#define PyBobMachineLogisticActivation_Type_NUM 5
#define PyBobMachineLogisticActivation_Type_TYPE PyTypeObject

/****************************************************
 * Bindings for xbob.io.HyperbolicTangentActivation *
 ****************************************************/

/* Type definition for PyBobMachineHyperbolicTangentActivationObject */
typedef struct {
  PyBobMachineActivationObject parent;

  /* Type-specific fields go here. */
  bob::machine::HyperbolicTangentActivation* base;

} PyBobMachineHyperbolicTangentActivationObject;

#define PyBobMachineHyperbolicTangentActivation_Type_NUM 6
#define PyBobMachineHyperbolicTangentActivation_Type_TYPE PyTypeObject

/**************************************************************
 * Bindings for xbob.io.MultipliedHyperbolicTangentActivation *
 **************************************************************/

/* Type definition: PyBobMachineMultipliedHyperbolicTangentActivationObject */
typedef struct {
  PyBobMachineActivationObject parent;

  /* Type-specific fields go here. */
  bob::machine::MultipliedHyperbolicTangentActivation* base;

} PyBobMachineMultipliedHyperbolicTangentActivationObject;

#define PyBobMachineMultipliedHyperbolicTangentActivation_Type_NUM 7
#define PyBobMachineMultipliedHyperbolicTangentActivation_Type_TYPE PyTypeObject

/* Total number of C API pointers */
#define PyXbobMachine_API_pointers 8

#ifdef XBOB_MACHINE_MODULE

  /* This section is used when compiling `xbob.machine' itself */

  /**************
   * Versioning *
   **************/

  extern int PyXbobMachine_APIVersion;

  /****************************************
   * Bindings for xbob.machine.Activation *
   ****************************************/

  extern PyBobMachineActivation_Type_TYPE PyBobMachineActivation_Type;

  PyBobMachineActivation_Check_RET PyBobMachineActivation_Check PyBobMachineActivation_Check_PROTO;

  /*******************************************
   * Bindings for xbob.io.IdentityActivation *
   *******************************************/

  extern PyBobMachineIdentityActivation_Type_TYPE PyBobMachineIdentityActivation_Type;

  /*****************************************
   * Bindings for xbob.io.LinearActivation *
   *****************************************/

  extern PyBobMachineLinearActivation_Type_TYPE PyBobMachineLinearActivation_Type;

  /*******************************************
   * Bindings for xbob.io.LogisticActivation *
   *******************************************/

  extern PyBobMachineLogisticActivation_Type_TYPE PyBobMachineLogisticActivation_Type;

  /****************************************************
   * Bindings for xbob.io.HyperbolicTangentActivation *
   ****************************************************/

  extern PyBobMachineHyperbolicTangentActivation_Type_TYPE PyBobMachineHyperbolicTangentActivation_Type;

  /**************************************************************
   * Bindings for xbob.io.MultipliedHyperbolicTangentActivation *
   **************************************************************/

  extern PyBobMachineMultipliedHyperbolicTangentActivation_Type_TYPE PyBobMachineMultipliedHyperbolicTangentActivation_Type;

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

  /**************
   * Versioning *
   **************/

# define PyXbobMachine_APIVersion (*(PyXbobMachine_APIVersion_TYPE *)PyXbobMachine_API[PyXbobMachine_APIVersion_NUM])

  /****************************************
   * Bindings for xbob.machine.Activation *
   ****************************************/

# define PyBobMachineActivation_Type (*(PyBobMachineActivation_Type_TYPE *)PyXbobMachine_API[PyBobMachineActivation_Type_NUM])

# define PyBobMachineActivation_Check (*(PyBobMachineActivation_Check_RET (*)PyBobMachineActivation_Check_PROTO) PyXbobMachine_API[PyBobMachineActivation_Check_NUM])

  /************************************************
   * Bindings for xbob.machine.IdentityActivation *
   ************************************************/

# define PyBobMachineIdentityActivation_Type (*(PyBobMachineIdentityActivation_Type_TYPE *)PyXbobMachine_API[PyBobMachineIdentityActivation_Type_NUM])

  /**********************************************
   * Bindings for xbob.machine.LinearActivation *
   **********************************************/

# define PyBobMachineLinearActivation_Type (*(PyBobMachineLinearActivation_Type_TYPE *)PyXbobMachine_API[PyBobMachineLinearActivation_Type_NUM])

  /************************************************
   * Bindings for xbob.machine.LogisticActivation *
   ************************************************/

# define PyBobMachineLogisticActivation_Type (*(PyBobMachineLogisticActivation_Type_TYPE *)PyXbobMachine_API[PyBobMachineLogisticActivation_Type_NUM])

  /*********************************************************
   * Bindings for xbob.machine.HyperbolicTangentActivation *
   *********************************************************/

# define PyBobMachineHyperbolicTangentActivation_Type (*(PyBobMachineHyperbolicTangentActivation_Type_TYPE *)PyXbobMachine_API[PyBobMachineHyperbolicTangentActivation_Type_NUM])

  /*******************************************************************
   * Bindings for xbob.machine.MultipliedHyperbolicTangentActivation *
   *******************************************************************/

# define PyBobMachineMultipliedHyperbolicTangentActivation_Type (*(PyBobMachineMultipliedHyperbolicTangentActivation_Type_TYPE *)PyXbobMachine_API[PyBobMachineMultipliedHyperbolicTangentActivation_Type_NUM])

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
