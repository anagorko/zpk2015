#include <iostream>
#include <chrono>
using namespace std;

void swap(int &a, int &b)
{
	int c = a; a = b; b = c;
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void bubble_sort(int t[], int p, int k)				// sortowanie babelkowe 
{
	for (int i = p; i < k; i++) {
		int pomoc = 0;								// pomoc - mowi o tym ile elementow posortowanych omijamy
		for (int j = p; j < k - pomoc - 1; j++) {
			if (t[j] > t[j+1]) {
				swap(t[j],t[j+1]);
			}
		}
		pomoc++;
	}

}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)			   // sortowanie przez scalanie 
{
	if (k <= p) return;

	int s = (p + k) / 2;			

	merge_sort(t, p, s);		
	merge_sort(t, s + 1, k);

	int* tab = new int[k + 1];			

	for (int i = p; i <= k; i++)
		tab[i] = t[i];

	int i = p;				
	int j = s + 1;

	for (int l = p; l <= k; l++) {
		if (i <= s) {
			if (j <= k) {
				if (tab[i] < tab[j]) {	
					t[l] = tab[i];
					i++;		
				}
				else {
					t[l] = tab[j];
					j++;
				}
			}
			else {
				t[l] = tab[i];
				i++;
			}
		}
		else {
			t[l] = tab[j];
			j++;
		}
	}
	delete[] tab;
}

void test(int n)
{
	//int t1[n], t2[n];
	int* t1 = new int[n];
	int* t2 = new int[n];

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

	cout << "  Bubble sort time: " << chrono::duration <double>(diff_bubble).count() << endl;
	cout << "  Merge sort time: " << chrono::duration <double>(diff_merge).count() << endl;
	cout << "  Ratio: " << (chrono::duration <double>(diff_bubble).count() / chrono::duration <double>(diff_merge).count()) << endl;
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
