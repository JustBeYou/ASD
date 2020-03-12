namespace ASD {
    template <typename T>
    struct LinkedListNode;

    template <typename T>
    class LinkedList {
        public:
        LinkedList(): head(nullptr) {}
    
        LinkedList(const T& content) {
            this->head = new LinkedListNode<T>(content);
        }

        void addHead(const T& content) {
            if (this->head == nullptr) {
                this->head = new LinkedListNode<T>(content);
            } else {
                auto newNode = new LinkedListNode<T>(content);
                newNode->next = this->head;
                this->head = newNode;
            }
        }

        void addTail() {

        }

        class iterator;

        iterator begin() const {
            return iterator(this->head);
        }

        iterator end() const {
            return iterator(nullptr);
        }

        class iterator {
            public:
            iterator(LinkedListNode<T>* pointer): pointer(pointer) {}
            iterator(LinkedListNode<T>*& pointer): pointer(pointer) {}

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

            LinkedListNode<T>& operator*() { 
                return *(this->pointer);
            }
            
            LinkedListNode<T>* operator->() { 
                return this->pointer;
            }

            private:
            LinkedListNode<T>* pointer;
        };

        private:
        LinkedListNode<T>* head;
    };

    template <typename T>
    struct LinkedListNode {
        T content;
        LinkedListNode* next;

        LinkedListNode(const T& content): content(content), next(nullptr) {}
    };
}