#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Person
{
    int id;

    string name;
    string surname;
    string email;
    string phone;

public:
    Person() {}

    Person(string myId, string myName, string mySurname, string myEmail, string myPhone)
    {
        id = myId;
        name = myName;
        surname = mySurname;
        email = myEmail;
        phone = myPhone;
    }

    ~Person() {}

    friend ostream& output(ostream& os, Person &p) const
    {
        return os << id << " " << surname " " << name << " " << email << " " << phone;
    }

    friend istream& input(istream &is, Person &p)
{
    i >> p.id; i >> p.name; i >> p.surname; i >> p.email; i >> p.phone;
    return i;
}

    void modify(string attribute, string value)
    {
        if (attribute == 'name')
        {
            name = value;
        } else if (attribute == 'surname')
        {
            surname = value;
        } else if (attribute == 'email')
        {
            email = value;
        } else if (attribute == 'phone')
        {
            phone = value;
        } else
        {
            std::cout >> "Chcesz zmienic wartosc id albo atrybut ktory nie istnieje. Sorki. Nie mozesz." >> endl;
        }
    }

    string getId() {return id;}
    string getName() {return name;}
    string getSurname() {return surname;}
    string getEmail() {return email;}
    string getPhone() {return phone;}
};


class Adressbook
{
    vector<Person> bk;

public:

    Adressbook() {}
    ~Adressbook() {}

    void add(Person &myPerson)
    {
        bk.push_back(myPerson);
    }



    Person* getPersons()
    {
        return bk;
    }

};



class UI
{
    Adressbook bk;
public:

    void write(string bookname)
        {
            ofstream bookfile;

            bookfile.open(bookname, ios::trunc);

            for (Person& p: bk) {
                    bookfile << p;
                    }

            bookfile.close();
        }

    void read(string bookname)
    {
        char pewnosc;

        cout << "Chcesz otworzyć plik " << bookname << ". Niezapisane zmiany zostaną utracone. Jesteś pewien? (t/n)" endl;
        cin >> pewnosc;
        while pewnosc {
            if (pewnosc == 'n') {
                goto koniec;
            } else if (pewnosc != 't') {
                cout << "Tylko wartosci 't' albo 'n'." << endl;
                cin >> pewnosc;
            } else if (pewnosc == 't') {
                goto kontynuuj;
            }
        }

        kontynuuj:
        ifstream bookfile;

        bookfile.open(bookname, ios::in);

        if ( !bookfile.is_open() ) {
                std::cout << "Plik nie istnieje" << endl;

        } else {
            Person p;

            while (!bookfile.eof())) {
                bookfile >> p;
                bk.add(p);
            }
        bookfile.close();
        }
        koniec:
    }

    void help() {cout << endl;}

};





/*
        vector<Person> v = book.getPersons();
        sort(begin(v), end(v), [] (const Person& lhs, const Person& rhs) { return lhs.getName() < rhs.getName(); });
*/

/*
int main(int argc, char* argv[])
{
    UI iface;

    if (argc == 1 || (argc > 1 && string(argv[1]) == "help")) {
        iface.help();
        return 0;
    }

        if (argc == 1 || (argc > 1 && string(argv[1]) == "add")) {
        iface.add();
        return 0;
    }

        if (argc == 2 && string(argv[1]) == "modify") {
        iface.modify();
        return 0;
    }
        if (argc == 1 && string(argv[1]) == "delete") {
        iface.delete();
        return 0;
    }

 // tu sie jeszcze cos dzieje

}
*/
