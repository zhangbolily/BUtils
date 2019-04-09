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
#include <queue>
#include <thread>
#include <atomic>

namespace BUtils {
using namespace BCore;
using std::list;
using std::thread;
using std::atomic_int32_t;
using std::priority_queue;

class BTimerPrivate {
 public:
    explicit BTimerPrivate() noexcept;
    ~BTimerPrivate();

    int32           m_status;
    BTimerEvent*    m_timer_event;

    static thread*      m_timer_thread;
    static atomic_int32_t   m_ref_count;
    static atomic_int32_t   m_max_id;
    static priority_queue
            <int32, list<BTimerEvent*>, std::greater<int32>>
            m_timer_event_queue;
    static int32 createID();
    static void insertTimerEvent(BTimerEvent* timer_event);
    static void deleteTimerEvent(BTimerEvent* timer_event);
    static void updateEventQueue();
    static void eventLoop();
};

}  // namespace BUtils

#endif  // INCLUDE_BUTILS_BTIMERPRIVATE_H_