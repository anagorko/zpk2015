#include <iostream>
#include <math.h>

using namespace std;

int szukaj_poczatek(int predkosci[], int gr_dol, int gr_gor, int element){
    int x = (gr_gor + gr_dol) / 2;
    while(predkosci[x] != element || predkosci[x-1] == predkosci[x]){
        if(gr_dol <= gr_gor && predkosci[gr_dol]!= element)
            return -1;

        if(predkosci[x] < element){
            gr_dol = x;
        }else{
            /*czyli kiedy predkosci[x] > element || predkosci[x] == element, ale nadal nie jest to poczatek ciagu*/
            gr_gor = x;
        }
        x = (gr_gor + gr_dol) / 2;

    }
    return x;

}

int szukaj_koniec(int predkosci[], int gr_dol, int gr_gor, int element){
    int x = (gr_gor + gr_dol) / 2;
    while(predkosci[x] != element || predkosci[x+1] == predkosci[x]){
        if(predkosci[x] > element){
            gr_gor = x;
        }else{
            /*czyli kiedy predkosci[x] < element || predkosci[x] == element, ale nadal nie jest to koniec ciagu*/
            gr_dol = x;
        }
        x = (gr_gor + gr_dol) / 2;

        if(gr_gor <= gr_dol)
            return -1;
        if(x== gr_dol && (gr_gor - gr_dol)==1)
            if(predkosci[gr_gor] == element)
                return gr_gor;
            else
                return gr_dol;
    }
    return x;
}

int main() {
    int ile_czastek;
    cin >> ile_czastek;
    /*tablica z predkosciami czastek*/
    int predkosci[ile_czastek];
    /*pobieranie danych wej�cia, uzupelniamy predkosci*/
    for(int i = 0; i < ile_czastek; i++){
        cin >> predkosci[i] ;
    }

    int ile_zapytan;
    cin >> ile_zapytan;
    int zapytania[ile_zapytan];
    for(int i = 0; i < ile_zapytan; i++){
        cin >> zapytania[i] ;
    }

    /*tu b�dziemy zapisywa� odpowiedzi na pytania*/
    int odpowiedzi[ile_zapytan];

    /*znajdywanie rozwi�za� pojedynczej zagadki w petli po wszystkich zagadkach*/
    /*granica dolna b�dzie sie zmienia�, bo przecie� pr�dko�ci cz�stek uporz�dkowane rosn�co*/
    int gr_dol = 0;
    for(int i = 0; i < ile_zapytan; i++){
        int zapytanie = zapytania[i];
        int gr_gor = ile_czastek - 1;

        int poczatek = szukaj_poczatek(predkosci, gr_dol, gr_gor, zapytanie);
        int koniec = szukaj_koniec(predkosci, gr_dol, gr_gor, zapytanie);

        if(poczatek >= 0 && koniec >= 0)
            odpowiedzi[i] = koniec - poczatek + 1;
        else
            odpowiedzi[i] = 0;

        /*dla usprawnienia, zmieniamy doln� granic� dynamicznie na podstawie wcze�niejszych wyszukiwa�*/
        gr_dol += odpowiedzi[i];
        cout << odpowiedzi[i] << endl;




    }/*end of for loop*/
} /*end of main paragraph*/
