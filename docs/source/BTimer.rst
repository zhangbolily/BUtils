.. -*- coding: utf-8 -*-

.. _btimer_rst:

=============
BTimer
=============

Defined in header "BUtils/BTimer.h"

Overview
========

Class BTimer provides repetitive and single-shot timers with a minimum precision of 1 millisecond.

API
===

-----
Types
-----

.. highlight:: cpp
    :linenothreshold: 4
enum BTimerStatus {
    Active,
    Stop
};

-------
Methods
-------


---------
Reference
---------

.. function:: explicit BTimer() noexcept

Construct a BTimer object.

.. function:: ~BTimer()

Destruct a BTimer object.

.. function:: bool operator>(const BTimer& rtimer) const

Returns true if id is greater than rtimer's id.

.. function:: bool operator<(const BTimer& rtimer) const

Returns true if id is less than rtimer's id.

.. function:: bool operator==(const BTimer& rtimer) const

Returns true if id is equal to rtimer's id.

.. function:: void start()

Start this timer; takes no effects if timeout is 0.

.. function:: void stop()

Stop this timer; takes no effects if this timer is expired(timeout occurs).

.. function:: bool isActive() const

Returns true if this timer is running.

.. function:: bool isSingleShot() const

Returns true if interval action is only triggered once.

.. function:: int32 id() const

Returns the id of this timer.

.. function:: uint32 interval() const

Returns the timeout interval of this timer in milliseconds.

.. function:: uint32 timeout() const

Returns the timeout of this timer in milliseconds.

.. function:: void setActive(bool _active)

Takes no effects calling by user.

.. function:: void callOnInterval(std::function<void()> timer_action)

Set the action that will be triggered after timeout interval.

.. function:: void callOnTimeout(std::function<void()> timer_action)

Set the action that will be triggered after timeout.

.. function:: void setInterval(uint32 _interval)

Set the timeout interval in milliseconds. Default value is 0.

.. function:: void setInterval(std::chrono::milliseconds _interval)

Set the timeout interval in milliseconds. Default value is 0.

.. function:: void setTimeout(uint32 _timeout)

Set the timeout in milliseconds. Default value is the maximum number of unsigned int.

.. function:: void setTimeout(std::chrono::milliseconds _timeout)

Set the timeout in milliseconds. Default value is the maximum number of unsigned int.

.. function:: void setSingleShot(bool singleshot)

The interval action will be triggered only once if singleshot is true.

.. function:: static uint precision()

Returns the precision of timer in milliseconds. Default value is 1 millisecond.

.. function:: static void setPrecision(uint)

Set the timer precision in milliseconds.