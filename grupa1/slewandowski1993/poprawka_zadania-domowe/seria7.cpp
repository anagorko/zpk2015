#include<algorithm>
#include<conio.h>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

/* stworzenie klasy Person o zadanych parametrach */
class Person
{

    public:

    string name, surname, email, phone;
    int id;

    Person(string _name, string _surname, string _email, string _phone, int _id){
        name = _name;
        surname = _surname;
        email = _email;
        phone = _phone;
        id = _id;
    }

    ~Person(){
    }

    string getName() const{
        return name;
    }
    string getSurname() const{
        return surname;
    }
    string getEmail() const{
        return email;
    }
    string getPhone() const{
        return phone;
    }

    int getid() const{
        return id;
    }

    void setName(string _name){
        name = _name;
    }

    void setSurname(string _surname){
        surname = _surname;
    }

    void setEmail(string _email){
        email = _email;
    }

    void setPhone(string _phone){
        phone = _phone;
    }

    void setid(int _id){
        id = _id;
    }

    friend ostream& operator<<(ostream& os, Person& p);
    friend istream& operator>>(istream& is, Person& p);
};

ostream& operator<<(ostream &os, Person &osoba) {

    os << osoba.name << " ";
    os << osoba.surname << " ";
    os << osoba.email << " ";
    os << osoba.phone << " ";
    os << osoba.id << ". ";

    return os;
}

istream& operator>>(istream &is, Person &osoba) {

    is >> osoba.name;
    is >> osoba.surname;
    is >> osoba.email;
    is >> osoba.phone;
    is >> osoba.id;

    return is;
}


/* stworzenie klasy addressbook o zadanych wlasciwosiach */
class Addressbook {

public:

	vector<Person> bk;

    void open(string);
    void save(string);
    void add(string, string, string, string);
    void show();
    void modify(string, string, string, string, int);
    void deletee(int);
    void sortt();

};

void Addressbook::open(string book_name) {

    ifstream book;
    string name;
    string surname;
    string email;
    string phone;
    int id;

    book.open( book_name.c_str() );
    if( !book.good() )
    {
        cout << "Plik niepoprawny" << endl;
    }

    else {

        while (!book.eof()) {
            book >> name;
            book >> surname;
            book >> email;
            book >> phone;
            add(name, surname, email, phone);
        }

        bk.pop_back();
        book.close();
    };
}

void Addressbook::save(string book_name) {

    ofstream book;

    book.open( book_name.c_str() );
    if( !book.good() )
    {
        cout << "Plik niepoprawny" << endl;
    }

    else{
        for (Person& p: bk) {
            book << p;
        }
    }
}

void Addressbook::add( string name, string surname, string email, string phone) {

    bk.push_back(Person(name, surname, email, phone, bk.size() + 1));

}

void Addressbook::show() {

	for (int i = 0; i < bk.size(); i++) {
		cout << bk[i] << endl;
	}

}

void Addressbook::modify(string name, string surname, string email, string phone, int id) {

    if (id > bk.size() ){
        cout << "Taki wpis nie istnieje" << endl;
    }

    else{
        bk[id - 1].name = name;
        bk[id - 1].surname = surname;
        bk[id - 1].email = email;
        bk[id - 1].phone = phone;
    };
}

void Addressbook::deletee(int id) {

    if (id > bk.size() ){
        cout << "Taki wpis nie istnieje" << endl;
    }

    else{
         for (int i = id; i < bk.size(); i++) {
            bk[i - 1].name = bk[i].name;
            bk[i - 1].surname = bk[i].surname;
            bk[i - 1].email = bk[i].email;
            bk[i - 1].phone = bk[i].phone;
        };

        bk.pop_back();
    };

}

void Addressbook::sortt() {
    sort(bk.begin(), bk.end(), [] (const Person& lhs, const Person& rhs) { return lhs.surname < rhs.surname; });
}


/* stworzenie interfaceu użytkownika */
class UI {
	Addressbook my_book;

public:
	int interface();
    void open_book();
	void show_all();
	void add_id();
	void modify_id();
	void del_id();
	void sort_all();
	void save_book();
};

int UI::interface() {

	char ans;

	cout << "\n1 - otworz" << endl;
	cout << "2 - lista osob" << endl;
	cout << "3 - dodaj wpis" << endl;
	cout << "4 - modyfikuj wpis" << endl;
	cout << "5 - usun wpis" << endl;
	cout << "6 - sortuj wpisy" << endl;
	cout << "7 - zapisz" << endl;

	do {
		ans = getch();
		switch(ans) {
			case '1':
				open_book();
				interface();
				break;
			case '2':
				show_all();
				interface();
				break;
			case '3':
				add_id();
				interface();
				break;
			case '4':
				modify_id();
				interface();
				break;
			case '5':
				del_id();
				interface();
				break;
			case '6':
				sort_all();
				interface();
				break;
			case '7':
				save_book();
				interface();
				break;
		}
	} while (1>0);

	return 0;
}

void UI::open_book() {

	string name;
	cout << "\nPodaj nazwe pliku: ";
	cin >> name;

	my_book.open(name);
}

void UI::show_all() {

	cout << "\nLista osob:" << endl;
	if (my_book.bk.empty() == 1)				// je¿eli nie ma wpisów w ksi¹¿ce adresowej
		cout << "<ksiazka jest pusta>" << endl;		// - wyœwietlenie komunikatu
	else
		my_book.show();

}

void UI::add_id() {

	string ans_name;
	string ans_surname;
	string ans_mail;
	string ans_phone;

	cout << "\nPodaj dane osoby:" << endl;
	cout << "Imie: ";
	cin >> ans_name;
	cout << "\nNazwisko: ";
	cin >> ans_surname;
	cout << "\nE-mail: ";
	cin >> ans_mail;
	cout << "\nNr telefonu: ";
	cin >> ans_phone;

	my_book.add(ans_name, ans_surname, ans_mail, ans_phone);

}

void UI::modify_id() {

	int id;
	string ans_name;
	string ans_surname;
	string ans_mail;
	string ans_phone;

	cout << "\nPodaj wpis, ktory chcesz zmodyfikowac: ";
	cin >> id;
	cin.ignore();

	cout << "\nPodaj dane osoby:" << endl;
	cout << "Imie: ";
	cin >> ans_name;
	cout << "Nazwisko: ";
	cin >> ans_surname;
	cout << "E-mail: ";
	cin >> ans_mail;
	cout << "Nr telefonu: ";
	cin >> ans_phone;

	my_book.modify(ans_name, ans_surname, ans_mail, ans_phone, id);

}

void UI::del_id() {

	int id;
	cout << "\nPodaj wpis, ktory chcesz usunac: ";
	cin >> id;

	my_book.deletee(id);
}

void UI::sort_all() {

    cout << "\nWpisy zostaly posortowane po nazwisku " << endl;
    my_book.sortt();

}

void UI::save_book() {

	string nazwa;
	cout << "\nPodaj nazwe pliku: ";
	cin >> nazwa;

	my_book.save(nazwa);

}


int main() {

	UI user_interface;
	user_interface.interface();

}
