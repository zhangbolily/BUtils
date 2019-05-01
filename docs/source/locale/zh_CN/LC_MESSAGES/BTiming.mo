��    /      �                               C     3   W  0   �  ,   �  &   �  8     $   I  6   n  *   �  ,   �     �  p        v     �     �  `   �            "   -     P     \     w     �     �     �     �     �     �     
     )  o   I  ^   �       >   0  H   o  =   �  G   �     >	     Q	     W	     \	     a	     g	  �  l	     �
     �
     �
  C   �
  3   B  0   v  ,   �  &   �  8   �  $   4  6   Y  *   �  ,   �     �  p   �     a     t     �  `   �     �     �  "        ;     G     b     w     �     �     �     �     �     �       o   4  ^   �       >     H   Z  =   �  G   �     )     <     B     G     L     R   0 1 2 :cpp:enum:`BTimingStatus {CPUTiming, Timing, Stop} <BTimingStatus>` :cpp:func:`BTiming() noexcept <BTiming::BTiming()>` :cpp:func:`CPUTime() const <BTiming::CPUTime()>` :cpp:func:`isActive() <BTiming::isActive()>` :cpp:func:`start() <BTiming::start()>` :cpp:func:`startCPUTiming() <BTiming::startCPUTiming()>` :cpp:func:`stop() <BTiming::stop()>` :cpp:func:`stopCPUTiming() <BTiming::stopCPUTiming()>` :cpp:func:`time() const <BTiming::time()>` :cpp:func:`~BTiming() <BTiming::~BTiming()>` BTiming BTiming can record both :term:`real time` and :term:`CPU time` with the same minimum precision of 1 microsecond. BTiming::CPUTiming BTiming::Stop BTiming::Timing Class BTiming provides a timing system to record time with a minimum precision of 1 microsecond. Constant Construct a BTiming object. Defined in header <BUtils/BTiming> Description Destruct a BTiming object. Detailed Description Example for timing one second: Member Function Documentation Member Type Documentation Overview Public Functions Public Types Represents recording CPU time. Represents recording real time. Returns the CPU time recorded by calling startCPUTiming and stopCPUTiming in microseconds; otherwise returns 0. Returns the real time recorded by calling start and stop in microseconds; otherwise returns 0. Returns true if timing. Start recording CPU time. Takes no effects if start is called. Start recording real time. Takes no effects if startCPUTiming is called. Stop recording CPU time. Takes no effects if start is called. Stop recording real time. Takes no effects if startCPUTiming is called. Stopped recording. Value bool enum int64 void Project-Id-Version: BUtils 0.1.2-beta
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
 0 1 2 :cpp:enum:`BTimingStatus {CPUTiming, Timing, Stop} <BTimingStatus>` :cpp:func:`BTiming() noexcept <BTiming::BTiming()>` :cpp:func:`CPUTime() const <BTiming::CPUTime()>` :cpp:func:`isActive() <BTiming::isActive()>` :cpp:func:`start() <BTiming::start()>` :cpp:func:`startCPUTiming() <BTiming::startCPUTiming()>` :cpp:func:`stop() <BTiming::stop()>` :cpp:func:`stopCPUTiming() <BTiming::stopCPUTiming()>` :cpp:func:`time() const <BTiming::time()>` :cpp:func:`~BTiming() <BTiming::~BTiming()>` BTiming BTiming can record both :term:`real time` and :term:`CPU time` with the same minimum precision of 1 microsecond. BTiming::CPUTiming BTiming::Stop BTiming::Timing Class BTiming provides a timing system to record time with a minimum precision of 1 microsecond. Constant Construct a BTiming object. Defined in header <BUtils/BTiming> Description Destruct a BTiming object. Detailed Description Example for timing one second: Member Function Documentation Member Type Documentation Overview Public Functions Public Types Represents recording CPU time. Represents recording real time. Returns the CPU time recorded by calling startCPUTiming and stopCPUTiming in microseconds; otherwise returns 0. Returns the real time recorded by calling start and stop in microseconds; otherwise returns 0. Returns true if timing. Start recording CPU time. Takes no effects if start is called. Start recording real time. Takes no effects if startCPUTiming is called. Stop recording CPU time. Takes no effects if start is called. Stop recording real time. Takes no effects if startCPUTiming is called. Stopped recording. Value bool enum int64 void 