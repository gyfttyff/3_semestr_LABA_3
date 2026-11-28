package structures

import (
	"fmt"
	"os"
)

type Array[T any] struct {
	data     []T
	size     int
	capacity int
}

func NewArray[T any]() *Array[T] {
	return &Array[T]{}
}

func (a *Array[T]) Init(capacity int) {
	a.data = make([]T, 0, capacity)
	a.size = 0
	a.capacity = capacity
}

func (a *Array[T]) Push(value T) {
	if a.size == a.capacity {
		a.resize()
	}
	a.data = append(a.data, value)
	a.size++
}

func (a *Array[T]) PushIdx(index int, value T) {
	if index < 0 || index > a.size {
		panic("Index out of bounds")
	}
	if a.size == a.capacity {
		a.resize()
	}
	a.data = append(a.data, *new(T))
	copy(a.data[index+1:], a.data[index:])
	a.data[index] = value
	a.size++
}

func (a *Array[T]) DelInd(index int) {
	if index < 0 || index >= a.size {
		panic("Index out of bounds")
	}
	copy(a.data[index:], a.data[index+1:])
	a.data[a.size-1] = *new(T)
	a.size--
}

func (a *Array[T]) Get(index int) T {
	if index < 0 || index >= a.size {
		panic("Index out of bounds")
	}
	return a.data[index]
}

func (a *Array[T]) Len() int {
	return a.size
}

func (a *Array[T]) Print() {
	fmt.Print("Array [", a.size, "]: ")
	for i := 0; i < a.size; i++ {
		fmt.Print(a.data[i])
		if i < a.size-1 {
			fmt.Print(" ")
		}
	}
	fmt.Println()
}

func (a *Array[T]) Clear() {
	a.data = nil
	a.size = 0
	a.capacity = 0
}

func (a *Array[T]) resize() {
	newCapacity := a.capacity * 2
	if newCapacity == 0 {
		newCapacity = 1
	}
	newData := make([]T, a.size, newCapacity)
	copy(newData, a.data)
	a.data = newData
	a.capacity = newCapacity
}

func (a *Array[T]) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	fmt.Fprintln(file, a.size)
	for i := 0; i < a.size; i++ {
		fmt.Fprintln(file, a.data[i])
	}
	return nil
}

func (a *Array[T]) LoadText(filename string) bool {
	file, err := os.Open(filename)
	if err != nil {
		return false
	}
	defer file.Close()
	a.Clear()
	var size int
	if _, err := fmt.Fscan(file, &size); err != nil {
		return false
	}
	if size < 0 || size > 1000000 {
		return false
	}
	a.Init(size)
	for i := 0; i < size; i++ {
		var val T
		if _, err := fmt.Fscan(file, &val); err != nil {
			return false
		}
		a.Push(val)
	}
	return true
}

func (a *Array[T]) SaveBin(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	// Упрощённая бинарная сериализация
	fmt.Fprintln(file, a.size)
	for i := 0; i < a.size; i++ {
		fmt.Fprintln(file, a.data[i])
	}
	return nil
}

func (a *Array[T]) LoadBin(filename string) bool {
	return a.LoadText(filename) // Для простоты используем тот же формат
}
