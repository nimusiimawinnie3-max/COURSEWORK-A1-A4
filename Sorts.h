#pragma once
#include "ResultArray.h"

template <typename T, typename Cmp>
void insertionSort(T a[], int n, Cmp cmp) {
    for (int i = 1; i < n; i++) {
        T key = a[i];
        int j = i - 1;
        while (j >= 0 && cmp(key, a[j])) {   // strict, so it stays stable
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

template <typename T, typename Cmp>
void mergeSort(T a[], int lo, int hi, Cmp cmp) {
    if (lo >= hi) return;
    int mid = (lo + hi) / 2;
    mergeSort(a, lo, mid, cmp);
    mergeSort(a, mid + 1, hi, cmp);

    T* tmp = new T[hi - lo + 1];
    int i = lo, j = mid + 1, k = 0;
    while (i <= mid && j <= hi)
        tmp[k++] = cmp(a[j], a[i]) ? a[j++] : a[i++];   // ties take the left one
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= hi) tmp[k++] = a[j++];
    for (k = 0; k < hi - lo + 1; k++) a[lo + k] = tmp[k];
    delete[] tmp;
}

int binarySearch(Result a[], int n, const string& key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (a[mid].RegNo == key) return mid;
        if (a[mid].RegNo < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}