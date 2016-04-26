#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Person
{
public:
    string name;
    string surname;
    string email;
    string phone;
    int  id;

    Person(string _name, string _surname, string _email,  string _phone, int  _id)
    {

        name=_name;
        surname=_surname;
        email=_email;
        phone=_phone;
        id=_id;
    }

    ~Person(){}
};
 ostream& operator<<(ostream &o, Person p){

         o<<"Name: "<< p.name<<endl;
         o<<"Surname: "<< p.surname<<endl;
         o<<"Email: "<< p.email<<endl;
         o<<"Phone: "<< p.phone<<endl;
         o<<"Id: "<< p.id<<endl;

    return o;
}

 istream& operator>>(istream &i, Person &p) {

     i>>p.surname;
     i>>p.email;
     i>>p.phone;
     i>>p.id;

     return i;
}



class Addressbook
{


vector<Person> bk;

//zapisywanie do pliku
void write(string bookname) {
        ofstream bookfile;
        bookfile.open(bookname, ios::trunc);

        for (Person& p: bk) {
            bookfile << p;
        }

        bookfile.close();
    }

//wypisywanie ksiazki
void read(string bookname) {
        ofstream bookfile;
        bookfile.open(bookname, ios::trunc);

        for (Person& p: bk) {
            cout<< p;
        }

        bookfile.close();
    }

//dodawanie osoby
void add(string bookname) {
        Person p;
        ofstream bookfile;
        bookfile.open(bookname, ios::trunc);
        cout<<"podaj dane osoby"<<endl;
        cin>>p;
        bookfile << p;

        bookfile.close();
    }

void del(string bookname, int i){

        Person p;
        ofstream bookfile;
        bookfile.open(bookname, ios::trunc);

        //usuniêcie
        for (Person p: bk) {
            if (p.id==i) { ~p(); }
        }

        //zmiana numeracji pozostalych
        for (Person p: bk) {
            if (p.id>i) { p.id=p.id-1;}
        }

        bookfile.close();

}


void mod(string bookname, int i, char* c){

        Person p;
        ofstream bookfile;
        bookfile.open(bookname, ios::trunc);

        for (Person p: bk) {
            if (p.id==i) {
                if(c="n"){cout<<"podaj imie"<<endl;cin>>p.name;};
                if(c="s"){cout<<"podaj nazwisko"<<endl;cin>>p.surname; };
                if(c="e"){cout<<"podaj email"<<endl;cin>>p.email; };
                if(c="p"){cout<<"podaj telefon"<<endl;cin>>p.phone; };
                }
        }

        bookfile.close();

}

};



class UI{
public:
     void help(){
    cout<<"dostepne funkcje"<<endl;
    cout<<"utworz ksiazke -> *new* +  nazwe ksiazki" <<endl;
    cout<<"dodaj osobe -> *add* + nazwe ksiazki "<<endl;
    cout<<"wypisz ksiazke -> *read* + nazwe ksiazki" <<endl;
    cout<<"usun osobe -> *del* + nazwa kasizki + nr id" <<endl;
    cout<<"zmien dane osoby -> *mod* +  nazwa kasizki +nr id + n/s/e/p" <<endl;
    cout<<"dane osoby -> *getper* +  nazwa kasizki + nr id " <<endl;
    cout<<"" <<endl;
    }

   Person getPersonData(string bookname, int i){

        Person p;
        vector<Person> bk;

        ofstream bookfile;
        bookfile.open(bookname, ios::trunc);

        for ( p: bk) {
            if (p.id==i) { return p;  }
        }

        bookfile.close();
}


};

int main(int argc, char* argv[])
{
  UI iface;

   if (argc == 1 || (argc > 1 && string(argv[1]) == "help")) {
        iface.help();
        return 0;
    }
   if (string(argv[1]) == "new") {
       Addressbook.write(string(argv[2]);
        return 0;
    }

   if (string(argv[1]) == "add") {
       Addressbook.add(string(argv[2]);
        return 0;
    }

   if (string(argv[1]) == "read") {
       Addressbook.read(string(argv[2]);
        return 0;
    }

    if (string(argv[1]) == "del") {
       Addressbook.del(string(argv[2]), int(argv[3]));
        return 0;
    }

    if (string(argv[1]) == "mod") {
       Addressbook.mod(string(argv[2]), int(argv[3]), arqv[4]);
        return 0;
    }

    if (string(argv[1]) == "getper") {
       cout<<iface.getPersonData(string(argv[2]), int(argv[3]))<<endl;
        return 0;
    }

}

