#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Person
{
    string Name, Surname, Email, Phone;
    int id;

public:
    Person(){
    }
    ~Person(){
    }

    string getName() const{
        return Name;
    }
    string getSurname() const{
        return Surname;
    }
    string getEmail() const{
        return Email;
    }
    string getPhone() const{
        return Phone;
    }
    int getid() const{
        return id;
    }
    void setName(string N){
        Name = N;
    }
    void setSurname(string S){
        Surname = S;
    }
    void setEmail(string E){
        Email = E;
    }
    void setPhone(string P){
        Phone = P;
    }
    void setid(int nr){
        id = nr;
    }

    friend ostream& operator<<(ostream& os, Person& p);
    friend istream& operator>>(istream& is, Person& p);
};

ostream& operator<<(ostream& os, Person& p){
    return os << p.id << " " << p.Name << " " <<  p.Surname << " " << p.Email << " " << p.Phone << endl;
}

istream& operator>>(istream& is, Person& p){
    is >> p.id;
    is >> p.Name;
    is >> p.Surname;
    is >> p.Email;
    is >> p.Phone;
    return is;
}

class Addressbook
{
    vector<Person> bk;

public:
    Addressbook(){
    }
    ~Addressbook(){
    }

    void read(string bookname){
        ifstream bookfile;
        bookfile.open(bookname);

        string osoba;

        while(getline(bookfile, osoba)){
            Person p;
            istringstream iss(osoba);
            iss >> p;
            bk.push_back(p);
        }
        bookfile.close();
    }
    void write(string bookname){
        ofstream bookfile;
        bookfile.open(bookname, ios::trunc);

        for (Person& p: bk) {
            bookfile << p;
        }
        bookfile.close();
    }
    bool del(int nr, Person& be){
        for (int i = 0; i < bk.size(); i++){
            if (bk[i].getid() == nr){
                be = bk[i];
                bk.erase(bk.begin() + i);
                return true;
            }
        }
        return false;
    }
    vector<Person> getPersons(){
        return bk;
    }
    void setPerson(Person& p){
        bk.push_back(p);
    }
};

class UI
{
    Addressbook book;
    string bookname;
public:
    UI(string name){
        bookname = name;
        book.read(bookname);
    }
    ~UI(){}

    void add(){
        vector<Person> v = book.getPersons();
        sort(v.begin(), v.end(), [] (const Person& lhs, const Person& rhs) { return lhs.getid() < rhs.getid(); });

        int nr = 1;

        for (Person& p: v){
            if (p.getid() == nr){
                nr++;
            }
        }

        Person p;

        string imie, nazwisko, email, tel;
        cout << "Podaj imie:" << endl;
        cin >> imie;
        p.setName(imie);
        cout << "Podaj nazwisko:" << endl;
        cin >> nazwisko;
        p.setSurname(nazwisko);
        cout << "Podaj email:" << endl;
        cin >> email;
        p.setEmail(email);
        cout << "Podaj telefon:" << endl;
        cin >> tel;
        p.setPhone(tel);
        p.setid(nr);

        book.setPerson(p);

        book.write(bookname);
        cout << "Dodano osobe: " << p << endl;
    }
    void del(int nr){
        Person be;
        if (book.del(nr, be)){
            book.write(bookname);
            cout << "Usunieto osobe: " << be << endl;
        } else {
            cout << "Nie znaleziono osoby o pdanym id" <<endl;
        }
    }
    void modify(int nr){
        Person p;
        if (book.del(nr, p)){
            cout << "Modyfikujesz osobe: " << p << endl;
            string imie, nazwisko, email, tel;
            cout << "Podaj nowe imie:" << endl;
            cin >> imie;
            p.setName(imie);
            cout << "Podaj nowe nazwisko:" << endl;
            cin >> nazwisko;
            p.setSurname(nazwisko);
            cout << "Podaj nowy email:" << endl;
            cin >> email;
            p.setEmail(email);
            cout << "Podaj nowy telefon:" << endl;
            cin >> tel;
            p.setPhone(tel);
            p.setid(nr);

            book.setPerson(p);

            book.write(bookname);
            cout << "Dane osoby po modyfikacji: " << p << endl;
        } else {
            cout << "Nie znaleziono osoby o podanym id" <<endl;
        }
    }
    static void help(){
        cout << "Instrukcja:" << endl;
        cout << "help - wyswietl pomoc" << endl;
        cout << "Jesli nie potrzebujesz pomocy, podaj nazwe ksiazki a po spacji jedno z polecen:" << endl;
        cout << "add - dodaj nowa osobe" << endl;
        cout << "Jesli nie chcesz podawac ktoregos pola z danymi, wpisz -" << endl;
        cout << "delete [id] - usun osobe o podanym numerze id" << endl;
        cout << "modify [id] - modyfikuj dane osoby o podanym numerze id" << endl;
        cout << "sort (id/name/surname/email/phone) - wyswietl zawartosc ksiazki posortowana domyslnie lub wg id/imienia/..." << endl;
    }
    void print(int i) {
        cout << "Osoby: " << endl;
        vector<Person> v = book.getPersons();

        if (i == 1){
            sort(v.begin(), v.end(), [] (const Person& lhs, const Person& rhs) { return lhs.getid() < rhs.getid(); });
        } else if (i == 2){
            sort(v.begin(), v.end(), [] (const Person& lhs, const Person& rhs) { return lhs.getName() < rhs.getName(); });
        } else if (i == 3){
            sort(v.begin(), v.end(), [] (const Person& lhs, const Person& rhs) { return lhs.getSurname() < rhs.getSurname(); });
        } else if (i == 4){
            sort(v.begin(), v.end(), [] (const Person& lhs, const Person& rhs) { return lhs.getEmail() < rhs.getEmail(); });
        } else if (i == 5){
            sort(v.begin(), v.end(), [] (const Person& lhs, const Person& rhs) { return lhs.getPhone() < rhs.getPhone(); });
        }

        for (Person& p: v){
            cout << p << endl;
        }

    }
};

int main(int argc, char* argv[])
{
    if (argc <= 1 || (argc > 1 && string(argv[1]) == "help")) {
        UI::help();
        return 0;
    }
    UI iface(argv[1]);

    if (argc > 2 && string(argv[2]) == "add") {
        iface.add();
        return 0;
    }
    if (argc > 3 && string(argv[2]) == "modify") {
        iface.modify(atoi(argv[3]));
        return 0;
    }
    if (argc > 3 && string(argv[2]) == "delete") {
        iface.del(atoi(argv[3]));
        return 0;
    }
    if (argc > 3 && string(argv[2]) == "sort"){
        if (string(argv[3]) == "id"){
            iface.print(1);
        } else if (string(argv[3]) == "name"){
            iface.print(2);
        } else if (string(argv[3]) == "surname"){
            iface.print(3);
        } else if (string(argv[3]) == "email"){
            iface.print(4);
        } else if (string(argv[3]) == "phone"){
            iface.print(5);
        } else {
            iface.print(0);
        }
        return 0;
    }
    iface.print(0);
}
