package GoExamples

func createFunctionHeap2(a uint64, b uint64, c uint64, d uint64) *func() {
	sampleFunction := func() {
		test += a + b + c + d
	}
	return &sampleFunction
}

func testFunctionHeap2Single(a uint64, b uint64, c uint64, d uint64) {
	sampleFunction := createFunctionHeap2(a, b, c, d)
	callFunction(*sampleFunction)
}
