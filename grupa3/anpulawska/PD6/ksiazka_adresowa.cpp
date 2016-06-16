#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>

using namespace std;

class Person
{
	int id;
	string name, surname, mail;

public:

	Person(string n = "", string s= "", string m= "")
	{
	    int i = -1;
        id = i;
		name = n;
		surname = s;
		mail = m;

	}

	int getId()
	{
	    return id;
	}
	string getName() const
	{
	    return name;
	}
	string getSurname() const
	{
	    return surname;
	}
    string getMail()
	{
	    return mail;
	}

    void setId(int i)
    {
        id = i;
    }
    void setName(string n)
    {
        name = n;
    }
   void setSurname(string s)
    {
        surname = s;
    }
    void setMail(string m)
    {
        mail = m;
    }
};

ostream& operator<<(ostream& o, Person& p)
{
    o << p.getId()<< " " << p.getName() << " " << p.getSurname() << " " << p.getMail() <<endl;
    return o;
}

istream& operator>>(istream& istr, Person& p)
{
    int i;
    string n, s, m;
    istr >> i >> n >> s >> m;

    p.setId(i);
    p.setName(n);
    p.setSurname(s);
    p.setMail(m);

    return istr;
}



class Adressbook
{
	vector<Person> book;

public:

    void sortBook(string z)
	{

		if(z == "imie")
		{
			sort(begin(book), end(book), [] (const Person& lhs, const Person& rhs) { return lhs.getName() < rhs.getName(); });

		}

		if(z == "nazwisko")
		{
			sort(begin(book), end(book), [] (const Person& lhs, const Person& rhs) { return lhs.getSurname() < rhs.getSurname(); });
		}
	}

	void add(string n, string s, string m)
	{
	    Person nPerson = Person(n, s, m);
	    for (int i = 0; i < book.size(); i++)
	    {
	        if (book[i].getId() == 0)
	        {
	            book[i] = nPerson;
	            book[i].setId(i+1);
	            cout << "dodano wpis" << endl;
	            return;
	        }
	    }

	    book.resize(book.size() + 1, nPerson);
	    book[book.size() - 1].setId(book.size());
		cout << "dodano wpis" << endl;
	}

	void modify(int x, string item, string content)
	{
        if (book[x-1].getId() == 0 || x > (book.size()))
        {
            cout << "Nie ma osoby o podanym ID" << endl;
            return;
        }
        if (item == "imie")
        {
            book[x-1].setName(content);
            cout <<"Zmodyfikowano osobe o ID: " << x <<endl;
            return;
        }
        if (item == "nazwisko")
        {
            book[x-1].setSurname(content);
            cout <<"Zmodyfikowano osobe o ID: " << x <<endl;
            return;
        }
        if (item == "mail")
        {
            book[x-1].setMail(content);
            cout <<"Zmodyfikowano osobe o ID: " << x <<endl;
            return;
        }
            cout <<"Zla nazwa wartoœci" << endl;
	}

	void deleteByID(unsigned int x)
	{
        if (book[x-1].getId() == 0 || x > (book.size()))
            cout << "Nie ma osoby o podanym ID" << endl;
        else{
            book[x-1].setId(0);
            cout << "Usunieto wpis o numerze: " << x << endl;
        }
	}

	void read(string bookname)
	{
    	ifstream bookfile;
        bookfile.open(bookname.c_str(), ios::in);

        int n;
        bookfile >> n;

        book.resize(n);

        for (int i = 0; i < book.size(); i++)
        {
            bookfile >> book[i];
        }
        bookfile.close();
    }

    void write(string bookname)
	{
    	ofstream bookfile;
        bookfile.open(bookname.c_str(), ios::trunc);

        bookfile << book.size()<<endl;
        for (int i = 0; i < book.size(); i++)
			bookfile << book[i];

        bookfile.close();
    }


    vector<Person> get_vector()
    {
        return book;
    }
};

class UI
{

public:

    void help()
    {
        cout<< "I. Nazwa ksiazki adresowej"<<endl<<"II.Dzialanie:"<<endl<<endl<< "   dodaj"<<endl<< "   zmien"<<endl<< "   usun"<<endl<<"  nowa_ksiazka - tworzy nowa ksiazke adresowa o nazwie podanej jako pierwszy argument."<<endl<<"wyswietl"<<endl<<"Przy braku zmiennej program wypisze cala ksiazke.";
    }

        void modify(Adressbook& book)
        {
            int id;
            string item, content;
            cout<< "Wpis o ktorym ID zmienic?";
            cin>>id;
            cout<<"Co chcesz zmienic? (imie/nazwisko/mail)";
            cin>>item;
            cout<<"Nowe dane:";
            cin>>content;

            book.modify(id, item, content);
        }

    void deleteByID(Adressbook& book)
    {
        int x;
        cout<<"Które ID usunac?";
        cin>>x;
        book.deleteByID(x);
    }

    void add(Adressbook& book)
    {

        string name, surname, mail;
        cout<<"Imie:";
        cin>>name;

        cout<<"Nazwisko:";
        cin>>surname;

        cout<<"Mail:";
        cin>>mail;

        book.add(name, surname, mail);
    }

    void show(Adressbook book)
    {
        vector<Person> bk;
        bk = book.get_vector();
        for(int i = 0; i < bk.size(); i++)
        {
            if(bk[i].getId() != 0)
            {
                cout<<bk[i];
            }
    }
    }

	void sort(Adressbook book, string x)
	{
		book.sortBook(x);
		cout << "Posortowano";
	}

};

int main(int argc, char* argv[])
{

    UI iface;
    if (argc == 1  || (argc > 1 && string(argv[1]) == "help"))
    {
        iface.help();
        return 0;
    }

    if (argc > 2)
    {
        if(string(argv[2]) == "nowa_ksiazka")
        {
            Adressbook book;

            book.write(string(argv[1]) + ".txt");
            return 0;
        }
        Adressbook book;

        book.read(string(argv[1]) + ".txt");

        if(string(argv[2]) == "dodaj")
            iface.add(book);
        if(string(argv[2]) == "zmien")
            iface.modify(book);
        if(string(argv[2]) == "usun")
            iface.deleteByID(book);
        if(string(argv[2]) == "wyswietl")
            iface.show(book);
		if(string(argv[2]) == "posortuj")
            iface.sort(book, string(argv[3]));

        book.write(string(argv[1]) + ".txt");
    }
	return 0;
}
