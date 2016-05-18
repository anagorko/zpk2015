#include <iostream>
#include <chrono>
#include <cstdio>
#include<stdlib.h>

using namespace std;

void swap(int &a, int &b)
{
    int c = a; a = b; b = c;
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void bubble_sort(int t[], int p, int k)
{
    int z=1;
    for (int i=p; i<k-1; i++)
    {
        for(int a=p; a<k-z; a++)
        {
            if (t[a]>t[a+1])
            {
                swap(t[a],t[a+1]);
            }
        }
        z++;
    }
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)
{
    if(k-p==1)
    {
        return;
    }

    int srodek = (k+p)/2;
    merge_sort(t, p, srodek);
    merge_sort(t, srodek, k);

    int nowa_tablica[k-p];
    int pierwszy=p;
    int drugi=srodek;
    int trzeci=0;
    while (pierwszy < srodek || drugi < k)
    {
        if(pierwszy == srodek) // pierwsza sie juz skonczyla
        {
            nowa_tablica[trzeci]=t[drugi];
            drugi++;
        }
        else if (drugi == k) // druga sie juz skonczyla
        {
            nowa_tablica[trzeci] = t[pierwszy];
            pierwszy++;
        }
        // zadna sie nie skonczyla jeszcze
        else if(t[pierwszy] < t[drugi])
        {
            nowa_tablica[trzeci] = t[pierwszy];
            pierwszy++;
        }
        else
        {
            nowa_tablica[trzeci]=t[drugi];
            drugi++;
        }
        trzeci++;
    }
    int j=0;
    for(int i=p;i<k;i++)
    {
        t[i]=nowa_tablica[j];
        j++;
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

    cout << "  Bubble sort time: " << chrono::duration<double>(diff_bubble).count() << endl;
    cout << "  Merge sort time: " << chrono::duration<double>(diff_merge).count() << endl;
    cout << "  Ratio: " << (chrono::duration<double>(diff_bubble).count() / chrono::duration<double>(diff_merge).count()) << endl;
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
