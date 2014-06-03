#!/usr/bin/env python
# vim: set fileencoding=utf-8 :
# Andre Anjos <andre.anjos@idiap.ch>
# Mon 16 Apr 08:18:08 2012 CEST

from setuptools import setup, find_packages, dist
dist.Distribution(dict(setup_requires=['bob.blitz', 'bob.io.base']))
from bob.blitz.extension import Extension
import bob.io.base

import os
package_dir = os.path.dirname(os.path.realpath(__file__))
package_dir = os.path.join(package_dir, 'bob', 'learn', 'activation', 'include')
include_dirs = [package_dir, bob.io.base.get_include()]

packages = ['bob-machine >= 1.2.2']
version = '2.0.0a0'

setup(

    name='bob.learn.activation',
    version=version,
    description='Bindings for bob.machine\'s Activation functors',
    url='http://github.com/bioidiap/bob.learn.activation',
    license='BSD',
    author='Andre Anjos',
    author_email='andre.anjos@idiap.ch',

    long_description=open('README.rst').read(),

    packages=find_packages(),
    include_package_data=True,
    zip_safe=False,

    install_requires=[
      'setuptools',
      'bob.blitz',
      'bob.io.base',
    ],

    namespace_packages=[
      "bob",
      "bob.learn",
      ],

    ext_modules = [
      Extension("bob.learn.activation.version",
        [
          "bob/learn/activation/version.cpp",
          ],
        packages = packages,
        include_dirs = include_dirs,
        version = version,
        ),
      Extension("bob.learn.activation._library",
        [
          "bob/learn/activation/activation.cpp",
          "bob/learn/activation/identity.cpp",
          "bob/learn/activation/linear.cpp",
          "bob/learn/activation/logistic.cpp",
          "bob/learn/activation/tanh.cpp",
          "bob/learn/activation/mult_tanh.cpp",
          "bob/learn/activation/main.cpp",
          ],
        packages = packages,
        include_dirs = include_dirs,
        version = version,
        ),
      ],

    classifiers = [
      'Development Status :: 3 - Alpha',
      'Intended Audience :: Developers',
      'License :: OSI Approved :: BSD License',
      'Natural Language :: English',
      'Programming Language :: Python',
      'Programming Language :: Python :: 3',
      'Topic :: Software Development :: Libraries :: Python Modules',
      ],

    )
