#include <iostream>
#include <chrono>
#include <cstdio>
using namespace std;

void swap(int &a, int &b)
{
    int c = a; a = b; b = c;
}

void bubble_sort(int t[], int p, int k)
{
    for( int i=0; i < k; i++ )
    {
        for( int p=0; p<k-1; p++ )
        {
            if( t[p] > t[p+1] )
                 swap(t[p], t[p+1]);
        }
    }
}

void merge(int t[], int m, int p, int sr, int k)
{
    int i, j, l, u[m];
    for (i=p; i<=k; i++)
        u[i] = t[i];
    i = p;
    j = sr+1;
    l = p;
    while (i<=sr && j<=k)
    {
        if (u[i]<u[j])
                t[l++]=u[i++];
        else
                t[l++]=u[j++];
    }
    while (i<=sr)
       t[l++] = u[i++];
    for (i = p; i <= k; i++) cout << t[i] << " ";
    cout << endl;
}


void merge_sort(int t[], int p, int k)
{
    int u[k];
    int sr;
    if (p<k)
    {
        sr=(p+k)/2;
        merge_sort(t, p, sr);
        merge_sort(t, sr+1, k);
        merge(t, u, p, sr, k);
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
