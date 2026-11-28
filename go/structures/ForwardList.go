package structures

import (
	"fmt"
	"os"
)

type Node[T comparable] struct {
	data T
	next *Node[T]
}

type ForwardList[T comparable] struct {
	head *Node[T]
}

func NewForwardList[T comparable]() *ForwardList[T] {
	return &ForwardList[T]{}
}

func (f *ForwardList[T]) PushHead(value T) {
	node := &Node[T]{data: value, next: f.head}
	f.head = node
}

func (f *ForwardList[T]) Push(value T) {
	if f.head == nil {
		f.PushHead(value)
		return
	}
	curr := f.head
	for curr.next != nil {
		curr = curr.next
	}
	curr.next = &Node[T]{data: value}
}

func (f *ForwardList[T]) Del(value T) {
	if f.head == nil {
		return
	}
	if f.head.data == value {
		f.head = f.head.next
		return
	}
	curr := f.head
	for curr.next != nil {
		if curr.next.data == value {
			curr.next = curr.next.next
			return
		}
		curr = curr.next
	}
}

func (f *ForwardList[T]) Get(value T) T {
	curr := f.head
	for curr != nil {
		if curr.data == value {
			return curr.data
		}
		curr = curr.next
	}
	panic("Value not found")
}

func (f *ForwardList[T]) Print() {
	fmt.Print("List: ")
	curr := f.head
	for curr != nil {
		fmt.Print(curr.data)
		if curr.next != nil {
			fmt.Print(" -> ")
		}
		curr = curr.next
	}
	fmt.Println(" -> nullptr")
}

func (f *ForwardList[T]) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	curr := f.head
	for curr != nil {
		fmt.Fprintln(file, curr.data)
		curr = curr.next
	}
	return nil
}

func (f *ForwardList[T]) LoadText(filename string) bool {
	file, err := os.Open(filename)
	if err != nil {
		return false
	}
	defer file.Close()
	f.head = nil
	var val T
	for {
		if _, err := fmt.Fscan(file, &val); err != nil {
			break
		}
		f.Push(val)
	}
	return true
}

func (f *ForwardList[T]) SaveBin(filename string) error {
	return f.SaveText(filename)
}

func (f *ForwardList[T]) LoadBin(filename string) bool {
	return f.LoadText(filename)
}
