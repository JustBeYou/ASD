#pragma once

#include <memory>
#include <vector>
#include <fstream>
#include <iostream>

namespace ASD {

struct NodePrintOrder {
        bool inorder;

        NodePrintOrder(bool inorder = true): inorder(inorder) {}

        bool operator==(const NodePrintOrder& rhs) const {
            return inorder == rhs.inorder;
        }

        friend std::ostream& operator<<(std::ostream& out, NodePrintOrder& order);
} NodePrintInorder, NodePrintPostOrder(false);

static auto printOrder = NodePrintInorder;
std::ostream& operator<<(std::ostream& out, NodePrintOrder& order) {
    printOrder = order;
    return out; 
}

template <typename KeyType>
struct Node {
    std::unique_ptr<Node> left, right;
    KeyType key;

    Node(const KeyType& key): left(nullptr), right(nullptr), key(key) {}

    friend std::ostream& operator<<(std::ostream& out, Node<KeyType>& node) {

        if (printOrder == NodePrintInorder) {
            if (node.left != nullptr) out << *(node.left);
            out << node.key << " ";
            if (node.right != nullptr) out << *(node.right);
        } else {
            out << node.key << " ";
            if (node.left != nullptr) out << *(node.left);
            if (node.right != nullptr) out << *(node.right);
        }

        return out;
    }
};

template <typename KeyType>
class BST {
    using Node = Node<KeyType>;
    using NodePtr = std::unique_ptr<Node>;

    public:
    BST() {

    }

    BST(const std::vector<KeyType>& v) {
        if (v.size() == 0) return ;

        for (const auto& key: v) {
            insert(key);
        }
    }

    void insert(const KeyType& key) {
        internalInsert(key, root);
    }

    friend std::ostream& operator<<(std::ostream& out, BST<KeyType>& bst) {
        out << "In-order: " << NodePrintInorder << *(bst.root) << std::endl;
        out << "Post-order: " << NodePrintPostOrder << *(bst.root) << std::endl;
        return out;
    }

    private:
    NodePtr root = nullptr;

    void internalInsert(const KeyType& key, NodePtr& node) {
        if (node == nullptr) node = std::make_unique<Node>(key);
        else {
            if (key <= node->key) internalInsert(key, node->left);
            else                  internalInsert(key, node->right);
        }
    }
};

};