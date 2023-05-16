package GoExamples

var test uint64 = 1

func callFunction(f func()) {
	f()
}

func testFunctionCaptureSingle(x uint64, y uint64) {
	sampleFunction := func() {
		test += x + y
	}

	callFunction(sampleFunction)
}
