/* MIT License
*
* Copyright (c) 2018 Ball Chang
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

/*
 * @Author      : Ball Chang
 * @File        : BTimerPrivate.h
 * @Date        : 2019-4-3
*/

#ifndef INCLUDE_BUTILS_BTIMERPRIVATE_H_
#define INCLUDE_BUTILS_BTIMERPRIVATE_H_

#include "BCore/BCore.h"
#include "BCore/BDebug.h"
#include "BCore/BType.h"
#include "BUtils/BTimerEvent.h"

#include <list>
#include <map>
#include <utility>
#include <queue>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#ifdef WIN32
#else
#include <sys/prctl.h>
#endif

namespace BUtils {
using namespace BCore;
using std::map;
using std::list;
using std::pair;
using std::queue;
using std::vector;
using std::thread;
using std::mutex;
using std::unique_lock;
using std::condition_variable;
using std::atomic_int;
using std::atomic_bool;
using std::atomic_long;

class BTimerPrivate {
 public:
    explicit BTimerPrivate() noexcept;
    ~BTimerPrivate();

    BTimerEvent*    m_timer_event;

    static thread*      m_event_loop_thread;
    static thread*      m_action_thread;
    static uint         m_timer_precision;
    static mutex        m_event_mutex;
    static mutex        m_action_mutex;
    static condition_variable m_action_cond;
    static atomic_bool  m_is_active;
    static atomic_long  m_counter;
    static atomic_int   m_event_loop_active;
    static atomic_int   m_action_trigger_active;
    static atomic_int   m_ref_count;
    static atomic_int   m_max_id;
    static queue<std::function<void()> > m_action_queue;
    static map<int32, std::list<BTimerEvent*>> m_timer_event_list_map;
    static int32 createID();
    static uint precision();
    static void setPrecision(uint);
    static void insertTimerEvent(BTimerEvent* timer_event);
    static void insertTimerEvent(uint counter_index, BTimerEvent* timer_event);
    static void deleteTimerEvent(BTimerEvent* timer_event);
    static void eventLoop();
    static void actionTrigger();
};

}  // namespace BUtils

#endif  // INCLUDE_BUTILS_BTIMERPRIVATE_H_
