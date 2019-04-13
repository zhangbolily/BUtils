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

bool BTimer::operator>(const BTimer& rtimer) const {
    return this->id() > rtimer.id();
}

bool BTimer::operator<(const BTimer& rtimer) const {
    return this->id() < rtimer.id();
}

bool BTimer::operator==(const BTimer& rtimer) const {
    return this->id() == rtimer.id();
}

void BTimer::start() {
    setActive(true);
    BTimerPrivate::insertTimerEvent(m_private_ptr->m_timer_event);
}

void BTimer::stop() {
    BTimerPrivate::deleteTimerEvent(m_private_ptr->m_timer_event);
    setActive(false);
}

bool BTimer::isActive() const {
    return m_private_ptr->m_timer_event->isActive();
}

bool BTimer::isSingleShot() const {
    return m_private_ptr->m_timer_event->isSingleShot();
}

int32 BTimer::id() const {
    return m_private_ptr->m_timer_event->id();
}

uint32 BTimer::interval() const {
    return m_private_ptr->m_timer_event->interval();
}
uint32 BTimer::timeout() const {
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

void BTimer::setInterval(uint32 _interval) {
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

void BTimer::setTimeout(uint32 _timeout) {
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

uint BTimer::precision() {
    return BTimerPrivate::precision();
}

void BTimer::setPrecision(uint _precision) {
    BTimerPrivate::setPrecision(_precision);
}

// End of BTimer implementation

// Start implementation of BTimerPrivate

thread*         BTimerPrivate::m_action_thread = nullptr;
thread*         BTimerPrivate::m_event_loop_thread = nullptr;
uint            BTimerPrivate::m_timer_precision = 1;   // Default 1ms
mutex           BTimerPrivate::m_event_mutex;
mutex           BTimerPrivate::m_action_mutex;
condition_variable BTimerPrivate::m_action_cond;
atomic_bool     BTimerPrivate::m_is_active(false);
atomic_int      BTimerPrivate::m_event_loop_active(false);
atomic_int      BTimerPrivate::m_action_trigger_active(false);
atomic_int  	BTimerPrivate::m_max_id(0);
atomic_int  	BTimerPrivate::m_ref_count(0);
atomic_long  	BTimerPrivate::m_counter(0);
queue<std::function<void()> > BTimerPrivate::m_action_queue;
map<int32, std::list<BTimerEvent*>> BTimerPrivate::m_timer_event_list_map;

BTimerPrivate::BTimerPrivate() noexcept
    : m_timer_event(new BTimerEvent()) {
    if (m_ref_count == 0 && !m_is_active) {
        // TODO(Ball Chang): Create a new event loop thread.
        m_is_active = true;
        if (!m_event_loop_active) {
            if (m_event_loop_thread != nullptr) {
                delete m_event_loop_thread;
                m_event_loop_thread = nullptr;
            }
            m_event_loop_thread = new thread(BTimerPrivate::eventLoop);
            m_event_loop_thread->detach();
        }

        if (!m_action_trigger_active) {
            if (m_action_thread != nullptr) {
                delete m_action_thread;
                m_action_thread = nullptr;
            }
            m_action_thread = new thread(BTimerPrivate::actionTrigger);
            m_action_thread->detach();
        }
    }
    m_ref_count++;
    m_timer_event->setId(BTimerPrivate::createID());
}

BTimerPrivate::~BTimerPrivate() {
	deleteTimerEvent(m_timer_event);
	std::chrono::microseconds sleep_us(100);

	if (m_timer_event != nullptr) {
		delete m_timer_event;
	}	
	
    if (m_ref_count == 1) {
        m_counter = 0;
        m_is_active = false;
        std::this_thread::sleep_for(sleep_us);

        if (!m_event_loop_active) {
            delete m_event_loop_thread;
            m_event_loop_thread = nullptr;
        }

        if (!m_action_trigger_active) {
            delete m_action_thread;
            m_action_thread = nullptr;
        }
    }
    m_ref_count--;
}

int32 BTimerPrivate::createID() {
    return m_max_id++;
}

uint BTimerPrivate::precision() {
    return m_timer_precision;
}

void BTimerPrivate::setPrecision(uint precision) {
	m_timer_precision = precision;
}

void BTimerPrivate::insertTimerEvent(BTimerEvent* timer_event) {
	std::chrono::microseconds wait_us(100);
	while(timer_event->timeout()) {
		if (m_event_mutex.try_lock()) {
		    if (timer_event->interval() < timer_event->timeout()
		        && timer_event->interval()) {
                uint event_list_index = timer_event->interval() + m_counter;
                timer_event->setCounter(event_list_index);
                m_timer_event_list_map[event_list_index]
                        .push_back(timer_event);
		    } else {
                uint event_list_index = timer_event->timeout() + m_counter;
                timer_event->setTimeout(0);
                timer_event->setCounter(event_list_index);
                m_timer_event_list_map[event_list_index]
                        .push_back(timer_event);
		    }
    		m_event_mutex.unlock();
    		return;
		} else {
			m_event_mutex.unlock();
			std::this_thread::sleep_for(wait_us);
		}
	}
    // timeout and interval both are 0, won't be insert into timer.
    timer_event->setActive(false);
}

void BTimerPrivate::insertTimerEvent(uint counter_index, BTimerEvent* timer_event) {
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
    while (timer_event->isActive()) {
        if (m_event_mutex.try_lock()) {
            int32 event_list_index = timer_event->counter();
            auto& event_list = m_timer_event_list_map[event_list_index];
            auto it =
                    std::find(event_list.begin(), event_list.end(), timer_event);

            if (it != event_list.end()) {
                event_list.erase(it);
                B_PRINT_DEBUG("BTimerPrivate::deleteTimerEvent erased a timer event."
                              "Timer id is: " << timer_event->id())
            } else {
                B_PRINT_DEBUG("BTimerPrivate::deleteTimerEvent Don't find "
                              "specified timer according to the counter index: "
                              << event_list_index
                              << " Timer info: [ ID: " << timer_event->id()
                              << " , Interval: " << timer_event->interval()
                              << " , Timeout: " << timer_event->timeout() << "]")
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
    m_event_loop_active = true;
#ifdef WIN32
#else
    prctl(PR_SET_NAME, "eventLoop");
#endif
    BTiming time_correction;
    std::chrono::microseconds sleep_us(m_timer_precision * 1000);
    std::chrono::microseconds sleep_us_correction;

    while(m_is_active) {
        time_correction.start();
        m_event_mutex.lock();

        if (!m_timer_event_list_map.empty()
            && (m_counter - m_timer_event_list_map.begin()->first) >= 0) {
            auto event_list_pair = m_timer_event_list_map.begin();
            auto& event_list = event_list_pair->second;

            m_action_mutex.lock();
            for (auto it = event_list.begin(); it != event_list.end();) {
                if ((*it)->timeout() < (*it)->interval()) {
                	B_PRINT_DEBUG("BTimerPrivate::eventLoop timeout occred. Timer info: ["
            						<< "ID: " << (*it)->id()
            						<< ", Interval: " << (*it)->interval()
            						<< ", Timeout: " << (*it)->timeout()
            						<< ", Counter: " << (*it)->counter() << "]")
                    if ((*it)->timeoutAction()) {
                        m_action_queue.push((*it)->timeoutAction());
                    }
                    (*it)->setTimeout(0);
                    (*it)->setActive(false);
                } else {
                    (*it)->setTimeout((*it)->timeout() - (*it)->interval());

                    if ((*it)->intervalAction()) {
                        m_action_queue.push((*it)->intervalAction());
                    }
                    // All of events in this list are expired.
                    // Reinsert them into event queue.
                    if ((*it)->isSingleShot()) {
                        insertTimerEvent((*it)->timeout() + m_counter, *it);
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
        time_correction.stop();
        sleep_us_correction =
                std::chrono::microseconds(time_correction.time());
        std::this_thread::sleep_for(sleep_us - sleep_us_correction);
        m_counter += m_timer_precision;
    }

    m_event_loop_active = false;
}

void BTimerPrivate::actionTrigger() {
    m_action_trigger_active = true;
#ifdef WIN32
#else
    prctl(PR_SET_NAME, "actionTrigger");
#endif

    std::chrono::milliseconds wait_ms(100);
    std::chrono::microseconds wait_us(100);
    while(m_is_active) {
        std::unique_lock<std::mutex> lock(m_action_mutex);
        m_action_cond.wait_for(lock, wait_ms);
        lock.unlock();

        while(!m_action_queue.empty()) {
            if (m_action_mutex.try_lock()) {
                m_action_queue.front()();
                m_action_queue.pop();
                m_action_mutex.unlock();
            } else {
                std::this_thread::sleep_for(wait_us);
            }
        }
    }

    m_action_trigger_active = false;
}

// End of BTimerPrivate implementation

}  // namespace BThreadPack
