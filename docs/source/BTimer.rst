.. -*- coding: utf-8 -*-

.. _btimer_rst:

=============
BTimer
=============

Defined in header <BUtils/BTimer>

Overview
========

Class BTimer provides repetitive and single-shot timers with a minimum precision of 1 millisecond.

Public Types
=============

.. list-table::
    :widths: 1 4
    :align: left

    * - enum
      - :cpp:enum:`BTimerStatus {Active, Stop} <BTimerStatus>`

Properties
===========

.. list-table::
    :widths: 1 4
    :align: left

    * - bool
      - :cpp:member:`singleShot`

    * - std::chrono::milliseconds
      - :cpp:member:`interval`

    * - std::chrono::milliseconds
      - :cpp:member:`timeout`

Public Functions
=================

.. list-table::
    :widths: 1 4
    :align: left

    * -
      - :cpp:func:`BTimer() <BTimer::BTimer()>`

    * -
      - :cpp:func:`~BTimer() <BTimer::~BTimer()>`

    * - bool
      - :cpp:func:`operator>(const BTimer& rtimer) const <BTimer::operator>()>`

    * - bool
      - :cpp:func:`operator\<(const BTimer& rtimer) const <BTimer::operator<()>`

    * - bool
      - :cpp:func:`operator=(const BTimer& rtimer) const <BTimer::operator=()>`

    * - void
      - :cpp:func:`start() <BTimer::start()>`

    * - void
      - :cpp:func:`stop() <BTimer::stop()>`

    * - bool
      - :cpp:func:`isActive() const <BTimer::isActive()>`

    * - bool
      - :cpp:func:`isSingleShot() const <BTimer::isSingleShot()>`

    * - int32
      - :cpp:func:`id() const <BTimer::id()>`

    * - uint32
      - :cpp:func:`interval() const <BTimer::interval()>`

    * - uint32
      - :cpp:func:`timeout() const <BTimer::timeout()>`

    * - void
      - :cpp:func:`reset() <BTimer::reset()>`

    * - void
      - :cpp:func:`setActive(bool) <BTimer::setActive()>`

    * - void
      - :cpp:func:`callOnInterval(std::function timer_action) <BTimer::callOnInterval()>`

    * - void
      - :cpp:func:`callOnTimeout(std::function timer_action) <BTimer::callOnTimeout()>`

    * - void
      - :cpp:func:`setInterval(uint32 _interval) <BTimer::setInterval()>`

    * - void
      - :cpp:func:`setInterval(std::chrono::milliseconds _interval) <BTimer::setInterval()>`

    * - void
      - :cpp:func:`setTimeout(uint32 _timeout) <BTimer::setTimeout()>`

    * - void
      - :cpp:func:`setTimeout(std::chrono::milliseconds _timeout) <BTimer::setTimeout()>`

    * - void
      - :cpp:func:`setSingleShot(bool singleshot) <BTimer::setSingleShot()>`

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

The accuracy of timers depends on the underlying operating system and hardware. On most system and hardware platform,
system clock has an accuracy of microsecond is very common.

On most platforms, BTimer can support a resolution of 1 millisecond. But under heavy work load (such as many timer events)
or high CPU usage (the timer event loop can't wake up immediately) can make the precision not so accurate.

Member Type Documentation
==========================

.. cpp:enum:: BTimerStatus

This enum type is used when calling :cpp:func:`isActive() const <BTimer::isActive()>` and :cpp:func:`setActive(bool) <BTimer::setActive()>` .

.. list-table::
    :widths: 4 2 4
    :align: left
    :header-rows: 1

    * - Constant
      - Value
      - Description

    * - BTimer::Active
      - 0
      - Timer is activated.

    * - BTimer::Stop
      - 1
      - Timer is stop.

Property Documentation
=======================

.. cpp:member:: bool singleShot

This property holds whether the timer triggers the interval action when interval timeout occurs.

If true, the interval action will be triggered after every interval period unless timeout occurs. The default value is false.

-------------------
Access functions:
-------------------

.. list-table::
    :widths: 1 4
    :align: left

    * - bool
      - :cpp:func:`isSingleShot() const <BTimer::isSingleShot()>`

    * - void
      - :cpp:func:`setSingleShot(bool singleshot) <BTimer::setSingleShot()>`


.. cpp:member:: std::chrono::milliseconds interval

This property holds the interval period of this timer. After every interval period, interval action will be triggered.
The default value is 0, which means no interval.

-------------------
Access functions:
-------------------

.. list-table::
    :widths: 1 4
    :align: left

    * - uint32
      - :cpp:func:`interval() const <BTimer::interval()>`

    * - void
      - :cpp:func:`setInterval(std::chrono::milliseconds) <BTimer::setInterval()>`


.. cpp:member:: std::chrono::milliseconds timeout

This property holds the expiration time of this timer. After timeout, the timer will be removed from the timer system
until next start calls.

.. Note::
    The default value is the maximum value of unsigned int, which means "infinite" for this timer.

-------------------
Access functions:
-------------------

.. list-table::
    :widths: 1 4
    :align: left

    * - uint32
      - :cpp:func:`timeout() const <BTimer::timeout()>`

    * - void
      - :cpp:func:`setTimeout(std::chrono::milliseconds) <BTimer::setTimeout()>`


Member Function Documentation
===============================

.. cpp:function:: explicit BTimer::BTimer() noexcept

Construct a BTimer object.

.. cpp:function:: BTimer::~BTimer()

Destruct a BTimer object.

.. cpp:function:: bool BTimer::operator>(const BTimer& rtimer) const

Returns true if id is greater than rtimer's id.

.. cpp:function:: bool BTimer::operator<(const BTimer& rtimer) const

Returns true if id is less than rtimer's id.

.. cpp:function:: bool BTimer::operator==(const BTimer& rtimer) const

Returns true if id is equal to rtimer's id.

.. cpp:function:: void BTimer::start()

Start this timer; takes no effects if timeout is 0.

.. cpp:function:: void BTimer::stop()

Stop this timer; takes no effects if this timer is expired(timeout occurs).

.. cpp:function:: bool BTimer::isActive() const

Returns true if this timer is running.

.. cpp:function:: bool BTimer::isSingleShot() const

Returns true if interval action is only triggered once.

.. cpp:function:: int32 BTimer::id() const

Returns the id of this timer.

.. cpp:function:: uint32 BTimer::interval() const

Returns the timeout interval of this timer in milliseconds.

.. cpp:function:: uint32 BTimer::timeout() const

Returns the timeout of this timer in milliseconds.

.. cpp:function:: void BTimer::reset()

Reset all properties of this timer(except timer id) to default value and stop this timer.

.. cpp:function:: void BTimer::setActive(bool _active)

Takes no effects calling by user.

.. cpp:function:: void BTimer::callOnInterval(std::function<void()> timer_action)

Set the action that will be triggered after timeout interval.

.. cpp:function:: void BTimer::callOnTimeout(std::function<void()> timer_action)

Set the action that will be triggered after timeout.

.. cpp:function:: void BTimer::setInterval(uint32 _interval)
.. cpp:function:: void BTimer::setInterval(std::chrono::milliseconds _interval)

Set the timeout interval in milliseconds. Default value is 0.

.. cpp:function:: void BTimer::setTimeout(uint32 _timeout)
.. cpp:function:: void BTimer::setTimeout(std::chrono::milliseconds _timeout)

Set the timeout in milliseconds. Default value is the maximum number of unsigned int.

.. cpp:function:: void BTimer::setSingleShot(bool singleshot)

The interval action will be triggered only once if singleshot is true.

.. cpp:function:: static uint BTimer::precision()

Returns the precision of timer in milliseconds. Default value is 1 millisecond.

.. cpp:function:: static void BTimer::setPrecision(uint)

Set the timer precision in milliseconds.