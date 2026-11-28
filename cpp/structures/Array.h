

#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <type_traits>

template <typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;

    void resize() {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; ++i) newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Array() : data(nullptr), size(0), capacity(0) {}

    void MInit(int initialCapacity = 1) {
        if (data != nullptr) delete[] data;
        capacity = initialCapacity;
        size = 0;
        data = new T[capacity];
    }

    void MPush(const T& val) {
        if (size == capacity) resize();
        data[size++] = val;
    }

    void MPushIdx(int index, const T& val) {
        if (index < 0 || index > size) throw std::out_of_range("Index out of bounds");
        if (size == capacity) resize();
        for (int i = size; i > index; --i) data[i] = data[i - 1];
        data[index] = val;
        size++;
    }

    T MGet(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    void MDelInd(int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of bounds");
        for (int i = index; i < size - 1; ++i) data[i] = data[i + 1];
        size--;
    }

    int MLen() const { return size; }

    void MPrint() const {
        std::cout << "Array [" << size << "]: ";
        for (int i = 0; i < size; ++i) std::cout << data[i] << " ";
        std::cout << "\n";
    }

    void MClear() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    ~Array() { delete[] data; }

    // глубокая копия объекта конструктор

    Array(const Array& other) : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }

    // Оператор присваивания объектов (массивов)

    Array& operator=(const Array& other) {
        if (this != &other) {// Защита от самоприсваивания одного массива (адрес конкретного объекта который вызвал этот оператор)
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; ++i) data[i] = other.data[i];
        }
        return *this;
    }

    //СЕРИАЛИЗАЦИЯ     

    void SaveText(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Cannot open file for writing: " + filename);
        file << size << "\n";
        for (int i = 0; i < size; ++i) file << data[i] << "\n";
    }

    bool LoadText(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        int newSize;
        if (!(file >> newSize)) return false;  // Не удалось прочитать размер
        if (newSize < 0 || newSize > 1000000) return false;
        MClear();
        MInit(newSize > 0 ? newSize : 1);
        for (int i = 0; i < newSize; ++i) {
            T val;
            file >> val;
            MPush(val);
        }
        return true;
    }

    void SaveBin(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) throw std::runtime_error("Cannot open file for writing: " + filename);
        file.write(reinterpret_cast<const char*>(&size), sizeof(int)); // открываем поток записи по длине сайз и размером байтов для интов 
        for (int i = 0; i < size; ++i) {
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
        int newSize;
        // Читаем размер
        file.read(reinterpret_cast<char*>(&newSize), sizeof(int));
        if (!file) return false;
        if (newSize < 0 || newSize > 1000000) return false;
        MClear();
        MInit(newSize > 0 ? newSize : 1);
        for (int i = 0; i < newSize; ++i) {
            if constexpr (std::is_same_v<T, std::string>) {
                size_t len;
                file.read(reinterpret_cast<char*>(&len), sizeof(size_t)); 
                T val(len, '\0');
                if (len > 0) file.read(&val[0], len);             // Читаем блок памяти напрямую в наш массив
                MPush(val);
            } else {
                T val;
                file.read(reinterpret_cast<char*>(&val), sizeof(T));
                MPush(val);
            }
        }
        return true;
    }
};