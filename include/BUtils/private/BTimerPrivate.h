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
#include <utility>
#include <queue>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace BUtils {
using namespace BCore;
using std::list;
using std::pair;
using std::queue;
using std::vector;
using std::thread;
using std::mutex;
using std::unique_lock;
using std::condition_variable;
using std::atomic_int;
using std::atomic_long;
using std::priority_queue;

class BTimerEventList: public std::list<BTimerEvent*> {
 public:
    BTimerEventList() = default;
    BTimerEventList(const BTimerEventList&);
    BTimerEventList(BTimerEventList&&);

    BTimerEventList& operator=(const BTimerEventList&);
    BTimerEventList& operator=(BTimerEventList&&);

    int32 interval();
    void setInterval(int32 _interval);

 private:
    atomic_int m_interval;
};

class BTimerPriorityQueue: public priority_queue
        <std::pair<int32, BTimerEventList>,
         std::vector<std::pair<int32, BTimerEventList>>,
         std::greater<std::pair<int32, BTimerEventList>>> {
 public:
    BTimerPriorityQueue() = default;
    BTimerPriorityQueue(const BTimerPriorityQueue&);
    BTimerPriorityQueue(BTimerPriorityQueue&&);

    BTimerPriorityQueue& operator=(const BTimerPriorityQueue&);
    BTimerPriorityQueue& operator=(BTimerPriorityQueue&&);

    void updateQueue();
    BTimerEventList& getEventList(int32 interval);
};

class BTimerPrivate {
 public:
    explicit BTimerPrivate() noexcept;
    ~BTimerPrivate();

    int32           m_status;
    BTimerEvent*    m_timer_event;

    static thread*      m_event_loop_thread;
    static thread*      m_action_thread;
    static bool         m_is_active;
    static int32        m_timer_precision;
    static mutex        m_event_mutex;
    static mutex        m_action_mutex;
    static condition_variable m_action_cond;
    static atomic_long  m_counter;
    static atomic_int   m_ref_count;
    static atomic_int   m_max_id;
    static queue<std::function<void()> > m_action_queue;
    static BTimerPriorityQueue m_timer_event_queue;
    static int32 createID();
    static int32 precision();
    static void setPrecision(int32);
    static void insertTimerEvent(BTimerEvent* timer_event);
    static void deleteTimerEvent(BTimerEvent* timer_event);
    static void updateEventQueue();
    static void eventLoop();
    static void actionTrigger();
};

}  // namespace BUtils

#endif  // INCLUDE_BUTILS_BTIMERPRIVATE_H_
