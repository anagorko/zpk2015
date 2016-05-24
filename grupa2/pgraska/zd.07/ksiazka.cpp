#include <iostream>
#include <string>
#include <vector>
#include <fstream>	

using namespace std;

static int idCounter = 0;

class Wpis{
private:
	string name;
	string surname;
	string email;
	string phone;
	int id;

public:
	Wpis(string _name, string _surname, string _email, string _phone) {	
		idCounter++;														// program bedzie liczyl ID 
		id = idCounter;
		//id = _id;
		name = _name;
		surname = _surname;
		email = _email;
		phone = _phone;
	}

	friend ostream& operator << (ostream&, Wpis&);
	friend istream& operator >> (istream&, Wpis&);	

	int getId() {
		return id;
	}

	string getname() {
		return name;
	}
	string getsurname() {
		return surname;
	}
	string getemail() {
		return email;
	}
	string getphone() {
		return phone;
	}

	void modyfikuj(string _name, string _surname, string _email, string _phone) {
		name = _name;
		surname = _surname;
		email = _email;
		phone = _phone;
	}
};

ostream& operator << (ostream& out, Wpis& w) {
	out << w.id << "\n";
	out << w.name << "\n";
	out << w.surname << "\n";
	out << w.email << "\n";
	out << w.phone << "\n";

	return out;
}
istream& operator >> (istream& in, Wpis& w) {
	
	in >> w.name;
	in >> w.surname;
	in >> w.email;
	in >> w.phone;

	return in;
}

class ksiazka_adresowa {
private:
	vector<Wpis*> wpisy;
public:
	void dodaj(string _name, string _surname, string _email, string _phone) {
		wpisy.push_back(new Wpis(_name,_surname,_email,_phone));				
	}
	bool usun(int id) {
		for (int i = 0; i < wpisy.size(); i++) {
			if (wpisy[i]->getId() == id) {
				
				delete wpisy[i];
				wpisy[i] = NULL;
				wpisy.erase(wpisy.begin()+i);
				return true;													
			}														    
		}
		return false;
	 }
	void zapisz(string sciezka) {
		fstream plik;
		plik.open(sciezka,ios::out);
		plik << wpisy.size() << "\n";		

		for (int i = 0; i < wpisy.size(); i++) {
	
			plik << *wpisy[i];					
		}


		plik.close();
	}
	void wczytaj(string sciezka) {
		fstream plik;
		plik.open(sciezka, ios::in);

		int liczbaWpisow;
		plik >> liczbaWpisow;
		string l;
		getline(plik,l);
		for (int i = 0; i < wpisy.size();i++) {
			delete wpisy[i];
		}
		wpisy.clear();

		for (int i = 0; i < liczbaWpisow; i++) {
			string id;
			string name;
			string surname;
			string email;
			string phone;
			getline(plik,id);
			getline(plik,name);
			getline(plik, surname);
			getline(plik,email);
			getline(plik,phone);
			wpisy.push_back(new Wpis(name,surname,email,phone));
		}
		plik.close();
	}
	void wypisz_wpisy() {
		for (int i = 0; i<wpisy.size(); i++)
		{
			cout << wpisy[i]->getId() << " " << wpisy[i]->getname() << " " << wpisy[i]->getsurname() << " " << wpisy[i]->getemail() << " " << wpisy[i]->getphone() << "\n";
		}
	}

	bool modyfikuj_wpis(int _id) {
		for (int i = 0; i < wpisy.size(); i++) {
			if (_id == wpisy[i]->getId()) {
				string im;
				string n;
				string e;
				string t;
				cout << "Podaj imie" << endl;
				cin >> im;
				cout << "Podaj nazwisko" << endl;
				cin >> n;
				cout << "Podaj e-mail" << endl;
				cin >> e;
				cout << "Podaj numer" << endl;
				cin >> t;
				wpisy[i]->modyfikuj(im,n,e,t);
				return true;
			}
		}
		return false;
	}
};

int main()
{
	ksiazka_adresowa* k = new ksiazka_adresowa();
	
	bool koniec = false;
	while (!koniec) {
		system("cls");
		cout << "\t\tMenu\n\n";
		cout << "d - dodaj wpis\n";
		cout << "u - usun wpis\n";
		cout << "m - modyfikuj wpis\n";
		cout << "p - wydrukuj ksiazke\n";
		cout << "w - wczytaj z pliku\n";
		cout << "z - zapisz do pliku\n";
		cout << "q - wyjscie\n";

		char sterowanie;

		cin >> sterowanie;

		switch (sterowanie) {
		case 'd':
			{
				system("cls");
				string im;
				string na;
				string em;
				string te;

				cout << "Dodawanie wpisu\n\n";
				cout << "Podaj imie\n";
				cin >> im;
				cout << "Podaj nazwisko\n";
				cin >> na;
				cout << "Podaj email\n";
				cin >> em;
				cout << "Podaj telefon\n";
				cin >> te;
				k->dodaj(im,na,em,te);
				cout << "Dodano wpis\n";
				system("pause");
			}	
			break;
		case 'u':
			{
				system("cls");
				int _id;
				cout << "Usuwanie wpisu\n\n";
				cout << "Podaj id\n";
				cin >> _id;
				bool czyUsunieto = k->usun(_id);
				if (czyUsunieto) {
					cout << "Usunieto wpis\n";
				}
				else {
					cout << "Brak wpisu o id = " << _id << "\n";
				}
				system("pause");
			}
			break;
		case 'm':
			{
				system("cls");
				cout << "Modyfikowanie wpisu\n\n";

				cout << "Podaj id\n";
				int id;
				cin >> id;

				bool czyZmodyfikowano = k->modyfikuj_wpis(id);
				if (czyZmodyfikowano) {
					cout << "Zmodyfikowano\n";
				}
				else {
					cout << "Brak wpisu o id = " << id << "\n";
				}
				system("pause");
			}
			break;
		case 'p':
			system("cls");
			cout << "Wpisy ksiazki\n\n";
			k->wypisz_wpisy();
			system("pause");
			break;
		case 'w':
			{
				system("cls");
				cout << "Wczytywanie z pliku\n\n";
				cout << "Podaj sciezke do pliku\n";
				string sciezka;
				cin >> sciezka;
				k->wczytaj(sciezka);
				cout << "Wczytano plik\n";
				system("pause");
			}
			break;
		case 'z':
			{
				system("cls");
				cout << "Zapisywanie do pliku\n\n";
				cout << "Podaj sciezke do pliku\n";
				string sciezka;
				cin >> sciezka;
				k->zapisz(sciezka);
				cout << "Zapisano do pliku\n";
				system("pause");
			}
			break;
		case 'q':
			koniec = true;
			system("cls");
			cout << "Wyjscie z programu\n";
			cout << "Dziekujemy!!!\n";
			break;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}
