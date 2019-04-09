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
 * @File        : BTimer.cpp
 * @Date        : 2018-12-19
*/

#include "BUtils/BTimer.h"
#include "BUtils/private/BTimerPrivate.h"

namespace BUtils {

// Start implementation of BTimer
BTimer::BTimer() noexcept
    : m_private_ptr(new BTimerPrivate) {
}

BTimer::~BTimer() {
    if (m_private_ptr != nullptr) {
        delete m_private_ptr;
    }
}

void BTimer::start() {
    setActive(true);
}

void BTimer::stop() {
    setActive(false);
}

bool BTimer::isActive() {
    return m_private_ptr->m_timer_event->isActive();
}

bool BTimer::isSingleShot() {
    return m_private_ptr->m_timer_event->isSingleShot();
}

int32 BTimer::id() {
    return m_private_ptr->m_timer_event->id();
}

int32 BTimer::interval() {
    return m_private_ptr->m_timer_event->interval();
}
int32 BTimer::timeout() {
    return m_private_ptr->m_timer_event->timeout();
}

void BTimer::setId(int32 _id) {
    m_private_ptr->m_timer_event->setId(_id);
}

void BTimer::setActive(bool _active) {
    m_private_ptr->m_timer_event->setActive(_active);
}

void BTimer::callOnInterval(std::function<void()> timer_action) {
    m_private_ptr->m_timer_event->setIntervalAction(timer_action);
}

void BTimer::callOnTimeout(std::function<void()> timer_action) {
    m_private_ptr->m_timer_event->setTimeoutAction(timer_action);
}

void BTimer::setInterval(int32 _interval) {
    m_private_ptr->m_timer_event->setInterval(_interval);
}

void BTimer::setInterval(std::chrono::milliseconds _interval) {
    m_private_ptr->m_timer_event->setInterval(_interval);
}

void BTimer::setTimeout(int32 _timeout) {
    m_private_ptr->m_timer_event->setTimeout(_timeout);
}

void BTimer::setTimeout(std::chrono::milliseconds _timeout) {
    m_private_ptr->m_timer_event->setTimeout(_timeout);
}

void BTimer::setSingleShot(bool singleshot) {
    m_private_ptr->m_timer_event->setSingleShot(singleshot);
}

// End of BTimer implementation

// Start implementation of BTimerPrivate

BTimerPrivate::BTimerPrivate() noexcept
    : m_timer_event(new BTimerEvent()) {
    if (m_ref_count == 0) {
        // TODO(Ball Chang): Create a new event loop thread.
        m_timer_thread = new thread();
    }
    m_ref_count++;
    m_timer_event->setId(BTimerPrivate::createID());
}

BTimerPrivate::~BTimerPrivate() {
    if (m_ref_count == 1) {
        delete m_timer_thread;
        m_timer_thread = nullptr;
    }
    m_ref_count--;
}

int32 BTimerPrivate::createID() {
    return m_max_id++;
}

void BTimerPrivate::insertTimerEvent(BTimerEvent* timer_event) {
    m_timer_event_queue.push(timer_event);
}

void BTimerPrivate::deleteTimerEvent(BTimerEvent* timer_event) {

}

void BTimerPrivate::updateEventQueue() {

}

void BTimerPrivate::eventLoop() {

}

// End of BTimerPrivate implementation

}  // namespace BThreadPack
