package structures

import (
	"os"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

func TestArrayPushGetLen(t *testing.T) {
	a := NewArray[int]()
	a.Init(2)
	a.Push(10)
	a.Push(30)
	a.PushIdx(1, 20)
	assert.Equal(t, 3, a.Len())
	assert.Equal(t, 20, a.Get(1))
}

func TestArrayPushIdxErrors(t *testing.T) {
	a := NewArray[int]()
	a.Push(1)
	assert.Panics(t, func() { a.PushIdx(-1, 0) })
	assert.Panics(t, func() { a.PushIdx(5, 0) })
	assert.NotPanics(t, func() { a.PushIdx(0, 9) })
}

func TestArrayGetDelErrors(t *testing.T) {
	a := NewArray[int]()
	assert.Panics(t, func() { a.Get(0) })
	assert.Panics(t, func() { a.DelInd(0) })
}

func TestArrayDelAndClear(t *testing.T) {
	a := NewArray[int]()
	a.Push(1)
	a.Push(2)
	a.Push(3)
	a.DelInd(0)
	assert.Equal(t, 2, a.Get(0))
	a.Clear()
	assert.Equal(t, 0, a.Len())
	a.Push(5)
	assert.Equal(t, 1, a.Len())
}

func TestArraySerializeText(t *testing.T) {
	a := NewArray[int]()
	a.Push(1)
	a.Push(2)
	a.Push(3)
	require.NoError(t, a.SaveText("go_a.txt"))
	b := NewArray[int]()
	require.True(t, b.LoadText("go_a.txt"))
	assert.Equal(t, 3, b.Len())
	assert.Equal(t, 3, b.Get(2))
	os.Remove("go_a.txt")
}

func TestArraySerializeBin(t *testing.T) {
	a := NewArray[int]()
	a.Push(7)
	a.Push(8)
	require.NoError(t, a.SaveBin("go_a.bin"))
	b := NewArray[int]()
	require.True(t, b.LoadBin("go_a.bin"))
	assert.Equal(t, 2, b.Len())
	assert.Equal(t, 8, b.Get(1))
	os.Remove("go_a.bin")
}

func TestArrayLoadBadFile(t *testing.T) {
	a := NewArray[int]()
	assert.False(t, a.LoadText("nonexistent.txt"))
	assert.False(t, a.LoadBin("nonexistent.bin"))
}
