#include<algorithm>
#include<conio.h>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;



class Person 
{		

public:

	int id;			
	string name;	
	string surname;	
	string email;	
	string phone;	

	Person(int, string, string, string, string);

	friend ostream& operator<<(ostream&, Person&);	
	friend istream& operator >> (istream&, Person&);	

};

Person::Person(int xid, string xname, string xsurname, string xemail, string xphone)
	:id(xid),
	name(xname),
	surname(xsurname),
	email(xemail),
	phone(xphone)
{
}

ostream& operator<<(ostream &os, Person &osoba) 
{

	os << osoba.id << ". ";
	os << osoba.name << " ";
	os << osoba.surname << " ";
	os << osoba.email << " ";
	os << osoba.phone << " ";

	return os;
}

istream& operator >> (istream &is, Person &osoba) 
{

	is >> osoba.id;
	is >> osoba.name;
	is >> osoba.surname;
	is >> osoba.email;
	is >> osoba.phone;

	return is;
}



class Addressbook 
{		

public:

	vector<Person> bk;

	void otworz(string);      								
	void zapisz(string);									
	void dodaj(string, string, string, string);				
	void wyswietl();										
	void modyfikuj(int, string, string, string, string);    
	void usun(int);         								
	void sortuj(string);    								

};

void Addressbook::otworz(string nazwaksiazki) 
{

	fstream plik;
	string id;
	string imie;
	string nazwisko;
	string email;
	string telefon;

	bk.clear();										

	plik.open(nazwaksiazki + ".txt", ios::in);
	if (plik.good() != true)						
		cout << "Nie ma takiego pliku!" << endl;	

	while (!plik.eof())
	{							
		getline(plik, id, ' ');					
		getline(plik, imie, ' ');
		getline(plik, nazwisko, ' ');
		getline(plik, email, ' ');
		getline(plik, telefon, ' ');
		dodaj(imie, nazwisko, email, telefon);		
	}

	bk.pop_back();

	plik.close();
}

void Addressbook::zapisz(string nazwaksiazki) 
{

	ofstream bookfile;

	bookfile.open(nazwaksiazki + ".txt", ios::trunc);

	for (Person& p : bk) 
		bookfile << p;

	bookfile.close();

}

void Addressbook::dodaj(string imie, string nazwisko, string email, string telefon) 
{
	bk.push_back(Person(bk.size() + 1, imie, nazwisko, email, telefon));
}

void Addressbook::wyswietl() 
{
	for (int i = 0; i < bk.size(); i++) 
		cout << bk[i] << endl;


}

void Addressbook::modyfikuj(int id, string imie, string nazwisko, string email, string telefon) 
{

	bk[id - 1].name = nazwisko;
	bk[id - 1].surname = imie;
	bk[id - 1].email = email;
	bk[id - 1].phone = telefon;

}

void Addressbook::usun(int id) 
{

	for (int i = id; i < bk.size(); i++) 
	{		
		bk[i - 1].name = bk[i].name;
		bk[i - 1].surname = bk[i].surname;
		bk[i - 1].email = bk[i].email;
		bk[i - 1].phone = bk[i].phone;
	}

	bk.pop_back();								

}

void Addressbook::sortuj(string kategoria) 
{
	if (kategoria == "name")
		sort(bk.begin(), bk.end(), [](const Person& lhs, const Person& rhs) { return lhs.name < rhs.name; });
	else if (kategoria == "surname")
		sort(bk.begin(), bk.end(), [](const Person& lhs, const Person& rhs) { return lhs.surname < rhs.surname; });
	else if (kategoria == "email")
		sort(bk.begin(), bk.end(), [](const Person& lhs, const Person& rhs) { return lhs.email < rhs.email; });
	else if (kategoria == "phone")
		sort(bk.begin(), bk.end(), [](const Person& lhs, const Person& rhs) { return lhs.phone < rhs.phone; });

	for (int i = 0; i < bk.size(); i++) 
		bk[i].id = i + 1;

}



class UI 
{		

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

int UI::bazaOsob() 
{

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

	do 
	{
		odp = getch();
		switch (odp) 
		{
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

void UI::otworzKsiazke() 
{

	string nazwa;
	cout << "\nPodaj nazwe pliku: ";
	cin >> nazwa;

	mojaKsiazka.otworz(nazwa);
}

void UI::wyswietlOsoby() 
{
	cout << "\nLista osob:" << endl;
	if (mojaKsiazka.bk.empty() == 1)				
		cout << "<ksiazka jest pusta>" << endl;		
	else
		mojaKsiazka.wyswietl();

}

void UI::dodajWpis()
{

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

void UI::modyfikujWpis() 
{

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

void UI::usunWpis() 
{

	int nr;
	cout << "\nPodaj wpis, ktory chcesz usunac: ";
	cin >> nr;

	mojaKsiazka.usun(nr);
}

void UI::sortujWpisy() 
{

	char odp;

	cout << "\nWybierz kategorie, po ktorej chcesz posortowac: " << endl;
	cout << "a. imie" << endl;
	cout << "b. nazwisko" << endl;
	cout << "c. email" << endl;
	cout << "d. nr telefonu" << endl;

	odp = getch();
	switch (odp) 
	{
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

void UI::zapiszKsiazke() 
{
	string nazwa;
	cout << "\nPodaj nazwe pliku: ";
	cin >> nazwa;

	mojaKsiazka.zapisz(nazwa);

}



int main()
{

	UI mojInterfejs;
	mojInterfejs.bazaOsob();

}
