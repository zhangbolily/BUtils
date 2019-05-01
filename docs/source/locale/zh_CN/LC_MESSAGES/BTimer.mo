��    \      �              �     �     �  6   �  '     Q   @  O   �  %   �  1     1   :  9   l  G   �  G   �  H   6       %   �  1   �  T   �  J   D	  A   �	  /   �	  D   
  Q   F
  H   �
  >   �
  %      #   F  /   j  )   �     �     �     �     
          :  �   A  �        �     �  b        i     r  !   �     �     �     �     �  }   
     �     �  �   �     �  
   �     �     �     �  Y   �     I  O   g  ;   �  2   �  +   &  /   R  ,   �  7   �  &   �  =     4   L  U   �  =   �  (     3   >     r  K   �  !   �  �   �  ^   �  F   	  �   P  �   �  �   l  `        u     �     �     �     �     �     �     �     �     �  �  �     e     g  6   i  '   �  Q   �  O     %   j  1   �  1   �  9   �  G   .  G   v  H   �       %     1   E  T   w  J   �  A     /   Y  D   �  Q   �  H      >   i  %   �  #   �  /   �  )   "      L      c      |      �      �      �   �   �   �   �!     r"     �"  U   �"     �"     �"  &   #     /#     ;#     U#     j#  }   �#     $     &$  �   @$     &%  
   -%     8%     O%     `%  Y   m%     �%  O   �%  ;   5&  2   q&  +   �&  /   �&  ,    '  7   -'  &   e'  =   �'  4   �'  U   �'  =   U(  (   �(  3   �(     �(  K   )  !   T)  �   v)  ^   (*  F   �*  �   �*  �   \+  �   �+  `   �,     �,     -     -     -     !-     &-     ,-     F-     K-     R-   0 1 :cpp:enum:`BTimerStatus {Active, Stop} <BTimerStatus>` :cpp:func:`BTimer() <BTimer::BTimer()>` :cpp:func:`callOnInterval(std::function timer_action) <BTimer::callOnInterval()>` :cpp:func:`callOnTimeout(std::function timer_action) <BTimer::callOnTimeout()>` :cpp:func:`id() const <BTimer::id()>` :cpp:func:`interval() const <BTimer::interval()>` :cpp:func:`isActive() const <BTimer::isActive()>` :cpp:func:`isSingleShot() const <BTimer::isSingleShot()>` :cpp:func:`operator=(const BTimer& rtimer) const <BTimer::operator=()>` :cpp:func:`operator>(const BTimer& rtimer) const <BTimer::operator>()>` :cpp:func:`operator\<(const BTimer& rtimer) const <BTimer::operator<()>` :cpp:func:`precision()` :cpp:func:`reset() <BTimer::reset()>` :cpp:func:`setActive(bool) <BTimer::setActive()>` :cpp:func:`setInterval(std::chrono::milliseconds _interval) <BTimer::setInterval()>` :cpp:func:`setInterval(std::chrono::milliseconds) <BTimer::setInterval()>` :cpp:func:`setInterval(uint32 _interval) <BTimer::setInterval()>` :cpp:func:`setPrecision(uint) <setPrecision()>` :cpp:func:`setSingleShot(bool singleshot) <BTimer::setSingleShot()>` :cpp:func:`setTimeout(std::chrono::milliseconds _timeout) <BTimer::setTimeout()>` :cpp:func:`setTimeout(std::chrono::milliseconds) <BTimer::setTimeout()>` :cpp:func:`setTimeout(uint32 _timeout) <BTimer::setTimeout()>` :cpp:func:`start() <BTimer::start()>` :cpp:func:`stop() <BTimer::stop()>` :cpp:func:`timeout() const <BTimer::timeout()>` :cpp:func:`~BTimer() <BTimer::~BTimer()>` :cpp:member:`interval` :cpp:member:`singleShot` :cpp:member:`timeout` Access functions: Accuracy and Timer Resolution BTimer BTimer provides a easy to user programing interface for doing periodic jobs in your application. Just create a :term:`timer` and set up the properties, then start it. You can change the properties of a timer at any time. BTimer's timer event system is designed to work in multi-threads environments, but BTimer object itself doesn't. Do not share a single BTimer object in threads, just create and use it in the same thread. BTimer::Active BTimer::Stop Class BTimer provides repetitive and single-shot timers with a minimum precision of 1 millisecond. Constant Construct a BTimer object. Defined in header <BUtils/BTimer> Description Destruct a BTimer object. Detailed Description Example for a one second timer: If true, the interval action will be triggered after every interval period unless timeout occurs. The default value is false. Member Function Documentation Member Type Documentation On most platforms, BTimer can support a resolution of 1 millisecond. But under heavy work load (such as many timer events) or high CPU usage (the timer event loop can't wake up immediately) can make the precision not so accurate. Overview Properties Property Documentation Public Functions Public Types Reset all properties of this timer(except timer id) to default value and stop this timer. Returns the id of this timer. Returns the precision of timer in milliseconds. Default value is 1 millisecond. Returns the timeout interval of this timer in milliseconds. Returns the timeout of this timer in milliseconds. Returns true if id is equal to rtimer's id. Returns true if id is greater than rtimer's id. Returns true if id is less than rtimer's id. Returns true if interval action is only triggered once. Returns true if this timer is running. Set the action that will be triggered after timeout interval. Set the action that will be triggered after timeout. Set the timeout in milliseconds. Default value is the maximum number of unsigned int. Set the timeout interval in milliseconds. Default value is 0. Set the timer precision in milliseconds. Start this timer; takes no effects if timeout is 0. Static Public Functions Stop this timer; takes no effects if this timer is expired(timeout occurs). Takes no effects calling by user. The accuracy of timers depends on the underlying operating system and hardware. On most system and hardware platform, system clock has an accuracy of microsecond is very common. The default value is the maximum value of unsigned int, which means "infinite" for this timer. The interval action will be triggered only once if singleshot is true. This enum type is used when calling :cpp:func:`isActive() const <BTimer::isActive()>` and :cpp:func:`setActive(bool) <BTimer::setActive()>` . This property holds the expiration time of this timer. After timeout, the timer will be removed from the timer system until next start calls. This property holds the interval period of this timer. After every interval period, interval action will be triggered. The default value is 0, which means no interval. This property holds whether the timer triggers the interval action when interval timeout occurs. Timer is activated. Timer is stop. Value bool enum int32 std::chrono::milliseconds uint uint32 void Project-Id-Version: BUtils 0.1.2-beta
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2019-05-01 23:59+0800
PO-Revision-Date: YEAR-MO-DA HO:MI+ZONE
Last-Translator: FULL NAME <EMAIL@ADDRESS>
Language: zh_Hans_CN
Language-Team: zh_Hans_CN <LL@li.org>
Plural-Forms: nplurals=1; plural=0
MIME-Version: 1.0
Content-Type: text/plain; charset=utf-8
Content-Transfer-Encoding: 8bit
Generated-By: Babel 2.4.0
 0 1 :cpp:enum:`BTimerStatus {Active, Stop} <BTimerStatus>` :cpp:func:`BTimer() <BTimer::BTimer()>` :cpp:func:`callOnInterval(std::function timer_action) <BTimer::callOnInterval()>` :cpp:func:`callOnTimeout(std::function timer_action) <BTimer::callOnTimeout()>` :cpp:func:`id() const <BTimer::id()>` :cpp:func:`interval() const <BTimer::interval()>` :cpp:func:`isActive() const <BTimer::isActive()>` :cpp:func:`isSingleShot() const <BTimer::isSingleShot()>` :cpp:func:`operator=(const BTimer& rtimer) const <BTimer::operator=()>` :cpp:func:`operator>(const BTimer& rtimer) const <BTimer::operator>()>` :cpp:func:`operator\<(const BTimer& rtimer) const <BTimer::operator<()>` :cpp:func:`precision()` :cpp:func:`reset() <BTimer::reset()>` :cpp:func:`setActive(bool) <BTimer::setActive()>` :cpp:func:`setInterval(std::chrono::milliseconds _interval) <BTimer::setInterval()>` :cpp:func:`setInterval(std::chrono::milliseconds) <BTimer::setInterval()>` :cpp:func:`setInterval(uint32 _interval) <BTimer::setInterval()>` :cpp:func:`setPrecision(uint) <setPrecision()>` :cpp:func:`setSingleShot(bool singleshot) <BTimer::setSingleShot()>` :cpp:func:`setTimeout(std::chrono::milliseconds _timeout) <BTimer::setTimeout()>` :cpp:func:`setTimeout(std::chrono::milliseconds) <BTimer::setTimeout()>` :cpp:func:`setTimeout(uint32 _timeout) <BTimer::setTimeout()>` :cpp:func:`start() <BTimer::start()>` :cpp:func:`stop() <BTimer::stop()>` :cpp:func:`timeout() const <BTimer::timeout()>` :cpp:func:`~BTimer() <BTimer::~BTimer()>` :cpp:member:`interval` :cpp:member:`singleShot` :cpp:member:`timeout` Access functions: Accuracy and Timer Resolution BTimer BTimer provides a easy to user programing interface for doing periodic jobs in your application. Just create a :term:`timer` and set up the properties, then start it. You can change the properties of a timer at any time. BTimer's timer event system is designed to work in multi-threads environments, but BTimer object itself doesn't. Do not share a single BTimer object in threads, just create and use it in the same thread. BTimer::Active BTimer::Stop BTimer 类提供最小精度为 1 ms 的周期性重复和单次触发的定时器。 Constant Construct a BTimer object. 定义在头文件 <BUtils/BTimer> 中 Description Destruct a BTimer object. Detailed Description Example for a one second timer: If true, the interval action will be triggered after every interval period unless timeout occurs. The default value is false. Member Function Documentation Member Type Documentation On most platforms, BTimer can support a resolution of 1 millisecond. But under heavy work load (such as many timer events) or high CPU usage (the timer event loop can't wake up immediately) can make the precision not so accurate. 概述 Properties Property Documentation Public Functions 公有类型 Reset all properties of this timer(except timer id) to default value and stop this timer. Returns the id of this timer. Returns the precision of timer in milliseconds. Default value is 1 millisecond. Returns the timeout interval of this timer in milliseconds. Returns the timeout of this timer in milliseconds. Returns true if id is equal to rtimer's id. Returns true if id is greater than rtimer's id. Returns true if id is less than rtimer's id. Returns true if interval action is only triggered once. Returns true if this timer is running. Set the action that will be triggered after timeout interval. Set the action that will be triggered after timeout. Set the timeout in milliseconds. Default value is the maximum number of unsigned int. Set the timeout interval in milliseconds. Default value is 0. Set the timer precision in milliseconds. Start this timer; takes no effects if timeout is 0. Static Public Functions Stop this timer; takes no effects if this timer is expired(timeout occurs). Takes no effects calling by user. The accuracy of timers depends on the underlying operating system and hardware. On most system and hardware platform, system clock has an accuracy of microsecond is very common. The default value is the maximum value of unsigned int, which means "infinite" for this timer. The interval action will be triggered only once if singleshot is true. This enum type is used when calling :cpp:func:`isActive() const <BTimer::isActive()>` and :cpp:func:`setActive(bool) <BTimer::setActive()>` . This property holds the expiration time of this timer. After timeout, the timer will be removed from the timer system until next start calls. This property holds the interval period of this timer. After every interval period, interval action will be triggered. The default value is 0, which means no interval. This property holds whether the timer triggers the interval action when interval timeout occurs. Timer is activated. Timer is stop. Value bool enum int32 std::chrono::milliseconds uint uint32 void 