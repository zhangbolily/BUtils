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
 * @File        : tests.cpp
 * @Date        : 2019-4-2
*/

#include <iostream>
#include <string>
#include <set>
#include <unistd.h>

#include "BUtils/BUtils.h"
#include "BCore/BDebug.h"
#include "BUtils/BTiming.h"
#include "BUtils/BTimer.h"

void action1() {
	std::cout << "I'm action 1" << std::endl;
}

void action2() {
	std::cout << "I'm action 2" << std::endl;
}

void action3() {
	std::cout << "I'm action 3" << std::endl;
}

void action4() {
    std::cout << "I'm action 4" << std::endl;
}

void action5() {
    std::cout << "I'm action 5" << std::endl;
}

int main(int argc, char** argv) {
    using namespace BCore;
    using namespace BUtils;

    using std::string;
    using std::set;

    std::cout << "Start BUtils testing" << std::endl;
    set<string> UUID_set;
    for( int i=0; i < 10; i++) {
        string test_UUID = generateUUID4();
        if (!isUUID4(test_UUID)) {
            B_PRINT_ERROR("BUtils test generateUUID4 UUID: "
                                  << test_UUID << " is not a valid UUID.")
        }
        auto insertResult = UUID_set.insert(test_UUID);
        if (!insertResult.second) {
            B_PRINT_ERROR("BUtils test generateUUID4 insert UUID: "
                          << test_UUID << " failed.")
        }

        std::cout << "generateUUID4 UUID:" << test_UUID
                << " is a valid UUID" << std::endl;
    }
    
    string fake_UUID = generateUUID4();
    fake_UUID.replace(fake_UUID.begin(), fake_UUID.end(), '-', '_');
    std::cout << "UUID: " << fake_UUID << " is " << isUUID4(fake_UUID) << std::endl;
    fake_UUID.erase(fake_UUID.begin());
    std::cout << "UUID: " << fake_UUID << " is " << isUUID4(fake_UUID) << std::endl;

    std::cout << "Testing BTiming" << std::endl;
    BTiming testTiming;
    testTiming.start();
    std::cout << "Timing: " << testTiming.isActive() << std::endl;
    sleep(1);
    std::cout << "Before call stop. "
    	"Timing result is: " << testTiming.time() << " us." << std::endl;
    testTiming.stop();
    std::cout << "Timing result is: " << testTiming.time() << " us." << std::endl;
    testTiming.startCPUTiming();
    sleep(1);
    std::cout << "Before call stop. "
    	"CPUTiming result is: " << testTiming.CPUTime() << " us." << std::endl;
    testTiming.stopCPUTiming();
    std::cout << "CPU Timing result is: " << testTiming.CPUTime() << " us." << std::endl;
    
    BTimer testTimer1;
    BTimer testTimer2;
    BTimer testTimer3;
    std::cout << "Testing BTimer, id: " << testTimer1.id() << std::endl;
    std::cout << "Testing BTimer, id: " << testTimer2.id() << std::endl;
    testTimer1.setInterval(1000);
    testTimer1.setTimeout(5000);
    testTimer1.callOnTimeout(action1);
    testTimer1.start();
    
    testTimer2.setInterval(1000);
    testTimer2.setTimeout(5000);
    testTimer2.callOnInterval(action2);
    testTimer2.callOnTimeout(action3);
    testTimer2.start();

    testTimer3.setInterval(1000);
    testTimer3.setTimeout(5000);
    testTimer3.start();
    testTimer3.setInterval(1000);
    testTimer3.setTimeout(5000);
    testTimer3.setSingleShot(true);
    testTimer3.callOnInterval(action4);
    testTimer3.callOnTimeout(action5);

    sleep(2);
    std::chrono::milliseconds interval_ms(500);
    std::chrono::milliseconds timeout_ms(10000);
    testTimer2.setInterval(interval_ms);
    testTimer2.setTimeout(timeout_ms);

    std::cout << "Timer: " << testTimer2.id() << " timeout: "
                << testTimer2.timeout() << std::endl;
    std::cout << "Timer: " << testTimer2.id() << " interval: "
              << testTimer2.interval() << std::endl;
    std::cout << "Timer: " << testTimer2.id() << " isSingleShot: "
              << testTimer2.isSingleShot() << std::endl;
    sleep(3);

    testTimer2.stop();
    
    sleep(20);
}
