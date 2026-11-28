package structures

import (
	"fmt"
	"os"
)

type HashTable struct {
	table    []string
	state    []int
	capacity int
}

func NewHashTable() *HashTable {
	return &HashTable{}
}

func (h *HashTable) Init(capacity int) {
	h.table = make([]string, capacity)
	h.state = make([]int, capacity)
	h.capacity = capacity
}

func (h *HashTable) hash(key string) int {
	hashVal := 0
	for _, c := range key {
		hashVal = hashVal*31 + int(c)
	}
	return (hashVal%h.capacity + h.capacity) % h.capacity
}

func (h *HashTable) Add(key string) {
	idx := h.hash(key)
	for h.state[idx] == 1 {
		if h.table[idx] == key {
			return
		}
		idx = (idx + 1) % h.capacity
	}
	h.table[idx] = key
	h.state[idx] = 1
}

func (h *HashTable) Contains(key string) bool {
	idx := h.hash(key)
	startIdx := idx
	for h.state[idx] != 0 {
		if h.state[idx] == 1 && h.table[idx] == key {
			return true
		}
		idx = (idx + 1) % h.capacity
		if idx == startIdx {
			break
		}
	}
	return false
}

func (h *HashTable) Remove(key string) {
	idx := h.hash(key)
	startIdx := idx
	for h.state[idx] != 0 {
		if h.state[idx] == 1 && h.table[idx] == key {
			h.state[idx] = 2
			return
		}
		idx = (idx + 1) % h.capacity
		if idx == startIdx {
			break
		}
	}
}

func (h *HashTable) Print() {
	fmt.Print("HashTable: ")
	for i := 0; i < h.capacity; i++ {
		if h.state[i] == 1 {
			fmt.Printf("[%d:%s] ", i, h.table[i])
		}
	}
	fmt.Println()
}

func (h *HashTable) SaveText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()
	fmt.Fprintln(file, h.capacity)
	for i := 0; i < h.capacity; i++ {
		fmt.Fprintln(file, h.state[i])
		if h.state[i] == 1 {
			fmt.Fprintln(file, h.table[i])
		}
	}
	return nil
}

func (h *HashTable) LoadText(filename string) bool {
	file, err := os.Open(filename)
	if err != nil {
		return false
	}
	defer file.Close()
	var cap int
	if _, err := fmt.Fscan(file, &cap); err != nil {
		return false
	}
	if cap < 0 || cap > 1000000 {
		return false
	}
	h.Init(cap)
	for i := 0; i < cap; i++ {
		var state int
		if _, err := fmt.Fscan(file, &state); err != nil {
			return false
		}
		h.state[i] = state
		if state == 1 {
			var val string
			if _, err := fmt.Fscan(file, &val); err != nil {
				return false
			}
			h.table[i] = val
		}
	}
	return true
}

func (h *HashTable) SaveBin(filename string) error {
	return h.SaveText(filename)
}

func (h *HashTable) LoadBin(filename string) bool {
	return h.LoadText(filename)
}
