#include <iostream>
#include <cassert>
#include "LinkedList.hpp"

using namespace std;

void test_LinkedList();

int main() {
    test_LinkedList();

    return 0;
}

void test_LinkedList() {
    cout << "Linked list testing... ";

    ASD::LinkedList<int> list;

    auto begin = list.begin();
    assert(begin == list.end());

    list.addHead(123);
    list.addHead(321);
    list.addHead(999);
    auto it = list.begin();
    assert(it->content == 999);
    ++it;
    assert(it->content == 321);
    ++it;
    assert(it->content == 123);
    ++it;
    assert(it == list.end());

    cout << "OK" << endl;
}