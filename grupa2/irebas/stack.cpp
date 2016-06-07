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
    Stack();
    ~Stack();

    float pop();
    float top();

    bool empty();
    void push(float);
};

Stack(){
    t = NULL;
}

~Stack(){
    while(t != NULL)
        pop();
}

float top(){
    if (t == NULL){
            cout << "B³êdne dane, spróbuj jeszcze raz" << endl;
        }
        else{
            return t -> value;
        }
    }

float pop(){
    if(t == NULL){
        cout << "B³êdne dane, spróbuj jeszcze raz" << endl;
    }
    else {
        float pvalue = t -> value;
        t = t -> prev;
        return pvalue;
    }
}

bool empty()
{
    if(t==NULL)
        return true;
    else
        return false;
}

void push(float nvalue){
    Element * page = new Element;
    page -> value = nvalue;
    if(t != NULL)
        page -> prev = t;
    t = page;
}



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
