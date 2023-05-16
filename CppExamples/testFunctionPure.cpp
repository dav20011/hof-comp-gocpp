#include <chrono>
#include <iostream>
#include <functional>

#include "test.h"

using namespace std::chrono;

constexpr uint64_t ITERATIONS = 10000000;

static volatile uint64_t test;

static void callFunction(std::function<void()> func) {
    func();
}

void testFunctionPureSingle() {
    auto sampleFunction = [] {
        test += test;
    };

    callFunction(sampleFunction);
}

void testFunctionPure() {
    std::cout << "Starting the FunctionPure test." << std::endl;
    auto start = high_resolution_clock::now();

    for (uint64_t i = 0; i < ITERATIONS; i++) {
        testFunctionPureSingle();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "FunctionPure finished after " << duration.count() << "us." << std::endl;
}
