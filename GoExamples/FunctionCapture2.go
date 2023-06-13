package GoExamples

func createFunctionCapture2(x uint64, y uint64) *func() {
	sampleFunction := func() {
		test += x + y
	}
	return &sampleFunction
}

func testFunctionCapture2Single(x uint64, y uint64) {
	sampleFunction := createFunctionCapture2(x, y)
	callFunction(*sampleFunction)
}
