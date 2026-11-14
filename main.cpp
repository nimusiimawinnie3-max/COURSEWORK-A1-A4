#include <iostream>
#include <fstream>
#include <sstream>
#include "Sorts.h"
using namespace std;

void load(DynArray<Result>& a, string file) {
    ifstream in(file);
    string line;
    while (getline(in, line)) {          // read one whole line at a time
        if (line == "") continue;        // skip blank lines
        stringstream ss(line);           // lets us cut the line into pieces
        Result r;
        string m;
        getline(ss, r.RegNo, ',');       // read up to the first comma
        getline(ss, r.name, ',');        // then up to the next comma
        getline(ss, r.course, ',');
        getline(ss, m);                  // the rest of the line is the marks as text
        r.marks = stoi(m);               // convert the text to a number
        a.add(r);
    }
}

void save(DynArray<Result>& a, string file) {
    ofstream out(file);
    for (int i = 0; i < a.size(); i++) {
        Result r = a.raw()[i];
        out << r.RegNo << "," << r.name << "," << r.course << "," << r.marks << "\n";
    }
}

// prints every record in the array, one per line
void display(DynArray<Result>& a) {
    for (int i = 0; i < a.size(); i++) {          // go through each record
        Result r = a.raw()[i];                    // raw() gives access to the array itself
        cout << i + 1 << ". " << r.RegNo << " | " << r.name << " | "
             << r.course << " | " << r.marks << endl;
    }
}

int main() {
   DynArray<Result> a;
load(a, "results.txt");
cout << "Loaded " << a.size() << " records, capacity " << a.capacity() << endl;

cout << "\nBefore sorting:" << endl;
display(a);                                       // shows the 10 records as loaded

auto byReg = [](const Result& x, const Result& y) { return x.RegNo < y.RegNo; };
mergeSort(a.raw(), 0, a.size() - 1, byReg);

cout << "\nAfter sorting by registration number:" << endl;
display(a);//same records, now in order

    save(a, "results.txt");
    return 0;
}