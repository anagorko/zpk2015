#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Person
{
        int ID;
        string Name;
        string Surname;
        string Phone;
        string Email;

public:

    void setID(int id){
        ID = id;
    };
    void setName(string n){
        Name = n;
    };
    void setSurname(string s){
        Surname = s;
    };
    void setPhone(string p){
        Phone = p;
    };
    void setEmail(string e){
        Email = e;
    };

    int getID() const{
        return ID;
    };
    string getName() const{
        return Name;
    };
    string getSurname() const{
        return Surname;
    };
    string getPhone() const{
        return Phone;
    };
    string getEmail() const{
        return Email;
    };

    friend ostream& operator<<(ostream& os, const Person &p);
    friend ofstream& operator<<(ofstream& os, const Person &p);
};

ostream& operator<<(ostream& os, const Person &p){
    os << p.ID << " " << p.Name << " " << p.Surname << " " << p.Phone << " " << p.Email << endl;
    return os;
};

ofstream& operator<<(ofstream& os, const Person &p){
    os << p.ID << " " << p.Name << " " << p.Surname << " " << p.Phone << " " << p.Email << endl;
    return os;
};

class AddressBook
{
    vector <Person> book;

public:

    vector <Person> getPersons() const{
        return book;
    };

    int returnID(int i){
        return book[i].getID();
    };

    int returnPos(int p){
        bool exist = false;
        for(int i = 0;i<book.size();i++){
            if(returnID(i) == p){
                return i;
                exist = true;
                break;
            }
        }
        if(exist==false)
            return -1;
    };

    int getNewId(){
        if(book.size() == 0)
            return 1;
        else
            return book[book.size() - 1].getID() + 1;
    };

    void add(){
        Person p;
        p.setID(getNewId());
        string name;
        cout << "Wprowadz imie: ";
        cin >> name;
        p.setName(name);
        string surname;
        cout << "Wprowadz nazwisko: ";
        cin >> surname;
        p.setSurname(surname);
        string phone;
        cout << "Wprowadz numer telefonu: ";
        cin >> phone;
        p.setPhone(phone);
        string email;
        cout << "Wprowadz adres e-mail: ";
        cin >> email;
        p.setEmail(email);
        book.push_back(p);
    };

    void contacts(){
        if(book.size()==0)
            cout << "Ksiazka adresowa jest pusta" << endl;
        else {
            cout << "Zawartosc ksiazki adresowej: " << endl;
            for(int i = 0;i < book.size();i++){
                cout << book[i];
            }
        }
    };

    void remove(){
        cout << "Wprowadz ID do usuniecia" << endl;
        int i;
        cin >> i;
        if(returnPos(i)==-1)
            cout << "Brak wpisu o podanym ID" << endl;
        else{
            book.erase(book.begin() + returnPos(i));
            cout << "Usunieto wpis" << endl;
        }
    };

    void DeleteAll(){
        book.clear();
    };

    bool IfEmpty(){
        if(book.empty())
            return true;
        else
            return false;
    };

    void modify(){
        cout << "Wprowadz ID do zmodyfikowania" << endl;
        int i;
        cin >> i;
        if(returnPos(i)==-1)
            cout << "Brak wpisu o podanym ID" << endl;
        else {
        cout << "Wprowadz nowe dane:" << endl;
        Person p;
        p.setID(i);
        string name;
        cout << "Wprowadz imie: ";
        cin >> name;
        p.setName(name);
        string surname;
        cout << "Wprowadz nazwisko: ";
        cin >> surname;
        p.setSurname(surname);
        string phone;
        cout << "Wprowadz numer telefonu: ";
        cin >> phone;
        p.setPhone(phone);
        string email;
        cout << "Wprowadz adres e-mail: ";
        cin >> email;
        p.setEmail(email);
        book[returnPos(i)] = p;
        cout << "Wpis zostal zmodyfikowany" << endl;
        }
    };

    void sorting(string column){
        if (book.size() == 0)
            cout << "Ksiazka adresowa jest pusta." << endl;
        else{
            vector <Person> v = this -> getPersons();
            if(column == "imie")
                sort(begin(v), end(v), [] (const Person& lhs, const Person& rhs) { return lhs.getName() < rhs.getName(); });
            if(column == "nazwisko")
                sort(begin(v), end(v), [] (const Person& lhs, const Person& rhs) { return lhs.getSurname() < rhs.getSurname(); });
            if(column == "id")
                sort(begin(v), end(v), [] (const Person& lhs, const Person& rhs) { return lhs.getID() < rhs.getID(); });

            cout << "Posortowane wpisy:" << endl;
            for (Person& p: v) {
                cout << p;
            }
            string wybor;
            cout << "Czy zachowac zmiany? (t/n) _\b";
            cin >> wybor;
            if(wybor == "t")
                book = v;
        }
    };

    void write(string bookname) {
        ofstream bookfile;

        bookfile.open(bookname, ios::trunc);

        for (Person& p: book) {
            bookfile << p;
        }

        bookfile.close();
    };

    void read(string bookname){
        fstream bookfile;
        string id;
        string name;
        string surname;
        string phone;
        string email;

        book.clear();

        bookfile.open(bookname, ios::in);
        if (bookfile.good() != true){
            cout << "Nie udalo sie wczytac pliku" << endl;
            bookfile.close();
        }
        else{
            Person p;
            while(!bookfile.eof()){
                getline(bookfile, id,' ');
                getline(bookfile, name,' ');
                getline(bookfile, surname,' ');
                getline(bookfile, phone,' ');
                getline(bookfile, email);
                int id2 = atoi(id.c_str());
                p.setID(id2);
                p.setName(name);
                p.setSurname(surname);
                p.setPhone(phone);
                p.setEmail(email);
                book.push_back(p);
            }
        }
        bookfile.close();
        if(returnPos(0) != -1)
            book.erase(book.begin() + returnPos(0));
    };
};

class UI{

private:

    AddressBook book;

public:
    void MainMenu(){
        string wybor;
        cout << "     Ksiazka adresowa 0.99" << endl << endl;
        cout << "     Menu glowne" << endl;
        cout << "1: Nowa ksiazka adresowa" << endl;
        cout << "2: Wczytaj ksiazke adresowa z pliku" << endl;
        cout << "3: Wyswietl zawartosc ksiazki adresowej" << endl;
        cout << "4: Dodaj wpis do ksiazki adresowej" << endl;
        cout << "5: Zmodyfikuj wpis w ksiazce adresowej" << endl;
        cout << "6: Usun wpis z ksiazki adresowej" << endl;
        cout << "7: Posortuj wpisy" << endl;
        cout << "8: Zapisz ksiazke adresowa do pliku" << endl;
        cout << "9: Zakoncz program" << endl << endl;
        cout << "Co chcesz zrobic? _\b";
        cin >> wybor;
        while (wybor != "1" && wybor != "2" && wybor != "3" && wybor != "4" && wybor != "5" && wybor != "6" &&
               wybor != "7" && wybor != "8" && wybor != "9") {
            cout << "Bledny numer. Sprobuj jeszcze raz: _\b";
            cin >> wybor;
            }
            if(wybor != "9")
                system("cls");

            if(wybor == "1")
                NewAddressBook();
            else if(wybor == "2")
                ReadAddressBook();
            else if(wybor == "3")
                ShowAddressBook();
            else if(wybor == "4")
                AddAddressToBook();
            else if(wybor == "5")
                ModifyAddress();
            else if(wybor == "6")
                RemoveAddress();
            else if(wybor == "7")
                SortAddresses();
            else if(wybor == "8")
                WriteBook();
            else if(wybor == "9")
                return;
    };

    void NewAddressBook(){
        string zapis;
        if(book.IfEmpty() == false){
            cout << "Czy chcesz zapisac aktualnie otwarta ksiazke adresowa? (t/n) _\b";
            cin >> zapis;
                if(zapis == "t"){
                    string bookname;
                    cout << "Podaj nazwe ksiazki adresowej, ktora chcesz zapisac" << endl;
                    cin >> bookname;
                    bookname += ".txt";
                    book.write(bookname);
                    book.DeleteAll();
                }
                else
                    book.DeleteAll();
        }
        string wybor;
        book.DeleteAll();
        cout << "Czy chcesz dodac pierwszy wpis do ksiazki adresowej? (t/n) _\b";
        cin >> wybor;
        if(wybor == "t"){
            book.add();
        }
        while(wybor != "n"){
            cout << "Czy chcesz dodac kolejny wpis do ksiazki adresowej? (t/n) _\b";
            cin >> wybor;
            if (wybor == "t")
                book.add();
            else
                break;
        }
        system("cls");
        MainMenu();
    };

    void ReadAddressBook(){
        string wybor;
        if(book.IfEmpty() == false){
            cout << "Czy chcesz zapisac aktualnie otwarta ksiazke adresowa? (t/n) _\b";
            cin >> wybor;
            if(wybor == "t"){
                string bookname;
                cout << "Podaj nazwe ksiazki adresowej, ktora chcesz zapisac" << endl;
                cin >> bookname;
                bookname += ".txt";
                book.write(bookname);
                book.DeleteAll();
                string bookname2;
                cout << "Podaj nazwe ksiazki adresowej, ktora chcesz wczytac" << endl;
                cin >> bookname2;
                bookname2 += ".txt";
                book.read(bookname2);
                if(book.IfEmpty() == false){
                    cout << "Ksiazka adresowa zostala wczytana poprawnie" << endl;
                    cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
                    string menu;
                    cin >> menu;
                    if(menu != ""){
                        system("cls");
                        MainMenu();
                    }
                }
                if(book.IfEmpty()){
                    cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
                    string menu;
                    cin >> menu;
                    if(menu != ""){
                        system("cls");
                        MainMenu();
                    }
                }
            }
            if(wybor == "n"){
                book.DeleteAll();
                string bookname;
                cout << "Podaj nazwe ksiazki adresowej, ktora chcesz wczytac" << endl;
                cin >> bookname;
                bookname += ".txt";
                book.read(bookname);
                if(book.IfEmpty() == false){
                    cout << "Ksiazka adresowa zostala wczytana poprawnie" << endl;
                    cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
                    string menu;
                    cin >> menu;
                    if(menu != ""){
                        system("cls");
                        MainMenu();
                    }
                }
                if(book.IfEmpty()){
                    cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
                    string menu;
                    cin >> menu;
                    if(menu != ""){
                        system("cls");
                        MainMenu();
                    }
                }
            }
        }
        if(book.IfEmpty()){
            book.DeleteAll();
            string bookname;
            cout << "Podaj nazwe ksiazki adresowej, ktora chcesz wczytac" << endl;
            cin >> bookname;
            bookname += ".txt";
            book.read(bookname);
            if(book.IfEmpty() == false){
                cout << "Ksiazka adresowa zostala wczytana poprawnie" << endl;
                cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
                string menu;
                cin >> menu;
                if(menu != ""){
                    system("cls");
                    MainMenu();
                }
            }
            if(book.IfEmpty()){
                cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
                string menu;
                cin >> menu;
                if(menu != ""){
                    system("cls");
                    MainMenu();
                }
            }
        }
    };

    void ShowAddressBook(){
        book.contacts();
        cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
            string menu;
            cin >> menu;
            if(menu != ""){
                system("cls");
                MainMenu();
            }
    };

    void AddAddressToBook(){
        book.add();
        string wybor;
        while(wybor != "n"){
            cout << "Czy chcesz dodac kolejny wpis do ksiazki adresowej? (t/n) _\b";
            cin >> wybor;
            if (wybor == "t")
                book.add();
            else
                break;
        }
        cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
            string menu;
            cin >> menu;
            if(menu != ""){
                system("cls");
                MainMenu();
            }
    };

    void ModifyAddress(){
        book.modify();
        string wybor;
        while(wybor != "n"){
            cout << "Czy chcesz zmodyfikowac kolejny wpis w ksiazce adresowej? (t/n) _\b";
            cin >> wybor;
            if (wybor == "t")
                book.modify();
            else
                break;
        }
        cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
            string menu;
            cin >> menu;
            if(menu != ""){
                system("cls");
                MainMenu();
            }
    };

    void RemoveAddress(){
        book.remove();
        string wybor;
        while(wybor != "n"){
            cout << "Czy chcesz usunac kolejny wpis z ksiazki adresowej? (t/n) _\b";
            cin >> wybor;
            if (wybor == "t")
                book.remove();
            else
                break;
        }
        cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
            string menu;
            cin >> menu;
            if(menu != ""){
                system("cls");
                MainMenu();
            }
    };

    void SortAddresses(){
        string sorting;
        cout << "Po ktorej kolumnie chcesz posortowac wpisy? (imie, nazwisko, id)" << endl;
        cin >> sorting;
        while(sorting != "imie" && sorting != "nazwisko" && sorting != "id"){
            cout << "Bledna nazwa kolumny. Sprobuj jeszcze raz (imie, nazwisko, id) _\b";
            cin >> sorting;
        }
        book.sorting(sorting);
        string wybor;
        while(wybor != "n"){
            cout << "Czy chcesz posortowac wpisy po innej kolumnie? (t/n) _\b";
            cin >> wybor;
            if (wybor == "t"){
                cout << "Po ktorej kolumnie chcesz posortowac wpisy? (imie, nazwisko, id)" << endl;
                cin >> sorting;
                while(sorting != "imie" && sorting != "nazwisko" && sorting != "id"){
                        cout << "Bledna nazwa kolumny. Sprobuj jeszcze raz (imie, nazwisko, id) _\b";
                        cin >> sorting;
                }
                book.sorting(sorting);
            }
            else
                break;
        }
        cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
            string menu;
            cin >> menu;
            if(menu != ""){
                system("cls");
                MainMenu();
            }
    };

    void WriteBook(){
        cout << "Podaj nazwe ksiazki adresowej, ktora chcesz zapisac" << endl;
        string nazwa;
        cin >> nazwa;
        nazwa += ".txt";
        book.write(nazwa);
        cout << "Ksiazka adresowa zostala zapisana" << endl;
        cout << "Nacisnij dowolny przycisk, aby powrocic do Menu glownego" << endl;
            string menu;
            cin >> menu;
            if(menu != ""){
                system("cls");
                MainMenu();
            }
    };
};

int main(){
    UI ui;
    ui.MainMenu();
};
