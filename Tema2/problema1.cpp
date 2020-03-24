#include <iostream>
#include <vector>
#include "Heap.hpp"

using namespace std;

int main() {
    vector<int> v({10, 7, 11, 5, 9, 3, 8, 4, 6, 2});
    ASD::Heap<int> heap(v);

    cout << "Heap: " << heap << endl;
    heap.push(1);
    heap.push(12);
    cout << "Heap: " << heap << endl;

    cout << "Sorted: ";
    while(not heap.isEmpty()) {
        int elem = heap.pop();
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}