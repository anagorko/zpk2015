#include <iostream>
#include <math.h>

using namespace std;

long long oblicz_f(long long x, long long p, long long q){
    long long wynik = pow(x,3) + p*x - q;
    return(wynik);
}

int main() {
    int ile_zagadek;
    cin >> ile_zagadek;
    /*tablice z parametrami zagadek*/
    long long p[ile_zagadek];
    long long q[ile_zagadek];


    /*pobieranie danych wejœcia*/
    for(int i = 0; i < ile_zagadek; i++){
        cin >> p[i] ;
        cin >> q[i] ;
    }
    /*znajdywanie rozwi¹zañ pojedynczej zagadki w petli po wszystkich zagadkach*/

    for(int i = 0; i < ile_zagadek; i++){
        int gr_dol = 0;
        /*najpierw szukamy górnej granicy przedzia³u do szukania binarnego
        zauwa¿amy przy tym , ¿e nasza funkcja jest rosn¹ca*/
        long long gr_gor = 10;
        bool gr_found = false;
        while(!gr_found){
            if(oblicz_f(gr_gor, p[i], q[i]) >= 0){
                gr_found = true;
            }else{
                gr_gor *= 10;
            }
        }

        /*mamy doln¹ i górn¹ granicê, szukamy binarnie wyniku*/
        bool wynik_found = false;
        while(!wynik_found){

            int x = (gr_dol + gr_gor) / 2;
            /*je¿eli nie istnieje pierwiastek, czyli dochodzimy do momentu kiedy gr_dol = x*/
            if(gr_dol >= gr_gor -1){
                /*jeœli miêdzy granicami jest odstêp 1, to trzeba sprawdziæ jeszcze granice*/
                if(oblicz_f(gr_dol, p[i], q[i]) == 0)
                    cout << gr_dol << endl;
                else if (oblicz_f(gr_gor, p[i], q[i]) == 0)
                    cout << gr_gor << endl;
                else
                    cout << "NIE" << endl;

                wynik_found = true;
            }else{
                if(oblicz_f(x, p[i], q[i]) == 0){
                    wynik_found = true;
                    cout << x << endl;
                }else{
                    if(oblicz_f(x, p[i], q[i]) > 0){
                        gr_gor = x;

                    }else{
                        gr_dol = x;
                    }
                }
            }

        } /*end of while loop*/
    }/*end of for loop*/
} /*end of main paragraph*/
