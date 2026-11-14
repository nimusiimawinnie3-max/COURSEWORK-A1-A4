#include <iostream>
#include "Sorts.h"

void check(string id, bool pass) {
    cout << id << ": " << (pass ? "PASS" : "FAIL") << endl;
}

int main() {
    DynArray<Result> a;
    Result r;

    // T1: empty array
    check("T1 empty size is 0", a.size() == 0);
    check("T2 get on empty returns false", !a.get(0, r));
    check("T3 removeAt on empty returns false", !a.removeAt(0));

    // T4: one record
    a.add({"VU-001", "Ann", "Java", 70});
    check("T4 one record size is 1", a.size() == 1);

    // T5: growth (capacity starts at 4)
    for (int i = 2; i <= 5; i++) a.add({"VU-00" + to_string(i), "S", "Java", 50});
    check("T5 capacity doubled to 8", a.capacity() == 8);

    // T6: remove first and last
    check("T6 remove first", a.removeAt(0) && a.size() == 4);
    check("T7 remove last", a.removeAt(a.size() - 1) && a.size() == 3);
    check("T8 invalid position -1", !a.removeAt(-1));

    // T9: sorting
    auto byMarks = [](const Result& x, const Result& y) { return x.marks < y.marks; };
    DynArray<Result> b;
    b.add({"A", "x", "c", 30});
    b.add({"B", "y", "c", 20});
    b.add({"C", "z", "c", 20});   // duplicate marks
    insertionSort(b.raw(), b.size(), byMarks);
    check("T9 sorted ascending", b.raw()[0].marks == 20 && b.raw()[2].marks == 30);
    check("T10 stable: B before C", b.raw()[0].RegNo == "B" && b.raw()[1].RegNo == "C");

    // T11: already sorted and reversed input with merge sort
    mergeSort(b.raw(), 0, b.size() - 1, byMarks);
    check("T11 already sorted stays sorted", b.raw()[0].marks == 20 && b.raw()[2].marks == 30);

    // T12: binary search
    auto byReg = [](const Result& x, const Result& y) { return x.RegNo < y.RegNo; };
    mergeSort(b.raw(), 0, b.size() - 1, byReg);
    check("T12 search present key", binarySearch(b.raw(), b.size(), "B") == 1);
    check("T13 search absent key", binarySearch(b.raw(), b.size(), "ZZZ") == -1);

    // T14: deep copy
    DynArray<Result> c = b;
    c.removeAt(0);
    check("T14 copy is independent", b.size() == 3 && c.size() == 2);

    return 0;
}