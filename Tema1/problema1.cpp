#include <iostream>
#include "Stack.hpp"

int main() {
    ASD::Stack<int> stack;
    stack.push(1); ASD::print<int>(stack);
    stack.pop(); ASD::print<int>(stack);
    stack.push(2); ASD::print<int>(stack);
    stack.push(3); ASD::print<int>(stack);

    return 0;
}