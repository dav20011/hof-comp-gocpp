#include <iostream>

#include "test.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }

    std::string test = argv[1];

    if (test == "FunctionPointer") {
        testFunctionPointer();
    } else if (test == "Lambda") {
        testLambda();
    } else if (test == "LambdaCapture") {
        testLambdaCapture();
    } else if (test == "FunctionPure") {
        testFunctionPure();
    } else if (test == "FunctionCapture") {
        testFunctionCapture();
    } else if (test == "FunctionHeap") {
        testFunctionHeap();
    } else if (test == "StructHeap") {
        testStructHeap();
    } else if (test == "LambdaLift") {
        testLambdaLift();
    } else {
        std::cout << "Unknown test" << std::endl;
        return 1;
    }

    return 0;
}


