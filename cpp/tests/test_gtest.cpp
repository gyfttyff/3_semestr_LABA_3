#include <gtest/gtest.h>
#include <cstdio>
#include "structures/Array.h"
#include "structures/ForwardList.h"
#include "structures/Doublylist.h"
#include "structures/Stack.h"
#include "structures/Queue.h"
#include "structures/HashTable.h"
#include "structures/CompleteBinaryTree.h"

// ARRAY
TEST(Array, PushGetLen) {
    Array<int> a;
    a.MInit(2);
    a.MPush(10);
    a.MPush(30);
    a.MPushIdx(1, 20);
    EXPECT_EQ(a.MLen(), 3);
    EXPECT_EQ(a.MGet(1), 20);
}

TEST(Array, PushIdxErrors) {
    Array<int> a;
    a.MPush(1);
    EXPECT_THROW(a.MPushIdx(-1, 0), std::out_of_range);
    EXPECT_THROW(a.MPushIdx(5, 0), std::out_of_range);
    EXPECT_NO_THROW(a.MPushIdx(0, 9));
    EXPECT_NO_THROW(a.MPushIdx(a.MLen(), 8));
}

TEST(Array, GetDelErrors) {
    Array<int> a;
    EXPECT_THROW(a.MGet(0), std::out_of_range);
    EXPECT_THROW(a.MDelInd(0), std::out_of_range);
}

TEST(Array, DelAndClear) {
    Array<int> a;
    a.MPush(1); a.MPush(2); a.MPush(3);
    EXPECT_NO_THROW(a.MDelInd(0));
    EXPECT_EQ(a.MGet(0), 2);
    a.MClear();
    EXPECT_EQ(a.MLen(), 0);
    a.MPush(5);
    EXPECT_EQ(a.MLen(), 1);
}

TEST(Array, CopyAndAssign) {
    Array<int> a;
    a.MPush(1); a.MPush(2);
    Array<int> b(a);
    b.MPush(3);
    EXPECT_EQ(a.MLen(), 2);
    EXPECT_EQ(b.MLen(), 3);
    Array<int> c;
    c = a;
    c.MPush(4);
    EXPECT_EQ(a.MLen(), 2);
    EXPECT_EQ(c.MLen(), 3);
}

TEST(Array, SerializeText) {
    Array<int> a;
    a.MPush(1); a.MPush(2); a.MPush(3);
    ASSERT_NO_THROW(a.SaveText("gtest_a.txt"));
    Array<int> b;
    ASSERT_TRUE(b.LoadText("gtest_a.txt"));
    EXPECT_EQ(b.MLen(), 3);
    EXPECT_EQ(b.MGet(2), 3);
    std::remove("gtest_a.txt");
}

TEST(Array, SerializeBin) {
    Array<int> a;
    a.MPush(7); a.MPush(8);
    ASSERT_NO_THROW(a.SaveBin("gtest_a.bin"));
    Array<int> b;
    ASSERT_TRUE(b.LoadBin("gtest_a.bin"));
    EXPECT_EQ(b.MLen(), 2);
    EXPECT_EQ(b.MGet(1), 8);
    std::remove("gtest_a.bin");
}

TEST(Array, LoadBadFile) {
    Array<int> a;
    EXPECT_FALSE(a.LoadText("nonexistent_xyz.txt"));
    EXPECT_FALSE(a.LoadBin("nonexistent_xyz.bin"));
}

// FORWARD LIST 
TEST(ForwardList, PushFindDel) {
    ForwardList<int> f;
    f.FPushHead(2);
    f.FPushHead(1);
    f.FPush(3);
    EXPECT_EQ(f.FGetHead(), 1);
    EXPECT_EQ(f.FGetTail(), 3);
    EXPECT_NO_THROW(f.FDel(2));
    EXPECT_THROW(f.FGet(2), std::runtime_error);
}

TEST(ForwardList, PushBeforeAfter) {
    ForwardList<int> f;
    f.FPush(1); f.FPush(3);
    f.FPushBefore(3, 2);
    EXPECT_EQ(f.FGetIdx(1), 2);
    f.FPushAfter(1, 99);
    EXPECT_EQ(f.FGetIdx(1), 99);
}

TEST(ForwardList, DelEmpty) {
    ForwardList<int> f;
    EXPECT_NO_THROW(f.FDel(99));
    EXPECT_NO_THROW(f.FDelHead());
    EXPECT_NO_THROW(f.FDelTail());
}

TEST(ForwardList, DelHeadTailMiddle) {
    ForwardList<int> f;
    f.FPush(1); f.FPush(2); f.FPush(3);
    f.FDelHead();
    EXPECT_EQ(f.FGetHead(), 2);
    f.FDelTail();
    EXPECT_EQ(f.FGetTail(), 2);
    f.FDel(2);
    EXPECT_THROW(f.FGetHead(), std::runtime_error);
}

TEST(ForwardList, CopyAndAssign) {
    ForwardList<int> f;
    f.FPush(1); f.FPush(2);
    ForwardList<int> g(f);
    g.FPush(3);
    EXPECT_EQ(f.FGetTail(), 2);
    EXPECT_EQ(g.FGetTail(), 3);
}

TEST(ForwardList, SerializeText) {
    ForwardList<int> f;
    f.FPush(1); f.FPush(2);
    ASSERT_NO_THROW(f.SaveText("gtest_f.txt"));
    ForwardList<int> g;
    ASSERT_TRUE(g.LoadText("gtest_f.txt"));
    EXPECT_EQ(g.FGetTail(), 2);
    std::remove("gtest_f.txt");
}

TEST(ForwardList, SerializeBin) {
    ForwardList<int> f;
    f.FPush(7); f.FPush(8);
    ASSERT_NO_THROW(f.SaveBin("gtest_f.bin"));
    ForwardList<int> g;
    ASSERT_TRUE(g.LoadBin("gtest_f.bin"));
    EXPECT_EQ(g.FGetHead(), 7);
    std::remove("gtest_f.bin");
}

TEST(ForwardList, LoadBadFile) {
    ForwardList<int> f;
    EXPECT_FALSE(f.LoadText("nonexistent_xyz.txt"));
    EXPECT_FALSE(f.LoadBin("nonexistent_xyz.bin"));
}

// DOUBLY LIST 
TEST(DoublyList, PushBothEnds) {
    DoublyList<int> l;
    l.LPush(2);
    l.LPushHead(1);
    l.LPush(3);
    EXPECT_EQ(l.LGetHead(), 1);
    EXPECT_EQ(l.LGetTail(), 3);
}

TEST(DoublyList, PushBeforeAfter) {
    DoublyList<int> l;
    l.LPush(1); l.LPush(3);
    l.LPushBefore(3, 2);
    EXPECT_EQ(l.LGetIdx(1), 2);
    l.LPushAfter(1, 99);
    EXPECT_EQ(l.LGetIdx(1), 99);
}

TEST(DoublyList, DelOperations) {
    DoublyList<int> l;
    l.LPush(1); l.LPush(2); l.LPush(3);
    l.LDel(2);
    EXPECT_THROW(l.LGet(2), std::runtime_error);
    l.LDelHead();
    EXPECT_EQ(l.LGetHead(), 3);
    l.LDelTail();
    EXPECT_THROW(l.LGetHead(), std::runtime_error);
}

TEST(DoublyList, DelEmpty) {
    DoublyList<int> l;
    EXPECT_NO_THROW(l.LDel(1));
    EXPECT_NO_THROW(l.LDelHead());
    EXPECT_NO_THROW(l.LDelTail());
}

TEST(DoublyList, CopyAndAssign) {
    DoublyList<int> l;
    l.LPush(1); l.LPush(2);
    DoublyList<int> g(l);
    g.LPush(3);
    EXPECT_EQ(l.LGetTail(), 2);
    EXPECT_EQ(g.LGetTail(), 3);
}

TEST(DoublyList, SerializeText) {
    DoublyList<int> l;
    l.LPush(10); l.LPush(20);
    ASSERT_NO_THROW(l.SaveText("gtest_l.txt"));
    DoublyList<int> l2;
    ASSERT_TRUE(l2.LoadText("gtest_l.txt"));
    EXPECT_EQ(l2.LGetTail(), 20);
    std::remove("gtest_l.txt");
}

TEST(DoublyList, SerializeBin) {
    DoublyList<int> l;
    l.LPush(5); l.LPush(6);
    ASSERT_NO_THROW(l.SaveBin("gtest_l.bin"));
    DoublyList<int> l2;
    ASSERT_TRUE(l2.LoadBin("gtest_l.bin"));
    EXPECT_EQ(l2.LGetTail(), 6);
    std::remove("gtest_l.bin");
}

TEST(DoublyList, LoadBadFile) {
    DoublyList<int> l;
    EXPECT_FALSE(l.LoadText("nonexistent_xyz.txt"));
    EXPECT_FALSE(l.LoadBin("nonexistent_xyz.bin"));
}

// STACK 
TEST(Stack, PushPopTop) {
    Stack<int> s;
    s.SInit(2);
    EXPECT_THROW(s.SPeek(), std::runtime_error);
    EXPECT_THROW(s.SPop(), std::runtime_error);
    s.SPush(1);
    s.SPush(2);
    EXPECT_EQ(s.SPeek(), 2);
    EXPECT_EQ(s.SPop(), 2);
    EXPECT_EQ(s.SPeek(), 1);
}

TEST(Stack, PopToEmpty) {
    Stack<int> s;
    s.SInit(1);
    s.SPush(1);
    EXPECT_NO_THROW(s.SPop());
    EXPECT_THROW(s.SPop(), std::runtime_error);
}

TEST(Stack, Resize) {
    Stack<int> s;
    s.SInit(1);
    for (int i = 0; i < 10; ++i) s.SPush(i);
    EXPECT_EQ(s.SPeek(), 9);
}

TEST(Stack, CopyAndAssign) {
    Stack<int> s;
    s.SInit(2);
    s.SPush(1); s.SPush(2);
    Stack<int> t(s);
    t.SPush(3);
    EXPECT_EQ(s.SPeek(), 2);
    EXPECT_EQ(t.SPeek(), 3);
}

TEST(Stack, SerializeText) {
    Stack<int> s;
    s.SInit(2);
    s.SPush(1); s.SPush(2); s.SPush(3);
    ASSERT_NO_THROW(s.SaveText("gtest_s.txt"));
    Stack<int> s2;
    ASSERT_TRUE(s2.LoadText("gtest_s.txt"));
    EXPECT_EQ(s2.SPeek(), 3);
    std::remove("gtest_s.txt");
}

TEST(Stack, SerializeBin) {
    Stack<int> s;
    s.SInit(2);
    s.SPush(1); s.SPush(2);
    ASSERT_NO_THROW(s.SaveBin("gtest_s.bin"));
    Stack<int> s2;
    ASSERT_TRUE(s2.LoadBin("gtest_s.bin"));
    EXPECT_EQ(s2.SPeek(), 2);
    std::remove("gtest_s.bin");
}

TEST(Stack, LoadBadFile) {
    Stack<int> s;
    EXPECT_FALSE(s.LoadText("nonexistent_xyz.txt"));
    EXPECT_FALSE(s.LoadBin("nonexistent_xyz.bin"));
}

// QUEUE 
TEST(Queue, PushPopFront) {
    Queue<int> q;
    q.QInit(2);
    EXPECT_THROW(q.QPeek(), std::runtime_error);
    EXPECT_THROW(q.QPop(), std::runtime_error);
    q.QPush(1);
    q.QPush(2);
    EXPECT_EQ(q.QPeek(), 1);
    EXPECT_EQ(q.QPop(), 1);
    EXPECT_EQ(q.QPeek(), 2);
}

TEST(Queue, PopToEmpty) {
    Queue<int> q;
    q.QInit(1);
    q.QPush(1);
    EXPECT_NO_THROW(q.QPop());
    EXPECT_THROW(q.QPop(), std::runtime_error);
}

TEST(Queue, Resize) {
    Queue<int> q;
    q.QInit(1);
    for (int i = 0; i < 10; ++i) q.QPush(i);
    EXPECT_EQ(q.QPeek(), 0);
}

TEST(Queue, WrapAround) {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1); q.QPush(2);
    q.QPop();
    q.QPush(3);
    EXPECT_EQ(q.QPop(), 2);
    EXPECT_EQ(q.QPop(), 3);
}

TEST(Queue, CopyAndAssign) {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1);
    Queue<int> t(q);
    t.QPush(2);
    EXPECT_EQ(q.QPeek(), 1);
    EXPECT_EQ(t.QPeek(), 1);
}

TEST(Queue, SerializeText) {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1); q.QPush(2); q.QPush(3);
    ASSERT_NO_THROW(q.SaveText("gtest_q.txt"));
    Queue<int> q2;
    ASSERT_TRUE(q2.LoadText("gtest_q.txt"));
    EXPECT_EQ(q2.QPeek(), 1);
    std::remove("gtest_q.txt");
}

TEST(Queue, SerializeBin) {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1); q.QPush(2);
    ASSERT_NO_THROW(q.SaveBin("gtest_q.bin"));
    Queue<int> q2;
    ASSERT_TRUE(q2.LoadBin("gtest_q.bin"));
    EXPECT_EQ(q2.QPeek(), 1);
    std::remove("gtest_q.bin");
}

TEST(Queue, LoadBadFile) {
    Queue<int> q;
    EXPECT_FALSE(q.LoadText("nonexistent_xyz.txt"));
    EXPECT_FALSE(q.LoadBin("nonexistent_xyz.bin"));
}

// HASH TABLE 
TEST(HashTable, InsertFindUpdate) {
    HashTable h;
    h.HInit(7);
    h.add("one");
    h.add("two");
    EXPECT_TRUE(h.contains("one"));
    EXPECT_FALSE(h.contains("nope"));
}

TEST(HashTable, Delete) {
    HashTable h;
    h.HInit(7);
    h.add("a");
    h.add("k");
    EXPECT_TRUE(h.contains("a"));
    h.remove("a");
    EXPECT_FALSE(h.contains("a"));
    EXPECT_NO_THROW(h.remove("nope"));
}

TEST(HashTable, Collisions) {
    HashTable h;
    h.HInit(3);
    h.add("a");
    h.add("b");
    h.add("c");
    EXPECT_TRUE(h.contains("a"));
    EXPECT_TRUE(h.contains("b"));
    EXPECT_TRUE(h.contains("c"));
}

TEST(HashTable, CopyAndAssign) {
    HashTable h;
    h.HInit(7);
    h.add("a");
    HashTable g(h);
    g.add("b");
    EXPECT_TRUE(h.contains("a"));
    EXPECT_TRUE(g.contains("b"));
}

TEST(HashTable, SerializeText) {
    HashTable h;
    h.HInit(7);
    h.add("x"); h.add("y");
    ASSERT_NO_THROW(h.SaveText("gtest_h.txt"));
    HashTable h2;
    ASSERT_TRUE(h2.LoadText("gtest_h.txt"));
    EXPECT_TRUE(h2.contains("x"));
    EXPECT_TRUE(h2.contains("y"));
    std::remove("gtest_h.txt");
}

TEST(HashTable, SerializeBin) {
    HashTable h;
    h.HInit(7);
    h.add("x"); h.add("yy");
    ASSERT_NO_THROW(h.SaveBin("gtest_h.bin"));
    HashTable h2;
    ASSERT_TRUE(h2.LoadBin("gtest_h.bin"));
    EXPECT_TRUE(h2.contains("yy"));
    std::remove("gtest_h.bin");
}

TEST(HashTable, LoadBadFile) {
    HashTable h;
    EXPECT_FALSE(h.LoadText("nonexistent_xyz.txt"));
    EXPECT_FALSE(h.LoadBin("nonexistent_xyz.bin"));
}

// TREE 
TEST(Tree, InsertAndFind) {
    CompleteBinaryTree<int> t;
    EXPECT_FALSE(t.TSearch(1));
    for (int i = 1; i <= 7; i++) t.TInsert(i);
    EXPECT_TRUE(t.TIsComplete());
    for (int i = 1; i <= 7; i++) EXPECT_TRUE(t.TSearch(i));
    EXPECT_FALSE(t.TSearch(99));
}

TEST(Tree, NotComplete) {
    CompleteBinaryTree<int> t;
    t.TInsert(1);
    t.TInsert(2);
    t.TInsert(3);
    t.TInsert(4);
    EXPECT_TRUE(t.TIsComplete());
}

TEST(Tree, ClearAndReuse) {
    CompleteBinaryTree<int> t;
    t.TInsert(1); t.TInsert(2);
    t.TClear();
    EXPECT_FALSE(t.TSearch(1));
    EXPECT_NO_THROW(t.TInsert(42));
    EXPECT_TRUE(t.TSearch(42));
}

TEST(Tree, CopyAndAssign) {
    CompleteBinaryTree<int> t;
    t.TInsert(1); t.TInsert(2);
    CompleteBinaryTree<int> g(t);
    g.TInsert(3);
    EXPECT_TRUE(g.TSearch(3));
    EXPECT_TRUE(t.TSearch(1));
}

TEST(Tree, SerializeText) {
    CompleteBinaryTree<int> t;
    for (int i = 1; i <= 7; i++) t.TInsert(i);
    ASSERT_NO_THROW(t.SaveText("gtest_t.txt"));
    CompleteBinaryTree<int> t2;
    ASSERT_TRUE(t2.LoadText("gtest_t.txt"));
    EXPECT_TRUE(t2.TIsComplete());
    EXPECT_TRUE(t2.TSearch(7));
    std::remove("gtest_t.txt");
}

TEST(Tree, SerializeBin) {
    CompleteBinaryTree<int> t;
    for (int i = 1; i <= 7; i++) t.TInsert(i);
    ASSERT_NO_THROW(t.SaveBin("gtest_t.bin"));
    CompleteBinaryTree<int> t2;
    ASSERT_TRUE(t2.LoadBin("gtest_t.bin"));
    EXPECT_TRUE(t2.TIsComplete());
    EXPECT_TRUE(t2.TSearch(7));
    std::remove("gtest_t.bin");
}

TEST(Tree, LoadBadFile) {
    CompleteBinaryTree<int> t;
    EXPECT_FALSE(t.LoadText("nonexistent_xyz.txt"));
    EXPECT_FALSE(t.LoadBin("nonexistent_xyz.bin"));
}