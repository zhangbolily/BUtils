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
    setActive(false);
    m_private_ptr->deleteTimerEvent(m_private_ptr->m_timer_event);
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

// Start implementation of BTimerEventList

BTimerEventList::BTimerEventList(const BTimerEventList& elist)
        : list<BTimerEvent*>(std::move(elist)){
    m_interval.store(elist.m_interval);
}

BTimerEventList::BTimerEventList(BTimerEventList&& elist)
        : list<BTimerEvent*>(std::move(elist)){
    m_interval.store(elist.m_interval);
}

BTimerEventList& BTimerEventList::operator=(const BTimerEventList& elist) {
    list<BTimerEvent*>::operator=(std::move(elist));
    m_interval.store(elist.m_interval);

    return *this;
}

BTimerEventList& BTimerEventList::operator=(BTimerEventList&& elist) {
    list<BTimerEvent*>::operator=(std::move(elist));
    m_interval.store(elist.m_interval);

    return *this;
}

int32 BTimerEventList::interval() {
    return m_interval;
}

void BTimerEventList::setInterval(BCore::int32 _interval) {
    m_interval = _interval;
}

// End of BTimerEventList implementation

// Start implementation of BTimerPriorityQueue

BTimerPriorityQueue::BTimerPriorityQueue(const BTimerPriorityQueue& timer_queue)
        : priority_queue
              <std::pair<int32, BTimerEventList>,
              std::vector<std::pair<int32, BTimerEventList>>,
              std::greater<std::pair<int32, BTimerEventList>>>(std::move(timer_queue)) {
}

BTimerPriorityQueue::BTimerPriorityQueue(BTimerPriorityQueue&& timer_queue)
    : priority_queue
          <std::pair<int32, BTimerEventList>,
          std::vector<std::pair<int32, BTimerEventList>>,
          std::greater<std::pair<int32, BTimerEventList>>>(std::move(timer_queue)) {
}

BTimerPriorityQueue& BTimerPriorityQueue::operator=(const BTimerPriorityQueue& timer_queue) {
    priority_queue
            <std::pair<int32, BTimerEventList>,
                    std::vector<std::pair<int32, BTimerEventList>>,
                    std::greater<std::pair<int32, BTimerEventList>>>
    ::operator=(std::move(timer_queue));
}

BTimerPriorityQueue& BTimerPriorityQueue::operator=(BTimerPriorityQueue&& timer_queue) {
    priority_queue
            <std::pair<int32, BTimerEventList>,
                    std::vector<std::pair<int32, BTimerEventList>>,
                    std::greater<std::pair<int32, BTimerEventList>>>
    ::operator=(std::move(timer_queue));
}

void BTimerPriorityQueue::updateQueue() {
    std::make_heap(c.begin(), c.end(), comp);
}

BTimerEventList& BTimerPriorityQueue::getEventList(int32 interval) {
    BTimerEventList result_event_list;
    for (auto it = c.begin(); it != c.end(); it++) {
        if (it->second.interval() == interval) {
            return it->second;
        }
    }
    // Don't find the correspond list, create a new list.
    BTimerEventList event_list;
    event_list.setInterval(interval);
    emplace(0, std::move(event_list));
    for (auto it = c.begin(); it != c.end(); it++) {
        if (it->second.interval() == interval) {
            return it->second;
        }
    }
}

// End of BTimerPriorityQueue implementation

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
BTimerPriorityQueue     BTimerPrivate::m_timer_event_queue;

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
            m_timer_event_list_map[timer_event->interval() + m_counter]
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
            int32 event_list_index = timer_event->interval() + m_counter;
            auto event_list = m_timer_event_list_map[event_list_index];
            auto it = std::find(event_list.begin(), event_list.end(), timer_event);
            event_list.erase(it);
            if (event_list.empty()) {
                m_timer_event_list_map.erase(event_list_index);
            }
            m_event_mutex.unlock();
            return;
        } else {
            m_event_mutex.unlock();
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
                    insertTimerEvent(*it);
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
                m_timer_event_list_map.erase(m_timer_event_list_map.begin());
            }
        }
        
        m_event_mutex.unlock();
        std::chrono::milliseconds sleep_ms(m_timer_precision);
        std::this_thread::sleep_for(sleep_ms);
        m_counter += m_timer_precision;
    }
}

void BTimerPrivate::actionTrigger() {
    std::chrono::microseconds wait_us(100);
    while(true) {
        std::unique_lock<std::mutex> lock(m_action_mutex);
        m_action_cond.wait_for(lock, wait_us);

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
