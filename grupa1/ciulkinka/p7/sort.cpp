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
    for (int j = p + 1; j < k - p; j++)
    {
        for (int i = p + 1; i < k - p; i++)
        {
            if (t[i-1] < t[i])
                swap(t[i], t[i-1]);
        }
    }
}

// scalanie 2 posortowanych fragmentow tablicy
void scal(int t[], int pocz, int sro, int kon)
{
    int licz1 = 0;
    int licz2 = 0;

    cout << endl << "1" << endl;
    int temp1[sro - pocz];
    int temp2[kon - sro];

    cout << "2"  << endl;
    // zapelniam tablice pomocnicze
    for (int i = 0; i < sro; i++)
    {
        temp1[i] = t[pocz + i];
    }
    for (int i = 0; i < kon - sro + 1; i++)
    {
        temp2[i] = t[sro + i];
    }

    while(licz1 < (sro - pocz) && licz2 < (kon - sro))
    {
        if(pocz + licz1 >= sro) //jesli pierwszy zbior skonczony, doklej caly drugi i zakoncz petle
        {
            while(sro + licz2 < kon)
            {
                t[pocz + licz1 + licz2] = temp2[licz2];
                licz2++;
            }
            break;
        } else if(sro + licz2 >= kon) //jesli drugi zbior skonczony, doklej caly pierwszy i zakoncz petle
        {
            while(pocz + licz1 < sro)
            {
                t[pocz + licz1 + licz2] = temp1[licz1];
                licz1++;
            }
            break;
        }

        // sprawdz co jest wieksze i wrzuc do zbioru
        if (temp1[licz1] <= temp2[licz2])
        {
            t[pocz + licz1 + licz2] =  temp1[licz1];
            licz1++;
        } else
        {
            t[pocz + licz1 + licz2] = temp2[licz2];
            licz2++;
        }

        cout << "licz1 = " << licz1 << endl;
        cout << "   licz2 = " << licz2 << endl;
    }
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)
{
    int s = (k - p) / 2;

    cout << "asd ";

    merge_sort(t, p, s);
    merge_sort(t, s, k);
    scal(t, p, s, k);
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

    cout << "bubble zrobiem" << endl;

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
