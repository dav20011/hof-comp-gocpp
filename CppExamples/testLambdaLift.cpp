#include <chrono>
#include <iostream>

#include "test.h"

using namespace std::chrono;

constexpr uint64_t ITERATIONS = 10000000;

static volatile uint64_t test;

template <typename T>
static void callFunction(T func, uint64_t x, uint64_t y) {
    func(x, y);
}

void sampleFunction(uint64_t x, uint64_t y) {
    test += x + y;
};

void testLambdaLiftSingle(uint64_t x, uint64_t y) {
    callFunction(sampleFunction, x, y);
}

void testLambdaLift() {
    std::cout << "Starting the LambdaCapture test." << std::endl;
    auto start = high_resolution_clock::now();

    for (uint64_t i = 0; i < ITERATIONS; i++) {
        testLambdaLiftSingle(i, i + 1);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "LambdaCapture finished after " << duration.count() << "us." << std::endl;
}
