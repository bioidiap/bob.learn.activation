/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Wed 15 Jan 2014 10:15:21 CET
 *
 * @brief C/C++ Python API for activation functors in bob::machine
 */

#ifndef XBOB_LEARN_ACTIVATION_H
#define XBOB_LEARN_ACTIVATION_H

#include <Python.h>
#include <xbob.learn.activation/config.h>
#include <bob/machine/Activation.h>
#include <bob/machine/LinearMachine.h>

#define XBOB_LEARN_ACTIVATION_MODULE_PREFIX xbob.learn.activation
#define XBOB_LEARN_ACTIVATION_MODULE_NAME _library

/*******************
 * C API functions *
 *******************/

/**************
 * Versioning *
 **************/

#define PyXbobLearnActivation_APIVersion_NUM 0
#define PyXbobLearnActivation_APIVersion_TYPE int

/*************************************************
 * Bindings for xbob.learn.activation.Activation *
 *************************************************/

typedef struct {
  PyObject_HEAD
  bob::machine::Activation* base;
} PyBobLearnActivationObject;

#define PyBobLearnActivation_Type_NUM 1
#define PyBobLearnActivation_Type_TYPE PyTypeObject

#define PyBobLearnActivation_Check_NUM 2
#define PyBobLearnActivation_Check_RET int
#define PyBobLearnActivation_Check_PROTO (PyObject* o)

/***********************************************
 * Bindings for xbob.learn.activation.Identity *
 ***********************************************/

typedef struct {
  PyBobLearnActivationObject parent;
  bob::machine::IdentityActivation* base;
} PyBobLearnIdentityActivationObject;

#define PyBobLearnIdentityActivation_Type_NUM 3
#define PyBobLearnIdentityActivation_Type_TYPE PyTypeObject

/*********************************************
 * Bindings for xbob.learn.activation.Linear *
 *********************************************/

typedef struct {
  PyBobLearnActivationObject parent;
  bob::machine::LinearActivation* base;
} PyBobLearnLinearActivationObject;

#define PyBobLearnLinearActivation_Type_NUM 4
#define PyBobLearnLinearActivation_Type_TYPE PyTypeObject

/***********************************************
 * Bindings for xbob.learn.activation.Logistic *
 ***********************************************/

typedef struct {
  PyBobLearnActivationObject parent;
  bob::machine::LogisticActivation* base;
} PyBobLearnLogisticActivationObject;

#define PyBobLearnLogisticActivation_Type_NUM 5
#define PyBobLearnLogisticActivation_Type_TYPE PyTypeObject

/********************************************************
 * Bindings for xbob.learn.activation.HyperbolicTangent *
 ********************************************************/

typedef struct {
  PyBobLearnActivationObject parent;
  bob::machine::HyperbolicTangentActivation* base;
} PyBobLearnHyperbolicTangentActivationObject;

#define PyBobLearnHyperbolicTangentActivation_Type_NUM 6
#define PyBobLearnHyperbolicTangentActivation_Type_TYPE PyTypeObject

/******************************************************************
 * Bindings for xbob.learn.activation.MultipliedHyperbolicTangent *
 ******************************************************************/

typedef struct {
  PyBobLearnActivationObject parent;
  bob::machine::MultipliedHyperbolicTangentActivation* base;
} PyBobLearnMultipliedHyperbolicTangentActivationObject;

#define PyBobLearnMultipliedHyperbolicTangentActivation_Type_NUM 7
#define PyBobLearnMultipliedHyperbolicTangentActivation_Type_TYPE PyTypeObject

/* Total number of C API pointers */
#define PyXbobLearnActivation_API_pointers 8

#ifdef XBOB_LEARN_ACTIVATION_MODULE

  /* This section is used when compiling `xbob.learn.activation' itself */

  /**************
   * Versioning *
   **************/

  extern int PyXbobLearnActivation_APIVersion;

  /*************************************************
   * Bindings for xbob.learn.activation.Activation *
   *************************************************/

  extern PyBobLearnActivation_Type_TYPE PyBobLearnActivation_Type;

  PyBobLearnActivation_Check_RET PyBobLearnActivation_Check PyBobLearnActivation_Check_PROTO;

  /***********************************************
   * Bindings for xbob.learn.activation.Identity *
   ***********************************************/

  extern PyBobLearnIdentityActivation_Type_TYPE PyBobLearnIdentityActivation_Type;

  /*********************************************
   * Bindings for xbob.learn.activation.Linear *
   *********************************************/

  extern PyBobLearnLinearActivation_Type_TYPE PyBobLearnLinearActivation_Type;

  /***********************************************
   * Bindings for xbob.learn.activation.Logistic *
   ***********************************************/

  extern PyBobLearnLogisticActivation_Type_TYPE PyBobLearnLogisticActivation_Type;

  /********************************************************
   * Bindings for xbob.learn.activation.HyperbolicTangent *
   ********************************************************/

  extern PyBobLearnHyperbolicTangentActivation_Type_TYPE PyBobLearnHyperbolicTangentActivation_Type;

  /******************************************************************
   * Bindings for xbob.learn.activation.MultipliedHyperbolicTangent *
   ******************************************************************/

  extern PyBobLearnMultipliedHyperbolicTangentActivation_Type_TYPE PyBobLearnMultipliedHyperbolicTangentActivation_Type;

#else

  /* This section is used in modules that use `xbob.learn.activation's' C-API */

/************************************************************************
 * Macros to avoid symbol collision and allow for separate compilation. *
 * We pig-back on symbols already defined for NumPy and apply the same  *
 * set of rules here, creating our own API symbol names.                *
 ************************************************************************/

#  if defined(PY_ARRAY_UNIQUE_SYMBOL)
#    define XBOB_LEARN_ACTIVATION_MAKE_API_NAME_INNER(a) XBOB_LEARN_ACTIVATION_ ## a
#    define XBOB_LEARN_ACTIVATION_MAKE_API_NAME(a) XBOB_LEARN_ACTIVATION_MAKE_API_NAME_INNER(a)
#    define PyXbobLearnActivation_API XBOB_LEARN_ACTIVATION_MAKE_API_NAME(PY_ARRAY_UNIQUE_SYMBOL)
#  endif

#  if defined(NO_IMPORT_ARRAY)
  extern void **PyXbobLearnActivation_API;
#  else
#    if defined(PY_ARRAY_UNIQUE_SYMBOL)
  void **PyXbobLearnActivation_API;
#    else
  static void **PyXbobLearnActivation_API=NULL;
#    endif
#  endif

  /**************
   * Versioning *
   **************/

# define PyXbobLearnActivation_APIVersion (*(PyXbobLearnActivation_APIVersion_TYPE *)PyXbobLearnActivation_API[PyXbobLearnActivation_APIVersion_NUM])

  /*************************************************
   * Bindings for xbob.learn.activation.Activation *
   *************************************************/

# define PyBobLearnActivation_Type (*(PyBobLearnActivation_Type_TYPE *)PyXbobLearnActivation_API[PyBobLearnActivation_Type_NUM])

# define PyBobLearnActivation_Check (*(PyBobLearnActivation_Check_RET (*)PyBobLearnActivation_Check_PROTO) PyXbobLearnActivation_API[PyBobLearnActivation_Check_NUM])

  /***********************************************
   * Bindings for xbob.learn.activation.Identity *
   ***********************************************/

# define PyBobLearnIdentityActivation_Type (*(PyBobLearnIdentityActivation_Type_TYPE *)PyXbobLearnActivation_API[PyBobLearnIdentityActivation_Type_NUM])

  /*********************************************
   * Bindings for xbob.learn.activation.Linear *
   *********************************************/

# define PyBobLearnLinearActivation_Type (*(PyBobLearnLinearActivation_Type_TYPE *)PyXbobLearnActivation_API[PyBobLearnLinearActivation_Type_NUM])

  /***********************************************
   * Bindings for xbob.learn.activation.Logistic *
   ***********************************************/

# define PyBobLearnLogisticActivation_Type (*(PyBobLearnLogisticActivation_Type_TYPE *)PyXbobLearnActivation_API[PyBobLearnLogisticActivation_Type_NUM])

  /********************************************************
   * Bindings for xbob.learn.activation.HyperbolicTangent *
   ********************************************************/

# define PyBobLearnHyperbolicTangentActivation_Type (*(PyBobLearnHyperbolicTangentActivation_Type_TYPE *)PyXbobLearnActivation_API[PyBobLearnHyperbolicTangentActivation_Type_NUM])

  /******************************************************************
   * Bindings for xbob.learn.activation.MultipliedHyperbolicTangent *
   ******************************************************************/

# define PyBobLearnMultipliedHyperbolicTangentActivation_Type (*(PyBobLearnMultipliedHyperbolicTangentActivation_Type_TYPE *)PyXbobLearnActivation_API[PyBobLearnMultipliedHyperbolicTangentActivation_Type_NUM])

# if !defined(NO_IMPORT_ARRAY)

  /**
   * Returns -1 on error, 0 on success. PyCapsule_Import will set an exception
   * if there's an error.
   */
  static int import_xbob_io(void) {

    PyObject *c_api_object;
    PyObject *module;

    module = PyImport_ImportModule(BOOST_PP_STRINGIZE(XBOB_LEARN_ACTIVATION_MODULE_PREFIX) "." BOOST_PP_STRINGIZE(XBOB_LEARN_ACTIVATION_MODULE_NAME));

    if (module == NULL) return -1;

    c_api_object = PyObject_GetAttrString(module, "_C_API");

    if (c_api_object == NULL) {
      Py_DECREF(module);
      return -1;
    }

#   if PY_VERSION_HEX >= 0x02070000
    if (PyCapsule_CheckExact(c_api_object)) {
      PyXbobLearnActivation_API = (void **)PyCapsule_GetPointer(c_api_object,
          PyCapsule_GetName(c_api_object));
    }
#   else
    if (PyCObject_Check(c_api_object)) {
      XbobLearnActivation_API = (void **)PyCObject_AsVoidPtr(c_api_object);
    }
#   endif

    Py_DECREF(c_api_object);
    Py_DECREF(module);

    if (!XbobLearnActivation_API) {
      PyErr_Format(PyExc_ImportError,
#   if PY_VERSION_HEX >= 0x02070000
          "cannot find C/C++ API capsule at `%s.%s._C_API'",
#   else
          "cannot find C/C++ API cobject at `%s.%s._C_API'",
#   endif
          BOOST_PP_STRINGIZE(XBOB_LEARN_ACTIVATION_MODULE_PREFIX),
          BOOST_PP_STRINGIZE(XBOB_LEARN_ACTIVATION_MODULE_NAME));
      return -1;
    }

    /* Checks that the imported version matches the compiled version */
    int imported_version = *(int*)PyXbobLearnActivation_API[PyXbobLearnActivation_APIVersion_NUM];

    if (XBOB_LEARN_ACTIVATION_API_VERSION != imported_version) {
      PyErr_Format(PyExc_ImportError, "%s.%s import error: you compiled against API version 0x%04x, but are now importing an API with version 0x%04x which is not compatible - check your Python runtime environment for errors", BOOST_PP_STRINGIZE(XBOB_LEARN_ACTIVATION_MODULE_PREFIX), BOOST_PP_STRINGIZE(XBOB_LEARN_ACTIVATION_MODULE_NAME), XBOB_LEARN_ACTIVATION_API_VERSION, imported_version);
      return -1;
    }

    /* If you get to this point, all is good */
    return 0;

  }

# endif //!defined(NO_IMPORT_ARRAY)

#endif /* XBOB_LEARN_ACTIVATION_MODULE */

#endif /* XBOB_LEARN_ACTIVATION_H */
