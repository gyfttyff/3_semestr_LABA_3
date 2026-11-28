package structures

import (
	"fmt"
	"testing"
)

func BenchmarkArrayPush(b *testing.B) {
	for i := 0; i < b.N; i++ {
		a := NewArray[int]()
		for j := 0; j < 1000; j++ {
			a.Push(j)
		}
	}
}

func BenchmarkArrayPushIdx(b *testing.B) {
	for i := 0; i < b.N; i++ {
		a := NewArray[int]()
		for j := 0; j < 100; j++ {
			a.Push(j)
		}
		for j := 0; j < 100; j++ {
			a.PushIdx(0, j)
		}
	}
}

func BenchmarkArrayDel(b *testing.B) {
	for i := 0; i < b.N; i++ {
		a := NewArray[int]()
		for j := 0; j < 1000; j++ {
			a.Push(j)
		}
		for j := 0; j < 1000; j++ {
			a.DelInd(0)
		}
	}
}

func BenchmarkForwardListPush(b *testing.B) {
	for i := 0; i < b.N; i++ {
		f := NewForwardList[int]()
		for j := 0; j < 1000; j++ {
			f.Push(j)
		}
	}
}

func BenchmarkForwardListPushHead(b *testing.B) {
	for i := 0; i < b.N; i++ {
		f := NewForwardList[int]()
		for j := 0; j < 1000; j++ {
			f.PushHead(j)
		}
	}
}

func BenchmarkDoublyListPush(b *testing.B) {
	for i := 0; i < b.N; i++ {
		d := NewDoublyList[int]()
		for j := 0; j < 1000; j++ {
			d.Push(j)
		}
	}
}

func BenchmarkStackPush(b *testing.B) {
	for i := 0; i < b.N; i++ {
		s := NewStack[int]()
		s.Init(1000)
		for j := 0; j < 1000; j++ {
			s.Push(j)
		}
	}
}

func BenchmarkQueuePush(b *testing.B) {
	for i := 0; i < b.N; i++ {
		q := NewQueue[int]()
		q.Init(1000)
		for j := 0; j < 1000; j++ {
			q.Push(j)
		}
	}
}

func BenchmarkHashTableInsert(b *testing.B) {
	for i := 0; i < b.N; i++ {
		h := NewHashTable()
		h.Init(1000)
		for j := 0; j < 1000; j++ {
			h.Add(fmt.Sprintf("%d", j))
		}
	}
}

func BenchmarkHashTableFind(b *testing.B) {
	for i := 0; i < b.N; i++ {
		h := NewHashTable()
		h.Init(1000)
		for j := 0; j < 1000; j++ {
			h.Add(fmt.Sprintf("%d", j))
		}
		for j := 0; j < 1000; j++ {
			h.Contains(fmt.Sprintf("%d", j))
		}
	}
}

func BenchmarkTreeInsert(b *testing.B) {
	for i := 0; i < b.N; i++ {
		t := NewCompleteBinaryTree[int]()
		for j := 0; j < 1000; j++ {
			t.Insert(j)
		}
	}
}

func BenchmarkTreeSearch(b *testing.B) {
	for i := 0; i < b.N; i++ {
		t := NewCompleteBinaryTree[int]()
		for j := 0; j < 1000; j++ {
			t.Insert(j)
		}
		for j := 0; j < 1000; j++ {
			t.Search(j)
		}
	}
}
