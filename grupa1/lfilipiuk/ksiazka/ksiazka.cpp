#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Person
{
    string name, surname, email, phone;
    int id;

public:
    Person(string n, string s, string e, string p, int identyfikator)
    {
        name = n;
        surname = s;
        email = e;
        phone = p;
        id = identyfikator;
    }

friend ostream& operator<<(ostream&, Person&);

string getName() const {
return name;
}

int getId() const {
return id;
}

};

 ostream & operator << (ostream &os, Person &p)
    {
        cout << p.id << " " << p.name << " " << p.surname << " " << p.email << " " << p.phone << endl;
        return os;
    }


class AddressBook{

    vector<Person> ksiazka;

public:

void add(){
    Person a = getPerson();
    ksiazka.push_back(a);
}

Person getPerson(){
    string name, surname, email, phone;

    cout<< "Enter contact information:"<<endl;
    cout<< "Name: ";
    cin>>name;
    cout<< "Surname: ";
    cin>>surname;
    cout<< "Email: ";
    cin>>email;
    cout<< "Phone: ";
    cin>>phone;

    int max_id = 0;
    for (const Person& p: ksiazka) {
        if (p.getId() > max_id) { max_id = p.getId(); }
    }

    return Person(name, surname, email,phone, max_id + 1);
}

void modify(int i){
    Person a = getPerson();
    ksiazka[i] = a;
}


void wypisz(){
    cout<<"Contents:\n"<<endl;
    for(int i=0;i<ksiazka.size();i++)
        cout<<ksiazka[i];
    cout<<endl;
}

void kasuj(int id){
    int index=-1;
    for (int i = 0; i < ksiazka.size(); i++) {
        if (ksiazka[i].getId() == id) {}
            index = i;
    }
    if (index!=-1)
        ksiazka.erase(ksiazka.begin()+index);
}

void sortuj(){

vector<Person> v = ksiazka;
sort(begin(ksiazka), end(ksiazka), [] (const Person& lhs, const Person& rhs) { return lhs.getName() < rhs.getName(); });

wypisz();
ksiazka = v;
}

    void write(string bookname) {
        ofstream bookfile;

        bookfile.open(bookname, ios::trunc);

        for (Person& p: ksiazka) {
            bookfile << p;
        }

        bookfile.close();
    }
};



/*
int main(int argc, char* argv[]){

   cout << "wpisano " << argc << "parametrow:" << endl;
   for (int i =0 ; i < argc; i++)
        cout << argv[i] << endl;
*/

int main(){
AddressBook ab;
ab.add();
ab.add();
ab.wypisz();
cout<<"Kasowanie"<<endl;
ab.kasuj(0);
ab.add();
ab.wypisz();
//ab.write("Plik.txt");

}
