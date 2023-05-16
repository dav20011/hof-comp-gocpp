package GoExamples

import (
	"testing"
	"time"
)

func TestFunctionHeap(t *testing.T) {
	start := time.Now()

	var i uint64 = 0
	for ; i < ITERATIONS; i++ {
		testFunctionHeapSingle(i, i+1, i+2, i+3)
	}

	t.Logf("FunctionHeap finished after %s", time.Since(start))
}
