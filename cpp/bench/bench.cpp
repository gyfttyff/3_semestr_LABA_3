#include <benchmark/benchmark.h>
#include "structures/Array.h"
#include "structures/ForwardList.h"
#include "structures/Doublylist.h"
#include "structures/Stack.h"
#include "structures/Queue.h"
#include "structures/HashTable.h"
#include "structures/CompleteBinaryTree.h"

static void BM_ArrayPush(benchmark::State& state) {
    for (auto _ : state) {
        Array<int> a;
        for (int i = 0; i < 1000; i++) a.MPush(i);
    }
}
BENCHMARK(BM_ArrayPush);

static void BM_ArrayPushIdx(benchmark::State& state) {
    for (auto _ : state) {
        Array<int> a;
        for (int i = 0; i < 100; i++) a.MPush(i);
        for (int i = 0; i < 100; i++) a.MPushIdx(0, i);
    }
}
BENCHMARK(BM_ArrayPushIdx);

static void BM_ArrayDel(benchmark::State& state) {
    for (auto _ : state) {
        Array<int> a;
        for (int i = 0; i < 1000; i++) a.MPush(i);
        for (int i = 0; i < 1000; i++) a.MDelInd(0);
    }
}
BENCHMARK(BM_ArrayDel);

static void BM_ForwardListPush(benchmark::State& state) {
    for (auto _ : state) {
        ForwardList<int> f;
        for (int i = 0; i < 1000; i++) f.FPush(i);
    }
}
BENCHMARK(BM_ForwardListPush);

static void BM_ForwardListPushHead(benchmark::State& state) {
    for (auto _ : state) {
        ForwardList<int> f;
        for (int i = 0; i < 1000; i++) f.FPushHead(i);
    }
}
BENCHMARK(BM_ForwardListPushHead);

static void BM_DoublyListPush(benchmark::State& state) {
    for (auto _ : state) {
        DoublyList<int> l;
        for (int i = 0; i < 1000; i++) l.LPush(i);
    }
}
BENCHMARK(BM_DoublyListPush);

static void BM_StackPush(benchmark::State& state) {
    for (auto _ : state) {
        Stack<int> s;
        s.SInit(1000);
        for (int i = 0; i < 1000; i++) s.SPush(i);
    }
}
BENCHMARK(BM_StackPush);

static void BM_QueuePush(benchmark::State& state) {
    for (auto _ : state) {
        Queue<int> q;
        q.QInit(1000);
        for (int i = 0; i < 1000; i++) q.QPush(i);
    }
}
BENCHMARK(BM_QueuePush);
  

static void BM_HashTableInsert(benchmark::State& state) {
    for (auto _ : state) {
        HashTable h;
        h.HInit(1000);
        for (int i = 0; i < 1000; i++) h.add(std::to_string(i));
    }
}
BENCHMARK(BM_HashTableInsert);

static void BM_HashTableFind(benchmark::State& state) {
    for (auto _ : state) {
        HashTable h;
        h.HInit(1000);
        for (int i = 0; i < 1000; i++) h.add(std::to_string(i));
        for (int i = 0; i < 1000; i++) h.contains(std::to_string(i));
    }
}
BENCHMARK(BM_HashTableFind);

static void BM_TreeInsert(benchmark::State& state) {
    for (auto _ : state) {
        CompleteBinaryTree<int> t;
        for (int i = 0; i < 1000; i++) t.TInsert(i);
    }
}
BENCHMARK(BM_TreeInsert);

static void BM_TreeSearch(benchmark::State& state) {
    for (auto _ : state) {
        CompleteBinaryTree<int> t;
        for (int i = 0; i < 1000; i++) t.TInsert(i);
        for (int i = 0; i < 1000; i++) t.TSearch(i);
    }
}
BENCHMARK(BM_TreeSearch);

static void BM_ArraySerializeText(benchmark::State& state) {
    for (auto _ : state) {
        Array<int> a;
        for (int i = 0; i < 1000; i++) a.MPush(i);
        a.SaveText("/tmp/bench_arr.txt");
    }
}
BENCHMARK(BM_ArraySerializeText);

static void BM_ArraySerializeBin(benchmark::State& state) {
    for (auto _ : state) {
        Array<int> a;
        for (int i = 0; i < 1000; i++) a.MPush(i);
        a.SaveBin("/tmp/bench_arr.bin");
    }
}
BENCHMARK(BM_ArraySerializeBin);

static void BM_ArrayLoadBin(benchmark::State& state) {
    Array<int> a;
    for (int i = 0; i < 1000; i++) a.MPush(i);
    a.SaveBin("/tmp/bench_arr.bin");
    for (auto _ : state) {
        Array<int> b;
        b.LoadBin("/tmp/bench_arr.bin");
    }
}
BENCHMARK(BM_ArrayLoadBin);

BENCHMARK_MAIN();