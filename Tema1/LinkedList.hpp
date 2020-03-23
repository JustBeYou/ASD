#pragma once
#include <stdexcept>
#include <new>

namespace ASD {
    template <typename T>
    struct LinkedListNode;

    template <typename T, class Node>
    class InternalLinkedList;

    template <typename T>
    using LinkedList = InternalLinkedList<T, LinkedListNode<T>>;

    template <typename T, typename Node>
    class InternalLinkedList {
        public:
        InternalLinkedList(): head(nullptr) {}
    
        InternalLinkedList(const T& content) {
            this->head = new Node(content);
        }

        ~InternalLinkedList() {
            this->clear();
        }

        void addHead(const T& content) {
            if (this->head == nullptr) {
                this->head = new Node(content);
            } else {
                auto newNode = new Node(content);
                newNode->link(head);
                this->head = newNode;
            }
        }

        void clear() {
            while (this->isNotEmpty()) {
                this->removeHead();
            }
        }

        void removeHead() {
            if (this->isEmpty()) {
                throw std::logic_error("List is already empty");
            }

            auto oldHead = this->head;
            this->head = this->head->next;
            delete oldHead;
        }

        bool isEmpty() const {
            return this->head == nullptr;
        }

        bool isNotEmpty() const {
            return !this->isEmpty();
        } 

        class iterator;

        iterator begin() {
            return iterator(this->head);
        }

        iterator end() {
            return iterator(nullptr);
        }

        class iterator {
            public:
            iterator(Node* pointer): pointer(pointer) {}

            iterator operator++() {
                auto current = *this;
                this->pointer = this->pointer->next;
                return current;
            };

            bool operator==(const iterator& rhs) const {
                return this->pointer == rhs.pointer;
            }

            bool operator!=(const iterator& rhs) const {
                return !(*this == rhs);
            }

            Node& operator*() { 
                return *(this->pointer);
            }
            
            Node* operator->() { 
                return this->pointer;
            }

            protected:
            Node* pointer;
        };

        protected:
        Node* head;
    };

    template <typename T>
    struct LinkedListNode {
        T content;
        LinkedListNode* next;

        LinkedListNode(const T& content): content(content), next(nullptr) {}
        void link(LinkedListNode* next) {
            this->next = next;
        }

        ~LinkedListNode() {
            this->next = nullptr;
        }
    };
}