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
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cmath>

#include "gtest/gtest.h"

#include "BCore/BType.h"
#include "BUtils/BUtils.h"
#include "BUtils/BTiming.h"
#include "BUtils/BTimer.h"

void action1() {
	std::cout << "I'm action 1" << std::endl;
}

void action2() {
	std::cout << "I'm action 2" << std::endl;
}

BUtils::BTiming testTimerTiming1;
BUtils::BTiming testTimerTiming2;

void action3() {
    testTimerTiming1.stop();
    std::cout << "I'm action 3, timing result is "
        << testTimerTiming1.time() << " us" << std::endl;
}

void action4() {
    testTimerTiming2.stop();
    std::cout << "I'm action 4, timing result is "
              << testTimerTiming2.time() << " us" << std::endl;
}

class BTimingTest : public ::testing::Test {

protected:

    void SetUp() override {
        std::cout << "SetUp runs before each case." << std::endl;
    }

    void TearDown() override {
        std::cout << "TearDown runs after each case." << std::endl;
    }
};

TEST(TestBUtils, BUtils) {
    using namespace BUtils;
    using std::string;
    using std::set;

    set<string> UUID_set;
    for( int i=0; i < 10; i++) {
        // Generated UUID must be unique and valid
        string test_UUID = generateUUID4();
        EXPECT_EQ(isUUID4(test_UUID), true);
        auto insertResult = UUID_set.insert(test_UUID);
        EXPECT_EQ(insertResult.second, true);
    }

    string fake_UUID = generateUUID4();
    fake_UUID.replace(14, 1, 1, '5');
    EXPECT_EQ(isUUID4(fake_UUID), false);
    fake_UUID.replace(8, 1, 1, '_');
    EXPECT_EQ(isUUID4(fake_UUID), false);
    fake_UUID.replace(1, 1, 1, 'G');
    EXPECT_EQ(isUUID4(fake_UUID), false);
    fake_UUID.erase(fake_UUID.begin());
    EXPECT_EQ(isUUID4(fake_UUID), false);
}

TEST(TestBTiming, BTiming) {
    BUtils::BTiming testTiming;
    testTiming.start();
    EXPECT_EQ(testTiming.isActive(), true);
    EXPECT_EQ(testTiming.time(), 0);
    sleep(1);
    testTiming.stopCPUTiming();
    EXPECT_EQ(testTiming.isActive(), true);
    testTiming.stop();
    EXPECT_EQ(testTiming.isActive(), false);
    EXPECT_GE(testTiming.time(), 1000);

    testTiming.startCPUTiming();
    EXPECT_EQ(testTiming.isActive(), true);
    EXPECT_EQ(testTiming.CPUTime(), 0);
    sleep(1);
    testTiming.stop();
    EXPECT_EQ(testTiming.isActive(), true);
    testTiming.stopCPUTiming();
    EXPECT_EQ(testTiming.isActive(), false);
    EXPECT_GT(testTiming.CPUTime(), 0);
}

TEST(TestBTimer, BTimer) {
    BUtils::BTimer testTimer;
    std::chrono::milliseconds test_1000ms(1000);
    std::chrono::milliseconds test_3000ms(3000);

    EXPECT_GE(testTimer.id(), 0);

    testTimer.setInterval(1000);
    testTimer.setTimeout(3000);
    testTimer.setSingleShot(false);
    EXPECT_GE(testTimer.interval(), 1000);
    EXPECT_GE(testTimer.timeout(), 3000);
    EXPECT_GE(testTimer.isSingleShot(), false);
    testTimer.callOnInterval(action1);
    testTimer.callOnTimeout(action2);
    testTimer.start();
    // Test set properties when running
    testTimer.setInterval(1000);
    testTimer.setTimeout(3000);
    testTimer.setSingleShot(false);
    EXPECT_GE(testTimer.interval(), 1000);
    EXPECT_LE(testTimer.timeout(), 3000);
    EXPECT_GE(testTimer.isSingleShot(), false);
    testTimer.callOnInterval(action1);
    testTimer.callOnTimeout(action2);
    sleep(4);
    testTimer.stop();
    EXPECT_GE(testTimer.timeout(), 0);

    testTimer.setInterval(test_1000ms);
    testTimer.setTimeout(test_3000ms);
    testTimer.setSingleShot(true);
    EXPECT_GE(testTimer.interval(), 1000);
    EXPECT_GE(testTimer.timeout(), 3000);
    EXPECT_GE(testTimer.isSingleShot(), true);
    testTimer.callOnInterval(action1);
    testTimer.callOnTimeout(action2);
    testTimer.start();
    // Test set properties when running
    testTimer.setInterval(test_1000ms);
    testTimer.setTimeout(test_3000ms);
    testTimer.setSingleShot(true);
    EXPECT_GE(testTimer.interval(), 1000);
    EXPECT_LE(testTimer.timeout(), 3000);
    EXPECT_GE(testTimer.isSingleShot(), true);
    testTimer.callOnInterval(action1);
    testTimer.callOnTimeout(action2);
    sleep(4);
    testTimer.stop();
    EXPECT_GE(testTimer.timeout(), 0);
}

TEST(BTimerBenchmark, BTimer) {
    using namespace BCore;
    // Accelerate the output of cout
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::chrono::milliseconds test_10000ms(10000);
    std::random_device true_rand;
    int32 timer_num = 10000;
    int32 rand_num = 0;
    std::vector<BUtils::BTimer*> timerVec(timer_num, nullptr);
    for (int i=0; i < timer_num; i++) {
        timerVec[i] = new BUtils::BTimer();
        rand_num = true_rand();
        rand_num = std::abs(rand_num);
        timerVec[i]->setInterval(rand_num % 1000);
        timerVec[i]->setTimeout(test_10000ms);
        timerVec[i]->callOnInterval(action1);
        timerVec[i]->callOnTimeout(action2);
    }

    testTimerTiming1.start();
    testTimerTiming2.start();
    timerVec[0]->callOnTimeout(action3);
    timerVec.back()->callOnTimeout(action4);
    for (int i=0; i < timer_num; i++) {
        timerVec[i]->start();
    }

    sleep(15);

    for (int i=0; i < timer_num; i++) {
        timerVec[i]->stop();
    }

    for (int i=0; i < timer_num; i++) {
        EXPECT_EQ(timerVec[i]->timeout(), 0);
    }

    for (int i=0; i < timer_num; i++) {
        delete timerVec[i];
    }
    timerVec.clear();
}
