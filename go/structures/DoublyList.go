package structures

import (
	"fmt"
	"os"
)

type DNode[T comparable] struct {
	data T
	prev *DNode[T]
	next *DNode[T]
}

type DoublyList[T comparable] struct {
	head *DNode[T]
	tail *DNode[T]
}

func NewDoublyList[T comparable]() *DoublyList[T] {
	return &DoublyList[T]{}
}

func (d *DoublyList[T]) Push(value T) {
	node := &DNode[T]{data: value}
	if d.tail == nil {
		d.head = node
		d.tail = node
	} else {
		node.prev = d.tail
		d.tail.next = node
		d.tail = node
	}
}

func (d *DoublyList[T]) PushHead(value T) {
	node := &DNode[T]{data: value, next: d.head}
	if d.head != nil {
		d.head.prev = node
	} else {
		d.tail = node
	}
	d.head = node
}

func (d *DoublyList[T]) Del(value T) {
	curr := d.head
	for curr != nil {
		if curr.data == value {
			if curr.prev != nil {
				curr.prev.next = curr.next
			} else {
				d.head = curr.next
			}
			if curr.next != nil {
				curr.next.prev = curr.prev
			} else {
				d.tail = curr.prev
			}
			return
		}
		curr = curr.next
	}
}

func (d *DoublyList[T]) Get(value T) T {
	curr := d.head
	for curr != nil {
		if curr.data == value {
			return curr.data
		}
		curr = curr.next
	}
	panic("Value not found")
}

func (d *DoublyList[T]) Print() {
	fmt.Print("DList: ")
	curr := d.head
	for curr != nil {
		fmt.Print(curr.data)
		if curr.next != nil {
			fmt.Print(" <-> ")
		}
		curr = curr.next
	}
	fmt.Println(" <-> nullptr")
}

func (d *DoublyList[T]) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	curr := d.head
	for curr != nil {
		fmt.Fprintln(file, curr.data)
		curr = curr.next
	}
	return nil
}

func (d *DoublyList[T]) LoadText(filename string) bool {
	file, err := os.Open(filename)
	if err != nil {
		return false
	}
	defer file.Close()
	d.head = nil
	d.tail = nil
	var val T
	for {
		if _, err := fmt.Fscan(file, &val); err != nil {
			break
		}
		d.Push(val)
	}
	return true
}

func (d *DoublyList[T]) SaveBin(filename string) error {
	return d.SaveText(filename)
}

func (d *DoublyList[T]) LoadBin(filename string) bool {
	return d.LoadText(filename)
}
