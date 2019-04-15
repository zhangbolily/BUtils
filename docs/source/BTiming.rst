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

.. highlight:: cpp
    :linenothreshold: 5
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

.. function:: BTiming() noexcept

Construct a BTiming object.

.. function:: ~BTiming()

Destruct a BTiming object.

.. function:: void start()

Start recording real time. Takes no effects if startCPUTiming is called.

.. function:: void stop()

Stop recording real time. Takes no effects if startCPUTiming is called.

.. function:: void startCPUTiming()

Start recording CPU time. Takes no effects if start is called.

.. function:: void stopCPUTiming()

Stop recording CPU time. Takes no effects if start is called.

.. function:: bool isActive()

Returns true if timing.

.. function:: int64 time() const

Returns the real time recorded by calling start and stop in microseconds; otherwise returns 0.

.. function:: int64 CPUTime() const

Returns the CPU time recorded by calling startCPUTiming and stopCPUTiming in microseconds; otherwise returns 0.