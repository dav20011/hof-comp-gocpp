#include <chrono>
#include <iostream>

#include "test.h"

using namespace std::chrono;

constexpr uint64_t ITERATIONS = 10000000;

static volatile uint64_t test;

static void sampleFunction() {
    test += test;
}

static void callFunction(void (*func)()) {
    func();
}

void testFunctionPointer() {
    std::cout << "Starting the FunctionPointer test." << std::endl;
    auto start = high_resolution_clock::now();

    for (uint64_t i = 0; i < ITERATIONS; i++) {
        callFunction(sampleFunction);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "FunctionPointer finished after " << duration.count() << "us." << std::endl;
}
