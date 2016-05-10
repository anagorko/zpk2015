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

for( int i = 0; i < k ; i++ )
    {
        for( int j = 0; j < k - 1; j++ )
        {
            if( t[ j ] > t[ j + 1 ] )
                 swap( t[ j ], t[ j + 1 ] );
        }
    }
return;
}

void merge(int t[], int p, int s, int k)
{
int *tpom = new int[(k-p+1)];
int i = p, j = s+1, l = 0;

while (i <= s && j <= k)
{
    if (t[j] < t[i])
    {
        tpom[l] = t[j];
        j++;
    }
    else
    {
        tpom[l] = t[i];
        i++;
    }
l++;
}
if (i <= s)
{
    while (i <= s)
    {
        tpom[l] = t[i];
        i++;
        l++;
    }
}
else
{
    while (j <= k)
    {
        tpom[l] = t[j];
        j++;
        l++;
    }
}

for (i = 0; i <= k-p; i++)
t[p+i] = tpom[i];

}
// sortuje t[p] .. t[k - 1] - bez t[k] !

void merge_sort(int t[], int p, int k)
{
    int s;
    if (p==k)
        return;
    if (p != k)
    {
        s = (p + k)/2;
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
