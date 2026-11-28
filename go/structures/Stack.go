package structures

import (
	"fmt"
	"os"
)

type Stack[T any] struct {
	data     []T
	top      int
	capacity int
}

func NewStack[T any]() *Stack[T] {
	return &Stack[T]{}
}

func (s *Stack[T]) Init(capacity int) {
	s.data = make([]T, capacity)
	s.top = -1
	s.capacity = capacity
}

func (s *Stack[T]) Push(value T) {
	if s.top == s.capacity-1 {
		s.resize()
	}
	s.top++
	s.data[s.top] = value
}

func (s *Stack[T]) Pop() T {
	if s.top == -1 {
		panic("Stack is empty")
	}
	val := s.data[s.top]
	s.top--
	return val
}

func (s *Stack[T]) Peek() T {
	if s.top == -1 {
		panic("Stack is empty")
	}
	return s.data[s.top]
}

func (s *Stack[T]) Len() int {
	return s.top + 1
}

func (s *Stack[T]) Print() {
	fmt.Print("Stack (top to bottom): ")
	for i := s.top; i >= 0; i-- {
		fmt.Print(s.data[i])
		if i > 0 {
			fmt.Print(" ")
		}
	}
	fmt.Println()
}

func (s *Stack[T]) resize() {
	newCapacity := s.capacity * 2
	newData := make([]T, newCapacity)
	copy(newData, s.data)
	s.data = newData
	s.capacity = newCapacity
}

func (s *Stack[T]) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	fmt.Fprintln(file, s.top+1)
	for i := 0; i <= s.top; i++ {
		fmt.Fprintln(file, s.data[i])
	}
	return nil
}

func (s *Stack[T]) LoadText(filename string) bool {
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
	s.Init(size)
	for i := 0; i < size; i++ {
		var val T
		if _, err := fmt.Fscan(file, &val); err != nil {
			return false
		}
		s.Push(val)
	}
	return true
}

func (s *Stack[T]) SaveBin(filename string) error {
	return s.SaveText(filename)
}

func (s *Stack[T]) LoadBin(filename string) bool {
	return s.LoadText(filename)
}
