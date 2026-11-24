#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <type_traits>

template <typename T>
class Queue {
private:
    T* data;
    int head;
    int tail;
    int count;
    int cap;

    void resize() {
        int newCap = (cap == 0) ? 1 : cap * 2;
        T* newData = new T[newCap];
        for (int i = 0; i < count; ++i) {
            newData[i] = data[(head + i) % cap];
        }
        delete[] data;
        data = newData;
        head = 0;
        tail = count - 1;
        cap = newCap;
    }

public:
    Queue() : data(nullptr), head(0), tail(-1), count(0), cap(0) {}

    void QInit(int initialCap = 1) {
        QClear();
        cap = initialCap;
        data = new T[cap];
        head = 0; tail = -1; count = 0;
    }

    void QPush(const T& val) {
        if (count == cap) resize();
        tail = (tail + 1) % cap;
        data[tail] = val;
        count++;
    }

    T QPop() {
        if (count == 0) throw std::runtime_error("Queue is empty");
        T val = data[head];
        head = (head + 1) % cap;
        count--;
        return val;
    }

    T QPeek() const {
        if (count == 0) throw std::runtime_error("Queue is empty");
        return data[head];
    }

    void QPrint() const {
        std::cout << "Queue (front to back): ";
        for (int i = 0; i < count; ++i) {
            std::cout << data[(head + i) % cap] << " ";
        }
        std::cout << "\n";
    }

    void QClear() {
        delete[] data;
        data = nullptr;
        head = 0; tail = -1; count = 0; cap = 0;
    }

    ~Queue() { QClear(); }

    Queue(const Queue& other) : head(0), tail(other.count - 1), count(other.count), cap(other.cap) {
        data = new T[cap];
        for (int i = 0; i < count; ++i) data[i] = other.data[(other.head + i) % other.cap];
    }

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            QClear();
            count = other.count; cap = other.cap;
            data = new T[cap];
            head = 0; tail = count - 1;
            for (int i = 0; i < count; ++i) data[i] = other.data[(other.head + i) % other.cap];
        }
        return *this;
    }

    void SaveText(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        file << count << "\n";
        for (int i = 0; i < count; ++i) file << data[(head + i) % cap] << "\n";
    }

    bool LoadText(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
         if (count < 0 || count > 1000000) return false;
        QClear();
        int count;
        if (!(file >> count)) return false;
        QInit(count > 0 ? count : 1);
        for (int i = 0; i < count; ++i) { T val; file >> val; QPush(val); }
        return true;
    }

    void SaveBin(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        file.write(reinterpret_cast<const char*>(&count), sizeof(int));
        for (int i = 0; i < count; ++i) {
            T val = data[(head + i) % cap];
            if constexpr (std::is_same_v<T, std::string>) {
                size_t len = val.length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
                if (len > 0) file.write(val.c_str(), len);
            } else {
                file.write(reinterpret_cast<const char*>(&val), sizeof(T));
            }
        }
    }

    bool LoadBin(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) return false;
         if (count < 0 || count > 1000000) return false;
        QClear();
        int count;
        file.read(reinterpret_cast<char*>(&count), sizeof(int));
        if (!file) return false;
        QInit(count > 0 ? count : 1);
        for (int i = 0; i < count; ++i) {
            if constexpr (std::is_same_v<T, std::string>) {
                size_t len;
                file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
                T val(len, '\0');
                if (len > 0) file.read(&val[0], len);
                QPush(val);
            } else {
                T val;
                file.read(reinterpret_cast<char*>(&val), sizeof(T));
                QPush(val);
            }
        }
        return true;
    }
};