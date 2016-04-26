#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


class Person {

    string name;
    string surname;
    string email;
    string phone;
    int id;

public:
    Person();
    Person(int i, string na, string su, string em, string ph);

    string getName() const;
    void setName( string);

    string getSurname() const;
    void setSurname( string);

    string getEmail() const;
    void setEmail( string);

    string getPhone() const;
    void setPhone( string);

    int getId () const;
    void setId ( int);

    friend ostream& operator<<(ostream&, const Person&);
    friend istream& operator>>(istream&, Person &p);
};

Person::Person(){ } //pusty konstruktor - uzytkownik poda dane o nowej sosobie

Person::Person(int i, string na,string su, string em, string ph){ //kostruktor do testowania
    id = i; name = na; surname = su; email = em; phone = ph;
}

ostream& operator<<(ostream &o, const Person& p)
{
    o << p.id << " "<< p.name <<" "<<p.surname<<" "<<p.email<<" "<<p.phone <<endl;
    return o;
}

istream& operator>>(istream &i, Person &p)
{
    i >> p.id; i >> p.name; i >> p.surname; i >> p.email; i >> p.phone;
    return i;
}

int Person::getId() const{ return id;}
void Person::setId(int _id){ id = _id; }

string Person::getName() const{ return name;}
void Person::setName(string _name){name = _name;}

string Person::getSurname() const{ return surname;}
void Person::setSurname(string _surname){ surname = _surname;}

string Person::getEmail() const{ return email;}
void Person::setEmail(string _email){email = _email;}

string Person::getPhone() const{ return phone;}
void Person::setPhone(string _phone){phone = _phone;}


class Addressbook {

    vector<Person> bk; //wektorej osob o nazwie bk

public:
    Addressbook();
    Person& getPersonData (int) const;
    void list(); //wyswietla zawartosc ksiazki adresowej czyli n wierszy
    void add ();
    void drop (int);
    void eraseAll ();
    bool exist (int);
    bool existString (string);
    void modify (int);
    void addSimply(string, string, string, string);
    vector<Person>& getPersons();
    void sorting(Addressbook& book);
    void find();
    void write (string);
    void read (string);
    void options();

};

Addressbook::Addressbook(){ }; //pusty konstruktor

void Addressbook::addSimply(string na, string su, string em, string ph) {
    Person p(bk.size() + 1, na, su, em, ph);
    bk.push_back(p);
}

void Addressbook::add () {
    Person p;
    string na, su, em, ph;
    cout << "Podaj dane kontaktowe:"<< endl;
    cout << "Imie: "; cin >> na;
    cout <<"Nazwisko: "; cin >> su;
    cout<<"Email: "; cin >> em;
    cout<< "Telefon: "; cin >> ph;

    p.setName(na); p.setSurname(su); p.setEmail(em); p.setPhone(ph);
    p.setId(bk.size() + 1); //id ososby to rozmiar wektora przed jej dodaniem + 1
    bk.push_back(p);
    cout <<"Dodano 1 nowy wpis." << endl;
}

void Addressbook::modify (int n) {
    if (!exist(n)) {
        cout <<"W tej ksiazce adresowej nie ma osoby o id "<< n << "." <<endl;
        this -> list();
    }
    else {
        Person p;
        string na, su, em, ph;
        cout << "Podaj dane kontaktowe:"<<endl;
        cout << "Imie: "; cin >> na;
        cout << "Nazwisko: "; cin >> su;
        cout << "Email: "; cin >> em;
        cout << "Telefon: "; cin >> ph;
        cout << endl;
        for (Person& p: bk) {
            if (p.getId() == n){
                p.setName(na); p.setSurname(su); p.setEmail(em); p.setPhone(ph);
            }
        }
        cout << "Zmodyfikowano rekord o numerze " << n << "." <<endl;
    }
}

bool Addressbook::exist (int n) {
    bool jest = false ;
    for (Person& p: bk) {
            if (p.getId() == n)
                jest = true;
        }
    return jest;
}

bool Addressbook::existString (string atrybut) {
    bool jest = false ;
    for (Person& p: bk) {
            if (p.getName()==atrybut || p.getSurname()==atrybut || p.getEmail()==atrybut || p.getPhone()==atrybut)
                jest = true;
        }
    return jest;
}

void Addressbook::drop (int n) {
    if (!exist(n)) {
        cout <<"W tej ksiazce adresowej nie ma osoby o id "<< n << "." <<endl;
        this -> list();
    }
    else {
        for (int i = 0; i < bk.size(); i++) {
            if (bk[i].getId() == n)
                bk.erase(bk.begin() + i);
        }
        cout << "Usunieto rekord " << n <<"." <<endl;
    }
}

void Addressbook::eraseAll () {
    bk.clear();
}

void Addressbook::options() {
    cout << "Dostepne opcje to:" << endl;
    cout << "1. l - komenda list - wyswietla obecny stan ksiazki adresowej" << endl;
    cout << "2. a - komenda add - dodaje nowy wpis" << endl;
    cout << "3. d - komenda delete - kasuje dany wpis" << endl;
    cout << "4. m - komenda modify - modyfikuje dany wpis" << endl;
    cout << "5. f - komenda find - znajduje wpis po id lub po atrybucie" << endl;
    cout << "6. r - komenda read - wczytuje ksiazke adresowa z pliku" << endl;
    cout << "7. w - komenda write - zapisuje obecny stan ksiazki adresowej do pliku" << endl;
    cout << "8. c - komenda clear - usuwa wszystkie wpisy z aktualnej ksiazki adresowej" << endl;
    cout << "9. o - komenda option - wypisuje dostepne opcje" << endl;
    cout << "10. e - komenda exit - zamyka program" << endl;
}

void Addressbook::list()  { //wyswietlanie zawartosci ksiazki adresowej
    if (bk.size() == 0)
           cout << "Ksiazka adresowa jest pusta." << endl;
    else {
        cout<<"Ksiazka adresowa aktualnie zawiera nastepujace " << bk.size() << " rekordy/rekordow." << endl;
        cout << "********************************************************" << endl;
            for (Person& p: bk) {
                cout << p;
            }
        cout << "********************************************************" << endl;
    }
}

void Addressbook::find() {
    string input;
    cout <<"Po jakim atrybucie chcesz odszukac osobe?" << endl;
    cout <<"Jezeli po Id - wprowadz slowo id." << endl;
    cout <<"Jezeli po innym atrybucie takim jak: Imie, Nazwisko, Email lub Telefon - wprowadz ten szukany atrybut." << endl;
    cin >> input;
    if (input == "id") {
        int id;
        cout <<"Wprowadz szukane Id: ";
        cin >> id;
            if (exist(id)){
                cout << "Znaleziono wpis:"<<endl;
                for (Person& p: bk) {
                    if (p.getId() == id)
                        cout << p;
                }
            }
            else {
                cout <<"W tej ksiazce adresowej nie ma osoby o id "<< id << "." <<endl;
                this->list();
            }
    }
    else {
        if (existString(input)){
                cout << "Znaleziono nastepujace wpisy:"<<endl;
                for (Person& p: bk) {
                    if (p.getName()==input || p.getSurname()==input || p.getEmail()==input || p.getPhone()==input)
                        cout << p;
                }
            }
            else {
                cout <<"W tej ksiazce adresowej nie ma osob o podanym atrybucie: "<< input <<endl;
                this->list();
            }
    }
}


/*
Person& Addressbook::getPersonData(int n) const {
return
}*/

vector<Person>& Addressbook::getPersons() {
    return bk;
}

/*
void Addressbook::sorting(Addressbook& book) {
    vector<Person> v = book.getPersons();
    sort(begin(v), end(v), [] (const Person& lhs, const Person& rhs) { return lhs.getName() < rhs.getName(); });
}*/

void Addressbook::write(string bookname) {
    ofstream bookfile;

    bookfile.open(bookname, ios::trunc);

    for (Person& p: bk) {
            bookfile << p;
        }
        bookfile.close();
}

void Addressbook::read(string bookname) {
    string word;
    vector <string> words;
    int ile = 0;
    ifstream myfile (bookname);
    if (myfile.is_open()) {

        while ( myfile.good()) {

            while (myfile >> word){
                words.push_back(word); //sczytujemy slowa do wektora
            }
        }
        myfile.close(); //zamykamy plik

        for (int i = 1; i < words.size(); i+=5) // omijamy co 5. element bo tam beda id kolejnych osob
            this->addSimply (words[i],words[i+1],words[i+2], words[i+3]); //prostym dodaniem tworzymy osoby
    }
    else {
        cout << "Otwieranie pliku sie nie powiodlo. Upewnij sie, ze podany plik istnieje." <<endl;
    }

}

int main()
{
    cout << "*********      PROSTA KSIAZKA ADRESOWA       ***********" <<endl;

    Addressbook book1; //tworzymy ksiazke o nazwie book1 i dodajemy do niej 5 ponizszych rekordow
    book1.addSimply("Jan", "Kowalski", "jk@dp.pl", "1112223");
    book1.addSimply("Wacek", "Abiz", "abiz@dp.pl", "11155553");
    book1.addSimply("Iwona", "Abiz", "abiz@dp.pl", "11155553");
    book1.addSimply("Zbigniew", "Jantar", "jako@dp.pl", "13333333");
    book1.addSimply("Jola", "Stonoga", "abiz@dp.pl", "1188888888");

    book1.options();
    cout << "********************************************************" << endl;
    cout << "W celu wybrania opcji podaj litere." <<endl;
    book1.list();

    char wybor;
    int id;
    string file;
        do {

            cin >> wybor;

            switch(wybor)
            {
            case 'l':
                book1.list();
            break;

            case 'a':
                book1.add();
            break;

            case 'f':
                book1.find();
            break;

            case 'd':
                cout << "Podaj id rekordu do usuniecia." << endl;
                cin >> id;
                book1.drop( id);
            break;

            case 'c':
                book1.eraseAll();
                cout << "Usunieto wszystkie wpisy." << endl;
            break;

            case 'm':
                cout << "Podaj id rekordu do modyfikacji." << endl;
                cin >> id;
                book1.modify( id);
            break;

            case 'r':
                cout << "Podaj nazwe pliku do wczytania." << endl;
                cin >> file;
                book1.read( file);
            break;

            case 'w':
                cout << "Podaj nazwe zapisywanego pliku." << endl;
                cin >> file;
                book1.write( file);
            break;

            case 'o':
                book1.options();
            break;

            case 'e':
                cout << "Zamykam ksiazke adresowa." << endl;
            break;

            default:
                cout<<"Nie ma takiej opcji w programie!" << endl << endl;
                book1.options();
            break;
            }

        } while (wybor != 'e');


return 0;
}
