package GoExamples

import (
	"testing"
	"time"
)

func TestFunctionHeap2(t *testing.T) {
	start := time.Now()

	var i uint64 = 0
	for ; i < ITERATIONS; i++ {
		testFunctionHeap2Single(i, i+1, i+2, i+3)
	}

	t.Logf("FunctionHeap2 finished after %s", time.Since(start))
}
