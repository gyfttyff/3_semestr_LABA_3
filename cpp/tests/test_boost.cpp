
#define BOOST_TEST_MODULE Lab3Tests
#include <boost/test/included/unit_test.hpp>
#include <cstdio>
#include "structures/Array.h"
#include "structures/ForwardList.h"
#include "structures/Doublylist.h"
#include "structures/Stack.h"
#include "structures/Queue.h"
#include "structures/HashTable.h"
#include "structures/CompleteBinaryTree.h"

BOOST_AUTO_TEST_CASE(ArrayPushGetLen) {
    Array<int> a;
    a.MInit(2);
    a.MPush(10);
    a.MPush(30);
    a.MPushIdx(1, 20);
    BOOST_CHECK_EQUAL(a.MLen(), 3);
    BOOST_CHECK_EQUAL(a.MGet(1), 20);
}

BOOST_AUTO_TEST_CASE(ArrayPushIdxErrors) {
    Array<int> a;
    a.MPush(1);
    BOOST_CHECK_THROW(a.MPushIdx(-1, 0), std::out_of_range);
    BOOST_CHECK_THROW(a.MPushIdx(5, 0), std::out_of_range);
    BOOST_CHECK_NO_THROW(a.MPushIdx(0, 9));
    BOOST_CHECK_NO_THROW(a.MPushIdx(a.MLen(), 8));
}

BOOST_AUTO_TEST_CASE(ArrayGetDelErrors) {
    Array<int> a;
    BOOST_CHECK_THROW(a.MGet(0), std::out_of_range);
    BOOST_CHECK_THROW(a.MDelInd(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ArrayDelAndClear) {
    Array<int> a;
    a.MPush(1); a.MPush(2); a.MPush(3);
    BOOST_CHECK_NO_THROW(a.MDelInd(0));
    BOOST_CHECK_EQUAL(a.MGet(0), 2);
    a.MClear();
    BOOST_CHECK_EQUAL(a.MLen(), 0);
    a.MPush(5);
    BOOST_CHECK_EQUAL(a.MLen(), 1);
}

BOOST_AUTO_TEST_CASE(ArrayCopyAndAssign) {
    Array<int> a;
    a.MPush(1); a.MPush(2);
    Array<int> b(a);
    b.MPush(3);
    BOOST_CHECK_EQUAL(a.MLen(), 2);
    BOOST_CHECK_EQUAL(b.MLen(), 3);
    Array<int> c;
    c = a;
    c.MPush(4);
    BOOST_CHECK_EQUAL(a.MLen(), 2);
    BOOST_CHECK_EQUAL(c.MLen(), 3);
}

BOOST_AUTO_TEST_CASE(ArraySerializeText) {
    Array<int> a;
    a.MPush(1); a.MPush(2); a.MPush(3);
    BOOST_CHECK_NO_THROW(a.SaveText("boost_a.txt"));
    Array<int> b;
    BOOST_CHECK(b.LoadText("boost_a.txt"));
    BOOST_CHECK_EQUAL(b.MLen(), 3);
    BOOST_CHECK_EQUAL(b.MGet(2), 3);
    std::remove("boost_a.txt");
}

BOOST_AUTO_TEST_CASE(ArraySerializeBin) {
    Array<int> a;
    a.MPush(7); a.MPush(8);
    BOOST_CHECK_NO_THROW(a.SaveBin("boost_a.bin"));
    Array<int> b;
    BOOST_CHECK(b.LoadBin("boost_a.bin"));
    BOOST_CHECK_EQUAL(b.MLen(), 2);
    BOOST_CHECK_EQUAL(b.MGet(1), 8);
    std::remove("boost_a.bin");
}

BOOST_AUTO_TEST_CASE(ArrayLoadBadFile) {
    Array<int> a;
    BOOST_CHECK(!a.LoadText("nonexistent_xyz.txt"));
    BOOST_CHECK(!a.LoadBin("nonexistent_xyz.bin"));
}

BOOST_AUTO_TEST_CASE(ForwardListPushFindDel) {
    ForwardList<int> f;
    f.FPushHead(2);
    f.FPushHead(1);
    f.FPush(3);
    BOOST_CHECK_EQUAL(f.FGetHead(), 1);
    BOOST_CHECK_EQUAL(f.FGetTail(), 3);
    BOOST_CHECK_NO_THROW(f.FDel(2));
    BOOST_CHECK_THROW(f.FGet(2), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(ForwardListPushBeforeAfter) {
    ForwardList<int> f;
    f.FPush(1); f.FPush(3);
    f.FPushBefore(3, 2);
    BOOST_CHECK_EQUAL(f.FGetIdx(1), 2);
    f.FPushAfter(1, 99);
    BOOST_CHECK_EQUAL(f.FGetIdx(1), 99);
}

BOOST_AUTO_TEST_CASE(ForwardListDelEmpty) {
    ForwardList<int> f;
    BOOST_CHECK_NO_THROW(f.FDel(99));
    BOOST_CHECK_NO_THROW(f.FDelHead());
    BOOST_CHECK_NO_THROW(f.FDelTail());
}

BOOST_AUTO_TEST_CASE(ForwardListDelHeadTailMiddle) {
    ForwardList<int> f;
    f.FPush(1); f.FPush(2); f.FPush(3);
    f.FDelHead();
    BOOST_CHECK_EQUAL(f.FGetHead(), 2);
    f.FDelTail();
    BOOST_CHECK_EQUAL(f.FGetTail(), 2);
    f.FDel(2);
    BOOST_CHECK_THROW(f.FGetHead(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(ForwardListCopyAndAssign) {
    ForwardList<int> f;
    f.FPush(1); f.FPush(2);
    ForwardList<int> g(f);
    g.FPush(3);
    BOOST_CHECK_EQUAL(f.FGetTail(), 2);
    BOOST_CHECK_EQUAL(g.FGetTail(), 3);
}

BOOST_AUTO_TEST_CASE(ForwardListSerializeText) {
    ForwardList<int> f;
    f.FPush(1); f.FPush(2);
    BOOST_CHECK_NO_THROW(f.SaveText("boost_f.txt"));
    ForwardList<int> g;
    BOOST_CHECK(g.LoadText("boost_f.txt"));
    BOOST_CHECK_EQUAL(g.FGetTail(), 2);
    std::remove("boost_f.txt");
}

BOOST_AUTO_TEST_CASE(ForwardListSerializeBin) {
    ForwardList<int> f;
    f.FPush(7); f.FPush(8);
    BOOST_CHECK_NO_THROW(f.SaveBin("boost_f.bin"));
    ForwardList<int> g;
    BOOST_CHECK(g.LoadBin("boost_f.bin"));
    BOOST_CHECK_EQUAL(g.FGetHead(), 7);
    std::remove("boost_f.bin");
}

BOOST_AUTO_TEST_CASE(ForwardListLoadBadFile) {
    ForwardList<int> f;
    BOOST_CHECK(!f.LoadText("nonexistent_xyz.txt"));
    BOOST_CHECK(!f.LoadBin("nonexistent_xyz.bin"));
}

BOOST_AUTO_TEST_CASE(DoublyListPushBothEnds) {
    DoublyList<int> l;
    l.LPush(2);
    l.LPushHead(1);
    l.LPush(3);
    BOOST_CHECK_EQUAL(l.LGetHead(), 1);
    BOOST_CHECK_EQUAL(l.LGetTail(), 3);
}

BOOST_AUTO_TEST_CASE(DoublyListPushBeforeAfter) {
    DoublyList<int> l;
    l.LPush(1); l.LPush(3);
    l.LPushBefore(3, 2);
    BOOST_CHECK_EQUAL(l.LGetIdx(1), 2);
    l.LPushAfter(1, 99);
    BOOST_CHECK_EQUAL(l.LGetIdx(1), 99);
}

BOOST_AUTO_TEST_CASE(DoublyListDelOperations) {
    DoublyList<int> l;
    l.LPush(1); l.LPush(2); l.LPush(3);
    l.LDel(2);
    BOOST_CHECK_THROW(l.LGet(2), std::runtime_error);
    l.LDelHead();
    BOOST_CHECK_EQUAL(l.LGetHead(), 3);
    l.LDelTail();
    BOOST_CHECK_THROW(l.LGetHead(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(DoublyListDelEmpty) {
    DoublyList<int> l;
    BOOST_CHECK_NO_THROW(l.LDel(1));
    BOOST_CHECK_NO_THROW(l.LDelHead());
    BOOST_CHECK_NO_THROW(l.LDelTail());
}

BOOST_AUTO_TEST_CASE(DoublyListCopyAndAssign) {
    DoublyList<int> l;
    l.LPush(1); l.LPush(2);
    DoublyList<int> g(l);
    g.LPush(3);
    BOOST_CHECK_EQUAL(l.LGetTail(), 2);
    BOOST_CHECK_EQUAL(g.LGetTail(), 3);
}

BOOST_AUTO_TEST_CASE(DoublyListSerializeText) {
    DoublyList<int> l;
    l.LPush(10); l.LPush(20);
    BOOST_CHECK_NO_THROW(l.SaveText("boost_l.txt"));
    DoublyList<int> l2;
    BOOST_CHECK(l2.LoadText("boost_l.txt"));
    BOOST_CHECK_EQUAL(l2.LGetTail(), 20);
    std::remove("boost_l.txt");
}

BOOST_AUTO_TEST_CASE(DoublyListSerializeBin) {
    DoublyList<int> l;
    l.LPush(5); l.LPush(6);
    BOOST_CHECK_NO_THROW(l.SaveBin("boost_l.bin"));
    DoublyList<int> l2;
    BOOST_CHECK(l2.LoadBin("boost_l.bin"));
    BOOST_CHECK_EQUAL(l2.LGetTail(), 6);
    std::remove("boost_l.bin");
}

BOOST_AUTO_TEST_CASE(DoublyListLoadBadFile) {
    DoublyList<int> l;
    BOOST_CHECK(!l.LoadText("nonexistent_xyz.txt"));
    BOOST_CHECK(!l.LoadBin("nonexistent_xyz.bin"));
}

BOOST_AUTO_TEST_CASE(StackPushPopTop) {
    Stack<int> s;
    s.SInit(2);
    BOOST_CHECK_THROW(s.SPeek(), std::runtime_error);
    BOOST_CHECK_THROW(s.SPop(), std::runtime_error);
    s.SPush(1);
    s.SPush(2);
    BOOST_CHECK_EQUAL(s.SPeek(), 2);
    BOOST_CHECK_EQUAL(s.SPop(), 2);
    BOOST_CHECK_EQUAL(s.SPeek(), 1);
}

BOOST_AUTO_TEST_CASE(StackPopToEmpty) {
    Stack<int> s;
    s.SInit(1);
    s.SPush(1);
    BOOST_CHECK_NO_THROW(s.SPop());
    BOOST_CHECK_THROW(s.SPop(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(StackResize) {
    Stack<int> s;
    s.SInit(1);
    for (int i = 0; i < 10; ++i) s.SPush(i);
    BOOST_CHECK_EQUAL(s.SPeek(), 9);
}

BOOST_AUTO_TEST_CASE(StackCopyAndAssign) {
    Stack<int> s;
    s.SInit(2);
    s.SPush(1); s.SPush(2);
    Stack<int> t(s);
    t.SPush(3);
    BOOST_CHECK_EQUAL(s.SPeek(), 2);
    BOOST_CHECK_EQUAL(t.SPeek(), 3);
}

BOOST_AUTO_TEST_CASE(StackSerializeText) {
    Stack<int> s;
    s.SInit(2);
    s.SPush(1); s.SPush(2); s.SPush(3);
    BOOST_CHECK_NO_THROW(s.SaveText("boost_s.txt"));
    Stack<int> s2;
    BOOST_CHECK(s2.LoadText("boost_s.txt"));
    BOOST_CHECK_EQUAL(s2.SPeek(), 3);
    std::remove("boost_s.txt");
}

BOOST_AUTO_TEST_CASE(StackSerializeBin) {
    Stack<int> s;
    s.SInit(2);
    s.SPush(1); s.SPush(2);
    BOOST_CHECK_NO_THROW(s.SaveBin("boost_s.bin"));
    Stack<int> s2;
    BOOST_CHECK(s2.LoadBin("boost_s.bin"));
    BOOST_CHECK_EQUAL(s2.SPeek(), 2);
    std::remove("boost_s.bin");
}

BOOST_AUTO_TEST_CASE(StackLoadBadFile) {
    Stack<int> s;
    BOOST_CHECK(!s.LoadText("nonexistent_xyz.txt"));
    BOOST_CHECK(!s.LoadBin("nonexistent_xyz.bin"));
}

BOOST_AUTO_TEST_CASE(QueuePushPopFront) {
    Queue<int> q;
    q.QInit(2);
    BOOST_CHECK_THROW(q.QPeek(), std::runtime_error);
    BOOST_CHECK_THROW(q.QPop(), std::runtime_error);
    q.QPush(1);
    q.QPush(2);
    BOOST_CHECK_EQUAL(q.QPeek(), 1);
    BOOST_CHECK_EQUAL(q.QPop(), 1);
    BOOST_CHECK_EQUAL(q.QPeek(), 2);
}

BOOST_AUTO_TEST_CASE(QueuePopToEmpty) {
    Queue<int> q;
    q.QInit(1);
    q.QPush(1);
    BOOST_CHECK_NO_THROW(q.QPop());
    BOOST_CHECK_THROW(q.QPop(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(QueueResize) {
    Queue<int> q;
    q.QInit(1);
    for (int i = 0; i < 10; ++i) q.QPush(i);
    BOOST_CHECK_EQUAL(q.QPeek(), 0);
}

BOOST_AUTO_TEST_CASE(QueueWrapAround) {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1); q.QPush(2);
    q.QPop();
    q.QPush(3);
    BOOST_CHECK_EQUAL(q.QPop(), 2);
    BOOST_CHECK_EQUAL(q.QPop(), 3);
}

BOOST_AUTO_TEST_CASE(QueueCopyAndAssign) {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1);
    Queue<int> t(q);
    t.QPush(2);
    BOOST_CHECK_EQUAL(q.QPeek(), 1);
    BOOST_CHECK_EQUAL(t.QPeek(), 1);
}

BOOST_AUTO_TEST_CASE(QueueSerializeText) {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1); q.QPush(2); q.QPush(3);
    BOOST_CHECK_NO_THROW(q.SaveText("boost_q.txt"));
    Queue<int> q2;
    BOOST_CHECK(q2.LoadText("boost_q.txt"));
    BOOST_CHECK_EQUAL(q2.QPeek(), 1);
    std::remove("boost_q.txt");
}

BOOST_AUTO_TEST_CASE(QueueSerializeBin) {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1); q.QPush(2);
    BOOST_CHECK_NO_THROW(q.SaveBin("boost_q.bin"));
    Queue<int> q2;
    BOOST_CHECK(q2.LoadBin("boost_q.bin"));
    BOOST_CHECK_EQUAL(q2.QPeek(), 1);
    std::remove("boost_q.bin");
}

BOOST_AUTO_TEST_CASE(QueueLoadBadFile) {
    Queue<int> q;
    BOOST_CHECK(!q.LoadText("nonexistent_xyz.txt"));
    BOOST_CHECK(!q.LoadBin("nonexistent_xyz.bin"));
}

BOOST_AUTO_TEST_CASE(HashTableInsertFindUpdate) {
    HashTable h;
    h.HInit(7);
    h.add("one");
    h.add("two");
    BOOST_CHECK(h.contains("one"));
    BOOST_CHECK(!h.contains("nope"));
}

BOOST_AUTO_TEST_CASE(HashTableDelete) {
    HashTable h;
    h.HInit(7);
    h.add("a");
    h.add("k");
    BOOST_CHECK(h.contains("a"));
    h.remove("a");
    BOOST_CHECK(!h.contains("a"));
    BOOST_CHECK_NO_THROW(h.remove("nope"));
}

BOOST_AUTO_TEST_CASE(HashTableCollisions) {
    HashTable h;
    h.HInit(3);
    h.add("a");
    h.add("b");
    h.add("c");
    BOOST_CHECK(h.contains("a"));
    BOOST_CHECK(h.contains("b"));
    BOOST_CHECK(h.contains("c"));
}

BOOST_AUTO_TEST_CASE(HashTableCopyAndAssign) {
    HashTable h;
    h.HInit(7);
    h.add("a");
    HashTable g(h);
    g.add("b");
    BOOST_CHECK(h.contains("a"));
    BOOST_CHECK(g.contains("b"));
}

BOOST_AUTO_TEST_CASE(HashTableSerializeText) {
    HashTable h;
    h.HInit(7);
    h.add("x"); h.add("y");
    BOOST_CHECK_NO_THROW(h.SaveText("boost_h.txt"));
    HashTable h2;
    BOOST_CHECK(h2.LoadText("boost_h.txt"));
    BOOST_CHECK(h2.contains("x"));
    BOOST_CHECK(h2.contains("y"));
    std::remove("boost_h.txt");
}

BOOST_AUTO_TEST_CASE(HashTableSerializeBin) {
    HashTable h;
    h.HInit(7);
    h.add("x"); h.add("yy");
    BOOST_CHECK_NO_THROW(h.SaveBin("boost_h.bin"));
    HashTable h2;
    BOOST_CHECK(h2.LoadBin("boost_h.bin"));
    BOOST_CHECK(h2.contains("yy"));
    std::remove("boost_h.bin");
}

BOOST_AUTO_TEST_CASE(HashTableLoadBadFile) {
    HashTable h;
    BOOST_CHECK(!h.LoadText("nonexistent_xyz.txt"));
    BOOST_CHECK(!h.LoadBin("nonexistent_xyz.bin"));
}

BOOST_AUTO_TEST_CASE(TreeInsertAndFind) {
    CompleteBinaryTree<int> t;
    BOOST_CHECK(!t.TSearch(1));
    for (int i = 1; i <= 7; i++) t.TInsert(i);
    BOOST_CHECK(t.TIsComplete());
    for (int i = 1; i <= 7; i++) BOOST_CHECK(t.TSearch(i));
    BOOST_CHECK(!t.TSearch(99));
}

BOOST_AUTO_TEST_CASE(TreeNotComplete) {
    CompleteBinaryTree<int> t;
    t.TInsert(1);
    t.TInsert(2);
    t.TInsert(3);
    t.TInsert(4);
    BOOST_CHECK(t.TIsComplete());
}

BOOST_AUTO_TEST_CASE(TreeClearAndReuse) {
    CompleteBinaryTree<int> t;
    t.TInsert(1); t.TInsert(2);
    t.TClear();
    BOOST_CHECK(!t.TSearch(1));
    BOOST_CHECK_NO_THROW(t.TInsert(42));
    BOOST_CHECK(t.TSearch(42));
}

BOOST_AUTO_TEST_CASE(TreeCopyAndAssign) {
    CompleteBinaryTree<int> t;
    t.TInsert(1); t.TInsert(2);
    CompleteBinaryTree<int> g(t);
    g.TInsert(3);
    BOOST_CHECK(g.TSearch(3));
    BOOST_CHECK(t.TSearch(1));
}

BOOST_AUTO_TEST_CASE(TreeSerializeText) {
    CompleteBinaryTree<int> t;
    for (int i = 1; i <= 7; i++) t.TInsert(i);
    BOOST_CHECK_NO_THROW(t.SaveText("boost_t.txt"));
    CompleteBinaryTree<int> t2;
    BOOST_CHECK(t2.LoadText("boost_t.txt"));
    BOOST_CHECK(t2.TIsComplete());
    BOOST_CHECK(t2.TSearch(7));
    std::remove("boost_t.txt");
}

BOOST_AUTO_TEST_CASE(TreeSerializeBin) {
    CompleteBinaryTree<int> t;
    for (int i = 1; i <= 7; i++) t.TInsert(i);
    BOOST_CHECK_NO_THROW(t.SaveBin("boost_t.bin"));
    CompleteBinaryTree<int> t2;
    BOOST_CHECK(t2.LoadBin("boost_t.bin"));
    BOOST_CHECK(t2.TIsComplete());
    BOOST_CHECK(t2.TSearch(7));
    std::remove("boost_t.bin");
}

BOOST_AUTO_TEST_CASE(TreeLoadBadFile) {
    CompleteBinaryTree<int> t;
    BOOST_CHECK(!t.LoadText("nonexistent_xyz.txt"));
    BOOST_CHECK(!t.LoadBin("nonexistent_xyz.bin"));
}