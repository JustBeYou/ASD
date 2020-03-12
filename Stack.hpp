#pragma once
#include "LinkedList.hpp"

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

        private:
        size_t elementCount;
        LinkedList<T> content;
    };
}