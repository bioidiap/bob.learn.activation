/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Thu  7 Nov 13:50:16 2013
 *
 * @brief Binds configuration information available from bob
 */

#include <Python.h>
#include "cleanup.h"

#define XBOB_MACHINE_MODULE
#include <xbob.machine/config.h>
#include <bob/config.h>
#include <boost/format.hpp>

#if WITH_LIBSVM
#include <svm.h>
#endif

static PyObject* get_libsvm_version() {
#if WITH_LIBSVM
  boost::format s("%d.%d.%d");
  s % (LIBSVM_VERSION / 100);
  s % ((LIBSVM_VERSION % 100) / 10);
  s % (LIBSVM_VERSION % 10);
  return Py_BuildValue("s", s.str().c_str());
#else
  return Py_BuildValue("s", "unavailable");
#endif
}

static PyObject* build_version_dictionary() {

  PyObject* retval = PyDict_New();
  if (!retval) return 0;
  auto retval_ = make_safe(retval);

  PyObject* version_string = get_libsvm_version();
  if (!version_string) return 0;
  auto version_string_ = make_safe(version_string);

  int status = PyDict_SetItemString(retval, "libsvm", version_string);
  if (status == 0) return 0;

  Py_INCREF(retval);
  return retval;

}

static PyMethodDef module_methods[] = {
    {0}  /* Sentinel */
};

PyDoc_STRVAR(module_docstr,
"Information about software used to compile the C++ Bob API"
);

PyMODINIT_FUNC XBOB_EXT_ENTRY_NAME (void) {

  PyObject* m = Py_InitModule3(XBOB_EXT_MODULE_NAME, module_methods, module_docstr);

  /* register some constants */
  PyModule_AddIntConstant(m, "__api_version__", XBOB_MACHINE_API_VERSION);
  PyModule_AddStringConstant(m, "__version__", XBOB_EXT_MODULE_VERSION);
  PyModule_AddObject(m, "versions", build_version_dictionary());

}
