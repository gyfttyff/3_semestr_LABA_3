#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <type_traits>

template <typename T>
class Stack {
private:
    T* data;
    int top;
    int cap;

    void resize() {
        int newCap = (cap == 0) ? 1 : cap * 2;
        T* newData = new T[newCap];
        for (int i = 0; i <= top; ++i) newData[i] = data[i];
        delete[] data;
        data = newData;
        cap = newCap;
    }

public:
    Stack() : data(nullptr), top(-1), cap(0) {}

    void SInit(int initialCap = 1) {
        SClear();
        cap = initialCap;
        data = new T[cap];
        top = -1;
    }

    void SPush(const T& val) {
        if (top + 1 == cap) resize();
        data[++top] = val;
    }

    T SPop() {
        if (top == -1) throw std::runtime_error("Stack is empty");
        return data[top--];
    }

    T SPeek() const {
        if (top == -1) throw std::runtime_error("Stack is empty");
        return data[top];
    }

    void SPrint() const {
        std::cout << "Stack (top to bottom): ";
        for (int i = top; i >= 0; --i) std::cout << data[i] << " ";
        std::cout << "\n";
    }

    void SClear() {
        delete[] data;
        data = nullptr;
        top = -1;
        cap = 0;
    }

    ~Stack() { SClear(); }

    Stack(const Stack& other) : top(other.top), cap(other.cap) {
        data = new T[cap];
        for (int i = 0; i <= top; ++i) data[i] = other.data[i];
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            SClear();
            top = other.top; cap = other.cap;
            data = new T[cap];
            for (int i = 0; i <= top; ++i) data[i] = other.data[i];
        }
        return *this;
    }

    void SaveText(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        file << (top + 1) << "\n";
        for (int i = 0; i <= top; ++i) file << data[i] << "\n";
    }

    bool LoadText(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        SClear();
        int count;
        if (count < 0 || count > 1000000) return false;

        if (!(file >> count)) return false;
        SInit(count > 0 ? count : 1);
        for (int i = 0; i < count; ++i) { T val; file >> val; SPush(val); }
        return true;
    }

    void SaveBin(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        int count = top + 1;
        file.write(reinterpret_cast<const char*>(&count), sizeof(int));
        for (int i = 0; i <= top; ++i) {
            if constexpr (std::is_same_v<T, std::string>) {
                size_t len = data[i].length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
                if (len > 0) file.write(data[i].c_str(), len);
            } else {
                file.write(reinterpret_cast<const char*>(&data[i]), sizeof(T));
            }
        }
    }

    bool LoadBin(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) return false;
        SClear();
        int count;
        if (count < 0 || count > 1000000) return false;

        file.read(reinterpret_cast<char*>(&count), sizeof(int));
        if (!file) return false;
        SInit(count > 0 ? count : 1);
        for (int i = 0; i < count; ++i) {
            if constexpr (std::is_same_v<T, std::string>) {
                size_t len;
                file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
                T val(len, '\0');
                if (len > 0) file.read(&val[0], len);
                SPush(val);
            } else {
                T val;
                file.read(reinterpret_cast<char*>(&val), sizeof(T));
                SPush(val);
            }
        }
        return true;
    }
};