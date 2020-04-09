#pragma once

#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>

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

    void remove(const KeyType& key) {
        internalRemove(key, root);
    }

    bool exists(const KeyType& key) const {
        return internalExists(key, root);
    }

    std::vector<KeyType> rangeQuery(const KeyType& leftBound, const KeyType& rightBound) const {
        std::vector<KeyType> solution;
        internalRangeQuery(leftBound, rightBound, root, solution);
        return solution;
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

    bool internalExists(const KeyType& key, const NodePtr& node) const {
        if (key == node->key) return true;

        if (node->left != nullptr and key <= node->key) return internalExists(key, node->left);
        else if (node->right != nullptr) return internalExists(key, node->right);
        
        return false;
    }

    void internalRangeQuery(const KeyType& leftBound, const KeyType& rightBound, const NodePtr& node, std::vector<KeyType>& solution) const {
        if (leftBound < node->key and node->left != nullptr) internalRangeQuery(leftBound, rightBound, node->left, solution);
        if (leftBound < node->key and node->key < rightBound) solution.push_back(node->key);
        if (rightBound > node->key and node->right != nullptr) internalRangeQuery(leftBound, rightBound, node->right, solution);
    }

    void internalRemove(const KeyType& key, NodePtr& node) {
        if (node == nullptr) return ;

        if (key < node->key) internalRemove(key, node->left);
        else if (key > node->key) internalRemove(key, node->right);
        else {
            if (node->left) {
                if (node->right) {
                    NodePtr& suitableRightNode = findSuitableRightNode(node->left);
                    node->key = suitableRightNode->key;
                    suitableRightNode = std::move(suitableRightNode->left);
                } else {
                    node = std::move(node->left);
                }
            } else if (node->right) {
                node = std::move(node->right);
            } else {
                node = std::move(nullptr);
            }
        }
    }

    NodePtr& findSuitableRightNode(NodePtr& node) {
        if (node->right != nullptr) return findSuitableRightNode(node->right);
        return node;
    }
};

};