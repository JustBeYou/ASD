#include <iostream>
#include "Dequeue.hpp"

int main() {
    ASD::Dequeue<int> dequeue;
    dequeue.pushLeft(1); ASD::print<int>(dequeue);
    dequeue.pushRight(2); ASD::print<int>(dequeue);
    dequeue.popRight(); ASD::print<int>(dequeue);
    dequeue.popLeft(); ASD::print<int>(dequeue);
    dequeue.pushRight(3); ASD::print<int>(dequeue);

    return 0;
}