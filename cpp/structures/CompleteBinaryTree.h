#pragma once

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <sstream>

template <typename T>
struct TNode {
    T data;
    TNode* left;
    TNode* right;
    TNode(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class CompleteBinaryTree {
private:
    TNode<T>* root;

    void clearRecursive(TNode<T>* node) {
        if (node != nullptr) {
            clearRecursive(node->left);
            clearRecursive(node->right);
            delete node;
        }
    }

    TNode<T>* copyRecursive(TNode<T>* node) {
        if (node == nullptr) return nullptr;
        TNode<T>* newNode = new TNode<T>(node->data);
        newNode->left = copyRecursive(node->left);
        newNode->right = copyRecursive(node->right);
        return newNode;
    }

    void writeValue(std::ofstream& file, const T& val) const {
        if constexpr (std::is_same_v<T, std::string>) {
            size_t len = val.length();
            file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
            if (len > 0) file.write(val.c_str(), len);
        } else {
            file.write(reinterpret_cast<const char*>(&val), sizeof(T));
        }
    }

    bool readValue(std::ifstream& file, T& val) {
        if constexpr (std::is_same_v<T, std::string>) {
            size_t len;
            file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
            if (!file) return false;
            val = T(len, '\0');
            if (len > 0) file.read(&val[0], len);
            return file.good();
        } else {
            file.read(reinterpret_cast<char*>(&val), sizeof(T));
            return file.good();
        }
    }

public:
    CompleteBinaryTree() : root(nullptr) {}

    void TInit() { TClear(); }

    void TInsert(const T& val) {
        TNode<T>* newNode = new TNode<T>(val);
        if (root == nullptr) { root = newNode; return; }
        std::queue<TNode<T>*> q;
        q.push(root);
        while (!q.empty()) {
            TNode<T>* curr = q.front(); q.pop();
            if (curr->left == nullptr) { curr->left = newNode; return; }
            else q.push(curr->left);
            if (curr->right == nullptr) { curr->right = newNode; return; }
            else q.push(curr->right);
        }
    }

    bool TSearch(const T& val) const {
        if (root == nullptr) return false;
        std::queue<TNode<T>*> q;
        q.push(root);
        while (!q.empty()) {
            TNode<T>* curr = q.front(); q.pop();
            if (curr->data == val) return true;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return false;
    }

    bool TIsComplete() const {
        if (root == nullptr) return true;
        std::queue<TNode<T>*> q;
        q.push(root);
        bool foundGap = false;
        while (!q.empty()) {
            TNode<T>* curr = q.front(); q.pop();
            if (curr->left) {
                if (foundGap) return false;
                q.push(curr->left);
            } else foundGap = true;
            if (curr->right) {
                if (foundGap) return false;
                q.push(curr->right);
            } else foundGap = true;
        }
        return true;
    }

    void TPrint() const {
        if (root == nullptr) { std::cout << "Tree is empty\n"; return; }
        std::queue<TNode<T>*> q;
        q.push(root);
        std::cout << "CBTree: ";
        while (!q.empty()) {
            TNode<T>* curr = q.front(); q.pop();
            std::cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        std::cout << "\n";
    }

    void TClear() {
        clearRecursive(root);
        root = nullptr;
    }

    ~CompleteBinaryTree() { TClear(); }

    CompleteBinaryTree(const CompleteBinaryTree& other) : root(nullptr) {
        root = copyRecursive(other.root);
    }

    CompleteBinaryTree& operator=(const CompleteBinaryTree& other) {
        if (this != &other) {
            TClear();
            root = copyRecursive(other.root);
        }
        return *this;
    }

    void SaveText(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        std::queue<TNode<T>*> q;
        if (root) q.push(root);
        while (!q.empty()) {
            TNode<T>* curr = q.front(); q.pop();
            if (curr != nullptr) {
                file << curr->data << "\n";
                q.push(curr->left);
                q.push(curr->right);
            } else {
                file << "NULL\n";
            }
        }
    }

    bool LoadText(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        TClear();
        std::string token;
        if (!(file >> token)) return false;
        if (token == "NULL") return true;
        std::istringstream iss(token);
        T val;
        iss >> val;
        root = new TNode<T>(val);
        std::queue<TNode<T>*> q;
        q.push(root);
        int nodeCount = 1;
        while (!q.empty() && (file >> token)) {
            TNode<T>* curr = q.front(); q.pop();
            if (token != "NULL") {
                std::istringstream issL(token);
                T valL; issL >> valL;
                curr->left = new TNode<T>(valL);
                q.push(curr->left);
                nodeCount++; 
                if (nodeCount > 1000000) return false;
            }
            if (!(file >> token)) break;
            if (token != "NULL") {
                std::istringstream issR(token);
                T valR; issR >> valR;
                curr->right = new TNode<T>(valR);
                q.push(curr->right);
                nodeCount++;
                if (nodeCount > 1000000) return false;
            }
        }
        return true;
    }

    void SaveBin(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        std::queue<TNode<T>*> q;
        if (root) q.push(root);
        while (!q.empty()) {
            TNode<T>* curr = q.front(); q.pop();
            if (curr != nullptr) {
                int isNull = 0;
                file.write(reinterpret_cast<const char*>(&isNull), sizeof(int));
                writeValue(file, curr->data);
                q.push(curr->left);
                q.push(curr->right);
            } else {
                int isNull = 1;
                file.write(reinterpret_cast<const char*>(&isNull), sizeof(int));
            }
        }
    }

    bool LoadBin(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) return false;
        TClear();
        int isNull;
        if (!file.read(reinterpret_cast<char*>(&isNull), sizeof(int))) return false;
        if (isNull == 1) return true;
        T val;
        if (!readValue(file, val)) return false;
        root = new TNode<T>(val);
        std::queue<TNode<T>*> q;
        q.push(root);
        int nodeCount = 1;
        while (!q.empty() && file.read(reinterpret_cast<char*>(&isNull), sizeof(int))) {
            TNode<T>* curr = q.front(); q.pop();
            if (isNull == 0) {
                T valL;
                if (!readValue(file, valL)) break;
                curr->left = new TNode<T>(valL);
                q.push(curr->left);
                 nodeCount++;
                if (nodeCount > 1000000) return false;
            }
            if (!file.read(reinterpret_cast<char*>(&isNull), sizeof(int))) break;
            if (isNull == 0) {
                T valR;
                if (!readValue(file, valR)) break;
                curr->right = new TNode<T>(valR);
                q.push(curr->right);
                 nodeCount++;
                if (nodeCount > 1000000) return false;
            }
        }
        return true;
    }
};