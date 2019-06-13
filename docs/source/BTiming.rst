.. -*- coding: utf-8 -*-

.. _btiming_rst:

=============
BTiming
=============

Defined in header <BUtils/BTiming>

Overview
========

Class BTiming provides a timing system to record time with a minimum precision of 1 microsecond.

Public Types
=============

.. list-table::
    :widths: 1 4
    :align: left

    * - enum
      - :cpp:enum:`BTimingStatus {CPUTiming, Timing, Stop} <BTimingStatus>`

Public Functions
=================

.. list-table::
    :widths: 1 4
    :align: left

    * -
      - :cpp:func:`BTiming() noexcept <BTiming::BTiming()>`

    * -
      - :cpp:func:`~BTiming() <BTiming::~BTiming()>`

    * - void
      - :cpp:func:`start() <BTiming::start()>`

    * - void
      - :cpp:func:`stop() <BTiming::stop()>`

    * - void
      - :cpp:func:`startCPUTiming() <BTiming::startCPUTiming()>`

    * - void
      - :cpp:func:`stopCPUTiming() <BTiming::stopCPUTiming()>`

    * - bool
      - :cpp:func:`isActive() <BTiming::isActive()>`

    * - int64
      - :cpp:func:`time() const <BTiming::time()>`

    * - int64
      - :cpp:func:`CPUTime() const <BTiming::CPUTime()>`

Detailed Description
=====================

Class BTiming provides a timing system to record time with a minimum precision of 1 microsecond.

BTiming can record both :term:`real time` and :term:`CPU time` with the same minimum precision of 1 microsecond.

Example for timing one second:

.. code-block:: cpp
    :linenos:

    #include <BUtils/BTiming>
    #include <unistd.h>
    #include <iostream>

    int main() {
        BUtils::BTiming timing;
        BUtils::BTiming CPUTiming;

        timing.start();
        CPUTiming.startCPUTiming();
        sleep(1);
        timing.stop();
        CPUTiming.stopCPUTiming();

        std::cout << "Real time is: " << timing.time() << " us" << std::endl;
        std::cout << "CPU time is: " << CPUTiming.CPUTime() << " us" << std::endl;
    }

Member Type Documentation
==========================

.. cpp:enum:: BTimingStatus

.. list-table::
    :widths: 4 2 4
    :align: left
    :header-rows: 1

    * - Constant
      - Value
      - Description

    * - BTiming::CPUTiming
      - 0
      - Represents recording CPU time.

    * - BTiming::Timing
      - 1
      - Represents recording real time.

    * - BTiming::Stop
      - 2
      - Stopped recording.


Member Function Documentation
===============================

.. cpp:function:: BTiming::BTiming() noexcept

Construct a BTiming object.

.. cpp:function:: BTiming::~BTiming()

Destruct a BTiming object.

.. cpp:function:: void BTiming::start()

Start recording real time. Takes no effects if startCPUTiming is called.

.. cpp:function:: void BTiming::stop()

Stop recording real time. Takes no effects if startCPUTiming is called.

.. cpp:function:: void BTiming::startCPUTiming()

Start recording CPU time. Takes no effects if start is called.

.. cpp:function:: void BTiming::stopCPUTiming()

Stop recording CPU time. Takes no effects if start is called.

.. cpp:function:: bool BTiming::isActive()

Returns true if timing.

.. cpp:function:: int64 BTiming::time() const

Returns the real time recorded by calling start and stop in microseconds; otherwise returns 0.

.. cpp:function:: int64 BTiming::CPUTime() const

Returns the CPU time recorded by calling startCPUTiming and stopCPUTiming in microseconds; otherwise returns 0.