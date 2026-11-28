package main

import (
	"fmt"
	"lab3/structures"
)

func main() {
	// Array
	arr := structures.NewArray[int]()
	arr.Init(4)
	arr.Push(10)
	arr.Push(20)
	arr.Push(30)
	arr.PushIdx(1, 15)
	arr.Print()

	// ForwardList
	fl := structures.NewForwardList[int]()
	fl.PushHead(2)
	fl.PushHead(1)
	fl.Push(3)
	fl.Print()

	// DoublyList
	dl := structures.NewDoublyList[int]()
	dl.Push(1)
	dl.Push(2)
	dl.PushHead(0)
	dl.Print()

	// Stack
	st := structures.NewStack[int]()
	st.Init(4)
	st.Push(10)
	st.Push(20)
	st.Print()

	// Queue
	q := structures.NewQueue[int]()
	q.Init(4)
	q.Push(10)
	q.Push(20)
	q.Print()

	// HashTable
	ht := structures.NewHashTable()
	ht.Init(11)
	ht.Add("name")
	ht.Add("value")
	ht.Print()

	// CompleteBinaryTree
	tr := structures.NewCompleteBinaryTree[int]()
	for i := 1; i <= 7; i++ {
		tr.Insert(i)
	}
	tr.Print()

	// СЕРИАЛИЗАЦИЯ
	fmt.Println("\nСЕРИАЛИЗАЦИЯ")

	_ = arr.SaveText("arr.txt")
	_ = arr.SaveBin("arr.bin")
	arrTxt := structures.NewArray[int]()
	arrBin := structures.NewArray[int]()
	arrTxt.LoadText("arr.txt")
	arrBin.LoadBin("arr.bin")
	fmt.Print("Array TXT: ")
	arrTxt.Print()
	fmt.Print("Array BIN: ")
	arrBin.Print()

	_ = fl.SaveText("fl.txt")
	_ = fl.SaveBin("fl.bin")
	flTxt := structures.NewForwardList[int]()
	flBin := structures.NewForwardList[int]()
	flTxt.LoadText("fl.txt")
	flBin.LoadBin("fl.bin")
	fmt.Print("ForwardList TXT: ")
	flTxt.Print()
	fmt.Print("ForwardList BIN: ")
	flBin.Print()

	_ = dl.SaveText("dl.txt")
	_ = dl.SaveBin("dl.bin")
	dlTxt := structures.NewDoublyList[int]()
	dlBin := structures.NewDoublyList[int]()
	dlTxt.LoadText("dl.txt")
	dlBin.LoadBin("dl.bin")
	fmt.Print("DoublyList TXT: ")
	dlTxt.Print()
	fmt.Print("DoublyList BIN: ")
	dlBin.Print()

	_ = st.SaveText("st.txt")
	_ = st.SaveBin("st.bin")
	stTxt := structures.NewStack[int]()
	stBin := structures.NewStack[int]()
	stTxt.LoadText("st.txt")
	stBin.LoadBin("st.bin")
	fmt.Print("Stack TXT: ")
	stTxt.Print()
	fmt.Print("Stack BIN: ")
	stBin.Print()

	_ = q.SaveText("q.txt")
	_ = q.SaveBin("q.bin")
	qTxt := structures.NewQueue[int]()
	qBin := structures.NewQueue[int]()
	qTxt.LoadText("q.txt")
	qBin.LoadBin("q.bin")
	fmt.Print("Queue TXT: ")
	qTxt.Print()
	fmt.Print("Queue BIN: ")
	qBin.Print()

	_ = ht.SaveText("ht.txt")
	_ = ht.SaveBin("ht.bin")
	htTxt := structures.NewHashTable()
	htBin := structures.NewHashTable()
	htTxt.LoadText("ht.txt")
	htBin.LoadBin("ht.bin")
	fmt.Print("HashTable TXT: ")
	htTxt.Print()
	fmt.Print("HashTable BIN: ")
	htBin.Print()

	_ = tr.SaveText("tr.txt")
	_ = tr.SaveBin("tr.bin")
	trTxt := structures.NewCompleteBinaryTree[int]()
	trBin := structures.NewCompleteBinaryTree[int]()
	trTxt.LoadText("tr.txt")
	trBin.LoadBin("tr.bin")
	fmt.Print("Tree TXT: ")
	trTxt.Print()
	fmt.Print("Tree BIN: ")
	trBin.Print()
}
