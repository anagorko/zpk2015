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
    int x;
    for(int i=p; i<k; i++)
        for(int j=p;j<k-i+p-1;j++)
            if(t[j]>t[j+1]){
                x=t[j];
                t[j]=t[j+1];
                t[j+1]=x;
            }
    
}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)
{
    if(k-1<=p) return;
    
    int srodek = (p+k-1)/2;
    merge_sort(t,p,srodek+1);
    merge_sort(t,srodek+1,k);
    
    
    int l;
    int pom[k];
    
  for(int i=p;i<k;i++) pom[i]=t[i];
    
   int i,j;
   i = p;
   j = srodek + 1;
    
    for (l=p;l<k;l++){
        if (i<=srodek)
            if(j < k)
                if(pom[j]<pom[i])
                    t[l] = pom[j++];
                 else
                    t[l] = pom[i++];
            else
                t[l] = pom[i++];
        else
             t[l] = pom[j++];
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
