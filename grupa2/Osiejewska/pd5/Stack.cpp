#include<iostream>
#include<string>
#include <cstdlib>
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

    Stack() {
        t = NULL;
    }

    ~Stack(){
        while (t != NULL){
        Element* pom = t -> prev;
        delete t;
        t = pom;
        }
    }

    bool empty(){
        if(t == NULL)
            return true;
        else
            return false;
    }

    float pop(){
        if (t == NULL){
           cout << "Blede dane, spobuj jeszcze raz" << endl;
        }
        else
            {
            float v = t -> value;
            Element* p = t-> prev;
            delete t;
            t = p;
            return v;
        }
    }

    float top(){
        if (t == NULL){
            cout << "Blede dane, spobuj jeszcze raz" << endl;
        }
        else{
            return t -> value;
        }
    }

    void push(float v){
            Element* p = t;
            t = new Element;
            t -> value = v;
            t -> prev = p;
    }
};

int main()
{
    Stack s;

    while (!cin.eof()) {
        string token;
        cin >> token;

        if (token == "+") {
            float l, r;

            r = s.pop();
            l = s.pop();

            s.push(l + r);
        } else if (token == "*") {
            float l, r;

            r = s.pop();
            l = s.pop();

            s.push(l * r);
        } else if (token == "=") {
            cout << s.top() << endl;
        } else {
            s.push(atof(token.c_str()));
        }
    }
}
