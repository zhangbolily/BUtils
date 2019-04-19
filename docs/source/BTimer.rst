.. -*- coding: utf-8 -*-

.. _btimer_rst:

=============
BTimer
=============

Defined in header "BUtils/BTimer.h"

Overview
========

Class BTimer provides repetitive and single-shot timers with a minimum precision of 1 millisecond.

Types
=====

.. code-block:: cpp
    :linenos:

    enum BTimerStatus {
        Active,
        Stop
    };

Public Functions
=================

.. list-table::
    :widths: 1 4
    :align: left

    * -
      - :cpp:func:`BTimer()`

    * -
      - :cpp:func:`~BTimer()`

    * - bool
      - :cpp:func:`operator>(const BTimer& rtimer) const <operator>()>`

    * - bool
      - :cpp:func:`operator\<(const BTimer& rtimer) const <operator<()>`

    * - bool
      - :cpp:func:`operator=(const BTimer& rtimer) const <operator=()>`

    * - void
      - :cpp:func:`start()`

    * - void
      - :cpp:func:`stop()`

    * - bool
      - :cpp:func:`isActive() const <isActive()>`

    * - bool
      - :cpp:func:`isSingleShot() const <isSingleShot()>`

    * - int32
      - :cpp:func:`id() const <id()>`

    * - uint32
      - :cpp:func:`interval() const <interval()>`

    * - uint32
      - :cpp:func:`timeout() const <timeout()>`

    * - void
      - :cpp:func:`reset()`

    * - void
      - :cpp:func:`setActive(bool) <setActive()>`

    * - void
      - :cpp:func:`callOnInterval(std::function timer_action) <callOnInterval()>`

    * - void
      - :cpp:func:`callOnTimeout(std::function timer_action) <callOnTimeout()>`

    * - void
      - :cpp:func:`setInterval(uint32 _interval) <setInterval()>`

    * - void
      - :cpp:func:`setInterval(std::chrono::milliseconds _interval) <setInterval()>`

    * - void
      - :cpp:func:`setTimeout(uint32 _timeout) <setTimeout()>`

    * - void
      - :cpp:func:`setTimeout(std::chrono::milliseconds _timeout) <setTimeout()>`

    * - void
      - :cpp:func:`setSingleShot(bool singleshot) <setSingleShot()>`

Static Public Functions
========================

.. list-table::
    :widths: 1 4
    :align: left

    * - uint
      - :cpp:func:`precision()`

    * - void
      - :cpp:func:`setPrecision(uint) <setPrecision()>`

Detailed Description
=====================

Class BTimer provides repetitive and single-shot timers with a minimum precision of 1 millisecond.

BTimer provides a easy to user programing interface for doing periodic jobs in your application.
Just create a :term:`timer` and set up the properties, then start it.
You can change the properties of a timer at any time.

Example for a one second timer:

.. code-block:: cpp
    :linenos:

    #include <BUtils/BTimer>
    #include <unistd.h>
    #include <iostream>

    void timerAction() {
        std::cout << "I'm timer action." << std::endl;
    }

    int main() {
        BUtils::BTimer timer;
        timer.callOnTimeout(timerAction);
        timer.setTimeout(1000);
        timer.start();
        // If timer object is destroyed, the timer event do not exist as well.
        // Sleep to make the timeout event occur.
        sleep(2);
    }

BTimer's timer event system is designed to work in multi-threads environments, but BTimer object itself doesn't.
Do not share a single BTimer object in threads, just create and use it in the same thread.

------------------------------
Accuracy and Timer Resolution
------------------------------

The accuracy of timers depends on the underlying operating system and hardware.
Most platforms support a resolution of 1 millisecond,
though the accuracy of the timer will not equal this resolution in many real-world situations.

Reference
==========

.. cpp:function:: explicit BTimer() noexcept

Construct a BTimer object.

.. cpp:function:: ~BTimer()

Destruct a BTimer object.

.. cpp:function:: bool operator>(const BTimer& rtimer) const

Returns true if id is greater than rtimer's id.

.. cpp:function:: bool operator<(const BTimer& rtimer) const

Returns true if id is less than rtimer's id.

.. cpp:function:: bool operator==(const BTimer& rtimer) const

Returns true if id is equal to rtimer's id.

.. cpp:function:: void start()

Start this timer; takes no effects if timeout is 0.

.. cpp:function:: void stop()

Stop this timer; takes no effects if this timer is expired(timeout occurs).

.. cpp:function:: bool isActive() const

Returns true if this timer is running.

.. cpp:function:: bool isSingleShot() const

Returns true if interval action is only triggered once.

.. cpp:function:: int32 id() const

Returns the id of this timer.

.. cpp:function:: uint32 interval() const

Returns the timeout interval of this timer in milliseconds.

.. cpp:function:: uint32 timeout() const

Returns the timeout of this timer in milliseconds.

.. cpp:function:: void reset()

Reset all properties of this timer(except timer id) to default value and stop this timer.

.. cpp:function:: void setActive(bool _active)

Takes no effects calling by user.

.. cpp:function:: void callOnInterval(std::function<void()> timer_action)

Set the action that will be triggered after timeout interval.

.. cpp:function:: void callOnTimeout(std::function<void()> timer_action)

Set the action that will be triggered after timeout.

.. cpp:function:: void setInterval(uint32 _interval)
.. cpp:function:: void setInterval(std::chrono::milliseconds _interval)

Set the timeout interval in milliseconds. Default value is 0.

.. cpp:function:: void setTimeout(uint32 _timeout)
.. cpp:function:: void setTimeout(std::chrono::milliseconds _timeout)

Set the timeout in milliseconds. Default value is the maximum number of unsigned int.

.. cpp:function:: void setSingleShot(bool singleshot)

The interval action will be triggered only once if singleshot is true.

.. cpp:function:: static uint precision()

Returns the precision of timer in milliseconds. Default value is 1 millisecond.

.. cpp:function:: static void setPrecision(uint)

Set the timer precision in milliseconds.