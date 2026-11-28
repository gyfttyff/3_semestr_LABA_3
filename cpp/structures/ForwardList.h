#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <type_traits>

template <typename T>
struct SNode {
    T data;
    SNode* next;
};

template <typename T>
class ForwardList {
private:
    SNode<T>* head;

public:
    ForwardList() : head(nullptr) {}

    void FInit() { FClear(); }

    void FPush(const T& val) {
        SNode<T>* newNode = new SNode<T>{val, nullptr};
        if (head == nullptr) { head = newNode; return; }
        SNode<T>* curr = head;
        while (curr->next != nullptr) curr = curr->next;
        curr->next = newNode;
    }

    void FPushHead(const T& val) {
        SNode<T>* newNode = new SNode<T>{val, head};
        head = newNode;
    }

    void FPushBefore(const T& target, const T& val) {
        if (head == nullptr) return;
        if (head->data == target) { FPushHead(val); return; }
        SNode<T>* curr = head;
        while (curr->next != nullptr && curr->next->data != target) curr = curr->next;
        if (curr->next != nullptr) {
            SNode<T>* newNode = new SNode<T>{val, curr->next};
            curr->next = newNode;
        }
    }

    void FPushAfter(const T& target, const T& val) {
        SNode<T>* curr = head;
        while (curr != nullptr && curr->data != target) curr = curr->next;
        if (curr != nullptr) {
            SNode<T>* newNode = new SNode<T>{val, curr->next};
            curr->next = newNode;
        }
    }

    void FDel(const T& val) {
        if (head == nullptr) return;
        if (head->data == val) { FDelHead(); return; }
        SNode<T>* curr = head;
        while (curr->next != nullptr && curr->next->data != val) curr = curr->next;
        if (curr->next != nullptr) {
            SNode<T>* toDelete = curr->next;
            curr->next = toDelete->next;
            delete toDelete;
        }
    }

    void FDelHead() {
        if (head == nullptr) return;
        SNode<T>* toDelete = head;
        head = head->next;
        delete toDelete;
    }

    void FDelTail() {
        if (head == nullptr) return;
        if (head->next == nullptr) { FDelHead(); return; }
        SNode<T>* curr = head;
        while (curr->next->next != nullptr) curr = curr->next;
        delete curr->next;
        curr->next = nullptr;
    }

    void FDelBefore(const T& target) {
        if (head == nullptr || head->data == target) return;
        if (head->next != nullptr && head->next->data == target) { FDelHead(); return; }
        SNode<T>* curr = head;
        while (curr->next != nullptr && curr->next->next != nullptr && curr->next->next->data != target) curr = curr->next;
        if (curr->next != nullptr && curr->next->next != nullptr) {
            SNode<T>* toDelete = curr->next;
            curr->next = curr->next->next;
            delete toDelete;
        }
    }

    void FDelAfter(const T& target) {
        SNode<T>* curr = head;
        while (curr != nullptr && curr->data != target) curr = curr->next;
        if (curr != nullptr && curr->next != nullptr) {
            SNode<T>* toDelete = curr->next;
            curr->next = toDelete->next;
            delete toDelete;
        }
    }

    T FGet(const T& val) const {
        SNode<T>* curr = head;
        while (curr != nullptr) {
            if (curr->data == val) return curr->data;
            curr = curr->next;
        }
        throw std::runtime_error("Element not found");
    }

    T FGetIdx(int index) const {
        SNode<T>* curr = head;
        int i = 0;
        while (curr != nullptr) {
            if (i == index) return curr->data;
            curr = curr->next; i++;
        }
        throw std::out_of_range("Index out of bounds");
    }

    T FGetHead() const {
        if (head == nullptr) throw std::runtime_error("List is empty");
        return head->data;
    }

    T FGetTail() const {
        if (head == nullptr) throw std::runtime_error("List is empty");
        SNode<T>* curr = head;
        while (curr->next != nullptr) curr = curr->next;
        return curr->data;
    }

    void FPrint() const {
        SNode<T>* curr = head;
        std::cout << "List: ";
        while (curr != nullptr) {
            std::cout << curr->data << " -> ";
            curr = curr->next;
        }
        std::cout << "nullptr\n";
    }

    void FClear() {
        SNode<T>* curr = head;
        while (curr != nullptr) {
            SNode<T>* next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
    }

    ~ForwardList() { FClear(); }

    ForwardList(const ForwardList& other) : head(nullptr) {
        SNode<T>* curr = other.head;
        while (curr != nullptr) { FPush(curr->data); curr = curr->next; }
    }

    ForwardList& operator=(const ForwardList& other) {
        if (this != &other) {
            FClear();
            SNode<T>* curr = other.head;
            while (curr != nullptr) { FPush(curr->data); curr = curr->next; }
        }
        return *this;
    }

    void SaveText(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        int count = 0;
        SNode<T>* curr = head;
        while (curr != nullptr) { count++; curr = curr->next; }
        file << count << "\n";
        curr = head;
        while (curr != nullptr) { file << curr->data << "\n"; curr = curr->next; }
    }

    bool LoadText(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        FClear();
        int count;
        if (count < 0 || count > 1000000) return false;

        if (!(file >> count)) return false;
        for (int i = 0; i < count; ++i) { T val; file >> val; FPush(val); }
        return true;
    }

    void SaveBin(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        int count = 0;
        SNode<T>* curr = head;
        while (curr != nullptr) { count++; curr = curr->next; }
        file.write(reinterpret_cast<const char*>(&count), sizeof(int));
        curr = head;
        while (curr != nullptr) {
            if constexpr (std::is_same_v<T, std::string>) {
                size_t len = curr->data.length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
                if (len > 0) file.write(curr->data.c_str(), len);
            } else {
                file.write(reinterpret_cast<const char*>(&curr->data), sizeof(T));
            }
            curr = curr->next;
        }
    }

    bool LoadBin(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) return false;
        FClear();
        int count;
        if (count < 0 || count > 1000000) return false;

        file.read(reinterpret_cast<char*>(&count), sizeof(int));
        if (!file) return false;
        for (int i = 0; i < count; ++i) {
            if constexpr (std::is_same_v<T, std::string>) {
                size_t len;
                file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
                T val(len, '\0');
                if (len > 0) file.read(&val[0], len);
                FPush(val);
            } else {
                T val;
                file.read(reinterpret_cast<char*>(&val), sizeof(T));
                FPush(val);
            }
        }
        return true;
    }
};