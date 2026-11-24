#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

class HashTable {
private:
    std::string* table;
    int* state;
    int capacity;

    int hash(const std::string& key) const {
        unsigned long h = 0;
        for (char c : key) {
            h = (h * 31 + c);
        }
        return (h % capacity + capacity) % capacity;
    }

public:
    HashTable() : table(nullptr), state(nullptr), capacity(0) {}

    void HInit(int cap = 11) {
        HClear();
        capacity = cap;
        table = new std::string[capacity];
        state = new int[capacity];
        for (int i = 0; i < capacity; i++) state[i] = 0;
    }

    void add(const std::string& key) {
        int idx = hash(key);
        while (state[idx] == 1) {
            if (table[idx] == key) return;
            idx = (idx + 1) % capacity;
        }
        table[idx] = key;
        state[idx] = 1;
    }

    bool contains(const std::string& key) const {
        int idx = hash(key);
        int startIdx = idx;
        while (state[idx] != 0) {
            if (state[idx] == 1 && table[idx] == key) return true;
            idx = (idx + 1) % capacity;
            if (idx == startIdx) break;
        }
        return false;
    }

    void remove(const std::string& key) {
        int idx = hash(key);
        int startIdx = idx;
        while (state[idx] != 0) {
            if (state[idx] == 1 && table[idx] == key) {
                state[idx] = 2;
                return;
            }
            idx = (idx + 1) % capacity;
            if (idx == startIdx) break;
        }
    }

    void print() const {
        std::cout << "HashTable: ";
        for (int i = 0; i < capacity; i++) {
            if (state[i] == 1) std::cout << "[" << i << ":" << table[i] << "] ";
        }
        std::cout << "\n";
    }

    void HClear() {
        delete[] table;
        delete[] state;
        table = nullptr;
        state = nullptr;
        capacity = 0;
    }

    ~HashTable() { HClear(); }

    HashTable(const HashTable& other) : capacity(other.capacity) {
        table = new std::string[capacity];
        state = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = other.table[i];
            state[i] = other.state[i];
        }
    }

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            HClear();
            capacity = other.capacity;
            table = new std::string[capacity];
            state = new int[capacity];
            for (int i = 0; i < capacity; i++) {
                table[i] = other.table[i];
                state[i] = other.state[i];
            }
        }
        return *this;
    }

    void SaveText(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        file << capacity << "\n";
        for (int i = 0; i < capacity; i++) {
            file << state[i] << "\n";
            if (state[i] == 1) file << table[i] << "\n";
        }
    }

    bool LoadText(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        HClear();
        int cap;
        if (cap < 0 || cap > 1000000) return false;

        if (!(file >> cap)) return false;
        HInit(cap);
        for (int i = 0; i < capacity; i++) {
            file >> state[i];
            if (state[i] == 1) file >> table[i];
        }
        return true;
    }

    void SaveBin(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) throw std::runtime_error("Cannot open file");
        file.write(reinterpret_cast<const char*>(&capacity), sizeof(int));
        file.write(reinterpret_cast<const char*>(state), capacity * sizeof(int));
        for (int i = 0; i < capacity; i++) {
            if (state[i] == 1) {
                size_t len = table[i].length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
                if (len > 0) file.write(table[i].c_str(), len);
            }
        }
    }

    bool LoadBin(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) return false;
        HClear();
        int cap;
        if (cap < 0 || cap > 1000000) return false;

        file.read(reinterpret_cast<char*>(&cap), sizeof(int));
        if (!file) return false;
        HInit(cap);
        file.read(reinterpret_cast<char*>(state), capacity * sizeof(int));
        for (int i = 0; i < capacity; i++) {
            if (state[i] == 1) {
                size_t len;
                file.read(reinterpret_cast<char*>(&len), sizeof(size_t));
                std::string val(len, '\0');
                if (len > 0) file.read(&val[0], len);
                table[i] = val;
            }
        }
        return true;
    }
};