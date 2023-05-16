package GoExamples

func testFunctionHeapSingle(a uint64, b uint64, c uint64, d uint64) {
	sampleFunction := func() {
		test += a + b + c + d
	}

	callFunction(sampleFunction)
}
