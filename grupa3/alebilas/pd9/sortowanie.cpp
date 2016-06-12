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
    for (int i=p; i<k; i++){
		for (int j=p; j<k-i+p-1; j++){
			if(t[j]>t[j+1]){
				swap(t[j], t[j+1]);
			}
		}
	}
}

void merge_main(int t[], int p, int midpoint, int k){
	// Nowa tablica do posortowanych liczb
	int *wsk = new int[p - k + 1];
	
	int i = p;
	int j = midpoint + 1;
	int m = 0;
	
	while(i <= midpoint && j <= k){
		if(t[i] > t[j]){
			wsk[m] = t[j];
			j++;
		}
		else{
			wsk[m] = t[i];
			i++;
		}
	m++;	
	}
	
	if(i <= midpoint){
		while(i <= midpoint){
			wsk[m] = t[i];
			i++;
			m++;
		}
	}
	else{
		while(j <= k){
			wsk[m] = t[j];
			j++;
			m++;
		}
	}
	
	for(i = 0; i<= k - p; i++)
		t[p + i] = wsk[i];
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)
{
	// podzial tablicy na dwie mniejsze
    int midpoint = (k + p)/2;
	
	if (p==k) return;
	if (p!=k){
		merge_sort(t, p, midpoint);
		merge_sort(t, midpoint + 1, k);
		merge_main(t, p, midpoint, k);
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
