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

        template <typename U>
        friend void print(Dequeue<U>& dequeue);

        private:
        size_t elementCount;
        DoubleLinkedList<T> content;
    };

    template <typename T>
    void print(Dequeue<T>& dequeue) {
        if (dequeue.elementCount == 0) {
            std::cout << "< >" << std::endl;
            return ;
        }
        if (dequeue.elementCount == 1) {
            std::cout << "< " << dequeue.content.end()->content << " >" << std::endl;
            return ; 
        }

        std::cout << "< ";
        for (auto it = dequeue.content.begin(); it != dequeue.content.end(); ++it) {
            std::cout << it->content << " ";
        }
        std::cout << dequeue.content.end()->content << " ";
        std::cout << ">" << std::endl;
    }
}