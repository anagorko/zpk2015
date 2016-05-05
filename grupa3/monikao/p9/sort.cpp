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
    for(int i = p; i < k; i++ ){
        for(int j = p; j < k-1; j++){
            if(t[j] > t[j+1]){
                swap(t[j], t[j+1]);
            }
        }


    }
}

void merge_arrays( int *t3, int *t1, int *t2, int len1, int len2){
    /*zmienne pomocnicze*/
    int j=0, k=0;
    /*³¹czymy 2 tablice u¿ywaj¹c wskaŸników na nich
      a¿ skoñcz¹ siê wyrazy w jednej z tablic*/
    while(j < len1 && k < len2){

        if(*t1 < *t2){
            *t3 = *t1;
            t1++;
            t3++;
            j++;
        }else{
            *t3 = *t2;
            t2++;
            t3++;
            k++;
        }
    }
    /*je¿eli nie wpisaliœmy wszystkich wyrazów z tablicy 1, uzupe³niamy t3 tymi wyrazami*/
    while(j< len1){
        *t3 = *t1;
        t1++;
        t3++;
        j++;
    }
    /*je¿eli nie wpisaliœmy wszystkich wyrazów z tablicy 2, uzupe³niamy t3 tymi wyrazami*/
    while(k< len2){
        *t3 = *t2;
        t2++;
        t3++;
        k++;
    }

}

// sortuje t[p] .. t[k - 1] - bez t[k] !
void merge_sort(int t[], int p, int k)
{
    /*tablicê dzielimy na 2 tablice o wymiarach (k-p)/2 oraz (k-p) - (k-p)/2 */
    int wym1 = (k-p)/2;
    int wym2 = (k - p) - wym1;

    int tab1[wym1];
    int tab2[wym2];
    for(int i = 0; i< wym1; i++){
        tab1[i] = t[i];
        tab2[i] = t[i+wym1];
    }
    if(wym2>wym1){
        tab2[wym2-1] = t[k-1];
    }

    /*je¿eli wym1 > 1, to sortujemy tab 1 funkcj¹, jeœli = 1, to tab1 = tab1 */
    if(wym1 > 1){
        merge_sort(tab1, 0, wym1);
    }
    /*analogicznie z tab2*/
    if(wym2 > 1){
        merge_sort(tab2, 0, wym2);
    }
    /*¿eby wykorzystaæ funkcjê merge_arrays, twrzymy wskaŸniki do tabel*/
    int *t1 = tab1;
    int *t2 = tab2;

    int *t3 = t;
    /*merge arrays*/
    merge_arrays(t3, t1, t2, wym1, wym2);


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

    for (int i = 0; i < n -1; i++) {
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

    test(10);
    test(1000);
    test(1000);
    test(10000);
    test(20000);
    test(30000);
    test(50000);
    test(100000);
}
