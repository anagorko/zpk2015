#include <iostream>
#include <chrono>
using namespace std;

void swap(int &a, int &b)
{
    int c = a; a = b; b = c;
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void bubble_sort(int t[], int p, int k)
{
    // DO ZAIMPLEMENTOWANIA
    for (int i=1; i<=k-p; i++)
    {
        for (int j=0; j=k-p-i; j++)
        {
            if(t[p+j] > t[p+j+1])
                swap(t[p+j], t[p+j+1]);
        }
    }
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)
{
    // DO ZAIMPLEMENTOWANIA
    int n[k-p+1];
    if (p<k)
    {
        int srodek = (p+k)/2;
        merge_sort(t, p, srodek);
        merge_sort(t, srodek + 1, k);
        int wskA=p, wskB=srodek+1;
        for (int i=0;i<k-p+1;i++)
        {
            if(wskA<=srodek && wskB<=k)
            {
                if(t[wskA]<=t[wskB])
                {
                    n[i] = t[wskA];
                    wskA++;
                }
                else
                {
                    n[i] = t[wskB];
                    wskB++;
                }
            }
            else if(wskA<=srodek && wskB>k)
            {
                n[i] = t[wskA];
                wskA++;
            }
            else if(wskA>srodek && wskB<=k)
            {
                n[i] = t[wskB];
                wskB++;
            }
        }
    }
    for (int i=p; i<=k; i++)
    {
        t[i] = n[i];
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
