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
 * @File        : BTimingPrivate.h
 * @Date        : 2019-4-3
*/

#ifndef INCLUDE_BUTILS_BTIMINGPRIVATE_H_
#define INCLUDE_BUTILS_BTIMINGPRIVATE_H_

#include <chrono>
#include <ctime>

#include "BCore/BCore.h"
#include "BCore/BDebug.h"
#include "BCore/BType.h"
#include "BUtils/BTiming.h"

namespace BUtils {
class BTimingPrivate {
 public:
    BTimingPrivate();
    ~BTimingPrivate();
    std::chrono::steady_clock::time_point m_start_time_us;
    std::chrono::steady_clock::time_point m_stop_time_us;
    std::clock_t m_cpu_time_start;
    std::clock_t m_cpu_time_stop;
    BTiming::BTimingStatus m_status;
};
}  // namespace BUtils

#endif  // INCLUDE_BUTILS_BTIMINGPRIVATE_H_