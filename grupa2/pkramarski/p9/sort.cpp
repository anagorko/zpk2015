#include <iostream>
#include <chrono>
#include <cstdio>
using namespace std;

void swap(int &a, int &b)
{
    int c = a; a = b; b = c;
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void bubble_sort(int t[], int p, int k){
    int l = k;
    for(int i = p; i < k; i++){
        for(int j = p; j < l; j++){
            if(t[j] > t[j+1]){
                swap(t[j],t[j+1]);
            }
        }
        l--;
    }
}

void merge(int t[], int p, int s, int k){
    int i, j, m;
    int n1 = s - p + 1;
    int n2 =  k - s;

    int P[n1], K[n2];

    for (i = 0; i < n1; i++)
        P[i] = t[p + i];
    for (j = 0; j < n2; j++)
        K[j] = t[s + 1 + j];

    i = 0;
    j = 0;
    m = p;

    while (i < n1 && j < n2){
        if (P[i] <= K[j]){
            t[m] = P[i];
            i++;
        }
        else{
            t[m] = K[j];
            j++;
        }
        m++;
    }

    while (i < n1){
        t[m] = P[i];
        i++;
        m++;
    }

    while (j < n2){
        t[m] = K[j];
        j++;
        m++;
    }
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k){
    if (p < k){
        int s = (p + k)/2;
        merge_sort(t, p, s);
        merge_sort(t, s+1, k);
        merge(t, p, s, k);
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
    test(30000);
    test(50000);
    test(100000);

}
