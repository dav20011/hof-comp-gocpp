#include <chrono>
#include <iostream>
#include <functional>

#include "test.h"

using namespace std::chrono;

constexpr uint64_t ITERATIONS = 10000000;

static volatile uint64_t test;

static void callFunction(const std::function<void()>& func) {
    func();
}

void testFunctionCaptureSingle(uint64_t x, uint64_t y) {
    auto sampleFunction = [x, y] {
        test += x + y;
    };

    callFunction(sampleFunction);
}

void testFunctionCapture() {
    std::cout << "Starting the FunctionCapture test." << std::endl;
    auto start = high_resolution_clock::now();

    for (uint64_t i = 0; i < ITERATIONS; i++) {
        testFunctionCaptureSingle(i, i + 1);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "FunctionCapture finished after " << duration.count() << "us." << std::endl;
}
