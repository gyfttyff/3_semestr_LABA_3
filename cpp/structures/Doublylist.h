#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <type_traits>

template <typename T>
struct DNode {
    T data;
    DNode* prev;
    DNode* next;
};

template <typename T>
class DoublyList {
private:
    DNode<T>* head;
    DNode<T>* tail;

public:
    DoublyList() : head(nullptr), tail(nullptr) {}

    void LInit() { LClear(); }

    void LPush(const T& val) {
        DNode<T>* newNode = new DNode<T>{val, tail, nullptr};
        if (tail != nullptr) tail->next = newNode;
        else head = newNode;
        tail = newNode;
    }

    void LPushHead(const T& val) {
        DNode<T>* newNode = new DNode<T>{val, nullptr, head};
        if (head != nullptr) head->prev = newNode;
        else tail = newNode;
        head = newNode;
    }

    void LPushBefore(const T& target, const T& val) {
        DNode<T>* curr = head;
        while (curr != nullptr && curr->data != target) curr = curr->next;
        if (curr != nullptr) {
            DNode<T>* newNode = new DNode<T>{val, curr->prev, curr};
            if (curr->prev != nullptr) curr->prev->next = newNode;
            else head = newNode;
            curr->prev = newNode;
        }
    }

    void LPushAfter(const T& target, const T& val) {
        DNode<T>* curr = head;
        while (curr != nullptr && curr->data != target) curr = curr->next;
        if (curr != nullptr) {
            DNode<T>* newNode = new DNode<T>{val, curr, curr->next};
            if (curr->next != nullptr) curr->next->prev = newNode;
            else tail = newNode;
            curr->next = newNode;
        }
    }

    void LDel(const T& val) {
        DNode<T>* curr = head;
        while (curr != nullptr && curr->data != val) curr = curr->next;
        if (curr != nullptr) {
            if (curr->prev != nullptr) curr->prev->next = curr->next;
            else head = curr->next;
            if (curr->next != nullptr) curr->next->prev = curr->prev;
            else tail = curr->prev;
            delete curr;
        }
    }

    void LDelHead() {
        if (head == nullptr) return;
        DNode<T>* toDelete = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        else tail = nullptr;
        delete toDelete;
    }

    void LDelTail() {
        if (tail == nullptr) return;
        DNode<T>* toDelete = tail;
        tail = tail->prev;
        if (tail != nullptr) tail->next = nullptr;
        else head = nullptr;
        delete toDelete;
    }

    void LDelBefore(const T& target) {
        DNode<T>* curr = head;
        while (curr != nullptr && curr->data != target) curr = curr->next;
        if (curr != nullptr && curr->prev != nullptr) {
            DNode<T>* toDelete = curr->prev;
            if (toDelete->prev != nullptr) toDelete->prev->next = curr;
            else head = curr;
            curr->prev = toDelete->prev;
            delete toDelete;
        }
    }

    void LDelAfter(const T& target) {
        DNode<T>* curr = head;
        while (curr != nullptr && curr->data != target) curr = curr->next;
        if (curr != nullptr && curr->next != nullptr) {
            DNode<T>* toDelete = curr->next;
            if (toDelete->next != nullptr) toDelete->next->prev = curr;
            else tail = curr;
            curr->next = toDelete->next;
            delete toDelete;
        }
    }

    T LGet(const T& val) const {
        DNode<T>* curr = head;
        while (curr != nullptr) {
            if (curr->data == val) return curr->data;
            curr = curr->next;
        }
        throw std::runtime_error("Element not found");
    }

    T LGetIdx(int index) const {
        DNode<T>* curr = head;
        int i = 0;
        while (curr != nullptr) {
            if (i == index) return curr->data;
            curr = curr->next; i++;
        }
        throw std::out_of_range("Index out of bounds");
    }

    T LGetHead() const {
        if (head == nullptr) throw std::runtime_error("List is empty");
        return head->data;
    }

    T LGetTail() const {
        if (tail == nullptr) throw std::runtime_error("List is empty");
        return tail->data;
    }

    void LPrint() const {
        DNode<T>* curr = head;
        std::cout << "DList: ";
        while (curr != nullptr) {
            std::cout << curr->data << " <-> ";
            curr = curr->next;
        }
        std::cout << "nullptr\n";
    }

    void LClear() {
        DNode<T>* curr = head;
        while (curr != nullptr) {
            DNode<T>* next = curr->next;
            delete curr;
            curr = next;
        }
        head = tail = nullptr;
    }

    ~DoublyList() { LClear(); }

    DoublyList(const DoublyList& other) : head(nullptr), tail(nullptr) {
        DNode<T>* curr = other.head;
        while (curr != nullptr) { LPush(curr->data); curr = curr->next; }
    }

    DoublyList& operator=(const DoublyList& other) {
        if (this != &other) {
            LClear();
            DNode<T>* curr = other.head;
            while (curr != nullptr) { LPush(curr->data); curr = curr->next; }
        }
        return *this;
    }

    void SaveText(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        int count = 0;
        DNode<T>* curr = head;
        while (curr != nullptr) { count++; curr = curr->next; }
        file << count << "\n";
        curr = head;
        while (curr != nullptr) { file << curr->data << "\n"; curr = curr->next; }
    }

    bool LoadText(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        LClear();
        int count;
        if (count < 0 || count > 1000000) return false;

        if (!(file >> count)) return false;
        for (int i = 0; i < count; ++i) { T val; file >> val; LPush(val); }
        return true;
    }

    void SaveBin(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        int count = 0;
        DNode<T>* curr = head;
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
        LClear();
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
                LPush(val);
            } else {
                T val;
                file.read(reinterpret_cast<char*>(&val), sizeof(T));
                LPush(val);
            }
        }
        return true;
    }
};