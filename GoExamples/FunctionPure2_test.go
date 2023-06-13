package GoExamples

import (
	"testing"
	"time"
)

func createFunctionPure2() *func() {
	sampleFunction := func() {
		test += test
	}
	return &sampleFunction
}

func testFunctionPure2Single() {
	sampleFunction := createFunctionPure2()
	callFunction(*sampleFunction)
}

func TestFunctionPure2(t *testing.T) {
	start := time.Now()

	var i uint64 = 0
	for ; i < ITERATIONS; i++ {
		testFunctionPure2Single()
	}

	t.Logf("FunctionPure finished after %s", time.Since(start))
}
