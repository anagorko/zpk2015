#include<iostream>
#include <vector>
#include <cmath>
using namespace std;

int zapytanie_predkosc(vector<int> tablica, int zapytanie){
    int start = 0;
    int end = tablica.size() - 1;
    int mid;
    int poczatek = -1;

    while (start < end){
        mid = (start + end)/2;
        if (tablica[mid] >= zapytanie)
            end = mid;
        else
            start = mid + 1;
    }

    if(tablica[start] == zapytanie)
        poczatek = start;

    int start2 = 0;
    int end2 = tablica.size() - 1;
    int mid2;
    int koniec = -1;

    while (start2 < end2){
        mid2 = (start2 + end2 + 1)/2;
        if (tablica[mid2] <= zapytanie)
            start2 = mid2;
        else
            end2 = mid2 - 1;
    }

    if(tablica[end2] == zapytanie)
        koniec = end2;

    if(poczatek == -1 && koniec == -1)
        return 0;
    else
        return koniec - poczatek + 1;
}

int main(){
    vector<int> tablica;
    int liczba_pomiarow;
    cin >> liczba_pomiarow;

    for(int i = 0;i < liczba_pomiarow;i++){
        int pomiar;
        cin >> pomiar;
        tablica.push_back(pomiar);
    }

    int liczba_zapytan;
    cin >> liczba_zapytan;
    vector<int> wystapienia;

    for(int j = 0; j < liczba_zapytan;j++){
        int zapytanie;
        cin >> zapytanie;
        wystapienia.push_back(zapytanie_predkosc(tablica, zapytanie));
    }

    for(int k = 0;k < liczba_zapytan;k++)
        cout << wystapienia[k] << endl;
};
