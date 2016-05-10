#include <iostream>
#include <chrono>
#include <cstdio>
using namespace std;

void swap(int &a, int &b)
{
    int c = a; a = b; b = c;
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void bubble_sort(int t[], int p, int k)
{
    int i = 0;
    while (i < k) {
        for (p = 0; p < k-1; p++) {
            if(t[p] > t[p+1]) //gdy lewy wiekszy od prawego to zamieniam swapem
                swap(t[p], t[p+1]);
        }
        i++;
    }
}

void merge(int *a, int *b, int p, int srodek, int k) {
    int h, i, j, m;
    h = p;
    i = p;
    j = srodek + 1;

    while ((h <= srodek) && (j <= k)) {     // etap sortowania
        if (a[h] <= a[j]) {
            b[i] = a[h];
            h++;
        }
        else {
            b[i] = a[j];
            j++;
        }
        i++;
    }

    if (h > srodek) {     //etap scalaniana na prawo od srodka
        for (m = j; m <= k; m++) {
            b[i] = a[m];
            i++;
        }
    }
    else { //na lewo od srodka
        for (m = h; m <= srodek; m++) {
            b[i] = a[m];
            i++;
        }
    }

    for (m = p; m <= k; m++) { //przepisuje posortowana tablice b do wejsciowej tablicy a
        a[m] = b[m];
    }
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int *t, int p, int k) {
    int srodek;
    int tab[k]; //pomocnicza tablica do sortowania i na koncu przepisywania
    if (p < k) {
        srodek = (p + k) / 2;
        merge_sort(t, p, srodek);
        merge_sort(t, srodek + 1, k);
        merge(t, tab, p, srodek, k);
    }
}


void test(int n)
{
    int t1[n], t2[n];

    for (int i = 0; i < n; i++) {
        t1[i] = t2[i] = rand();
    }

    cout << "Table size: " << n << endl;

    auto start = chrono::steady_clock::now();
    bubble_sort(t1, 0, n);
    auto end = chrono::steady_clock::now();

    auto diff_bubble = end - start;

    start = chrono::steady_clock::now();
    merge_sort(t2, 0, n);
    end = chrono::steady_clock::now();

    auto diff_merge = end - start;

    for (int i = 0; i < n - 1; i++) {
        if (t1[i] > t1[i + 1]) {
            cout << "  Wrong answer - bubble sort." << endl; break;
        }
        if (t2[i] > t2[i + 1]) {
            cout << "  Wrong answer - merge sort." << endl; break;
        }
    }

    cout << "  Bubble sort time: " << chrono::duration <double> (diff_bubble).count() << endl;
    cout << "  Merge sort time: " << chrono::duration <double> (diff_merge).count() << endl;
    cout << "  Ratio: " << (chrono::duration <double> (diff_bubble).count() / chrono::duration <double> (diff_merge).count()) << endl;
}

int main()
{
    test(100);
    test(1000);
    test(10000);
    test(20000);
    test(28000); //powyzej 28 tys. program "nieoczekiwanie" przestaje dzialac

}
