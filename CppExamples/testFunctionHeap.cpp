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

void testFunctionHeapSingle(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    auto sampleFunction = [a, b, c, d] {
        test += a + b + c + d;
    };

    callFunction(sampleFunction);
}

void testFunctionHeap() {
    std::cout << "Starting the FunctionHeap test." << std::endl;
    auto start = high_resolution_clock::now();

    for (uint64_t i = 0; i < ITERATIONS; i++) {
        testFunctionHeapSingle(i, i + 1, i + 2, i + 3);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "FunctionHeap finished after " << duration.count() << "us." << std::endl;
}
