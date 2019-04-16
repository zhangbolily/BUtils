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

.. code-block:: cpp
    :linenos:

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

.. cpp:function:: void setActive(bool _active)

Takes no effects calling by user.

.. cpp:function:: void callOnInterval(std::function<void()> timer_action)

Set the action that will be triggered after timeout interval.

.. cpp:function:: void callOnTimeout(std::function<void()> timer_action)

Set the action that will be triggered after timeout.

.. cpp:function:: void setInterval(uint32 _interval)

Set the timeout interval in milliseconds. Default value is 0.

.. cpp:function:: void setInterval(std::chrono::milliseconds _interval)

Set the timeout interval in milliseconds. Default value is 0.

.. cpp:function:: void setTimeout(uint32 _timeout)

Set the timeout in milliseconds. Default value is the maximum number of unsigned int.

.. cpp:function:: void setTimeout(std::chrono::milliseconds _timeout)

Set the timeout in milliseconds. Default value is the maximum number of unsigned int.

.. cpp:function:: void setSingleShot(bool singleshot)

The interval action will be triggered only once if singleshot is true.

.. cpp:function:: static uint precision()

Returns the precision of timer in milliseconds. Default value is 1 millisecond.

.. cpp:function:: static void setPrecision(uint)

Set the timer precision in milliseconds.