#include<iostream>
#include<string>
using namespace std;

class Stack
{
    struct Element
    {
        Element* prev;
        float value;
    };

    Element* t;

public:
    Stack(){
        t = NULL;
        };
    ~Stack(){
        while (t != NULL){
            Element* prev = t -> prev;
            delete t;
            t = prev;
        }
        };

    float pop(){
        if (empty() == true) return 0;
        Element* prev = t -> prev;
        float v = t -> value;
        delete t;
        t = prev;
        return v;
        };
    float top(){
        if (empty() == true) return 0;
        return t -> value;
        };

    bool empty(){
        if (t == NULL){
            return true;
        }
        return false;
        };
    void push(float v){
        Element* x = new Element;
        x -> value = v;
        x -> prev = t;
        t = x;
    };
};

int main()
{
    Stack s;
    int P = 0;  // zmienna sprawdza poprawnosc dzialania tzn. kazde dzialanie powinno zawierac trze elementy: dwie strony dzialania i operator

    while (!cin.eof()) {
        string token;
        cin >> token;

        if (token == "+") {
            P++;
            if (P==3){
            float l, r;
            r = s.pop();
            l = s.pop();
            s.push(l + r);
            P = 1;
            }
            else P=0;
        } else if (token == "*") {
            P++;
            if (P==3) {
            float l, r;
            r = s.pop();
            l = s.pop();
            s.push(l * r);
            P = 1;
            }
            else {
                P=0;
            }
        } else if (token == "=") {
            if (P==1) {
                    cout << s.top() << endl;
                    P = 0;
            }
            else cout << "Wprowadz poprawne dane w odwrotnej notacji polskiej!" << endl;
        } else {
            P++;
            try {
                s.push(stof(token));
           }
            catch (...) {
            cout << "Wprowadz poprawne dane w odwrotnej notacji polskiej!" << endl;
            P = 0;
            }
        }
    }
}
