#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Person
{
string name, surname, email, number;
int id;

public:
    Person() {}
    Person(string n, string s, string e, string nr, int i)
    {
    name = n;
    surname = s;
    email = e;
    number = nr;
    id = i;
    }

    void load (int i)
    {
        string n, s, e, nr;
        cout << "Name: ";
        cin >> n;
        cout << "Surname: ";
        cin >> s;
        cout << "Email: ";
        cin >> e;
        cout << "Number: ";
        cin >> nr;
        name = n;
        surname = s;
        email = e;
        number = nr;
        id = i;
    }

    int getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    string getSurname()
    {
        return surname;
    }

    string getEmail()
    {
        return email;
    }

    string getNumber()
    {
        return number;
    }

    friend ostream& operator << (ostream&, Person&);
};

    ostream & operator << (ostream &os, Person &p)
    {
        cout << p.id << " " << p.name << " " << p.surname << " " << p.email << " " << p.number << endl;
        return os;
    }

class Adressbook
{
    vector<Person> book;

public:
    Adressbook() {}

    void add()
    {
        Person p;
        int _id;
        if (book.size()==0) _id = -1;
        else _id = book[book.size()-1].getId();
        p.load(_id + 1);
        book.push_back(p);
    }

    void Delete()
    {
        cout << "Podaj nr id do usuniecia" << endl;
        int i;
        cin >> i;
        book.erase(book.begin()+i);
    }

    void modify()
    {
        cout << "Podaj nr id do zmodyfikowania." << endl;
        int i;
        cin >> i;
        Person p;
        p.load(i);
        book[i] = p;
    }

    void list ()
    {
        for (int i=0; i<book.size();i++)
        {
            if(book[i].getId() != -1)
            cout << book[i];
        }
    }

    void sort()
    {
        vector<Person> v = book;
        sort(begin(book), end(book), [] (const Person& lhs, const Person& rhs) { return lhs.getName() < rhs.getName(); });
        list();
        book = v;
    }

    void read(string nazwa)
    {
        nazwa.append(".txt");
        string line;
        ifstream myfile (nazwa.c_str());
        while (getline(myfile, line))
        {
            istringstream iss(line);
            int nr;
            iss >> nr;
            int id = nr;
            string word;
            string T[4];
            for (int i=0; i<=3; i++)
                {
                    iss >> word;
                    T[i] = word;
                }
            string name = T[0];
            string surname = T[1];
            string email = T[2];
            string number = T[3];
            Person p(name, surname, email, number, id);
            book.push_back(p);
        }
        myfile.close();
    }

    void write(string nazwa)
    {
        ofstream myfile ;
        myfile.open (nazwa.c_str(), ios::trunc);
        for (int i=0; i<book.size(); i++)
        {
            myfile << book[i].getId();
            myfile << " ";
            myfile << book[i].getName();
            myfile << " ";
            myfile << book[i].getSurname();
            myfile << " ";
            myfile << book[i].getEmail();
            myfile << " ";
            myfile << book[i].getNumber();
            myfile << "\n";
        }
    }

};

class UI
{
    Adressbook a;
    string nazwaKsiazki;

public:
    UI() {}

    void opener()
    {
        int abc;
        cout << "Wskaz ksiazke adresowa z ktorej chcesz skorzystac." << endl;
        string ab;
        cin >> ab ;
        a.read(ab);
        ab.append(".txt");
        nazwaKsiazki = ab;
    }

    void order()
    {
        while(1)
        {
            cout << "Co chcesz zrobic: 1-wypisz, 2-modyfikuj, 3-usun, 4-dodaj, 5-zakoncz prace z programem" << endl;
            int odczyt;
            cin >> odczyt;
            if (odczyt == 1)
                a.list();
            else if (odczyt == 2)
                {
                    a.modify();
                    a.write(nazwaKsiazki.c_str());
                }
            else if (odczyt == 3)
                {
                    a.Delete();
                    a.write(nazwaKsiazki.c_str());
                }
            else if (odczyt == 4)
                {
                    a.add();
                    a.write(nazwaKsiazki.c_str());
                }
            else if (odczyt == 5)
                exit(0);
        }
    }
};

int main()
{
UI u;
u.opener();
u.order();

return 0;
}
