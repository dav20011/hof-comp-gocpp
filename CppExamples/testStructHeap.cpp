#include <chrono>
#include <iostream>
#include <functional>

#include "test.h"

using namespace std::chrono;

constexpr uint64_t ITERATIONS = 10000000;

static volatile uint64_t test;

struct Callback {
    virtual void operator()() const = 0;
};

struct SampleFunction : Callback {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;

    SampleFunction(uint64_t a, uint64_t b, uint64_t c, uint64_t d) : a(a), b(b), c(c), d(d) {}

    void operator()() const override {
        test += a + b + c + d;
    }
};

static void callFunction(const Callback &func) {
    func();
}

void testStructHeapSingle(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    SampleFunction sampleFunction = {a, b, c, d};

    callFunction(sampleFunction);
}

void testStructHeap() {
    std::cout << "Starting the StructHeap test." << std::endl;
    auto start = high_resolution_clock::now();

    for (uint64_t i = 0; i < ITERATIONS; i++) {
        testStructHeapSingle(i, i + 1, i + 2, i + 3);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "StructHeap finished after " << duration.count() << "us." << std::endl;
}
