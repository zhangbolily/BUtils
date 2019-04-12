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

BTimerEvent::BTimerEvent() noexcept
    : m_private_ptr(new BTimerEventPrivate()) {
}

BTimerEvent::~BTimerEvent() {
    if (m_private_ptr != nullptr) {
        delete m_private_ptr;
    }
}

bool BTimerEvent::operator>(const BTimerEvent& revent) const {
    return this->counter() > revent.counter();
}

bool BTimerEvent::operator<(const BTimerEvent& revent) const {
    return this->counter() < revent.counter();
}

bool BTimerEvent::operator==(const BTimerEvent& revent) const {
    return this->id() == revent.id();
}

int32 BTimerEvent::id() const {
    return m_private_ptr->m_id;
}

bool BTimerEvent::isActive() const {
    return m_private_ptr->m_is_active;
}

bool BTimerEvent::isSingleShot() const {
    return m_private_ptr->m_is_single_shot;
}

uint32 BTimerEvent::counter() const {
    return m_private_ptr->m_counter;
}

uint32 BTimerEvent::interval() const {
    return m_private_ptr->m_interval.count();
}

uint32 BTimerEvent::timeout() const {
    return m_private_ptr->m_timeout.count();
}

std::function<void()> BTimerEvent::intervalAction() const {
    return m_private_ptr->m_interval_action;
}

std::function<void()> BTimerEvent::timeoutAction() const {
    return m_private_ptr->m_timeout_action;
}

void BTimerEvent::setId(BCore::int32 _id) {
    m_private_ptr->m_id = _id;
}

void BTimerEvent::setActive(bool _active) {
    m_private_ptr->m_is_active = _active;
}

void BTimerEvent::setIntervalAction(std::function<void()> timer_action) {
    m_private_ptr->m_interval_action = timer_action;
}

void BTimerEvent::setTimeoutAction(std::function<void()> timer_action) {
    m_private_ptr->m_timeout_action = timer_action;
}

void BTimerEvent::setCounter(BCore::uint32 _count) {
    m_private_ptr->m_counter = _count;
}

void BTimerEvent::setInterval(uint32 _interval) {
    m_private_ptr->m_interval = std::chrono::milliseconds(_interval);
}

void BTimerEvent::setInterval(std::chrono::milliseconds _interval) {
    m_private_ptr->m_interval = _interval;
}

void BTimerEvent::setTimeout(uint32 _timeout) {
    m_private_ptr->m_timeout = std::chrono::milliseconds(_timeout);
}

void BTimerEvent::setTimeout(std::chrono::milliseconds _timeout) {
    m_private_ptr->m_timeout = _timeout;
}

void BTimerEvent::setSingleShot(bool singleshot) {
    m_private_ptr->m_is_single_shot = singleshot;
}

// End of BTimerEvent implementation

// Start implementation of BTimerEventPrivate
BTimerEventPrivate::BTimerEventPrivate() noexcept
    : m_is_single_shot(false),
      m_interval(0),
      m_timeout(0),
      m_counter(0),
      m_interval_action(nullptr),
      m_timeout_action(nullptr){

}

BTimerEventPrivate::~BTimerEventPrivate() {

}

// End of BTimerEventPrivate implementation
}  // namespace BUtils