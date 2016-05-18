#include<chrono>
#include<cstdio>
#include<iostream>
using namespace std;

void swap(int & a, int & b) {
	int c = a; a = b; b = c;
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void bubble_sort(int t[], int p, int k) {
	for (int i = p; i < k - 1; ++i)
		for (int j = p; j < k - i - 1; ++j)
			if (t[j] > t[j + 1])
				swap(t[j], t[j + 1]);
}

// scala tablice
void merge_arrays(int t[], int p, int s, int k) {
	// zmienne pomocnicze
	int i = { p }, j = { s + 1 }, l = { p };

	// tablica pomocnicza
	int * pom = new int[k + 1];

	// scalanie
	while (i <= s && j <= k) {
		if (t[i] < t[j]) {
			pom[l] = t[i];
			++i;
		}
		else {
			pom[l] = t[j];
			++j;
		}
		++l;
	}

	// dopisanie pozostalych elementow
	while (i <= s) {
		pom[l] = t[i];
		++l;
		++i;
	}

	// dopisanie pozostalych elementow
	while (j <= k) {
		pom[l] = t[j];
		++l;
		++j;
	}

	// przepisanie tablicy pomocniczej do docelowej
	for (int m = p; m <= k; ++m)
		t[m] = pom[m];

	delete[] pom;
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k) {

	if (k == p)
		return;

	int s = (p + k) / 2;
	merge_sort(t, p, s);
	merge_sort(t, s + 1, k);
	merge_arrays(t, p, s, k);
}

void test(int n) {
	int * t1 = new int[n], * t2 = new int[n];

	for (int i = 0; i < n; i++) {
		t1[i] = t2[i] = rand();
	}

	cout << "Table size: " << n << endl;

	auto start = chrono::steady_clock::now();
	bubble_sort(t1, 0, n);
	auto end = chrono::steady_clock::now();

	auto diff_bubble = end - start;

	start = chrono::steady_clock::now();
	merge_sort(t2, 0, n - 1); // zmiana z n na n - 1
	end = chrono::steady_clock::now();

	auto diff_merge = end - start;

	for (int i = 0; i < n - 1; i++) {
		if (t1[i] > t1[i + 1]) {
			cout << "Wrong answer - bubble sort." << endl;
			break;
		}
		if (t2[i] > t2[i + 1]) {
			cout << "Wrong answer - merge sort." << endl;
			break;
		}
	}

	cout << "Bubble sort time: " << chrono::duration <double>(diff_bubble).count() << endl;
	cout << "Merge sort time: " << chrono::duration <double>(diff_merge).count() << endl;
	cout << "Ratio: " << (chrono::duration <double>(diff_bubble).count() / chrono::duration <double>(diff_merge).count()) << endl;

	delete[] t1;
	delete[] t2;
}

int main() {
	test(100);
	test(1000);
	test(10000);
	test(20000);
	test(30000);
	test(50000);
	test(100000);
}
