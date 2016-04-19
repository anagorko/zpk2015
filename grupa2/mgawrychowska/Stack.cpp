//stack.cpp
#include <string>
#include <stdlib.h>
#include<iostream>
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

Stack::~Stack() {
}

Stack::Stack() {
t=NULL;
}

float Stack::pop() {
if (!empty()) {
float h;
Element* g;
h=t -> value;
g=t -> prev;
t=g;
return h;
}
else {
cout << "error" << endl;
}

float Stack::top() {
if (!empty()){
return t -> value;
}
else {
cout << "error" << endl;
}
}
bool Stack::empty() {
return (t==null);
}

void Stack::push(float v) {
Element* z= new Element();
t=z->prev;
z->value=v
t=z;
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
            s.push(stof(token));
        }
    }
}

