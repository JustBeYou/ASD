#pragma once
#include "LinkedList.hpp"
#include <iostream>

namespace ASD {
    template <typename T>
    class Stack {
        public:
        Stack(): elementCount(0) {}

        void push(const T& element) {
            this->elementCount++;
            this->content.addHead(element);
        }

        T pop() {
            auto element = this->content.begin()->content;
            this->content.removeHead();
            this->elementCount--;
            return element;
        }

        size_t count() const {
            return this->elementCount;
        }

        template <typename U>
        friend void print(Stack<U>& stack);

        private:
        size_t elementCount;
        LinkedList<T> content;
    };

    template <typename T>
    void print(Stack<T>& stack) {
        std::cout << "< ";
        for (auto it = stack.content.begin(); it != stack.content.end(); ++it) {
            std::cout << it->content << " ";
        }
        std::cout << ">" << std::endl;
    }
}