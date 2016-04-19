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
        while (!empty()){
            pop();
        }
    }
    bool empty(){
        return (t == NULL);
    }
    float pop(){
        if (!empty()){
            float v = top();
            Element* w = t-> prev;
            delete t;
            t = w;
            return v;
        }
        else{
            cout << "blad" << endl;
            exit(1);
        }
    }
    float top(){
        if (!empty()){
            return t -> value;
        }
        else{
            cout << "blad" << endl;
            exit(1);
        }
    }
    void push(float v){
            Element* w = t;
            t = new Element;
            t -> value = v;
            t -> prev = w;
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

