package structures

import (
	"fmt"
	"os"
)

type TNode[T comparable] struct {
	data  T
	left  *TNode[T]
	right *TNode[T]
}

type CompleteBinaryTree[T comparable] struct {
	root *TNode[T]
}

func NewCompleteBinaryTree[T comparable]() *CompleteBinaryTree[T] {
	return &CompleteBinaryTree[T]{}
}

func (t *CompleteBinaryTree[T]) Insert(value T) {
	node := &TNode[T]{data: value}
	if t.root == nil {
		t.root = node
		return
	}
	queue := []*TNode[T]{t.root}
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		if curr.left == nil {
			curr.left = node
			return
		}
		queue = append(queue, curr.left)
		if curr.right == nil {
			curr.right = node
			return
		}
		queue = append(queue, curr.right)
	}
}

func (t *CompleteBinaryTree[T]) Search(value T) bool {
	if t.root == nil {
		return false
	}
	queue := []*TNode[T]{t.root}
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		if curr.data == value {
			return true
		}
		if curr.left != nil {
			queue = append(queue, curr.left)
		}
		if curr.right != nil {
			queue = append(queue, curr.right)
		}
	}
	return false
}

func (t *CompleteBinaryTree[T]) IsComplete() bool {
	if t.root == nil {
		return true
	}
	queue := []*TNode[T]{t.root}
	foundNull := false
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		if curr == nil {
			foundNull = true
		} else {
			if foundNull {
				return false
			}
			queue = append(queue, curr.left)
			queue = append(queue, curr.right)
		}
	}
	return true
}

func (t *CompleteBinaryTree[T]) Print() {
	fmt.Print("CBTree: ")
	if t.root == nil {
		fmt.Println()
		return
	}
	queue := []*TNode[T]{t.root}
	first := true
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		if !first {
			fmt.Print(" ")
		}
		fmt.Print(curr.data)
		first = false
		if curr.left != nil {
			queue = append(queue, curr.left)
		}
		if curr.right != nil {
			queue = append(queue, curr.right)
		}
	}
	fmt.Println()
}

func (t *CompleteBinaryTree[T]) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	if t.root == nil {
		fmt.Fprintln(file, 0)
		return nil
	}
	queue := []*TNode[T]{t.root}
	count := 0
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		count++
		if curr.left != nil {
			queue = append(queue, curr.left)
		}
		if curr.right != nil {
			queue = append(queue, curr.right)
		}
	}
	fmt.Fprintln(file, count)
	queue = []*TNode[T]{t.root}
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		fmt.Fprintln(file, curr.data)
		if curr.left != nil {
			queue = append(queue, curr.left)
		}
		if curr.right != nil {
			queue = append(queue, curr.right)
		}
	}
	return nil
}

func (t *CompleteBinaryTree[T]) LoadText(filename string) bool {
	file, err := os.Open(filename)
	if err != nil {
		return false
	}
	defer file.Close()
	var count int
	if _, err := fmt.Fscan(file, &count); err != nil {
		return false
	}
	if count < 0 || count > 1000000 {
		return false
	}
	t.root = nil
	for i := 0; i < count; i++ {
		var val T
		if _, err := fmt.Fscan(file, &val); err != nil {
			return false
		}
		t.Insert(val)
	}
	return true
}

func (t *CompleteBinaryTree[T]) SaveBin(filename string) error {
	return t.SaveText(filename)
}

func (t *CompleteBinaryTree[T]) LoadBin(filename string) bool {
	return t.LoadText(filename)
}
