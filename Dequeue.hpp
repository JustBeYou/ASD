#include "DoubleLinkedList.hpp"

namespace ASD {
    template <typename T>
    class Dequeue {
        public:
        Dequeue(): elementCount(0) {}

        void pushLeft(const T& element) {
            this->elementCount++;
            this->content.addHead(element);
        }

        void pushRight(const T& element) {
            this->elementCount++;
            this->content.addTail(element);
        }

        T popLeft() {
            auto element = this->content.begin()->content;
            this->content.removeHead();
            this->elementCount--;
            return element;
        }

        T popRight() {
            auto element = this->content.end()->content;
            this->content.removeTail();
            this->elementCount--;
            return element;
        }

        size_t count() const {
            return this->elementCount;
        }

        private:
        size_t elementCount;
        DoubleLinkedList<T> content;
    };
}