#include<algorithm>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// prototyp funkcji sprawdzajacej poprawnosc wprowadzonego znaku
void checkChoice(char &);

// prototyp funkcji czyszczacej ekran
void cleanScreen();

class Person {
private:
    string name, surname, email, phone;

public:
	// konstruktor z domyslnymi argumentami
    Person(string name_ = "-", string surname_ = "-", string email_ = "-", string phone_ = "-");
	~Person() {}

    string getName() const { return name; }
    string getSurname() const { return surname; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }

    void setName(string name_) { name = name_; }
    void setSurname(string surname_) { surname = surname_; }
    void setEmail(string email_) { email = email_; }
    void setPhone(string phone_) { phone = phone_; }

	friend istream & operator>>(istream & is, Person & p);
    friend ostream & operator<<(ostream & os, Person & p);

	friend ifstream & operator>>(ifstream & is, Person & p);
	friend ofstream & operator<<(ofstream & os, Person & p);
};

Person::Person(string name_, string surname_, string email_, string phone_) {
    name = name_;
    surname = surname_;
    email = email_;
    phone = phone_;
}

istream & operator>>(istream & is, Person & p) {
	getline(is, p.name);
	getline(is, p.surname);
	getline(is, p.email);
	getline(is, p.phone);

	return is;
}

ostream & operator<<(ostream & os, Person & p) {
    os << "Imie: " << p.name << endl
	   << "Nazwisko: " << p.surname << endl
	   << "Email: " << p.email << endl
	   << "Telefon: " << p.phone << endl;

    return os;
}

ifstream & operator>>(ifstream & is, Person & p) {
	getline(is, p.name);
	getline(is, p.surname);
	getline(is, p.email);
	getline(is, p.phone);

	return is;
}

ofstream & operator<<(ofstream & os, Person & p) {
	os << p.name << endl
	   << p.surname << endl
	   << p.email << endl
	   << p.phone << endl;

	return os;
}

class Addressbook {
private:
    vector <Person> bk;

public:
	Addressbook() {}
	~Addressbook() {}

	bool readBook(string bookname);
	void showBook() const;
    void writeBook(string bookname);

    void addPerson(const Person & p) { bk.push_back(p); }
	void deletePerson(int id) { bk.erase(bk.begin() + id); }
	void findPerson(string token);
    void modifyPerson(int id);
	
	void deleteAllPersons() { bk.clear(); }
	vector <Person> getPersons() const { return bk; }

	bool isBookEmpty() const { return bk.empty(); }
	int giveRecordsNumber() const { return bk.size(); }
	void showEntryByID() const;
};

bool Addressbook::readBook(string bookname) {
	// wczytywanie pliku *.txt
	string bookname_ = { bookname };
	bookname_ += ".txt";

	ifstream fin(bookname_);

	if (!bk.empty())
		// czyszczenie, zeby nie dolaczac wczytywanej ksiazki do tej, ktora juz istnieje
		bk.clear();

	if (!fin.is_open()) {
		cout << "Blad! Nie znaleziono ksiazki adresowej o podanej nazwie." << endl;
		return false;
	}
	else {
		Person p;
		while (fin >> p) {
			bk.push_back(p);
		}
	}

	fin.close();
	return true;
}

void Addressbook::showBook() const {
	for (Person p : bk)
		cout << p << endl;
}

void Addressbook::writeBook(string bookname) {
	// zapis do pliku *.txt
	string bookname_ = { bookname };
	bookname_ += ".txt";

	ofstream fout(bookname_, ios::trunc);

	for (Person & p : bk)
		fout << p;

	fout.close();
}

void Addressbook::findPerson(string token) {
	bool foundPerson = { false };

	for (int i = 0; i < bk.size(); ++i) {
		if (token == bk.at(i).getName() || token == bk.at(i).getSurname() || token == bk.at(i).getEmail() || token == bk.at(i).getPhone()) {
			cout << bk.at(i) << endl;
			foundPerson = true;
		}
	}

	if (!foundPerson)
		cout << "Nie znaleziono osoby spelniajacej podane kryteria." << endl;
}

void Addressbook::modifyPerson(int id) {
	int choice;
	string change;

	cout << "W celu zmiany danych adresowych wybierz odpowiedni numer: " << endl;
	cout << "\t 1: zmiana imienia" << endl;
	cout << "\t 2: zmiana nazwiska" << endl;
	cout << "\t 3: zmiana adresu email" << endl;
	cout << "\t 4: zmiana numeru telefonu" << endl;
	cout << "\t 5: zakoncz edycje" << endl;

	do {
		cout << "Podaj numer: _\b";
		cin >> choice;

		if (1 == choice) {
			cout << "Podaj nowe imie: ";
			cin >> change;
			bk.at(id).setName(change);
			break;
		}
		else if (2 == choice) {
			cout << "Podaj nowe nazwisko: ";
			cin >> change;
			bk.at(id).setSurname(change);
			break;
		}
		else if (3 == choice) {
			cout << "Podaj nowy adres email: ";
			cin >> change;
			bk.at(id).setEmail(change);
			break;
		}
		else if (4 == choice) {
			cout << "Podaj nowy numer telefonu: ";
			cin >> change;
			bk.at(id).setPhone(change);
			break;
		}
		else if (5 == choice) {
			break;
		}
		else
			cout << "Nie ma takiej opcji. Aby cos zmienic wybierz 1 (imie), 2 (nazwisko), 3 (email), 4 (telefon) lub zakoncz wpisujac 5." << endl;
	} while (5 != choice);
}

void Addressbook::showEntryByID() const {
	if (bk.empty())
		cout << "Ksiazka adresowa jest pusta lub nie zostala wczytana." << endl;
	else {
		cout << "Aktualnie w ksiazce adresowej znajduje sie " << bk.size() << " wpis / wpisow:" << endl << endl;

		for (int i = 0; i < bk.size(); ++i)
			cout << i + 1 << " " << bk.at(i).getName() << " " << bk.at(i).getSurname() << " " << bk.at(i).getEmail() << " " << bk.at(i).getPhone() << endl;
		cout << endl;
	}
}

class UI {
private:
	Addressbook ab;
	string bookname;

public:
	UI() {}
	~UI() {}

	void showMainMenu();
	
	void createNewAddressBook();
	void openAddressBook(bool opened = false, bool escape = true);
	void isAddressBookOpen(bool escape = true);
	
	void showAddressBook();

	void addAddressBookEntry(bool createNewAddressBookMenu = false);
	void findAddressBookEntry();
	void modifyAddressBookEntry();
	void removeAddressBookEntry();
	void sortAddressBookEntries();

	void escapeToMainMenu();
};

void UI::showMainMenu() {
	int choice;
	cout << endl;
	cout << "\t \t Simple Address Book 1.0" << endl << endl;
	cout << "\t \t      Menu glowne" << endl;

	cout << "\t  1: Stworz nowa ksiazke adresowa" << endl;
	cout << "\t  2: Wczytaj istniejaca ksiazke adresowa" << endl;
	cout << "\t  3: Wyswietl zawartosc istniejacej ksiazki adresowej" << endl;
	cout << "\t  4: Dodaj wpis do istniejacej lub nowo utworzonej ksiazki adresowej" << endl;
	cout << "\t  5: Zmodyfikuj wpis w istniejacej ksiazce adresowej" << endl;
	cout << "\t  6: Usun wpis z istniejacej ksiazki adresowej" << endl;
	cout << "\t  7: Szukaj wpisu" << endl;
	cout << "\t  8: Posortuj wpisy" << endl;
	cout << "\t  9: Zakoncz program" << endl << endl;
	cout << "Wybierz czynnosc: _\b";
	cin >> choice;

	while (1 > choice || 9 < choice) {
		cout << "Zostal wpisany nieprawidlowy numer. Wybierz 1, 2, 3, 4, 5, 6, 7, 8 lub 9: _\b";
		cin >> choice;	
	}
	
	// czyszczenie ekranu
	if (9 != choice)
		cleanScreen();

	if (1 == choice)
		createNewAddressBook();
	else if (2 == choice)
		openAddressBook();
	else if (3 == choice)
		showAddressBook();
	else if (4 == choice)
		addAddressBookEntry();
	else if (5 == choice)
		modifyAddressBookEntry();
	else if (6 == choice)
		removeAddressBookEntry();
	else if (7 == choice)
		findAddressBookEntry();
	else if (8 == choice)
		sortAddressBookEntries();
	else if (9 == choice)
		return;
}

void UI::createNewAddressBook() {
	char choice;

	cout << "Podaj nazwe dla ksiazki adresowej, ktora chcesz utworzyc: ";
	cin >> bookname;

	ab.writeBook(bookname);
	openAddressBook(true, false);

	cout << "Czy chcesz dodac pierwszy wpis do nowo utworzonej ksiazki adresowej? (t lub n) _\b";
	cin >> choice;

	checkChoice(choice);

	if ('t' == choice)
		addAddressBookEntry(true);

	while ('n' != choice) {
		cout << "Czy chcesz dodac kolejny wpis? (t lub n) _\b";
		cin >> choice;

		checkChoice(choice);

		if ('t' == choice)
			addAddressBookEntry(true);
		else
			break;
	}

	cleanScreen();
	showMainMenu();
}

void UI::openAddressBook(bool opened, bool escape) {
	if (!opened) {
		cout << "Podaj nazwe ksiazki adresowej, ktora chcesz wczytac: ";
		cin >> bookname;

		bool success = ab.readBook(bookname);

		if (success)
			cout << "Operacja zakonczona pomyslnie. Udalo sie wczytac podana ksiazka adresowa." << endl;
		else
			cout << "Nie udalo sie wczytac podanej ksiazki adresowej." << endl;
	}
	else
		bool success = ab.readBook(bookname);

	if(escape)
		escapeToMainMenu();
}

void UI::isAddressBookOpen(bool escape) {
	if (bookname.empty()) {
		char choice;
		cout << "Zadna ksiazka adresowa nie zostala wczytana. Czy chcesz wczytac istniejaca ksiazke adresowa? (t lub n) _\b";
		cin >> choice;

		checkChoice(choice);

		if ('t' == choice)
			openAddressBook(false, escape);
		else
			return;
	}
}

void UI::showAddressBook() {
	isAddressBookOpen(false);

	if (bookname.empty())
		cout << "Nie udalo sie wczytac podanej ksiazki adresowej." << endl;
	else {
		cout << endl << "\t \t \t \t Ksiazka adresowa \"" << bookname << "\"" << endl << endl;
		
		if (ab.isBookEmpty())
			cout << "Brak wpisow." << endl;
		else
			ab.showBook();
	}

	escapeToMainMenu();
}

void UI::addAddressBookEntry(bool createNewAddressBookMenu) {
	isAddressBookOpen(false);

	if (bookname.empty()) {
		cout << "Nie udalo sie wczytac podanej ksiazki adresowej." << endl;
	}
	else {
		char choice;
		string name_, surname_, email_, phone_;

		cout << endl << "\t \t \t Tworzenie nowego kontaktu" << endl << endl;
		cout << "Podaj imie kontaktu: ";
		cin >> name_;
		cout << "Podaj nazwisko kontaktu: ";
		cin >> surname_;
		cout << "Podaj adres email kontaktu: ";
		cin >> email_;
		cout << "Podaj telefon kontaktu: ";
		cin >> phone_;

		Person newOne = { name_, surname_, email_, phone_ };
		ab.addPerson(newOne);

		cout << "Czy chcesz zapisac nowy kontakt w ksiazce adresowej? (t lub n) _\b";
		cin >> choice;

		checkChoice(choice);

		if ('t' == choice && createNewAddressBookMenu)
			ab.writeBook(bookname);
		else if ('n' == choice && createNewAddressBookMenu)
			return;
		else if ('t' == choice && !createNewAddressBookMenu) {
			ab.writeBook(bookname);
			escapeToMainMenu();
		}
		else if ('n' == choice && !createNewAddressBookMenu)
			escapeToMainMenu();
	}
}

void UI::findAddressBookEntry() {
	isAddressBookOpen(false);

	if (ab.isBookEmpty())
		escapeToMainMenu();
	else {
		string token;

		cout << "Podaj imie, nazwisko, adres email lub numer telefoniczny osoby, ktorej szukasz: ";
		cin >> token;
		cout << endl;

		ab.findPerson(token);

		escapeToMainMenu();
	}
}

void UI::modifyAddressBookEntry() {
	isAddressBookOpen(false);
	ab.showEntryByID();

	if (ab.isBookEmpty())
		escapeToMainMenu();
	else {
		char choice = { 't' };
		int id = { 0 };

		cout << "Ktory wpis chcesz zmodyfikowac? Podaj ";

		for (int i = 0; i < ab.giveRecordsNumber(); ++i) {
			if (i == ab.giveRecordsNumber() - 1)
				cout << "lub ";
			cout << i + 1;
			if (i != ab.giveRecordsNumber() - 1)
				cout << ", ";
		}

		cout << ". _\b";
		cin >> id;

		while (1 > id || ab.giveRecordsNumber() < id) {
			cout << "Zostal wpisany nieprawidlowy identyfikator. Wpisz poprawny numer: _\b";
			cin >> id;
		}
		
		ab.modifyPerson(id - 1);

		while ('n' != choice) {
			cout << "Czy chcesz dalej zmieniac dane biezacego wpisu? Nacisnij t lub n: _\b";
			cin >> choice;

			checkChoice(choice);

			if ('t' == choice)
				ab.modifyPerson(id - 1);
		}

		cout << "Operacja zakonczona pomyslnie." << endl;
		ab.writeBook(bookname);
		escapeToMainMenu();
	}
}

void UI::removeAddressBookEntry() {
	isAddressBookOpen(false);
	ab.showEntryByID();

	if (ab.isBookEmpty())
		escapeToMainMenu();
	else {
		int id = { 0 };

		cout << "Ktory wpis chcesz usunac? Podaj ";

		for (int i = 0; i < ab.giveRecordsNumber(); ++i) {
			if (i == ab.giveRecordsNumber() - 1)
				cout << "lub ";
			cout << i + 1;
			if (i != ab.giveRecordsNumber() - 1)
				cout << ", ";
		}
		cout << ". _\b";
		cin >> id;

		while (1 > id || ab.giveRecordsNumber() < id) {
			cout << "Zostal wpisany nieprawidlowy identyfikator. Wpisz poprawny numer: _\b";
			cin >> id;
		}

		ab.deletePerson(id - 1);
		ab.writeBook(bookname);
		cout << "Operacja zakonczona pomyslnie." << endl;
		escapeToMainMenu();
	}
}

void UI::sortAddressBookEntries() {
	isAddressBookOpen(false);

	if (bookname.empty())
		cout << "Nie udalo sie wczytac podanej ksiazki adresowej." << endl;
	else if (ab.isBookEmpty())
		cout << "Brak wpisow. Nie ma niczego do posortowania." << endl;
	else {
		char choice, token;
		vector <Person> bks = ab.getPersons();

		cout << "Wpisy mozna posortowac po imieniu (i) lub nazwisku (n). Nacisnij i lub n: _\b";
		cin >> token;

		while ('i' != token && 'n' != token) {
			cout << "Zostal wpisany nieprawidlowy znak. Nacisnij i lub n: _\b";
			cin >> token;
		}

		if ('i' == token)
			sort(bks.begin(), bks.end(), [](const Person & lhs, const Person & rhs) { return lhs.getName() < rhs.getName(); });
		else
			sort(bks.begin(), bks.end(), [](const Person & lhs, const Person & rhs) { return lhs.getSurname() < rhs.getSurname(); });

		cout << "Czy chcesz wyswietlic posortowana ksiazke? (t lub n) _\b";
		cin >> choice;

		checkChoice(choice);

		if ('t' == choice) {
			cout << endl;
			for (Person p : bks)
				cout << p << endl;
		}

		cout << "Czy chcesz zapisac posortowana ksiazke? (t lub n) _\b";
		cin >> choice;

		checkChoice(choice);

		if ('t' == choice) {
			ab.deleteAllPersons();
			for (Person & p : bks)
				ab.addPerson(p);
			ab.writeBook(bookname);
		}
	}

	escapeToMainMenu();
}

void UI::escapeToMainMenu() {
	char choice;

	cout << "Czy chcesz wrocic do glownego menu (t) czy zakonczyc program (n)? (t lub n) _\b";
	cin >> choice;

	checkChoice(choice);

	if ('t' == choice) {
		cleanScreen();
		showMainMenu();
	}
	else
		return;
}

int main() {
	UI ui;
	ui.showMainMenu();
}

void checkChoice(char & choice) {
	while ('t' != choice && 'n' != choice) {
		cout << "Zostal wpisany nieprawidlowy znak. Nacisnij t lub n: _\b";
		cin >> choice;
	}
}

void cleanScreen() {
	// "cls" dla Windows, w innych systemach byc moze trzeba zmienic
	system("cls");
}
