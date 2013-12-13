.. vim: set fileencoding=utf-8 :
.. Andre Anjos <andre.dos.anjos@gmail.com>
.. Tue 15 Oct 14:59:05 2013

=========
 C++ API
=========

The C++ API of ``xbob.machine`` allows users to leverage from automatic
converters for classes in :py:class:`xbob.machine`.  To use the C API, clients
should first, include the header file ``<xbob.machine/api.h>`` on their
compilation units and then, make sure to call once ``import_xbob_machine()`` at
their module instantiation, as explained at the `Python manual
<http://docs.python.org/2/extending/extending.html#using-capsules>`_.

Here is a dummy C example showing how to include the header and where to call
the import function:

.. code-block:: c++

   #include <xbob.machine/api.h>

   PyMODINIT_FUNC initclient(void) {

     PyObject* m Py_InitModule("client", ClientMethods);

     if (!m) return;

     // imports the NumPy C-API
     import_array();

     // imports blitz.array C-API
     import_xbob_blitz();

     // imports xbob.io C-API
     import_xbob_io();

     // imports xbob.machine C-API
     import_xbob_machine();

   }

.. note::

  The include directory can be discovered using
  :py:func:`xbob.machine.get_include`.

Activation Support
------------------

.. cpp:type:: PyBobMachineActivationObject

   The pythonic object representation for a ``bob::machine::Activation``
   object.

   .. code-block:: cpp

      typedef struct {
        PyObject_HEAD
        boost::shared_ptr<bob::machine::Activation> a;
      } PyBobIoFileObject;

   .. cpp:member:: boost::shared_ptr<bob::machine::Activation> a

      A pointer to the activation function implementation

.. include:: links.rst
