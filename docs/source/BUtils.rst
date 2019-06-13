.. -*- coding: utf-8 -*-

.. _butils_rst:

=============
BUtils
=============

Defined in header <BUtils/BUtils>

Overview
========

Namespace BUtils provides many utility functions.

Public Types
=============

.. list-table::
    :widths: 1 4
    :align: left

    * - enum
      - :cpp:enum:`None`

Public Functions
=================

.. list-table::
    :widths: 1 4
    :align: left

    * - std::string
      - :cpp:func:`generateUUID4()`

    * - bool
      - :cpp:func:`isUUID4(const std::string &_uuid) <isUUID4()>`

Detailed Description
=====================

Namespace BUtils provides many utility functions.


Member Function Documentation
===============================

.. cpp:function:: std::string generateUUID4()

Returns a version 4 UUID(Based on random value).

.. cpp:function:: bool isUUID4(const std::string &_uuid)

Returns true if the input UUID is valid.
