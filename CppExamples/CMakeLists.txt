cmake_minimum_required(VERSION 3.24)
project(CppExamples)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppTests main.cpp testFunctionPointer.cpp testLambda.cpp testLambdaCapture.cpp testFunctionPure.cpp testFunctionCapture.cpp testFunctionHeap.cpp testStructHeap.cpp testLambdaLift.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

enable_testing()
add_test(NAME FunctionPointer COMMAND $<TARGET_FILE:CppTests> FunctionPointer)
add_test(NAME Lambda COMMAND $<TARGET_FILE:CppTests> Lambda)
add_test(NAME LambdaCapture COMMAND $<TARGET_FILE:CppTests> LambdaCapture)
add_test(NAME FunctionPure COMMAND $<TARGET_FILE:CppTests> FunctionPure)
add_test(NAME FunctionCapture COMMAND $<TARGET_FILE:CppTests> FunctionCapture)
add_test(NAME FunctionHeap COMMAND $<TARGET_FILE:CppTests> FunctionHeap)
add_test(NAME StructHeap COMMAND $<TARGET_FILE:CppTests> StructHeap)
add_test(NAME LambdaLift COMMAND $<TARGET_FILE:CppTests> LambdaLift)
