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
 * @Date        : 2019-4-6
*/

#include "BUtils/private/BTimerPrivate.h"
#include "BUtils/BTimer.h"

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
    m_private_ptr->insertTimerEvent(m_private_ptr->m_timer_event);
}

void BTimer::stop() {
    m_private_ptr->deleteTimerEvent(m_private_ptr->m_timer_event);
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

void BTimer::setActive(bool _active) {
    m_private_ptr->m_timer_event->setActive(_active);
}

void BTimer::callOnInterval(std::function<void()> timer_action) {
    if (isActive()) {
        stop();
        m_private_ptr->m_timer_event->setIntervalAction(timer_action);
        start();
    } else {
        m_private_ptr->m_timer_event->setIntervalAction(timer_action);
    }
}

void BTimer::callOnTimeout(std::function<void()> timer_action) {
    if (isActive()) {
        stop();
        m_private_ptr->m_timer_event->setTimeoutAction(timer_action);
        start();
    } else {
        m_private_ptr->m_timer_event->setTimeoutAction(timer_action);
    }
}

void BTimer::setInterval(int32 _interval) {
    if (isActive()) {
        stop();
        m_private_ptr->m_timer_event->setInterval(_interval);
        start();
    } else {
        m_private_ptr->m_timer_event->setInterval(_interval);
    }
}

void BTimer::setInterval(std::chrono::milliseconds _interval) {
    if (isActive()) {
        stop();
        m_private_ptr->m_timer_event->setInterval(_interval);
        start();
    } else {
        m_private_ptr->m_timer_event->setInterval(_interval);
    }
}

void BTimer::setTimeout(int32 _timeout) {
    if (isActive()) {
        stop();
        m_private_ptr->m_timer_event->setTimeout(_timeout);
        start();
    } else {
        m_private_ptr->m_timer_event->setTimeout(_timeout);
    }
}

void BTimer::setTimeout(std::chrono::milliseconds _timeout) {
    if (isActive()) {
        stop();
        m_private_ptr->m_timer_event->setTimeout(_timeout);
        start();
    } else {
        m_private_ptr->m_timer_event->setTimeout(_timeout);
    }
}

void BTimer::setSingleShot(bool singleshot) {
    if (isActive()) {
        stop();
        m_private_ptr->m_timer_event->setSingleShot(singleshot);
        start();
    } else {
        m_private_ptr->m_timer_event->setSingleShot(singleshot);
    }
}

// End of BTimer implementation

// Start implementation of BTimerPrivate

thread*         BTimerPrivate::m_action_thread = nullptr;
thread*         BTimerPrivate::m_event_loop_thread = nullptr;
int32           BTimerPrivate::m_timer_precision = 1;   // Default 1ms
mutex           BTimerPrivate::m_event_mutex;
mutex           BTimerPrivate::m_action_mutex;
condition_variable BTimerPrivate::m_action_cond;
bool            BTimerPrivate::m_is_active = false;
atomic_int  	BTimerPrivate::m_max_id(0);
atomic_int  	BTimerPrivate::m_ref_count(0);
atomic_long  	BTimerPrivate::m_counter(0);
queue<std::function<void()> > BTimerPrivate::m_action_queue;
map<int32, std::list<BTimerEvent*>> BTimerPrivate::m_timer_event_list_map;

BTimerPrivate::BTimerPrivate() noexcept
    : m_timer_event(new BTimerEvent()) {
    if (m_ref_count == 0) {
        // TODO(Ball Chang): Create a new event loop thread.
        m_is_active = true;
        m_event_loop_thread = new thread(BTimerPrivate::eventLoop);
        m_action_thread = new thread(BTimerPrivate::actionTrigger);
        m_event_loop_thread->detach();
        m_action_thread->detach();
    }
    m_ref_count++;
    m_timer_event->setId(BTimerPrivate::createID());
}

BTimerPrivate::~BTimerPrivate() {
    if (m_ref_count == 1) {
        m_is_active = false;
        delete m_event_loop_thread;
        m_event_loop_thread = nullptr;
        delete m_action_thread;
        m_action_thread = nullptr;
    }
    m_ref_count--;
}

int32 BTimerPrivate::createID() {
    return m_max_id++;
}

int32 BTimerPrivate::precision() {
    return m_timer_precision;
}

void BTimerPrivate::setPrecision(int32 precision) {
	m_timer_precision = precision;
}

void BTimerPrivate::insertTimerEvent(BTimerEvent* timer_event) {
	std::chrono::microseconds wait_us(100);
	while(true) {
		if (m_event_mutex.try_lock()) {
            int32 event_list_index = timer_event->interval() + m_counter;
            timer_event->setCounter(event_list_index);
            m_timer_event_list_map[event_list_index]
            .push_back(timer_event);
    		m_event_mutex.unlock();
    		return;
		} else {
			m_event_mutex.unlock();
			std::this_thread::sleep_for(wait_us);
		}
	}
}

void BTimerPrivate::insertTimerEvent(int32 counter_index, BTimerEvent* timer_event) {
    std::chrono::microseconds wait_us(100);
    while(true) {
        if (m_event_mutex.try_lock()) {
            timer_event->setCounter(counter_index);
            m_timer_event_list_map[counter_index]
                    .push_back(timer_event);
            m_event_mutex.unlock();
            return;
        } else {
            m_event_mutex.unlock();
            std::this_thread::sleep_for(wait_us);
        }
    }
}

void BTimerPrivate::deleteTimerEvent(BTimerEvent* timer_event) {
    std::chrono::microseconds wait_us(100);
    while (true) {
        if (m_event_mutex.try_lock()) {
            int32 event_list_index = timer_event->counter();
            auto& event_list = m_timer_event_list_map[event_list_index];
            std::list<BTimerEvent*>::iterator it =
                    std::find(event_list.begin(), event_list.end(), timer_event);

            if (it != event_list.end()) {
                event_list.erase(it);
                B_PRINT_DEBUG("BTimerPrivate::deleteTimerEvent erased a timer event."
                              "Timer id is: " << (*it)->id())
            } else {
                B_PRINT_DEBUG("BTimerPrivate::deleteTimerEvent Don't find "
                              "specified timer according to the counter index: "
                              << event_list_index)
            }

            if (event_list.empty()) {
                m_timer_event_list_map.erase(event_list_index);
            }
            m_event_mutex.unlock();
            return;
        } else {
            std::this_thread::sleep_for(wait_us);
        }
    }
}

void BTimerPrivate::eventLoop() {
    while(m_is_active) {
        m_event_mutex.lock();

        if (!m_timer_event_list_map.empty()
            && (m_counter - m_timer_event_list_map.begin()->first) >= 0) {
            B_PRINT_DEBUG("BTimerPrivate::eventLoop interval occured. Counter value is "
            				<< m_counter << " ms")
            auto event_list_pair = m_timer_event_list_map.begin();
            auto& event_list = event_list_pair->second;

            m_action_mutex.lock();
            for (auto it = event_list.begin(); it != event_list.end();) {
                if ((*it)->timeout() < (*it)->interval()) {
                	B_PRINT_DEBUG("BTimerPrivate::eventLoop timeout occred. Timer info: ["
            						<< "ID: " << (*it)->id()
            						<< ", Interval: " << (*it)->interval() << "]")
                    if ((*it)->timeoutAction()) {
                        m_action_queue.push((*it)->timeoutAction());
                    }
                } else {
                    (*it)->setTimeout((*it)->timeout() - (*it)->interval());
                    if ((*it)->intervalAction()) {
                        m_action_queue.push((*it)->intervalAction());
                    }
                    // All of events in this list are expired.
                    // Reinsert them into event queue.
                    if ((*it)->isSingleShot()) {
                        insertTimerEvent((*it)->timeout(), *it);
                        (*it)->setTimeout(0);
                    } else {
                        insertTimerEvent(*it);
                    }
                }
                it = event_list.erase(it);
            }
            B_PRINT_DEBUG("BTimerPrivate::eventLoop action queue has "
    						<< m_action_queue.size() << " actions")
            m_action_mutex.unlock();
            m_action_cond.notify_one();

            if (event_list.empty()) {
            	B_PRINT_DEBUG("BTimerPrivate::eventLoop is empty."
                           " Remove from event map.")
                m_timer_event_list_map.erase(event_list_pair);
            }
        }
        
        m_event_mutex.unlock();
        std::chrono::milliseconds sleep_ms(m_timer_precision);
        std::this_thread::sleep_for(sleep_ms);
        m_counter += m_timer_precision;
    }
}

void BTimerPrivate::actionTrigger() {
    std::chrono::milliseconds wait_ms(100);
    std::chrono::microseconds wait_us(100);
    while(m_is_active) {
        std::unique_lock<std::mutex> lock(m_action_mutex);
        m_action_cond.wait_for(lock, wait_ms);

        while(!m_action_queue.empty()) {
            if (m_action_mutex.try_lock()) {
                m_action_queue.front()();
                m_action_queue.pop();
                m_action_mutex.unlock();
            } else {
            	m_action_mutex.unlock();
            	std::this_thread::sleep_for(wait_us);
            }
        }
    }
}

// End of BTimerPrivate implementation

}  // namespace BThreadPack
