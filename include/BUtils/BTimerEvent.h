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
 * @File        : BTimerEvent.h
 * @Date        : 2019-4-8
*/

#ifndef INCLUDE_BUTILS_BTIMEREVENT_H_
#define INCLUDE_BUTILS_BTIMEREVENT_H_

#include "BCore/BCore.h"
#include "BCore/BDebug.h"
#include "BCore/BType.h"

#include <functional>

namespace BUtils {
using namespace BCore;

class BTimerEventPrivate;

class BTimerEvent {
 public:
    explicit BTimerEvent() noexcept;
    ~BTimerEvent();

    bool operator>(const BTimerEvent& revent) const;
    bool operator<(const BTimerEvent& revent) const;
    bool operator==(const BTimerEvent& revent) const;
    bool isActive() const;
    bool isSingleShot() const;
    int32 id() const;
    uint32 counter() const;
    uint32 interval() const;
    uint32 timeout() const;
    std::function<void()> intervalAction() const;
    std::function<void()> timeoutAction() const;
    void setId(int32 _id);
    void setActive(bool _active);
    void setTimeoutAction(std::function<void()> timer_action);
    void setIntervalAction(std::function<void()> timer_action);
    void setCounter(uint32 _count);
    void setInterval(uint32 _interval);
    void setInterval(std::chrono::milliseconds _interval);
    void setTimeout(uint32 _timeout);
    void setTimeout(std::chrono::milliseconds _timeout);
    void setSingleShot(bool singleshot);

 protected:
    BTimerEventPrivate* m_private_ptr;
};

}  // namespace BUtils

#endif  // INCLUDE_BUTILS_BTIMEREVENT_H_