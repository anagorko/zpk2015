#include<iostream>
#include <vector>
using namespace std;

// definicja funkcji do wyszukiwania wyników
int predkosc(vector <int> tablica, int zapytanie)
{
int pierwszy;
int ostatni;
int poczatek = 0;
int koniec = tablica.size() - 1;
int poczatek_temp = 0;
int koniec_temp = tablica.size() - 1;
int srodek;
bool czy = true;
// szukamy pierwszego wystapienia 

	while (poczatek < koniec)
	{
		srodek = (poczatek + koniec ) / 2;           
		if (tablica[srodek] >= zapytanie)
		{
			if ((tablica[srodek] == zapytanie) && czy)
			{   
				czy = false;
				poczatek_temp = srodek;
				koniec_temp = koniec;
			}
			koniec = srodek;
		}	
		else
			poczatek = srodek + 1;
	}
	pierwszy = poczatek;

	poczatek = poczatek_temp;
	koniec = koniec_temp;

// szukamy ostatniego wystapienia 
	while (poczatek < koniec)
	{
		srodek = (poczatek + koniec + 1) / 2;           // to jest dzielenie przez 2 z zaokrągleniem w górę
		if (tablica[srodek] <= zapytanie)
			poczatek = srodek;
		else
			koniec = srodek - 1;
	}
	ostatni = koniec;
	if (tablica[pierwszy] == zapytanie)
		return (ostatni - pierwszy + 1);
	else
		return 0;

}

int main()
{
	int dlugosc;
	int liczba_zapytan;
	vector <int> tablica;
	vector <int> wyniki;
	cin >> dlugosc; // znamy wymiar tablicy 

	// uzupełniamy tablice predkosc
	for (int i = 0; i<dlugosc; ++i)
	{
		int element;
		cin >> element;
		tablica.push_back(element);
	}

	// wczytujemy liczbe zapytan
	cin >> liczba_zapytan;
	// wypisujemy wyniki 

	for (int i = 0; i<liczba_zapytan; ++i)
	{
		int element;
		cin >> element;
		wyniki.push_back(predkosc(tablica, element));
	}
	

	for (int i = 0; i<liczba_zapytan; ++i)
	{
		cout << wyniki[i] << endl;
	}
}
