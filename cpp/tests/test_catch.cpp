#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstdio>
#include "structures/Array.h"
#include "structures/ForwardList.h"
#include "structures/Doublylist.h"
#include "structures/Stack.h"
#include "structures/Queue.h"
#include "structures/HashTable.h"
#include "structures/CompleteBinaryTree.h"

TEST_CASE("Array push/get/len", "[array]") {
    Array<int> a;
    a.MInit(2);
    a.MPush(10);
    a.MPush(30);
    a.MPushIdx(1, 20);
    REQUIRE(a.MLen() == 3);
    REQUIRE(a.MGet(1) == 20);
}

TEST_CASE("Array push idx errors", "[array]") {
    Array<int> a;
    a.MPush(1);
    REQUIRE_THROWS_AS(a.MPushIdx(-1, 0), std::out_of_range);
    REQUIRE_THROWS_AS(a.MPushIdx(5, 0), std::out_of_range);
    REQUIRE_NOTHROW(a.MPushIdx(0, 9));
    REQUIRE_NOTHROW(a.MPushIdx(a.MLen(), 8));
}

TEST_CASE("Array get/del errors", "[array]") {
    Array<int> a;
    REQUIRE_THROWS_AS(a.MGet(0), std::out_of_range);
    REQUIRE_THROWS_AS(a.MDelInd(0), std::out_of_range);
}

TEST_CASE("Array del and clear", "[array]") {
    Array<int> a;
    a.MPush(1); a.MPush(2); a.MPush(3);
    REQUIRE_NOTHROW(a.MDelInd(0));
    REQUIRE(a.MGet(0) == 2);
    a.MClear();
    REQUIRE(a.MLen() == 0);
    a.MPush(5);
    REQUIRE(a.MLen() == 1);
}

TEST_CASE("Array copy and assign", "[array]") {
    Array<int> a;
    a.MPush(1); a.MPush(2);
    Array<int> b(a);
    b.MPush(3);
    REQUIRE(a.MLen() == 2);
    REQUIRE(b.MLen() == 3);
    Array<int> c;
    c = a;
    c.MPush(4);
    REQUIRE(a.MLen() == 2);
    REQUIRE(c.MLen() == 3);
}

TEST_CASE("Array serialize text", "[array]") {
    Array<int> a;
    a.MPush(1); a.MPush(2); a.MPush(3);
    REQUIRE_NOTHROW(a.SaveText("catch_a.txt"));
    Array<int> b;
    REQUIRE(b.LoadText("catch_a.txt"));
    REQUIRE(b.MLen() == 3);
    REQUIRE(b.MGet(2) == 3);
    std::remove("catch_a.txt");
}

TEST_CASE("Array serialize bin", "[array]") {
    Array<int> a;
    a.MPush(7); a.MPush(8);
    REQUIRE_NOTHROW(a.SaveBin("catch_a.bin"));
    Array<int> b;
    REQUIRE(b.LoadBin("catch_a.bin"));
    REQUIRE(b.MLen() == 2);
    REQUIRE(b.MGet(1) == 8);
    std::remove("catch_a.bin");
}

TEST_CASE("Array load bad file", "[array]") {
    Array<int> a;
    REQUIRE_FALSE(a.LoadText("nonexistent_xyz.txt"));
    REQUIRE_FALSE(a.LoadBin("nonexistent_xyz.bin"));
}

TEST_CASE("ForwardList push/find/del", "[flist]") {
    ForwardList<int> f;
    f.FPushHead(2);
    f.FPushHead(1);
    f.FPush(3);
    REQUIRE(f.FGetHead() == 1);
    REQUIRE(f.FGetTail() == 3);
    REQUIRE_NOTHROW(f.FDel(2));
    REQUIRE_THROWS_AS(f.FGet(2), std::runtime_error);
}

TEST_CASE("ForwardList push before/after", "[flist]") {
    ForwardList<int> f;
    f.FPush(1); f.FPush(3);
    f.FPushBefore(3, 2);
    REQUIRE(f.FGetIdx(1) == 2);
    f.FPushAfter(1, 99);
    REQUIRE(f.FGetIdx(1) == 99);
}

TEST_CASE("ForwardList del empty", "[flist]") {
    ForwardList<int> f;
    REQUIRE_NOTHROW(f.FDel(99));
    REQUIRE_NOTHROW(f.FDelHead());
    REQUIRE_NOTHROW(f.FDelTail());
}

TEST_CASE("ForwardList del head/tail/middle", "[flist]") {
    ForwardList<int> f;
    f.FPush(1); f.FPush(2); f.FPush(3);
    f.FDelHead();
    REQUIRE(f.FGetHead() == 2);
    f.FDelTail();
    REQUIRE(f.FGetTail() == 2);
    f.FDel(2);
    REQUIRE_THROWS_AS(f.FGetHead(), std::runtime_error);
}

TEST_CASE("ForwardList copy and assign", "[flist]") {
    ForwardList<int> f;
    f.FPush(1); f.FPush(2);
    ForwardList<int> g(f);
    g.FPush(3);
    REQUIRE(f.FGetTail() == 2);
    REQUIRE(g.FGetTail() == 3);
}

TEST_CASE("ForwardList serialize text", "[flist]") {
    ForwardList<int> f;
    f.FPush(1); f.FPush(2);
    REQUIRE_NOTHROW(f.SaveText("catch_f.txt"));
    ForwardList<int> g;
    REQUIRE(g.LoadText("catch_f.txt"));
    REQUIRE(g.FGetTail() == 2);
    std::remove("catch_f.txt");
}

TEST_CASE("ForwardList serialize bin", "[flist]") {
    ForwardList<int> f;
    f.FPush(7); f.FPush(8);
    REQUIRE_NOTHROW(f.SaveBin("catch_f.bin"));
    ForwardList<int> g;
    REQUIRE(g.LoadBin("catch_f.bin"));
    REQUIRE(g.FGetHead() == 7);
    std::remove("catch_f.bin");
}

TEST_CASE("ForwardList load bad file", "[flist]") {
    ForwardList<int> f;
    REQUIRE_FALSE(f.LoadText("nonexistent_xyz.txt"));
    REQUIRE_FALSE(f.LoadBin("nonexistent_xyz.bin"));
}

TEST_CASE("DoublyList push both ends", "[dlist]") {
    DoublyList<int> l;
    l.LPush(2);
    l.LPushHead(1);
    l.LPush(3);
    REQUIRE(l.LGetHead() == 1);
    REQUIRE(l.LGetTail() == 3);
}

TEST_CASE("DoublyList push before/after", "[dlist]") {
    DoublyList<int> l;
    l.LPush(1); l.LPush(3);
    l.LPushBefore(3, 2);
    REQUIRE(l.LGetIdx(1) == 2);
    l.LPushAfter(1, 99);
    REQUIRE(l.LGetIdx(1) == 99);
}

TEST_CASE("DoublyList del operations", "[dlist]") {
    DoublyList<int> l;
    l.LPush(1); l.LPush(2); l.LPush(3);
    l.LDel(2);
    REQUIRE_THROWS_AS(l.LGet(2), std::runtime_error);
    l.LDelHead();
    REQUIRE(l.LGetHead() == 3);
    l.LDelTail();
    REQUIRE_THROWS_AS(l.LGetHead(), std::runtime_error);
}

TEST_CASE("DoublyList del empty", "[dlist]") {
    DoublyList<int> l;
    REQUIRE_NOTHROW(l.LDel(1));
    REQUIRE_NOTHROW(l.LDelHead());
    REQUIRE_NOTHROW(l.LDelTail());
}

TEST_CASE("DoublyList copy and assign", "[dlist]") {
    DoublyList<int> l;
    l.LPush(1); l.LPush(2);
    DoublyList<int> g(l);
    g.LPush(3);
    REQUIRE(l.LGetTail() == 2);
    REQUIRE(g.LGetTail() == 3);
}

TEST_CASE("DoublyList serialize text", "[dlist]") {
    DoublyList<int> l;
    l.LPush(10); l.LPush(20);
    REQUIRE_NOTHROW(l.SaveText("catch_l.txt"));
    DoublyList<int> l2;
    REQUIRE(l2.LoadText("catch_l.txt"));
    REQUIRE(l2.LGetTail() == 20);
    std::remove("catch_l.txt");
}

TEST_CASE("DoublyList serialize bin", "[dlist]") {
    DoublyList<int> l;
    l.LPush(5); l.LPush(6);
    REQUIRE_NOTHROW(l.SaveBin("catch_l.bin"));
    DoublyList<int> l2;
    REQUIRE(l2.LoadBin("catch_l.bin"));
    REQUIRE(l2.LGetTail() == 6);
    std::remove("catch_l.bin");
}

TEST_CASE("DoublyList load bad file", "[dlist]") {
    DoublyList<int> l;
    REQUIRE_FALSE(l.LoadText("nonexistent_xyz.txt"));
    REQUIRE_FALSE(l.LoadBin("nonexistent_xyz.bin"));
}

TEST_CASE("Stack push/pop/top", "[stack]") {
    Stack<int> s;
    s.SInit(2);
    REQUIRE_THROWS_AS(s.SPeek(), std::runtime_error);
    REQUIRE_THROWS_AS(s.SPop(), std::runtime_error);
    s.SPush(1);
    s.SPush(2);
    REQUIRE(s.SPeek() == 2);
    REQUIRE(s.SPop() == 2);
    REQUIRE(s.SPeek() == 1);
}

TEST_CASE("Stack pop to empty", "[stack]") {
    Stack<int> s;
    s.SInit(1);
    s.SPush(1);
    REQUIRE_NOTHROW(s.SPop());
    REQUIRE_THROWS_AS(s.SPop(), std::runtime_error);
}

TEST_CASE("Stack resize", "[stack]") {
    Stack<int> s;
    s.SInit(1);
    for (int i = 0; i < 10; ++i) s.SPush(i);
    REQUIRE(s.SPeek() == 9);
}

TEST_CASE("Stack copy and assign", "[stack]") {
    Stack<int> s;
    s.SInit(2);
    s.SPush(1); s.SPush(2);
    Stack<int> t(s);
    t.SPush(3);
    REQUIRE(s.SPeek() == 2);
    REQUIRE(t.SPeek() == 3);
}

TEST_CASE("Stack serialize text", "[stack]") {
    Stack<int> s;
    s.SInit(2);
    s.SPush(1); s.SPush(2); s.SPush(3);
    REQUIRE_NOTHROW(s.SaveText("catch_s.txt"));
    Stack<int> s2;
    REQUIRE(s2.LoadText("catch_s.txt"));
    REQUIRE(s2.SPeek() == 3);
    std::remove("catch_s.txt");
}

TEST_CASE("Stack serialize bin", "[stack]") {
    Stack<int> s;
    s.SInit(2);
    s.SPush(1); s.SPush(2);
    REQUIRE_NOTHROW(s.SaveBin("catch_s.bin"));
    Stack<int> s2;
    REQUIRE(s2.LoadBin("catch_s.bin"));
    REQUIRE(s2.SPeek() == 2);
    std::remove("catch_s.bin");
}

TEST_CASE("Stack load bad file", "[stack]") {
    Stack<int> s;
    REQUIRE_FALSE(s.LoadText("nonexistent_xyz.txt"));
    REQUIRE_FALSE(s.LoadBin("nonexistent_xyz.bin"));
}

TEST_CASE("Queue push/pop/front", "[queue]") {
    Queue<int> q;
    q.QInit(2);
    REQUIRE_THROWS_AS(q.QPeek(), std::runtime_error);
    REQUIRE_THROWS_AS(q.QPop(), std::runtime_error);
    q.QPush(1);
    q.QPush(2);
    REQUIRE(q.QPeek() == 1);
    REQUIRE(q.QPop() == 1);
    REQUIRE(q.QPeek() == 2);
}

TEST_CASE("Queue pop to empty", "[queue]") {
    Queue<int> q;
    q.QInit(1);
    q.QPush(1);
    REQUIRE_NOTHROW(q.QPop());
    REQUIRE_THROWS_AS(q.QPop(), std::runtime_error);
}

TEST_CASE("Queue resize", "[queue]") {
    Queue<int> q;
    q.QInit(1);
    for (int i = 0; i < 10; ++i) q.QPush(i);
    REQUIRE(q.QPeek() == 0);
}

TEST_CASE("Queue wrap around", "[queue]") {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1); q.QPush(2);
    q.QPop();
    q.QPush(3);
    REQUIRE(q.QPop() == 2);
    REQUIRE(q.QPop() == 3);
}

TEST_CASE("Queue copy and assign", "[queue]") {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1);
    Queue<int> t(q);
    t.QPush(2);
    REQUIRE(q.QPeek() == 1);
    REQUIRE(t.QPeek() == 1);
}

TEST_CASE("Queue serialize text", "[queue]") {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1); q.QPush(2); q.QPush(3);
    REQUIRE_NOTHROW(q.SaveText("catch_q.txt"));
    Queue<int> q2;
    REQUIRE(q2.LoadText("catch_q.txt"));
    REQUIRE(q2.QPeek() == 1);
    std::remove("catch_q.txt");
}

TEST_CASE("Queue serialize bin", "[queue]") {
    Queue<int> q;
    q.QInit(2);
    q.QPush(1); q.QPush(2);
    REQUIRE_NOTHROW(q.SaveBin("catch_q.bin"));
    Queue<int> q2;
    REQUIRE(q2.LoadBin("catch_q.bin"));
    REQUIRE(q2.QPeek() == 1);
    std::remove("catch_q.bin");
}

TEST_CASE("Queue load bad file", "[queue]") {
    Queue<int> q;
    REQUIRE_FALSE(q.LoadText("nonexistent_xyz.txt"));
    REQUIRE_FALSE(q.LoadBin("nonexistent_xyz.bin"));
}

TEST_CASE("HashTable insert/find/update", "[hash]") {
    HashTable h;
    h.HInit(7);
    h.add("one");
    h.add("two");
    REQUIRE(h.contains("one"));
    REQUIRE_FALSE(h.contains("nope"));
}

TEST_CASE("HashTable delete", "[hash]") {
    HashTable h;
    h.HInit(7);
    h.add("a");
    h.add("k");
    REQUIRE(h.contains("a"));
    h.remove("a");
    REQUIRE_FALSE(h.contains("a"));
    REQUIRE_NOTHROW(h.remove("nope"));
}

TEST_CASE("HashTable collisions", "[hash]") {
    HashTable h;
    h.HInit(3);
    h.add("a");
    h.add("b");
    h.add("c");
    REQUIRE(h.contains("a"));
    REQUIRE(h.contains("b"));
    REQUIRE(h.contains("c"));
}

TEST_CASE("HashTable copy and assign", "[hash]") {
    HashTable h;
    h.HInit(7);
    h.add("a");
    HashTable g(h);
    g.add("b");
    REQUIRE(h.contains("a"));
    REQUIRE(g.contains("b"));
}

TEST_CASE("HashTable serialize text", "[hash]") {
    HashTable h;
    h.HInit(7);
    h.add("x"); h.add("y");
    REQUIRE_NOTHROW(h.SaveText("catch_h.txt"));
    HashTable h2;
    REQUIRE(h2.LoadText("catch_h.txt"));
    REQUIRE(h2.contains("x"));
    REQUIRE(h2.contains("y"));
    std::remove("catch_h.txt");
}

TEST_CASE("HashTable serialize bin", "[hash]") {
    HashTable h;
    h.HInit(7);
    h.add("x"); h.add("yy");
    REQUIRE_NOTHROW(h.SaveBin("catch_h.bin"));
    HashTable h2;
    REQUIRE(h2.LoadBin("catch_h.bin"));
    REQUIRE(h2.contains("yy"));
    std::remove("catch_h.bin");
}

TEST_CASE("HashTable load bad file", "[hash]") {
    HashTable h;
    REQUIRE_FALSE(h.LoadText("nonexistent_xyz.txt"));
    REQUIRE_FALSE(h.LoadBin("nonexistent_xyz.bin"));
}

TEST_CASE("Tree insert and find", "[tree]") {
    CompleteBinaryTree<int> t;
    REQUIRE_FALSE(t.TSearch(1));
    for (int i = 1; i <= 7; i++) t.TInsert(i);
    REQUIRE(t.TIsComplete());
    for (int i = 1; i <= 7; i++) REQUIRE(t.TSearch(i));
    REQUIRE_FALSE(t.TSearch(99));
}

TEST_CASE("Tree not complete", "[tree]") {
    CompleteBinaryTree<int> t;
    t.TInsert(1);
    t.TInsert(2);
    t.TInsert(3);
    t.TInsert(4);
    REQUIRE(t.TIsComplete());
}

TEST_CASE("Tree clear and reuse", "[tree]") {
    CompleteBinaryTree<int> t;
    t.TInsert(1); t.TInsert(2);
    t.TClear();
    REQUIRE_FALSE(t.TSearch(1));
    REQUIRE_NOTHROW(t.TInsert(42));
    REQUIRE(t.TSearch(42));
}

TEST_CASE("Tree copy and assign", "[tree]") {
    CompleteBinaryTree<int> t;
    t.TInsert(1); t.TInsert(2);
    CompleteBinaryTree<int> g(t);
    g.TInsert(3);
    REQUIRE(g.TSearch(3));
    REQUIRE(t.TSearch(1));
}

TEST_CASE("Tree serialize text", "[tree]") {
    CompleteBinaryTree<int> t;
    for (int i = 1; i <= 7; i++) t.TInsert(i);
    REQUIRE_NOTHROW(t.SaveText("catch_t.txt"));
    CompleteBinaryTree<int> t2;
    REQUIRE(t2.LoadText("catch_t.txt"));
    REQUIRE(t2.TIsComplete());
    REQUIRE(t2.TSearch(7));
    std::remove("catch_t.txt");
}

TEST_CASE("Tree serialize bin", "[tree]") {
    CompleteBinaryTree<int> t;
    for (int i = 1; i <= 7; i++) t.TInsert(i);
    REQUIRE_NOTHROW(t.SaveBin("catch_t.bin"));
    CompleteBinaryTree<int> t2;
    REQUIRE(t2.LoadBin("catch_t.bin"));
    REQUIRE(t2.TIsComplete());
    REQUIRE(t2.TSearch(7));
    std::remove("catch_t.bin");
}

TEST_CASE("Tree load bad file", "[tree]") {
    CompleteBinaryTree<int> t;
    REQUIRE_FALSE(t.LoadText("nonexistent_xyz.txt"));
    REQUIRE_FALSE(t.LoadBin("nonexistent_xyz.bin"));
}
