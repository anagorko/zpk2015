#include<iostream>
#include<string>
#include<stdlib.h>

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

Stack::Stack() {
    t = NULL;
}

Stack::~Stack() {

}

void Stack::push(float v) {
    Element* nowy=new Element();
    nowy -> prev = t;
    nowy -> value=v;
    t = nowy;
}

float Stack::pop() {
    float top_value;
    top_value=t -> value;
    t = t -> prev;
    return top_value;
}

float Stack::top(){
    return t -> value;
}

bool Stack::empty() {
    return t == NULL;
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
