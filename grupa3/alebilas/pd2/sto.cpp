#include <iostream>
using namespace std;

int main(){

int A, B, K;

cin >> A;
cin >> B;
cin >> K;

int liczba_krzesel = 0; // liczba krzesel, ktora zostanie wydrukowana na koncu programu

int bok_A = A/K; // ile krzesel miesci sie w boku A
int bok_B = B/K; // ile krzesej miesci sie w boku B

if(bok_A<1 && bok_B<1) // jezeli liczba krzesel przy obu bokach jest < 1 to nie zmiesci sie ani jedno krzeslo
	{
		liczba_krzesel = 0;
	}

if(bok_A>=1 && bok_A<=2 && bok_B>=1 && bok_B<=2)
	{
		liczba_krzesel = bok_A*bok_B;
	}

else
	{
		liczba_krzesel = bok_A*bok_B; //ile by sie zmiescilo krzesel na calej powierzchni
		liczba_krzesel = liczba_krzesel - (bok_A-2)*(bok_B-2); //odjac te ktore na siebie nachodza
	}

cout << liczba_krzesel;

}
