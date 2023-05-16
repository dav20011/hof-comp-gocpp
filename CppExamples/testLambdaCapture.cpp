#include <chrono>
#include <iostream>

#include "test.h"

using namespace std::chrono;

constexpr uint64_t ITERATIONS = 10000000;

static volatile uint64_t test;

template <typename T>
static void callFunction(T func) {
    func();
}

void testLambdaCaptureSingle(uint64_t x, uint64_t y) {
    auto sampleFunction = [x, y] {
        test += x + y;
    };

    callFunction(sampleFunction);
}

void testLambdaCapture() {
    std::cout << "Starting the LambdaCapture test." << std::endl;
    auto start = high_resolution_clock::now();

    for (uint64_t i = 0; i < ITERATIONS; i++) {
        testLambdaCaptureSingle(i, i + 1);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "LambdaCapture finished after " << duration.count() << "us." << std::endl;
}
