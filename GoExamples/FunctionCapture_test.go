package GoExamples

import (
	"testing"
	"time"
)

func TestFunctionCapture(t *testing.T) {
	start := time.Now()

	var i uint64 = 0
	for ; i < ITERATIONS; i++ {
		testFunctionCaptureSingle(i, i+1)
	}

	t.Logf("FunctionCapture finished after %s", time.Since(start))
}
