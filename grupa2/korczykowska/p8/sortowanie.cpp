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
    for( int i = p; i < k; i++ )
    {
        for( int j = i+1; j < k; j++ )
        {
            if( t[ j ] > t[ j + 1 ] )
                 swap( t[ j+1 ], t[ j ] );

        }
    }
}

//potrzeba instrukcji, ktora w odpowiedni sposob bedzie
//scalac po kolei elementy kazdych dwoch skladowych tablicy


// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)
{
//"rekurencyjnie"
//dziele na dwie tablice po polowie, kazda z nich sortuje
//a potem je odpowiednio scalam robiąc porównania

int pol = (p+k)/2;
    merge_sort(t, p, pol);
    merge_sort(t, pol+1, k);
//potrzeba instrukcji, ktora w odpowiedni sposob bedzie
//scalac po kolei elementy kazdych dwoch skladowych tablicy

    //tabela pomocnicza
    int tab[k-p];
    int a = p;
    int b = pol+1;

    for (int i=0; i<k-p+1; i++){
            {
            if(a=pol && b<=k)
            {
                if(t[a]<=t[b])
                {
                    tab[i] = t[a];
                    a++;
                }
                else
                {
                    tab[i] = t[b];
                    b++;
                }
            }
            else if(a>pol && b<=k)
            {
                tab[i] = t[b];
                b++;
            }

            else if(a<=pol && b>k-1)
            {
                tab[i] = t[a];
                a++;
            }

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
