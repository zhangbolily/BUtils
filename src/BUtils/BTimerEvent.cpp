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
 * @File        : BTimerEvent.cpp
 * @Date        : 2019-4-8
*/

#include "BUtils/private/BTimerEventPrivate.h"
#include "BUtils/BTimerEvent.h"

namespace BUtils {
// Start implementation of BTimerEvent



// End of BTimerEvent implementation

// Start implementation of BTimerEventPrivate
BTimerEventPrivate::BTimerEventPrivate() noexcept
    : m_is_single_shot(false),
      m_interval(0),
      m_timeout(0),
      m_counter(0) {

}

BTimerEventPrivate::~BTimerEventPrivate() {

}

bool BTimerEventPrivate::isSingleShot() {
    return m_is_single_shot;
}

int32 BTimerEventPrivate::counter() {
    return m_counter;
}

int32 BTimerEventPrivate::interval() {
    return m_interval.count();
}

int32 BTimerEventPrivate::timeout() {
    return m_timeout.count();
}

std::function<void()> BTimerEventPrivate::action() {
    return m_action;
}

void BTimerEventPrivate::setAction(std::function<void()> timer_action) {
    m_action = timer_action;
}

void BTimerEventPrivate::setCounter(BCore::int32 _count) {
    m_counter = _count;
}

void BTimerEventPrivate::setInterval(int32 _interval) {
    m_interval = std::chrono::milliseconds(_interval);
}

void BTimerEventPrivate::setInterval(std::chrono::milliseconds _interval) {
    m_interval = _interval;
}

void BTimerEventPrivate::setTimeout(int32 _timeout) {
    m_timeout = std::chrono::milliseconds(_timeout);
}

void BTimerEventPrivate::setTimeout(std::chrono::milliseconds _timeout) {
    m_timeout = _timeout;
}

void BTimerEventPrivate::setSingleShot(bool singleshot) {
    m_is_single_shot = singleshot;
}

// End of BTimerEventPrivate implementation
}  // namespace BUtils