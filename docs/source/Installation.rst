.. -*- coding: utf-8 -*-

.. _installation_rst:

=============
Installation
=============

Quick start video
==================

The video below shows you how to build and launch a quick test with BUtils.

.. raw:: html

    <script id="asciicast-pxITpcCQsCXepW80eHSjB5byF" src="https://asciinema.org/a/pxITpcCQsCXepW80eHSjB5byF.js" async></script>

Quick start
===========

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

--------------
Prerequisites
--------------

::

    C++ Standard: c++11
    Build tools: cmake make autoconf automake gcc

--------------
Installation
--------------

.. code-block:: console

    $ git clone https://gitlab.com/zhangbolily/BUtils.git BUtils
    $ cd BUtils
    $ git submodule update --init --recursive
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ make install

------------------
Running the tests
------------------

.. code-block:: console

    $ cd build
    $ rm -rf ./*
    $ cmake -DBUILD_TESTING=ON -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug ..
    $ make tests
    $ bin/tests
