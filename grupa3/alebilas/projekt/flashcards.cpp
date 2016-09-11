// Autorki: Aleksandra Biłas, Kaja Cieślukowska

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
using namespace std;

// Definicja klasy i struktury Osoba
class Osoba {
public:
    struct tosoba{
        string nick;
        int najlepszy_wynik;
        int ostatni_wynik;
    };
};

// Definicja klasy i struktury Slowo
class Slowo {
public:
	struct tslowa{
	    string ang;
	    string pol;
	    int pkt;
	    };
};

/* Definicja metod dla Gracza */
class Gracz{
public:

    struct tosoba{
        string nick;
        int najlepszy_wynik;
        int ostatni_wynik;
    };

    tosoba tab_osob[200];
    int l_graczy;

// Metoda otwiera plik z osobami, zapisuje w tablicy oraz liczy liczbe graczy
	void otworz(){
		string o_linia;
		ifstream plik_osob("osoby.txt");
        l_graczy=0;

        while(not plik_osob.eof()){
            getline(plik_osob,o_linia);
			tab_osob[l_graczy].nick = o_linia;

			getline(plik_osob,o_linia);
			istringstream tekst2int(o_linia);
			tekst2int >> tab_osob[l_graczy].najlepszy_wynik;

			getline(plik_osob,o_linia);
			istringstream tekst2int1(o_linia);
			tekst2int1 >> tab_osob[l_graczy].ostatni_wynik;

            l_graczy++;
        }
	}
// Zapisanie tablicy z osobami i ich wynikow do pliku
	void zapisz(){
		ofstream plik_osob("osoby.txt");
		for (int i = 0; i < l_graczy-1; i++){
			plik_osob << tab_osob[i].nick << endl << tab_osob[i].najlepszy_wynik << endl << tab_osob[i].ostatni_wynik << endl;
		}
		plik_osob << tab_osob[l_graczy-1].nick << endl << tab_osob[l_graczy-1].najlepszy_wynik << endl << tab_osob[l_graczy-1].ostatni_wynik;
		plik_osob.close();
	}
// Wypisanie graczy i ich najlepszych wynikow na konsole
	void pokaz_graczy(){
	    cout << "Lista graczy i ich najlepsze wyniki:" << endl;

		for (int i=0; i<l_graczy; i++){
			cout << tab_osob[i].nick << " - " << tab_osob[i].najlepszy_wynik << endl;
		}
	}
};
// Definicja metod w klasie Fiszki
class Fiszki{
public:
	int odp, nr_slowa, l_slow, rand_start;
    struct tslowa{
        string ang;
        string pol;
        int pkt;
    };

    tslowa tab_slow[161];

// Gra polsko-angielska - losuje w zaleznosci od wyboru kategorii
	int pol_ang(int l_slow, int rand_start){
		system("cls");

		losuj_pa:
// Losowanie slowa polskiego i jego tlumaczenia angielskiego
        srand(time(NULL));
		int i = rand() % l_slow + rand_start;
// Jezeli slowo zostalo odgadniete co najmniej 5 razy poprawnie, to nie biezemy go pod uwage
		if(tab_slow[i].pkt>=5){
            goto losuj_pa;
		}
// Losujemy dwa inne slowka angielskie
		int j = rand() % 161;
		int k = rand() % 161;
// Wyswietlenie slowa polskiego
		cout << tab_slow[i].pol << endl;
// Losujemy kolejnosc wyswietlania odpowiedzi
		int l = rand() % 3;
		if(l == 0){
			cout << "1) " << tab_slow[i].ang << endl;
			cout << "2) " << tab_slow[j].ang << endl;
			cout << "3) " << tab_slow[k].ang << endl;
			odp = 1;
		}
		else if(l == 1){
			cout << "1) " << tab_slow[j].ang << endl;
			cout << "2) " << tab_slow[i].ang << endl;
			cout << "3) " << tab_slow[k].ang << endl;
			odp = 2;
		}
		else{
			cout << "1) " << tab_slow[j].ang << endl;
			cout << "2) " << tab_slow[k].ang << endl;
			cout << "3) " << tab_slow[i].ang << endl;
			odp = 3;
		}
// Zapamietanie numeru zgadywanego slowa w tabeli, aby pozniej mozna bylo dopisac mu punkt
		nr_slowa = i;
// Zapamietanie numeru poprawnej odpowiedzi (do pozniejszego porownania z odpowiedzia gracza)
		return odp;
	}

// Gra angielsko-polska - analogicznie do wersji polsko-angielskiej
	int ang_pol(int l_slow, int rand_start){
		system("cls");

		losuj_ap:
        srand(time(NULL));
		int i = rand() % l_slow + rand_start;

		if(tab_slow[i].pkt>=5){
            goto losuj_ap;
		}
		int j = rand() % 161;
		int k = rand() % 161;

		cout << tab_slow[i].ang << endl;

		int l = rand() % 3;
		if(l == 0){
			cout << "1) " << tab_slow[i].pol << endl;
			cout << "2) " << tab_slow[j].pol << endl;
			cout << "3) " << tab_slow[k].pol << endl;
			odp = 1;
		}
		else if(l == 1){
			cout << "1) " << tab_slow[j].pol << endl;
			cout << "2) " << tab_slow[i].pol << endl;
			cout << "3) " << tab_slow[k].pol << endl;
			odp = 2;
		}
		else{
			cout << "1) " << tab_slow[j].pol << endl;
			cout << "2) " << tab_slow[k].pol << endl;
			cout << "3) " << tab_slow[i].pol << endl;
			odp = 3;
		}
		nr_slowa = i;
		return odp;
	}

// Otwarcie pliku ze slowami danego uzytkownika i wypisanie do tabeli
	void otworz(string twoj_nick){
		string s_linia;
		ifstream plik_slow(twoj_nick);

        for(int i = 0; i <161; i++){
            getline(plik_slow,s_linia);
			tab_slow[i].ang = s_linia;

			getline(plik_slow,s_linia);
			tab_slow[i].pol = s_linia;

			getline(plik_slow,s_linia);
			istringstream tekst2int(s_linia);
			tekst2int >> tab_slow[i].pkt;
        }
	}
// Zapisanie tablicy slow do pliku
	void zapisz(string twoj_nick){
		ofstream file(twoj_nick);

		for (int i = 0; i < 161; i++){
			file << tab_slow[i].ang << endl << tab_slow[i].pol << endl << tab_slow[i].pkt << endl;
		}
	}
// Wybor kategorii slow
	void kategorie(int kat){
	    switch(kat){
        case 1:
            l_slow=45;
            rand_start=0;
            break;
        case 2:
            l_slow=25;
            rand_start=45;
            break;
        case 3:
            l_slow=33;
            rand_start=70;
            break;
        case 4:
            l_slow=19;
            rand_start=103;
            break;
        case 5:
            l_slow=39;
            rand_start=122;
            break;
        case 6:
            l_slow=161;
            rand_start=0;
            break;
        default:
            l_slow=161;
            rand_start=0;
            break;
	    }
	}
};

class Gra{
public:
    Gracz o_Gracz;
    Fiszki o_Fiszki;
    string twoj_nick, dalej;
    bool nowy;
    int nr_gracza, wynik, odpowiedz, wybrana_kat, wybor_gracza0, wybor_gracza1, wybor_gracza2;
// Powitanie
    void init(){
        system("color 74");
        system("title FLASHCARDS");
        system("cls");

        for (int i = 0; i < 80; i++) cout << "*";
        cout << endl;
        for (int i = 0; i < 80; i++) cout << "_";
        cout << endl << endl << setw(45) << "FLASHCARDS" << endl;
        cout << endl << setw(55) << "Ucz sie z nami angielskiego!" << endl;
        for (int i = 0; i < 80; i++) cout << "_";
        cout << endl;
        for (int i = 0; i < 80; i++)cout << "*";
        cout << endl << endl << endl;
    }
    void logowanie(){
        cout << "Podaj nick:" << endl;
        cin >> twoj_nick;

        o_Gracz.otworz();
// Szukanie wpisanego uzytkownika w tabeli z graczami. Jezeli uzytkonik znajdowal sie w bazie, zostaje zapamietany jego numer.
// Jezeli uzytkownik jest nowy, zostaje utworzony nowy imienny plik.
        for(int i=0; i < o_Gracz.l_graczy; i++){
            if(o_Gracz.tab_osob[i].nick==twoj_nick){
                     nowy=false;
                     nr_gracza = i;
                     break;
            }
        }
        if(nowy){
            o_Gracz.tab_osob[o_Gracz.l_graczy].nick=twoj_nick;
            o_Gracz.tab_osob[o_Gracz.l_graczy].najlepszy_wynik = 0;
            o_Gracz.tab_osob[o_Gracz.l_graczy].ostatni_wynik = 0;
            CopyFile("slowa.txt",twoj_nick.c_str(),false);
            nr_gracza = o_Gracz.l_graczy;
            o_Gracz.l_graczy++;
            o_Gracz.zapisz();
        }
        menu0();
    }

    void gra_pol_ang(){
        system("cls");
        wynik = 0;
        o_Fiszki.otworz(twoj_nick);
// Gra trwa 10 slow
        for(int j = 0; j<10; j++){
            system("cls");
            o_Fiszki.pol_ang(o_Fiszki.l_slow, o_Fiszki.rand_start);
            cout << "Ktora odpowiedz jest poprawna?" << endl;
            cin >> odpowiedz;
// Odpowiedz gracza jest porownywana z zapamietana poprawna odpowiedzia
            if(odpowiedz == o_Fiszki.odp){
// Jezeli slowo odgadniete poprawnie - dodajemy punkt do slowa w pliku twoj_nick oraz zwiekszamy aktualny wynik gracza o 1
                o_Fiszki.tab_slow[o_Fiszki.nr_slowa].pkt ++;
                wynik++;
                cout << "Dobra odpowiedz" << endl;
                system("pause");
            }
// Jezeli slowo nie zostalo odgadniete poprawnie - zmniejszamy punkty za slowo w pliku twoj_nick o 1
            else{
                o_Fiszki.tab_slow[o_Fiszki.nr_slowa].pkt --;
                cout << "Zla odpowiedz, poprawna odpowiedz to: " << o_Fiszki.tab_slow[o_Fiszki.nr_slowa].ang << endl;
                system("pause");
            }
        }
 // Po zakonczonej grze podsumowujemy wynik i zapisujemy w tabeli z graczami
        system("cls");
        cout << "Twoj wynik to: " << wynik << " / 10." << endl;
        system("pause");

        o_Gracz.tab_osob[nr_gracza].ostatni_wynik = wynik;
        if (wynik >= o_Gracz.tab_osob[nr_gracza].najlepszy_wynik){
            o_Gracz.tab_osob[nr_gracza].najlepszy_wynik = wynik;
            cout << "Gratulacje. Pobiles swoj rekord!" << endl;
        }
        else{
            cout << "Musisz jeszcze pocwiczyc." << endl;
        }
        system("pause");
// Zapisujemy zaktualizowane wyniki do plikow twoj_nick i slowa.txt
        o_Fiszki.zapisz(twoj_nick);
        o_Gracz.zapisz();

        menu1();
    }

    void gra_ang_pol(){
// Gra analogiczna do poprzedniej (wersja angielsko-polska)
        system("cls");
        o_Fiszki.otworz(twoj_nick);
        wynik = 0;
        for(int i = 0; i<10; i++){
            system("cls");
            o_Fiszki.ang_pol(o_Fiszki.l_slow, o_Fiszki.rand_start);
            cout << "Ktora odpowiedz jest poprawna?" << endl;
            cin >> odpowiedz;

            if(odpowiedz == o_Fiszki.odp){
                o_Fiszki.tab_slow[o_Fiszki.nr_slowa].pkt ++;
                wynik++;
                cout << "Dobra odpowiedz" << endl;
                system("pause");
            }
            else{
                o_Fiszki.tab_slow[o_Fiszki.nr_slowa].pkt --;
                cout << "Zla odpowiedz, poprawna odpowiedz to: " << o_Fiszki.tab_slow[o_Fiszki.nr_slowa].pol << endl;
                system("pause");
            }
        }
        system("cls");
        cout << "Twoj wynik to: " << wynik << " / 10." << endl;

        system("pause");
        o_Gracz.tab_osob[nr_gracza].ostatni_wynik = wynik;
        if (wynik >= o_Gracz.tab_osob[nr_gracza].najlepszy_wynik){
            o_Gracz.tab_osob[nr_gracza].najlepszy_wynik = wynik;
            cout << "Gratulacje. Pobiles swoj rekord!" << endl;
        }
        else{
            cout << "Musisz jeszcze pocwiczyc." << endl;
        }

        system("pause");
        o_Fiszki.zapisz(twoj_nick);
        o_Gracz.zapisz();

        menu1();
    }

    void trening_pol_ang(){
        system("cls");
        dalej = "t";
        o_Fiszki.otworz(twoj_nick);
        while (dalej == "t"){
            system("cls");
            o_Fiszki.pol_ang(o_Fiszki.l_slow, o_Fiszki.rand_start);
            cout << "Ktora odpowiedz jest poprawna?" << endl;
            cin >> odpowiedz;

            if(odpowiedz == o_Fiszki.odp){
                o_Fiszki.tab_slow[o_Fiszki.nr_slowa].pkt ++;
                cout << "Dobra odpowiedz" << endl;
                system("pause");
            }
            else{
                o_Fiszki.tab_slow[o_Fiszki.nr_slowa].pkt --;
                cout << "Zla odpowiedz, poprawna odpowiedz to: " << o_Fiszki.tab_slow[o_Fiszki.nr_slowa].ang << endl;
                system("pause");
            }

            system("cls");
            cout << "Czy chcesz odpowiadac dalej? t / n " << endl;
            cin >> dalej;
        }

        o_Fiszki.zapisz(twoj_nick);

        menu2();
    }

    void trening_ang_pol(){
        system("cls");
        dalej = "t";
        o_Fiszki.otworz(twoj_nick);
        while (dalej == "t"){
            system("cls");
            o_Fiszki.ang_pol(o_Fiszki.l_slow, o_Fiszki.rand_start);
            cout << "Ktora odpowiedz jest poprawna?" << endl;
            cin >> odpowiedz;

            if(odpowiedz == o_Fiszki.odp){
                o_Fiszki.tab_slow[o_Fiszki.nr_slowa].pkt ++;
                cout << "Dobra odpowiedz" << endl;
                system("pause");
            }
            else{
                o_Fiszki.tab_slow[o_Fiszki.nr_slowa].pkt --;
                cout << "Zla odpowiedz, poprawna odpowiedz to: " << o_Fiszki.tab_slow[o_Fiszki.nr_slowa].pol << endl;
                system("pause");
            }

            system("cls");
            cout << "Czy chcesz odpowiadac dalej? t / n " << endl;
            cin >> dalej;
        }

        o_Fiszki.zapisz(twoj_nick);

        menu2();
    }

    void menu0(){
	system("cls");
	cout << "Czesc " << twoj_nick << "!" << endl << "Zacznij z nami nauke angielskiego!" << endl;
	cout << "Ponizej znajduje sie menu, w ktorym bedziesz mogl wybrac opcje punktowanej nauki jezyka angielskiego, ale jezeli nie czujesz sie na silach, aby konkurowac z innymi graczami mozesz wybrac opcje treningu." << endl;
	cout << "Powodzenia!" << endl << endl << endl;
// Gracz wybiera rodzaj gry
	cout << "Wybierz opcje: " << endl;
	cout << "1. Gra" << endl;
	cout << "2. Trening" << endl;
	cout << "3. Pokaz graczy" << endl;
	cout << "4. Wyjdz" << endl;

    cin >> wybor_gracza0;
    switch (wybor_gracza0){
    case 1:
        system("cls");
// Gracz wybiera kategorie
        cout << "Wybierz kategorie:" << endl;
        cout << "1. Czlowiek" << endl;
        cout << "2. Rodzina" << endl;
        cout << "3. Sport" << endl;
        cout << "4. Szkola" << endl;
        cout << "5. Zywienie" << endl;
        cout << "6. Wszystko" << endl;
        cin >> wybrana_kat;
        o_Fiszki.kategorie(wybrana_kat);
        menu1();
    case 2:
        system("cls");
// Gracz wybiera kategorie
        cout << "Wybierz kategorie:" << endl;
        cout << "1. Czlowiek" << endl;
        cout << "2. Rodzina" << endl;
        cout << "3. Sport" << endl;
        cout << "4. Szkola" << endl;
        cout << "5. Zywienie" << endl;
        cout << "6. Wszystko" << endl;
        cin >> wybrana_kat;
        o_Fiszki.kategorie(wybrana_kat);
        menu2();
    case 3:
// Pokazuje liste graczy i ich najlepsze wyniki
        o_Gracz.pokaz_graczy();
        system("pause");
        menu0();
    case 4:
        exit(0);
    default:
        cout << "Nie ma takiej opcji - wybierz wlasciwa!" << endl;
        system("pause");
        menu0();
        }
    }
    void menu1(){
        system("cls");
        cout << "Wybrales gre punktowana. Wybierz wersje jezykowa, a nastepnie odpowiedz na 10 pytan. Za kazda dobra odpowiedz otrzymasz 1 punkt, natomiast za zla 0." << endl;
        cout << "1. Polsko - Angielski" << endl;
        cout << "2. Angielsko - Polski" << endl;
        cout << "3. Wroc do glownego menu" << endl;
        cout << "4. Wyjdz" << endl;

        cin >> wybor_gracza1;
        switch (wybor_gracza1){
            case 1:
                gra_pol_ang();
            case 2:
                gra_ang_pol();
            case 3:
                menu0();
            case 4:
                exit(0);
            default:
                cout << "Nie ma takiej opcji - wybierz wlasciwa!" << endl;
                system("pause");
                menu1();
        }
    }

    void menu2(){
        system("cls");
        cout << "Wybrales trening. Wybierz wersje jezykowa, a nastepnie odpowiedz na pytania." << endl;
        cout << "1. Polsko - Angielski" << endl;
        cout << "2. Angielsko - Polski" << endl;
        cout << "3. Wroc do glownego menu" << endl;
        cout << "4. Wyjdz" << endl;

        cin >> wybor_gracza2;
        switch (wybor_gracza2){
            case 1:
                trening_pol_ang();
            case 2:
                trening_ang_pol();
            case 3:
                system("cls");
                menu0();
            case 4:
                exit(0);
            default:
                cout << "Nie ma takiej opcji - wybierz wlasciwa!" << endl;
                system("pause");
                menu2();
        }
    }
};

// Glowna funkcja
int main() {
    Fiszki o_Fiszki;
    Gracz o_Gracz;
    Gra o_Gra;

    o_Gra.init();
    o_Gra.logowanie();
    o_Gra.menu0();
};
