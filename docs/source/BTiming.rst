.. -*- coding: utf-8 -*-

.. _btiming_rst:

=============
BTiming
=============

Defined in header "BUtils/BTiming.h"

Overview
========

Class BTiming is for recording time with a minimum precision of 1 microsecond.

API
===

-----
Types
-----

.. code-block:: cpp
    :linenos:

    enum BTimingStatus {
        CPUTiming,
        Timing,
        Stop
    };

-------
Methods
-------

Reference
---------

.. cpp:function:: BTiming() noexcept

Construct a BTiming object.

.. cpp:function:: ~BTiming()

Destruct a BTiming object.

.. cpp:function:: void start()

Start recording real time. Takes no effects if startCPUTiming is called.

.. cpp:function:: void stop()

Stop recording real time. Takes no effects if startCPUTiming is called.

.. cpp:function:: void startCPUTiming()

Start recording CPU time. Takes no effects if start is called.

.. cpp:function:: void stopCPUTiming()

Stop recording CPU time. Takes no effects if start is called.

.. cpp:function:: bool isActive()

Returns true if timing.

.. cpp:function:: int64 time() const

Returns the real time recorded by calling start and stop in microseconds; otherwise returns 0.

.. cpp:function:: int64 CPUTime() const

Returns the CPU time recorded by calling startCPUTiming and stopCPUTiming in microseconds; otherwise returns 0.