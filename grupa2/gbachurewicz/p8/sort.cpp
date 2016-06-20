#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <cstdio>

using namespace std;

void merge (int *tab, int n, int lewy, int srodek, int prawy)
{
    int pom[n];
    for (int i=0; i < n; i++) //przepisujemy tab do pom
        pom[i] = tab[i];

    int i = lewy, j = srodek+1, k = lewy;

    while (i <= srodek && j <= prawy) {
        if (pom[i] <= pom[j]) {
            tab[k] = pom[i];
            i++;
        }
        else {
            tab[k] = pom[j];
            j++;
        }
        k++;
    }
    while (i <= srodek) {
        tab[k] = pom[i];
        k++;
        i++;
    }
}

void mergeSort (int *tab, int n, int lewy, int prawy)
{
    if (lewy < prawy) {
        int srodek = (lewy + prawy)/2;
        mergeSort(tab, n, lewy, srodek);
        mergeSort(tab, n, srodek+1, prawy);
        merge(tab, n, lewy, srodek, prawy);
    }
}

void swap (int &a, int &b)
{
    int c = a; a = b; b = c;
}

void quickSort (int *tab, int lewy, int prawy)
{
    int pivot = tab[(lewy + prawy)/2];
    int i = lewy, j = prawy;
    do {
        while (tab[i] < pivot) i++;
        while (tab[j] > pivot) j--;
        if (i <= j) {
            swap(tab[i], tab[j]);
            i++; j--;
        }
    } while (i <= j);
    if (j > lewy) quickSort(tab, lewy, j);
    if (i < prawy) quickSort(tab, i, prawy);
}

void bubbleSort (int *tab, int lewy, int prawy)
{
    for (int i=0; i<prawy; i++){
        for (int j = lewy; j < prawy; j++) {
            if (tab[j]> tab[j+1])
                swap(tab[j], tab[j+1]);
        }
    }
}

void test(int n)
{
    int t1[n], t2[n], t3[n];

    for (int i = 0; i < n; i++) {
        t1[i] = t2[i] = t3[i] = rand();
    }

    cout << "Table size: " << n << endl;

    auto start = chrono::steady_clock::now();
    bubbleSort(t1, 0, n-1);
    auto end = chrono::steady_clock::now();

    auto diff_bubble = end - start;

    start = chrono::steady_clock::now();
    mergeSort(t2, n, 0, n-1);
    end = chrono::steady_clock::now();

    auto diff_merge = end - start;

    start = chrono::steady_clock::now();
    quickSort(t3, 0, n-1);
    end = chrono::steady_clock::now();

    auto diff_quick = end - start;

    for (int i = 0; i < n - 1; i++) {
        if (t1[i] > t1[i + 1]) {
            cout << "  Wrong answer - bubble sort." << endl; break;
        }
        if (t2[i] > t2[i + 1]) {
            cout << "  Wrong answer - merge sort." << endl; break;
        }
        if (t3[i] > t3[i + 1]) {
            cout << "  Wrong answer - quick sort." << endl; break;
        }
    }

    cout << "  Bubble sort time: " << chrono::duration <double> (diff_bubble).count() << endl;
    cout << "  Merge sort time: " << chrono::duration <double> (diff_merge).count() << endl;
    cout << " Quick sort time: " << chrono::duration <double> (diff_quick).count() << endl;
    cout << "  Ratio Bubble/Merge: " << (chrono::duration <double> (diff_bubble).count() / chrono::duration <double> (diff_merge).count()) << endl;
    cout << "  Ratio Bubble/Quick: " << (chrono::duration <double> (diff_bubble).count() / chrono::duration <double> (diff_quick).count()) << endl;
}

int main()
{
    test(100);
    test(1000);
    test(10000);
    test(20000);
    test(30000);
    test(50000);
    test(100000);
}
