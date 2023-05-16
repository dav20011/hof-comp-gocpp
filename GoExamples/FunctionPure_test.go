package GoExamples

import (
	"testing"
	"time"
)

const ITERATIONS uint64 = 10000000

func testFunctionPureSingle() {
	sampleFunction := func() {
		test += test
	}

	callFunction(sampleFunction)
}

func TestFunctionPure(t *testing.T) {
	start := time.Now()

	var i uint64 = 0
	for ; i < ITERATIONS; i++ {
		testFunctionPureSingle()
	}

	t.Logf("FunctionPure finished after %s", time.Since(start))
}
