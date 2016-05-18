#include <iostream>
#include <chrono>
#include <cstdio>
#include <cstdlib>
using namespace std;

void swap(int & a, int & b) {
	int c = a; a = b; b = c;
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void bubble_sort(int t[], int p, int k) {
	for (int j = p; j < k; j++)
		for (int i = p; i < k - j - 1; i++){
			if (t[i + 1] < t[i] ){
				swap(t[i], t[i + 1]);
			}
		}
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)
{
    // DO ZAIMPLEMENTOWANIA
    if (p == k){
        return;
    }
    if ( p < k){

	int sr = (p + k) / 2;
	merge_sort(t, p, sr);
	merge_sort(t, sr + 1, k);

	int podz1 = p;
	int podz2 = sr+1;
	int tab[k - p];

	for (int i=0;i<k-p+1;i++){
        if(podz1<=sr && podz2<=k){
            if(t[podz1]<=t[podz2]){
                tab[i] = t[podz1];
                podz1++;
            }
                else{
                    tab[i] = t[podz2];
                    podz2++;
                }
            }
            else if(podz1<=sr && podz2>k){
                tab[i] = t[podz1];
                podz1++;
            }
            else if(podz1>sr && podz2<=k){
                tab[i] = t[podz2];
                podz2++;
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
