package structures

import (
	"fmt"
	"os"
)

type Queue[T any] struct {
	data     []T
	head     int
	tail     int
	capacity int
}

func NewQueue[T any]() *Queue[T] {
	return &Queue[T]{}
}

func (q *Queue[T]) Init(capacity int) {
	q.data = make([]T, capacity)
	q.head = 0
	q.tail = 0
	q.capacity = capacity
}

func (q *Queue[T]) Push(value T) {
	if (q.tail+1)%q.capacity == q.head {
		q.resize()
	}
	q.data[q.tail] = value
	q.tail = (q.tail + 1) % q.capacity
}

func (q *Queue[T]) Pop() T {
	if q.head == q.tail {
		panic("Queue is empty")
	}
	val := q.data[q.head]
	q.head = (q.head + 1) % q.capacity
	return val
}

func (q *Queue[T]) Peek() T {
	if q.head == q.tail {
		panic("Queue is empty")
	}
	return q.data[q.head]
}

func (q *Queue[T]) Len() int {
	if q.tail >= q.head {
		return q.tail - q.head
	}
	return q.capacity - q.head + q.tail
}

func (q *Queue[T]) Print() {
	fmt.Print("Queue (front to back): ")
	i := q.head
	first := true
	for i != q.tail {
		if !first {
			fmt.Print(" ")
		}
		fmt.Print(q.data[i])
		i = (i + 1) % q.capacity
		first = false
	}
	fmt.Println()
}

func (q *Queue[T]) resize() {
	newCapacity := q.capacity * 2
	newData := make([]T, newCapacity)
	i := q.head
	j := 0
	for i != q.tail {
		newData[j] = q.data[i]
		i = (i + 1) % q.capacity
		j++
	}
	q.data = newData
	q.head = 0
	q.tail = j
	q.capacity = newCapacity
}

func (q *Queue[T]) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	fmt.Fprintln(file, q.Len())
	i := q.head
	for i != q.tail {
		fmt.Fprintln(file, q.data[i])
		i = (i + 1) % q.capacity
	}
	return nil
}

func (q *Queue[T]) LoadText(filename string) bool {
	file, err := os.Open(filename)
	if err != nil {
		return false
	}
	defer file.Close()
	var size int
	if _, err := fmt.Fscan(file, &size); err != nil {
		return false
	}
	if size < 0 || size > 1000000 {
		return false
	}
	q.Init(size + 1)
	for i := 0; i < size; i++ {
		var val T
		if _, err := fmt.Fscan(file, &val); err != nil {
			return false
		}
		q.Push(val)
	}
	return true
}

func (q *Queue[T]) SaveBin(filename string) error {
	return q.SaveText(filename)
}

func (q *Queue[T]) LoadBin(filename string) bool {
	return q.LoadText(filename)
}
