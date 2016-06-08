#include<algorithm>
#include<conio.h>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;



class Person {		// klasa obiektów reprezentujących pojedyncze wpisy do książki

public:

    int id;			// identyfikator wpisu
    string name;	// nazwisko
    string surname;	// imię
    string email;	// e-mail
    string phone;	// nr telefonu

	Person(int, string, string, string, string);

    friend ostream& operator<<(ostream&, Person&);	// operator odczytu rekordów
    friend istream& operator>>(istream&, Person&);	// operator zapisu rekordów

};

Person::Person(int xid, string xname, string xsurname, string xemail, string xphone)
	:id(xid),
	name(xname),
	surname(xsurname),
	email(xemail),
	phone(xphone)
{
}

ostream& operator<<(ostream &os, Person &osoba) {

    os << osoba.id << ". ";
    os << osoba.name << " ";
    os << osoba.surname << " ";
    os << osoba.email << " ";
    os << osoba.phone << " ";

    return os;
}

istream& operator>>(istream &is, Person &osoba) {

    is >> osoba.id;
    is >> osoba.name;
    is >> osoba.surname;
    is >> osoba.email;
    is >> osoba.phone;

    return is;
}



class Addressbook {		// klasa obiektów reprezentujących książkę adresową

public:

	vector<Person> bk;

    void otworz(string);      								// odczytywanie z pliku
    void zapisz(string);									// zapisywanie do pliku
    void dodaj(string, string, string, string);				// dodawanie nowego wpisu do książki
    void wyswietl();										// wyswietlenie zawartosci ksiazki adresowej
    void modyfikuj(int, string, string, string, string);    // modyfikowanie wpisu o danym identyfikatorze
    void usun(int);         								// usuwanie wpisu o danym identyfikatorze
    void sortuj(string);    								// sortowanie wpisow z ksiazki według danego kryterium

};

void Addressbook::otworz(string nazwaksiazki) {

    fstream plik;
    string id;
    string imie;
    string nazwisko;
    string email;
    string telefon;

	bk.clear();										// na wejściu czyścimy książkę adresową

    plik.open(nazwaksiazki + ".txt", ios::in);
	if (plik.good() != true)						// jeżeli otwarcie pliku się nie powiodło
		cout << "Nie ma takiego pliku!" << endl;	// - wyświetlenie komunikatu

    while (!plik.eof()) {							// dopóki nie został osiągnięty koniec pliku
    	getline(plik, id, ' ');						// - wczytujemy dane
    	getline(plik, imie, ' ');
    	getline(plik, nazwisko, ' ');
    	getline(plik, email, ' ');
    	getline(plik, telefon, ' ');
    	dodaj(imie, nazwisko, email, telefon);		// dodajemy je do książki adresowej
	}

	bk.pop_back();

	plik.close();
}

void Addressbook::zapisz(string nazwaksiazki) {

    ofstream bookfile;

    bookfile.open(nazwaksiazki + ".txt", ios::trunc);

    for (Person& p: bk) {
        bookfile << p;
    }

    bookfile.close();

}

void Addressbook::dodaj( string imie, string nazwisko, string email, string telefon) {

    bk.push_back(Person(bk.size() + 1, imie, nazwisko, email, telefon));

}

void Addressbook::wyswietl() {

	for (int i = 0; i < bk.size(); i++) {
		cout << bk[i] << endl;
	}

}

void Addressbook::modyfikuj(int id, string imie, string nazwisko, string email, string telefon) {

	bk[id - 1].name = nazwisko;
	bk[id - 1].surname = imie;
	bk[id - 1].email = email;
	bk[id - 1].phone = telefon;

}

void Addressbook::usun(int id) {

	for (int i = id; i < bk.size(); i++) {		// przesuwamy kolejne wpisy o jeden do przodu
		bk[i - 1].name = bk[i].name;
		bk[i - 1].surname = bk[i].surname;
		bk[i - 1].email = bk[i].email;
		bk[i - 1].phone = bk[i].phone;
	}

	bk.pop_back();								// kasujemy ostatni, niepotrzebny wpis

}

void Addressbook::sortuj(string kategoria) {

	if (kategoria == "name")
		sort(bk.begin(), bk.end(), [] (const Person& lhs, const Person& rhs) { return lhs.name < rhs.name; });
	else if (kategoria == "surname")
		sort(bk.begin(), bk.end(), [] (const Person& lhs, const Person& rhs) { return lhs.surname < rhs.surname; });
	else if (kategoria == "email")
		sort(bk.begin(), bk.end(), [] (const Person& lhs, const Person& rhs) { return lhs.email < rhs.email; });
	else if (kategoria == "phone")
		sort(bk.begin(), bk.end(), [] (const Person& lhs, const Person& rhs) { return lhs.phone < rhs.phone; });

    for (int i = 0; i < bk.size(); i++) {		// na nowo nadajemy odpowiedni identyfikator
    	bk[i].id = i + 1;
	}

}



class UI {		// klasa implementująca interfejs użytkownika

	Addressbook mojaKsiazka;

public:
	int bazaOsob();
	void wyswietlOsoby();
	void dodajWpis();
	void modyfikujWpis();
	void usunWpis();
	void sortujWpisy();
	void zapiszKsiazke();
	void otworzKsiazke();
};

int UI::bazaOsob() {

	char odp;

	cout << "*** KSIAZKA TELEFONICZNA ***" << endl;
	cout << "1. Otworz ksiazke" << endl;
	cout << "2. Lista osob" << endl;
	cout << "3. Dodaj wpis" << endl;
	cout << "4. Modyfikuj wpis" << endl;
	cout << "5. Usun wpis" << endl;
	cout << "6. Sortuj wpisy" << endl;
	cout << "7. Zapisz ksiazke" << endl;
	cout << "8. Wyjscie" << endl;

	do {
		odp = getch();
		switch(odp) {
			case '1':
				otworzKsiazke();
				break;
			case '2':
				wyswietlOsoby();
				break;
			case '3':
				dodajWpis();
				break;
			case '4':
				modyfikujWpis();
				break;
			case '5':
				usunWpis();
				wyswietlOsoby();
				break;
			case '6':
				sortujWpisy();
				wyswietlOsoby();
				break;
			case '7':
				zapiszKsiazke();
				break;
		}
	} while (odp != '8');

	return 0;
}

void UI::otworzKsiazke() {

	string nazwa;
	cout << "\nPodaj nazwe pliku: ";
	cin >> nazwa;

	mojaKsiazka.otworz(nazwa);
}

void UI::wyswietlOsoby() {

	cout << "\nLista osob:" << endl;
	if (mojaKsiazka.bk.empty() == 1)				// jeżeli nie ma wpisów w książce adresowej
		cout << "<ksiazka jest pusta>" << endl;		// - wyświetlenie komunikatu
	else
		mojaKsiazka.wyswietl();

}

void UI::dodajWpis() {

	string odpImie;
	string odpNazwisko;
	string odpEmail;
	string odpTelefon;

	cout << "\nPodaj dane osoby:" << endl;
	cout << "Imie: ";
	getline(cin, odpImie);
	cout << "Nazwisko: ";
	getline(cin, odpNazwisko);
	cout << "E-mail: ";
	getline(cin, odpEmail);
	cout << "Nr telefonu: ";
	getline(cin, odpTelefon);

	mojaKsiazka.dodaj(odpNazwisko, odpImie, odpEmail, odpTelefon);

}

void UI::modyfikujWpis() {

	int nr;
	string odpImie;
	string odpNazwisko;
	string odpEmail;
	string odpTelefon;

	cout << "\nPodaj wpis, ktory chcesz zmodyfikowac: ";
	cin >> nr;
	cin.ignore();

	cout << "\nPodaj dane osoby:" << endl;
	cout << "Imie: ";
	getline(cin, odpImie);
	cout << "Nazwisko: ";
	getline(cin, odpNazwisko);
	cout << "E-mail: ";
	getline(cin, odpEmail);
	cout << "Nr telefonu: ";
	getline(cin, odpTelefon);

	mojaKsiazka.modyfikuj(nr, odpImie, odpNazwisko, odpEmail, odpTelefon);

}

void UI::usunWpis() {

	int nr;
	cout << "\nPodaj wpis, ktory chcesz usunac: ";
	cin >> nr;

	mojaKsiazka.usun(nr);
}

void UI::sortujWpisy() {

	char odp;

	cout << "\nWybierz kategorie, po ktorej chcesz posortowac: " << endl;
	cout << "a. imie" << endl;
	cout << "b. nazwisko" << endl;
	cout << "c. email" << endl;
	cout << "d. nr telefonu" << endl;

	odp = getch();
	switch(odp) {
		case 'a':
			mojaKsiazka.sortuj("surname");
			break;
		case 'b':
			mojaKsiazka.sortuj("name");
			break;
		case 'c':
			mojaKsiazka.sortuj("email");
			break;
		case 'd':
			mojaKsiazka.sortuj("phone");
			break;
	}

}

void UI::zapiszKsiazke() {

	string nazwa;
	cout << "\nPodaj nazwe pliku: ";
	cin >> nazwa;

	mojaKsiazka.zapisz(nazwa);

}



int main() {

	UI mojInterfejs;
	mojInterfejs.bazaOsob();

}
