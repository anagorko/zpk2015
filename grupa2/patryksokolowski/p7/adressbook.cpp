#include<iostream>
#include <sstream>
#include<fstream>
#include<vector>
#include<string>
#include <algorithm>
using namespace std;

class record {
        int id;
        vector<string> data;
public:
    record(){
        id=0;
        data.resize(4);
    };
    record(int id_, string imie, string nazwisko, string email, string telefon){
        id=id_;
        data[0] = imie;
        data[1] = nazwisko;
        data[2] = email;
        data[3] = telefon;
    }
    int getId() const {
       return id;
    }
    void setId(int x){
        id = x;
    }
    void setData(int x){
        cin >> data[x];
    }
    string getData(int x) const {
        return data[x];
    }
    friend ostream& operator << (ostream& os, const record& r){
        cout << r.getId() << " " << r.getData(0) << " " << r.getData(1) << " " <<  r.getData(2) << " " << r.getData(3) << endl;
        return os;
    }
};

class book {

        vector<record> r;
public:
        book(){};
        book(vector<record> x){
            r=x;
        }
        vector<record> getRecords(){
            return r;
        }
        record getRecord(int x){
            return r[x];
        }
        void list_(){
            if (r.size() == 0) cout << "Ksiazka jest pusta" << endl;
            for (record& x:r){
                cout << x << endl;
            }
        }
        int max_id(){
            int x=0;
            for (int i=0;i<r.size();i++){
                if (r[i].getId()>x) x=r[i].getId();
            }
            return x;
        }
        void add(){
            r.resize(r.size()+1);
            r.back().setId(max_id()+1);
            cout << "Imie: ";
            r.back().setData(0);
            cout << "Nazwisko: ";
            r.back().setData(1);
            cout << "E-mail: ";
            r.back().setData(2);
            cout << "Numer telefonu: ";
            r.back().setData(3);
        }
        void insertRecord(record x){
            r.resize(r.size()+1);
            r.back()=x;
        }
        book sort_(int x){
            vector<record> v = getRecords();
            if (x==-1) {
                sort(begin(r), end(r), [] (const record& lhs, const record& rhs) { return lhs.getId() < rhs.getId(); });
            }
            switch (x){
                case 0:
                    sort(begin(r), end(r), [] (const record& lhs, const record& rhs) { return lhs.getData(0) < rhs.getData(0); });
                    break;
                case 1:
                    sort(begin(r), end(r), [] (const record& lhs, const record& rhs) { return lhs.getData(1) < rhs.getData(1); });
                    break;
                case 2:
                    sort(begin(r), end(r), [] (const record& lhs, const record& rhs) { return lhs.getData(2) < rhs.getData(2); });
                    break;
                case 3:
                    sort(begin(r), end(r), [] (const record& lhs, const record& rhs) { return lhs.getData(3) < rhs.getData(3); });
                    break;
            }
            return book(v);
        }
        void modify(int i){
            cout << "Record to modify: " << r[i] << endl;
            cout << "Please enter updated data";
            cout << "Imie: ";
            r[i].setData(0);
            cout << "Nazwisko: ";
            r[i].setData(1);
            cout << "E-mail: ";
            r[i].setData(2);
            cout << "Numer telefonu: ";
            r[i].setData(3);
        }
        void delete_(int i){
            for (int j=i;j<r.size()-1;j++){
                r[j] = r[j+1];
            }
            r.pop_back();
        }
};

class UI {
    string filename;
    book file;
public:
    UI(){};
    void loadfile(string name){
        ifstream myfile(filename+".txt");
        string line;
        if (myfile.is_open())
        {
            while ( getline(myfile,line))
            {
            istringstream iss(line);
            string T[5];
            string napis;
            for (int i=0;i<5;i++){
                iss >> napis;
                T[i] = napis;
            }
            string str = T[0];
            int id = atoi( str.c_str() );
            record r(id,T[1],T[2],T[3],T[4]);
            file.insertRecord(r);
            }
            myfile.close();
  }
    }
    void savefile(string name){
        ofstream bookfile;
        vector<record> bk = file.getRecords();
        bookfile.open(filename, ios::trunc);
         for (record& p: bk) {
            bookfile << p;
        }
        bookfile.close();
    }
    void addRecord(){
        file.add();
    }
    void deleteRecord(int i){
        cout << "Removing record: " << file.getRecord(i);
        file.delete_(i);
    }
    void modifyRecord(int i){
        file.modify(i);
        cout << "Record succesfully modified!" << endl;
    }
    void sort_book(int i){
        book m=file;
        m.sort_(i);
        m.list_();
    }
    void help() {
        cout << "help" << endl;
    }
};

int main(int argc, char* argv[]){
    cout << "jest " << argc << " argumentow" << endl;
    for (int i = 0; i < argc; i++) {
        cout << "argument nr " << i << ": " << argv[i] << endl;
    }

    UI iface;

    if (argc == 1 || (argc > 1 && string(argv[1]) == "help")) {
        iface.help();
        return 0;
    }
}
