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
int i = 0;
while (i < k) {


    for (p = 0; p < k-1; p++) {

    if(t[p] > t[p+1])
    swap(t[p], t[p+1]);

}

i++;

}
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)

{

    if (k - p > 1){
    
int i = 0;

int srodek = (p + k) / 2;
merge_sort(t, p, srodek);
merge_sort(t, srodek, k);

// wprowadzam pomocnicze zmienne

int a = p;
int b = srodek;
int s[k - p];

while (a < srodek && b < k){

    if (t[a] >= t[b]){
    s[i] = t[b];

    b++;
  }

    else if (t[a] < t[b]){
    s[i] = t[b];
    a++;
  }
i++;

}


    if (i < k - p){

    if (a < srodek){

    for (int j = i; j < k - p; j++)
    s[j] = t[a];
    a++;

  }
    else if (b < k){

    for (int j = i; j < k - p; j++)
    s[j] = t[b];
    b++;

  }

}

    for (int c = p; c < k; c++){
    t[c] = s[c-p];

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
