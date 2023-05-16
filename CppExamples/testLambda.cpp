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

void testLambdaSingle() {
    auto sampleFunction = [] {
        test += test;
    };

    callFunction(sampleFunction);
}

void testLambda() {
    std::cout << "Starting the Lambda test." << std::endl;
    auto start = high_resolution_clock::now();

    for (uint64_t i = 0; i < ITERATIONS; i++) {
        testLambdaSingle();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Lambda finished after " << duration.count() << "us." << std::endl;
}
