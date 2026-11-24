#include <iostream>
#include "structures/Array.h"
#include "structures/ForwardList.h"
#include "structures/Doublylist.h"
#include "structures/Stack.h"
#include "structures/Queue.h"
#include "structures/HashTable.h"
#include "structures/CompleteBinaryTree.h"

int main() {
    Array<int> arr;
    arr.MInit(4);
    arr.MPush(10); arr.MPush(20); arr.MPush(30);
    arr.MPushIdx(1, 15);
    arr.MPrint();

    ForwardList<int> fl;
    fl.FPushHead(2); fl.FPushHead(1); fl.FPush(3);
    fl.FPrint();

    DoublyList<int> dl;
    dl.LPush(1); dl.LPush(2); dl.LPushHead(0);
    dl.LPrint();

    Stack<int> st; st.SInit(4);
    st.SPush(10); st.SPush(20); st.SPrint();

    Queue<int> q; q.QInit(4);
    q.QPush(10); q.QPush(20); q.QPrint();

    HashTable ht; ht.HInit(11);
    ht.add("name"); ht.add("value"); ht.print();

    CompleteBinaryTree<int> tr;
    for (int i = 1; i <= 7; i++) tr.TInsert(i);
    tr.TPrint();

    std::cout << "\nСЕРИАЛИЗАЦИЯ\n";

    arr.SaveText("arr.txt");
    arr.SaveBin("arr.bin");
    Array<int> arrTxt, arrBin;
    arrTxt.LoadText("arr.txt");
    arrBin.LoadBin("arr.bin");
    std::cout << "Array TXT: "; arrTxt.MPrint();
    std::cout << "Array BIN: "; arrBin.MPrint();

    fl.SaveText("fl.txt");
    fl.SaveBin("fl.bin");
    ForwardList<int> flTxt, flBin;
    flTxt.LoadText("fl.txt");
    flBin.LoadBin("fl.bin");
    std::cout << "ForwardList TXT: "; flTxt.FPrint();
    std::cout << "ForwardList BIN: "; flBin.FPrint();

    dl.SaveText("dl.txt");
    dl.SaveBin("dl.bin");
    DoublyList<int> dlTxt, dlBin;
    dlTxt.LoadText("dl.txt");
    dlBin.LoadBin("dl.bin");
    std::cout << "DoublyList TXT: "; dlTxt.LPrint();
    std::cout << "DoublyList BIN: "; dlBin.LPrint();

    st.SaveText("st.txt");
    st.SaveBin("st.bin");
    Stack<int> stTxt, stBin;
    stTxt.LoadText("st.txt");
    stBin.LoadBin("st.bin");
    std::cout << "Stack TXT: "; stTxt.SPrint();
    std::cout << "Stack BIN: "; stBin.SPrint();

    q.SaveText("q.txt");
    q.SaveBin("q.bin");
    Queue<int> qTxt, qBin;
    qTxt.LoadText("q.txt");
    qBin.LoadBin("q.bin");
    std::cout << "Queue TXT: "; qTxt.QPrint();
    std::cout << "Queue BIN: "; qBin.QPrint();

    ht.SaveText("ht.txt");
    ht.SaveBin("ht.bin");
    HashTable htTxt, htBin;
    htTxt.LoadText("ht.txt");
    htBin.LoadBin("ht.bin");
    std::cout << "HashTable TXT: "; htTxt.print();
    std::cout << "HashTable BIN: "; htBin.print();

    tr.SaveText("tr.txt");
    tr.SaveBin("tr.bin");
    CompleteBinaryTree<int> trTxt, trBin;
    trTxt.LoadText("tr.txt");
    trBin.LoadBin("tr.bin");
    std::cout << "Tree TXT: "; trTxt.TPrint();
    std::cout << "Tree BIN: "; trBin.TPrint();

    return 0;
}
