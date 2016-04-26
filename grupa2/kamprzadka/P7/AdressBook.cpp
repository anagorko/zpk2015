#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

class Person
{
    public:
    struct PersonData
    {
        string imie, nazwisko, telefon, email;
        int id;
    };

    PersonData dane;


   // ostream& operator<<(ostream& os) const {
  //      return os << "id: "<<dane.id << "imie: " << dane.imie << endl << "nazwis: "<<dane.nazwisko<<endl<<dane.telefon<<endl<<dane.email<<endl;
   // }

    Person(int _id, string _imie, string _nazwisko, string _telefon, string _email)
    {
        dane.id=_id;
        dane.imie=_imie;
        dane.nazwisko=_nazwisko;
        dane.telefon=_telefon;
        dane.email=_email;
    }


};

class AddressBook
{

    public:
    vector <Person> lista;
    string tab="\t";

    void add()
    {
        cout<<"Dodaj element do ksiazki adresowej\n";
        string _imie, _nazwisko, _telefon, _email;
        cout<<"Imie: ";
        cin>>_imie;
        cout<<"Nazwisko: ";
        cin>>_nazwisko;
        cout<<"Telefon: ";
        cin>>_telefon;
        cout<<"Email: ";
        cin>>_email;
        int _id=lista.size()+1;
        Person n(_id, _imie, _nazwisko, _telefon, _email );
        lista.push_back(n);
        cout<<endl;
    }

    void add_raw(string _imie, string _nazwisko, string _telefon, string _email)
    {
        int _id=lista.size()+1;
        Person n(_id, _imie, _nazwisko, _telefon, _email );
        lista.push_back(n);
    }


    void listB()
    {
        cout<<"ID\tImie\tNazwis\tTelefon\tEmail"<<endl;
        int elem = lista.size();
        for (int i=0; i<elem; i++)
            cout<<lista[i].dane.id<<tab<<lista[i].dane.imie<<tab<<lista[i].dane.nazwisko<<tab<<lista[i].dane.telefon<<tab<<lista[i].dane.email<<endl;
    }

    bool alfabet(const Person &l, const Person &p)
    {
        return l.dane.nazwisko < p.dane.nazwisko;
    }

    void list_sort()
    {
        vector <Person> lista_pom;
        lista_pom=lista;
  //      sort (lista_pom.begin(), lista_pom.end(), alfabet); blad kompilacji w predefined_ops.h
        cout<<"ID\tImie\tNazwis\tTelefon\tEmail"<<endl;
        int elem = lista.size();
        for (int i=0; i<elem; i++)
            cout<<lista_pom[i].dane.id<<tab<<lista_pom[i].dane.imie<<tab<<lista_pom[i].dane.nazwisko<<tab<<lista_pom[i].dane.telefon<<tab<<lista_pom[i].dane.email<<endl;


    }

    void modify (int _id) //modyfikuje element
    {
        //cout<<"Dotychczasowe dane: "<<endl;
        //cout<<lista[_id-1].dane.id<<endl;
        cout<<"Podaj nowe dane: "<<endl;
        string _imie, _nazwisko, _telefon, _email;
        cout<<"Imie: ";
        cin>>_imie;
        cout<<"Nazwisko: ";
        cin>>_nazwisko;
        cout<<"Telefon: ";
        cin>>_telefon;
        cout<<"Email: ";
        cin>>_email;
        Person n(_id, _imie, _nazwisko, _telefon, _email);
        lista.at(_id-1)=n;
    }

    void del (int _id) //usuwa element
    {
        int i=_id-1;
        string odp;
        cout<<"Dotychczasowe dane: "<<endl;
        cout<<lista[i].dane.id<<tab<<lista[i].dane.imie<<tab<<lista[i].dane.nazwisko<<tab<<lista[i].dane.telefon<<tab<<lista[i].dane.email<<endl;

        cout<<"Czy chcesz usunac ten rekord? (T/N)"<<endl;
        cin>>odp;
        if(odp=="T" | odp=="t")
        {
            lista.erase(lista.begin()+i);
            for (int j=0; j<lista.size(); j++) //ponowne przeliczenie ID
                lista[j].dane.id=j+1;
        }

    }



    write(string adres) //zapisuje do pliku
    {
        string tab="\t";
        ofstream F (adres.c_str());
        int elem = lista.size();
        if (F)
        {
            for (int i=0; i<elem; i++)
                F<<lista[i].dane.imie<<tab<<lista[i].dane.nazwisko<<tab<<lista[i].dane.telefon<<tab<<lista[i].dane.email<<endl;
        }
        else
            cout << "Wystapil blad przy zapisie pliku\n";
        F.close();
    }

    read(string adres) //wczytuje z pliku
    {
        string imie, nazwisko, telefon, email;
        ifstream F (adres.c_str());
        if (F)
        {
            while(F.good())
            {
                F>>imie>>nazwisko>>telefon>>email;
                add_raw(imie, nazwisko, telefon, email);
            }
        }
        else
            cout << "Wystapil blad przy otwieraniu pliku\n";
        F.close();
    }
};

int main(int argc, char** argv)
{
    AddressBook Ab;
   // AddressBook Ab2;

    Ab.read("lista.txt");
    /*
    Ab.add();
    Ab.add();
    Ab.add();
    Ab.add();*/

    Ab.listB();
    //cout<<"a\n";
    //Ab.modify(2);
   // Ab.listB();
   // Ab.add();
   // Ab.listB();
   // Ab.write("lista1.txt");
   // Ab.write("lista2.txt");
   // Ab2.read("lista2.txt");
   // Ab2.listB();
 //   Ab.del(2);
  //  Ab.listB();

    return 0;
}
