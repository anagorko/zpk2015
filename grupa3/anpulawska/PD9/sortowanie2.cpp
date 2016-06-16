#include <iostream>
#include <chrono>
#include <cstdio>
#include <cstdlib>
using namespace std;

void swap(int &a, int &b)
{
    int c = a; a = b; b = c;
}

void scal(int t[],int pom[], int p, int s, int k)
{
    int i, j;
    for(i = s + 1; i>p; i--)
        pom[i-1] = t[i-1];

    for(j = s; j<k; j++)
        pom[k+s-j] = t[j+1];

    for(int l=p; l<=k; l++)
        if(pom[j]<pom[i])
            t[l] = pom[j--];
        else
            t[l] = pom[i++];
}

void sortuj (int t[],int pom[], int p, int k)
{
    if (k<=p) return;

    int s = (p+k)/2;

    sortuj(t, pom, p, s);
    sortuj(t,pom, s+1, k);

    scal(t, pom, p, s, k);
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void bubble_sort(int t[], int p, int k)
{
     for (int i = p; i < k; i++)
    {
        for (int j= p+1; j< k - i; j++)
            if(t[j-1] > t[j])
            swap(t[j-1],t[j]);
    }
}
// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)
{
    int *pom = new int [k];
    k--;
    sortuj(t, pom, p, k);
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
