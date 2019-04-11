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
 * @File        : BTimer.h
 * @Date        : 2019-4-9
*/

#ifndef INCLUDE_BUTILS_BTIMER_H_
#define INCLUDE_BUTILS_BTIMER_H_

#ifdef WIN32
#include "winuser.h"
#else
#include <signal.h>
#endif

#include "BCore/BCore.h"
#include "BCore/BDebug.h"
#include "BCore/BType.h"

#include <algorithm>
#include <functional>

namespace BUtils {

using namespace BCore;
using std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

class BTimerPrivate;

class BTimer{
    enum BTimerStatus {
        Active,
        Stop
    };

 public:
    explicit BTimer() noexcept;
    ~BTimer();

    void start();
    void stop();
    bool isActive();
    bool isSingleShot();
    int32 id();
    int32 interval();
    int32 timeout();
    void setActive(bool _active);
    void callOnInterval(std::function<void()> timer_action);
    void callOnTimeout(std::function<void()> timer_action);
    void setInterval(int32 _interval);
    void setInterval(std::chrono::milliseconds _interval);
    void setTimeout(int32 _timeout);
    void setTimeout(std::chrono::milliseconds _timeout);
    void setSingleShot(bool singleshot);

 protected:
    BTimerPrivate* m_private_ptr;

};
}  // namespace BUtils

#endif  // INCLUDE_BUTILS_BTIMER_H_
