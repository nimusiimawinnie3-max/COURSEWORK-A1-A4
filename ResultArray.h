#pragma once
#include <string>
using namespace std;

struct Result {
    string RegNo, name, course;
    int marks;
};

template <typename T>
class DynArray { //heap
    T* data;
    int count, cap;

    void grow() {                      // double the capacity
        cap *= 2;
        T* bigger = new T[cap];
        for (int i = 0; i < count; i++) bigger[i] = data[i];
        delete[] data;
        data = bigger;
    }

public:
    DynArray() { count = 0; cap = 4; data = new T[cap]; }

    DynArray(const DynArray& o) {      // deep copy
        count = o.count;
        cap = o.cap;
        data = new T[cap];
        for (int i = 0; i < count; i++) data[i] = o.data[i];
    }

    DynArray& operator=(const DynArray&) = delete;   // stops accidental shallow copies

    ~DynArray() { delete[] data; }

    void add(const T& x) {
        if (count == cap) grow();
        data[count++] = x;
    }

    bool removeAt(int p) {
        if (p < 0 || p >= count) return false;       // invalid, no crash
        for (int i = p; i < count - 1; i++) data[i] = data[i + 1];
        count--;
        return true;
    }

    bool get(int p, T& out) const {
        if (p < 0 || p >= count) return false;
        out = data[p];
        return true;
    }

    T* raw() { return data; }
    int size() const { return count; }
    int capacity() const { return cap; }
};