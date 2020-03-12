#pragma once
#include "LinkedList.hpp"
#include <stdexcept>

namespace ASD {
    template <typename T>
    class DoubleLinkedListNode;
    
    template <typename T>
    class DoubleLinkedList: public InternalLinkedList<T, DoubleLinkedListNode<T>> {
        using LinkedList = InternalLinkedList<T, DoubleLinkedListNode<T>>;

        public:
        DoubleLinkedList(): tail(nullptr) {}
    
        DoubleLinkedList(const T& content) {
            this->create(content);
        }

        void addHead(const T& content) {
            LinkedList::addHead(content);
            if (this->tail == nullptr) {
                this->tail = this->head;
            }
        }

        void removeHead() {
            LinkedList::removeHead();
            if (this->head == nullptr) {
                this->tail = nullptr;
            }
        }

        void addTail(const T& content) {
            if (this->head == nullptr) {
                this->create(); 
            } else {
                auto newNode = new DoubleLinkedListNode<T>(content);
                this->tail->link(newNode);
                this->tail = newNode;
            }
        }

        void removeTail() {
            if (this->isEmpty()) {
                throw std::logic_error("List is already empty");
            }

            auto oldTail = this->tail;
            this->tail = this->tail->prev;
            delete oldTail;

            if (this->tail == nullptr) {
                this->head = nullptr;
            }
        }

        void clear() {
            LinkedList::clear();
            this->tail = nullptr;
        }

        class iterator;

        iterator begin() {
            return iterator(this->head);
        }

        iterator end() {
            return iterator(this->tail);
        }

        class iterator: public LinkedList::iterator {
            public:
            iterator(DoubleLinkedListNode<T>* node): LinkedList::iterator(node) {}

            iterator operator++() {
                auto current = *this;
                this->pointer = this->pointer->next;

                if (this->pointer == nullptr) {
                    throw std::out_of_range("Nothing after the last element");
                }

                return current;
            };

            iterator operator--() {
                auto current = *this;
                this->pointer = this->pointer->prev;

                if (this->pointer == nullptr) {
                    throw std::out_of_range("Nothing behind the first element");
                }

                return current;
            };

            DoubleLinkedListNode<T>& operator*() { 
                return *(this->pointer);
            }
            
            DoubleLinkedListNode<T>* operator->() { 
                return this->pointer;
            }
        };

        protected:
        DoubleLinkedListNode<T>* tail;

        private:
        void create(const T& content) {
            this->head = new DoubleLinkedList(content);
            this->tail = this->head;
        } 
    };

    template <typename T>
    struct DoubleLinkedListNode {
        T content;
        DoubleLinkedListNode* next;
        DoubleLinkedListNode* prev;

        DoubleLinkedListNode(const T& content): content(content), next(nullptr), prev(nullptr) {}
        void link(DoubleLinkedListNode<T>* next) {
            this->next = next;
            next->prev = this;
        }

        ~DoubleLinkedListNode() {
            this->next = nullptr;
            this->prev = nullptr;
        } 
    };
}