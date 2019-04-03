/* MIT License
*
* Copyright (c) 2019 Ball Chang
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
 * @File        : BTiming.cpp
 * @Date        : 2019-4-3
*/

#include "BUtils/BTiming.h"
#include "BUtils/private/BTimingPrivate.h"

namespace BUtils {

// Start implementation of BTiming
BTiming::BTiming() noexcept
    : m_private_ptr(new BTimingPrivate) {
}

BTiming::~BTiming() {
    if (m_private_ptr != nullptr) {
        delete m_private_ptr;
    }
}

void BTiming::start() {
    if (m_private_ptr->m_status == BTiming::Stop) {
        m_private_ptr->m_status = BTiming::Timing;
        m_private_ptr->m_start_time_us = steady_clock::now();
    }
}

void BTiming::stop() {
    m_private_ptr->m_stop_time_us = steady_clock::now();
}

int64 BTiming::time() const {
    if (m_private_ptr->m_stop_time_us < m_private_ptr->m_start_time_us) {
        return std::chrono::microseconds().zero().count();
    } else {
        return duration_cast<microseconds>(
                m_private_ptr->m_stop_time_us
                - m_private_ptr->m_start_time_us).count();
    }
}

void BTiming::startCPUTiming() {
    if (m_private_ptr->m_status == BTiming::Stop) {
        m_private_ptr->m_status = BTiming::CPUTiming;
        m_private_ptr->m_cpu_time_start = std::clock();
    }
}

void BTiming::stopCPUTiming() {
    if (m_private_ptr->m_status == BTiming::CPUTiming) {
        m_private_ptr->m_status = BTiming::Stop;
        m_private_ptr->m_cpu_time_stop = std::clock();
    }
}

int64 BTiming::CPUTime() const {
    return 1000000*(m_private_ptr->m_cpu_time_stop
    - m_private_ptr->m_cpu_time_start)/CLOCKS_PER_SEC;
}
// End of BTiming implementation


// Start implementation of BTimingPrivate
BTimingPrivate::BTimingPrivate() {
}

BTimingPrivate::~BTimingPrivate() {
}
// End of BTimingPrivate implementation

}  // namespace BUtils
