package GoExamples

import (
	"testing"
	"time"
)

func TestFunctionCapture2(t *testing.T) {
	start := time.Now()

	var i uint64 = 0
	for ; i < ITERATIONS; i++ {
		testFunctionCapture2Single(i, i+1)
	}

	t.Logf("FunctionCapture2 finished after %s", time.Since(start))
}
