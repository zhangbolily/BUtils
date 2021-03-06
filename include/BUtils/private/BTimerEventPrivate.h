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
 * @File        : BTimerEventPrivate.h
 * @Date        : 2019-4-8
*/

#ifndef INCLUDE_BUTILS_BTIMEREVENTPRIVATE_H_
#define INCLUDE_BUTILS_BTIMEREVENTPRIVATE_H_

#include <chrono>
#include <atomic>
#include <functional>
#include <climits>

#include "BCore/BCore.h"
#include "BCore/BDebug.h"
#include "BCore/BType.h"

namespace BUtils {
using namespace BCore;
using std::function;
using std::atomic_bool;
using std::atomic_int;
using std::chrono::milliseconds;

class BTimerEventPrivate {
 public:
    explicit BTimerEventPrivate() noexcept;
    ~BTimerEventPrivate();

    atomic_int m_id;
    atomic_int m_counter;
    atomic_bool m_is_active;
    atomic_bool m_is_single_shot;
    std::chrono::milliseconds m_interval;
    std::chrono::milliseconds m_timeout;
    std::function<void()> m_interval_action;
    std::function<void()> m_timeout_action;
};

}  // namespace BUtils

#endif  // INCLUDE_BUTILS_BTIMEREVENTPRIVATE_H_
