#include <iostream>
#include <cassert>
#include "LinkedList.hpp"
#include "DoubleLinkedList.hpp"
#include "Stack.hpp"
#include "Dequeue.hpp"

#define print_assert(x) printf("Check: " #x "\n"); assert(x);

using namespace std;

void test_LinkedList();
void test_Stack();
void test_DoubleLinkedList();
void test_Dequeue();

int main() {
    test_LinkedList();
    test_Stack();
    test_DoubleLinkedList();
    test_Dequeue();

    return 0;
}

void test_LinkedList() {
    cout << "Linked list testing..." << endl;

    ASD::LinkedList<int> list;

    auto begin = list.begin();
    print_assert(begin == list.end());

    list.addHead(123);
    list.addHead(321);
    list.addHead(999);
    auto it = list.begin();
    print_assert(it->content == 999);
    ++it;
    print_assert(it->content == 321);
    ++it;
    print_assert(it->content == 123);
    ++it;
    print_assert(it == list.end());

    list.removeHead();
    auto newHead = list.begin();
    print_assert(newHead->content == 321);

    cout << "OK" << endl;
}

void test_Stack() {
    cout << "Stack testing..." << endl;
    ASD::Stack<int> stack;

    stack.push(1);
    print_assert(stack.pop() == 1);
    stack.push(2);
    stack.push(3);
    print_assert(stack.count() == 2);
    print_assert(stack.pop() == 3);

    cout << "OK" << endl;
}

void test_DoubleLinkedList() {
    cout << "Double linked list testing..." << endl;

    ASD::DoubleLinkedList<int> list;

    auto begin = list.begin();
    print_assert(begin == list.end());

    list.addHead(123);
    list.addHead(321);
    list.addHead(999);
    auto it = list.begin();
    print_assert(it->content == 999);
    ++it;
    print_assert(it->content == 321);
    ++it;
    print_assert(it->content == 123);
    print_assert(it == list.end());
    print_assert(it->content == 123);
    --it;
    print_assert(it->content == 321);
    --it;
    print_assert(it->content == 999);

    list.removeHead();
    auto newHead = list.begin();
    print_assert(newHead->content == 321);

    list.removeTail();
    auto newTail = list.end();
    print_assert(newTail->content == 321);

    cout << "OK" << endl;
}

void test_Dequeue() {
    cout << "Dequeue testing ..." << endl;

    ASD::Dequeue<int> dequeue;
    dequeue.pushLeft(1);
    dequeue.pushRight(2);
    print_assert(dequeue.count() == 2);
    print_assert(dequeue.popRight() == 2);
    print_assert(dequeue.popLeft() == 1);
    dequeue.pushRight(3);

    cout << "OK" << endl;
}