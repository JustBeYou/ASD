#pragma once

#include <vector>
#include <functional>
#include <stdexcept>
#include <utility>
#include <fstream>

namespace ASD {
    template <typename T, typename ComparatorType = std::less<T>>
    class Heap {
        public:
        Heap(std::vector<T>& v) {
            tree = v;
            for (size_t i = prevLayerIndex(lastLayerIndex()); i > 0; i--) {
                heapifyAt(i);
            }
            heapifyAt(0);
        }

        void push(const T& elem) {
            tree.push_back(elem);

            size_t index = tree.size() - 1;
            while (index != 0 and Comparator(tree[index], tree[parent(index)])) {
                std::swap(tree[index], tree[parent(index)]);
                index = parent(index);
            }
        }
        
        T pop() {
            const T root = tree[0];
            tree[0] = tree[tree.size() - 1];
            tree.pop_back();
            heapifyAt(0);

            return root;
        }

        T head() const {
            return tree[tree.size() - 1];
        }

        bool isEmpty() const {
            return tree.size() == 0;
        }

        friend std::ostream& operator<<(std::ostream& out, Heap<T, ComparatorType>& heap) {
            for (auto it: heap.tree) {
                out << it << " ";
            }
            out << std::endl;
        }

        private:
        std::vector<T> tree;
        ComparatorType Comparator;

        void heapifyAt(size_t index) {
            size_t rootCandidate = index;

            if (leftChildExists(index) and Comparator(tree[leftChild(index)], tree[rootCandidate])) {
                rootCandidate = leftChild(index);
            }

            if (rightChildExists(index) and Comparator(tree[rightChild(index)], tree[rootCandidate])) {
                rootCandidate = rightChild(index);
            }

            if (rootCandidate != index) {
                std::swap(tree[rootCandidate], tree[index]);
                heapifyAt(rootCandidate);
            }
        }

        size_t parent(const size_t child) const {
            if (child == 0) throw std::invalid_argument("Already on root layer");
            if (child % 2 == 0) {
                return (child - 2) / 2;
            }
            return (child - 1) / 2;
        }

        size_t leftChild(const size_t parent) const {
            return 2 * parent + 1;
        }

        bool leftChildExists(const size_t parent) const {
            return leftChild(parent) < tree.size();
        }

        size_t rightChild(const size_t parent) const {
            return 2 * parent + 2;
        }

        bool rightChildExists(const size_t parent) const {
            return rightChild(parent) < tree.size();
        }

        size_t lastLayerIndex() const {
            return layerIndex(tree.size() - 1);
        }

        size_t layerIndex(const size_t layer) const {
            return (1 << layer) - 1;
        }

        size_t prevLayerIndex(const size_t elemIndex) const {
            if (elemIndex == 0) throw std::invalid_argument("Already on root layer"); 
            return (elemIndex + 1) / 2 - 1;
        }

        size_t nextLayerIndex(const size_t elemIndex) const {
            const size_t layerIndex = (elemIndex + 1) * 2 - 1;
            if (elemIndex >= tree.size()) throw std::invalid_argument("Already on last layer");
            return layerIndex;
        }
    };
}