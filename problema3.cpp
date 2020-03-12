#include "Stack.hpp"
#include <map>
#include <vector>
#include <iostream>

using namespace std;
using namespace ASD;

bool isValid(vector<int> points) {
    Stack<int> stack;
    map<int, bool> inStack;

    for (auto point: points) {
        if (inStack[point]) {
            auto top = stack.pop();
            if (top != point ) {
                return false;
            }
        } else {
            inStack[point] = true;
            stack.push(point);
        }
    }

    if (stack.count() != 0) {
        return false;
    }

    return true;
}


int main() {
    cout << (isValid({1, 2, 2, 1, 3, 3, 4, 4}) ? "YES" : "NO") << endl;
    cout << (isValid({1, 2, 2, 3, 1, 4, 3, 4}) ? "YES" : "NO") << endl;

    return 0;
}