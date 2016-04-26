#include <fstream>
#include <istream>
#include <iostream>
#include <windows.h>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>


using namespace std;

class Person
{
public:
    int id;
    string Name;
    string Surname;
    string Email;
    string Phone;

friend ostream& operator<<(ostream&, Person &);
friend istream& operator>>(istream&, Person &);

};
ostream& operator<<(ostream &os, Person &p)
{
    os << p.id << " "
       << p.Name << " "
       << p.Surname << " "
       << p.Email << " "
       << p.Phone << endl;
    return os ;
}

istream& operator>>(istream &os, Person &p)
{
    os >>  p.id;
    getline(os, p.Name);
    getline(os, p.Surname);
    getline(os, p.Email);
    getline(os, p.Phone);
    return os ;
}

class AddressBook
{
    public:
        /*wektor z obiektami klasy Person przechowujacy wpisy*/
        vector<Person> bk;
        /*przydatne w klasie UI- czy metody write i read  nie zwróciły błędu*/
        bool error = false;
        /*metoda odczytywania pliku*/
        void write(string bk_file_name);
        /*otwiera plik*/
        void read(string bk_file_name) ;
        /*wylistowanie kontaktów*/
          /*bez sortowania*/
        void list_all();
          /*z sortowaniem według dowolnej kolumny*/
        void sort_by(string column_name);
        /*opcje dodaj/modyfikuj/ usuń wpis w ksiażce adresowej*/
        void add();
        void modify(int id);
        void delete_by_id(int id);
        /*znajdź najniższe id, które możemy wykorzystać do zpaisu*/
        int find_free_id();
        /*znajdź faktyczna ilość adresów w książce (pomijamy puste id)*/
        int find_real_size();
        /*znajdź najwyższe id kontaku w książce- przydatne gdy rozmiar faktyczny jest dużo mniejszy od najwyższego id
        z powodu wielu usnięć.*/
        int highest_existing_id();



};
void AddressBook::write(string bookname){
    ofstream bookfile;

    bookfile.open(bookname, ios::trunc);

    /*obsluga bledu otwarcia*/
    if(!bookfile){
        cout << "Cannot open file " << bookname << endl;
        bookfile.clear(bookfile.rdstate() & ~ios::badbit);
        error = true;
        cout << "Try again... \n" ;
    }else{
    /*zapisanie do pliku kolejnych elementów klasy person wektora bk*/
        for (Person& p: bk) {
            bookfile << p;
        }
    }

    bookfile.close();
}


void AddressBook::read(string bookname){
    ifstream bookfile(bookname);

        /*obsluga bledu otwarcia*/
    if(!bookfile){
        cout << "Cannot open file " << bookname << endl;
        bookfile.clear(bookfile.rdstate() & ~ios::badbit);
        error = true;
        cout << "Try again... \n" ;
    }else{
        int id;
        string Name;
        string Surname;
        string Email;
        string Phone;

        int counter = 0;
        while(bookfile >> id >> Name >> Surname >> Email >> Phone)
        {
            Person p;
            p.id = id;
            p.Name = Name;
            p.Surname = Surname;
            p.Email = Email;
            p.Phone = Phone;
            /*nie mogę użyć push.backa bo gdybym kilkukrotnie wczytywała ten sam plik, powielałabym te same rekordy*/
            if(counter >= bk.size())
                bk.resize(counter + 1);
            bk[counter] = p;
            counter ++;
        }
    }

    bookfile.close();

}


int AddressBook::find_free_id(){
    /*find the smallest unsigned id in bk vector*/
    bool not_found = true;
    int return_id = bk.size() + 1;
    for(int i = 0; i < bk.size() && not_found; i++){
        if(bk[i].id == 0){
            not_found = false;
            return_id = i+1;
        }
    }
    return return_id;
}


int AddressBook::find_real_size(){
    /*find the real size of address book (exclude deleted contracts)*/
    int real_size = 0;
    for(int i = 0; i < bk.size(); i++){
        if(bk[i].id > 0){
            real_size ++;
        }
    }
    return real_size;
}

int AddressBook::highest_existing_id(){
    /*find the real size of address book (exclude deleted contracts)*/
    int highest = 0;
    for(int i = 0; i < bk.size(); i++){
        if(bk[i].id > highest){
            highest = bk[i].id;
        }
    }
    return highest;
}

void AddressBook::add(){
    int add_id = find_free_id();
    Person add_person;
    add_person.id = add_id;
    cout << "Enter contact information:" << endl;
    cout << "Name: ";
    cin  >> add_person.Name;
    cout << "Surname: ";
    cin  >> add_person.Surname;
    cout << "Email: ";
    cin  >> add_person.Email;
    cout << "Phone: ";
    cin  >> add_person.Phone;
    if(bk.size() < add_id){
        bk.resize(add_id);
    }
    int add_id_vect = add_id - 1;
    bk[add_id_vect] = add_person;
    cout << "Contact added" << endl;
}

void AddressBook::modify(int id){
        if(bk.size() < id){
            cout << "Address book entry with id " << id << " not found in this address book" << endl;
        }else{
            Person modify_person = bk[id-1];
            if(modify_person.id > 0){
                cout << "Found address book entry: " << modify_person << endl;

                cout << "Enter updated contact information: " << endl;
                cout << "Name: ";
                cin  >> modify_person.Name;
                cout << "Surname: ";
                cin  >> modify_person.Surname;
                cout << "Email: ";
                cin  >> modify_person.Email;
                cout << "Phone: ";
                cin  >> modify_person.Phone;

                bk[id-1] = modify_person;
                cout << "Contact modified"<< endl;
            }else{
                cout << "Address book entry with id " << id << " not found in this address book" << endl;
            }
        }
}

void AddressBook::delete_by_id(int id){
        string empty_str = "-";
        if(bk.size() < id){
            cout << "Address book entry with id " << id << " not found in this address book" << endl;
        }else{
            int id_del = id-1;
            Person delete_person = bk[id_del];
            if(delete_person.id > 0){
                delete_person.id = 0;
                delete_person.Name = empty_str;
                delete_person.Surname = empty_str;
                delete_person.Email = empty_str;
                delete_person.Phone = empty_str;

                bk[id_del] = delete_person;
                cout << "Contact deleted" <<endl;
            }else{
                cout << "Address book entry with id " << id << " not found in this address book" << endl;
            }
        }
}

void AddressBook::list_all(){
    for(int i = 0; i < bk.size(); i++){
        if(bk[i].id > 0){
            cout << bk[i] <<endl;
        }

    }
}


void AddressBook::sort_by(string column){
    vector<Person> v = bk;
    bool show = true;

    if(column == "id" || column == "Id" )
        sort(begin(v), end(v), [] (const Person& lhs, const Person& rhs) { return lhs.id < rhs.id; });

    else if(column == "name" || column == "Name")
        sort(begin(v), end(v), [] (const Person& lhs, const Person& rhs) { return lhs.Name < rhs.Name; });

    else if(column == "surname" || column == "Surname")
        sort(begin(v), end(v), [] (const Person& lhs, const Person& rhs) { return lhs.Surname < rhs.Surname; });

    else if(column == "email" || column == "Email")
        sort(begin(v), end(v), [] (const Person& lhs, const Person& rhs) { return lhs.Email < rhs.Email; });

    else if(column == "phone" || column == "Phone")
        sort(begin(v), end(v), [] (const Person& lhs, const Person& rhs) { return lhs.Phone < rhs.Phone; });

    else{
        cout << "choose a correct column to sort by it (id/ Name/ Surname/ Email/ Phone)" << endl;
        show = false;
    }
    if(show){
        cout << "Contents: "<< endl;
        for(int i = 0; i < v.size(); i++){
            if(v[i].id > 0){
                cout << v[i] <<endl;
            }
        }
    }

}

class UI
{

    public:
    AddressBook AB;
    Person p;
    void help();
    bool started;
    bool perform;
    string option1;
    string name;

};
void UI::help(){

    if(!started){
        do{
            string name_in;
            cout << "Simple Address Book 1.0" <<endl;
            cout << "Please choose one of the options: " << endl;
            cout << "read    - open existing Address Book, specify name (e.g. read Addressbook1.txt)" <<endl;
            cout << "new     - create new Address Book, specify name (e.g. new Addressbook2.txt)" <<endl;
            cout << "          careful! if you use already existing name, you will overwrite the file" << endl;
            cout << "end now - finish work of program" << endl;
            cin >> option1 >> name;
            if(option1 == "read"){
                AB.read(name);
                if(!AB.error){
                    cout << "Contents: "<< endl;
                    AB.list_all();
                }
                started = true;
            }else if(option1 == "new"){
                cout << "Opening new address book: " << name << endl;
                AB.write(name);
                started = true;
            }else if(option1 == "end" & name == "now"){
                cout << "Ending work of program... "<< endl;
                started = false;
                perform = false;
            }else{
                cout << "Please choose either you want to create new address book or modify existing one" << endl;
            }
        }while((option1 != "read" && option1 != "new" && option1 != "end") || AB.error);
    }

    if(perform){
        cout << "What would you like to do in this address book? " <<endl;
        cout << "add - add contact" <<endl;
        cout << "modify - modify contact (specify id number) " << endl;
        cout << "delete - delete contact (specify id number)" << endl;
        cout << "list - list contacts not sorted" << endl;
        cout << "sort - list contacts sorted (specify either by id/ Name/ Surname/ Email/ Phone)" << endl;
        cout << "return - return to address book selection" << endl;
        string option2;
        cin >> option2 ;
        if(option2 == "add"){
            AB.read(name);
            AB.add();
            AB.write(name);

        }else if(option2 == "modify"){
            int parameter;
            AB.read(name);
            if(AB.find_real_size() > 0){
                cout << "There are " << AB.find_real_size() <<" entries already" <<endl;
                cout << "The highest existing id in book is: " << AB.highest_existing_id() << endl;
                cout << "Give id of contact you would like to modify: " << endl;
                cin >>parameter;
                if(parameter > 0){
                    AB.modify(parameter);
                    AB.write(name);
                }
            }else{
                cout << "There are no contacts in this Address Book. There is nothing to modify." << endl;
            }
        }else if(option2 == "delete"){
            int parameter;
            AB.read(name);
            if(AB.find_real_size() > 0){
                cout << "There are " << AB.find_real_size() <<" entries already" <<endl;
                cout << "The highest existing id in book is: " << AB.highest_existing_id() << endl;
                cout << "Give id of contact you would like to delete: " << endl;
                cin >>parameter;
                if(parameter > 0){
                    AB.delete_by_id(parameter);
                    AB.write(name);
                }
            }else{
                cout << "There are no contacts in this Address Book. There is nothing to delete." << endl;
            }
        }else if(option2 == "list"){
            AB.read(name);
            cout << "Contents: "<< endl;
            AB.list_all();
        }else if(option2 == "sort"){
            string parameter;
            cout << "Specify column by witch you would like to sort: " << endl;
            cout << "id/ Name/ Surname/ Email/ Phone" << endl;
            cin >>parameter;
            AB.read(name);
            AB.sort_by(parameter);
        }else if(option2 == "return"){
           started = false;
           cout << "Work with Address Book named " << name << " is finished" << endl;
        }else{
            cout << "Please, choose one of the options for specified Address Book" <<endl;

        }
    }
}


int main(int argc, char* argv[])
{
    UI iface;
    iface.started = false;
    iface.perform = true;
    AddressBook AB1;
    iface.AB = AB1;

    do{
        if ((argc == 1 || (argc > 1 && string(argv[1]) == "help") ) && iface.perform) {
            iface.help();
            if(!iface.perform)
                argc = 0;
        }
    }while((argc == 1 || (argc > 1 && string(argv[1]) == "help") ) && iface.perform);


}
