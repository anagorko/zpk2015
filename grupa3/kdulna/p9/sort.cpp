#include <iostream>
#include <chrono>
#include <cstdio>
#include <cstdlib>
using namespace std;

void swap(int &a, int &b)
{
    int c = a; a = b; b = c;
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void bubble_sort(int t[], int p, int k)
{
    int n = k;
    for (int j = p; j < k - 1; j++){
        for (int i = p; i < n - 1; i++){
            if (t[i] > t[i + 1]){
                swap (t[i], t[i + 1]);
            }
        }
        n--;
    }
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)
{
    if (k - p == 1){
        t[p] = t[p];
    }
    if (k - p > 1){
        int sr = (p + k) / 2;
        merge_sort(t, p, sr);
        merge_sort(t, sr, k);

        int p1 = p;
        int p2 = sr;

        int s[k - p];
        int i = 0;
        while (p1 < sr && p2 < k){
            if (t[p1] >= t[p2]){
                s[i] = t[p2];
                p2++;
            } else if (t[p1] < t[p2]){
                s[i] = t[p1];
                p1++;
            }
            i++;
        }

        if (i < k - p){
            if (p1 < sr){
                for (int j = i; j < k - p; j++)
                    s[j] = t[p1];
                    p1++;
            } else if (p2 < k){
                for (int j = i; j < k - p; j++)
                    s[j] = t[p2];
                    p2++;
            }
        }

        for (int z = p; z < k; z++){
            t[z] = s[z-p];
        }

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
