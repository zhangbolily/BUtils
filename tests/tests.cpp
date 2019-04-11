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

void timerAction() {
	std::cout << "Timer 1 It works!" << std::endl;
}

void timeoutAction() {
	std::cout << "Timer 2 It works!" << std::endl;
}

void intervalAction() {
	std::cout << "I'm Repeater. I'm Repeater." << std::endl;
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

    std::cout << "Testing BTiming" << std::endl;
    BTiming testTiming;
    testTiming.start();
    sleep(1);
    testTiming.stop();
    std::cout << "Timing result is: " << testTiming.time() << " us." << std::endl;
    testTiming.startCPUTiming();
    sleep(1);
    testTiming.stopCPUTiming();
    std::cout << "CPU Timing result is: " << testTiming.CPUTime() << " us." << std::endl;
    
    BTimer testTimer1;
    BTimer testTimer2;
    std::cout << "Testing BTimer, id: " << testTimer1.id() << std::endl;
    std::cout << "Testing BTimer, id: " << testTimer2.id() << std::endl;
    testTimer1.setInterval(1000);
    testTimer1.setTimeout(5000);
    testTimer1.callOnTimeout(timerAction);
    testTimer1.start();
    
    testTimer2.setInterval(1000);
    testTimer2.setTimeout(5000);
    testTimer2.callOnInterval(intervalAction);
    testTimer2.callOnTimeout(timeoutAction);
    testTimer2.start();
    
    while(1);
}
