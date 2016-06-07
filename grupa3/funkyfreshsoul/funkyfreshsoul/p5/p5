#include<iostream>
#include<string>
#include <sstream>
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

//konstruktor tworzy pusty stos - inicjalizacja
Stack::Stack() {
    t = NULL;
}

//destruktor aby zwolnic pamiec
Stack::~Stack() {
    while (t != NULL) {
        Element* poprzedni = t -> prev;
        delete t;
        t = poprzedni;
    }
}

//zdejmuje element z wierzchu w i zwraca te wartosc
float Stack::pop() {
    if (t != NULL) {
        Element* poprzedni = t -> prev;
        float w = t -> value;
        delete t;
        t = poprzedni;
        return w;
    }
    else
        return 0;
}

// podglada co na wierzchu stosu
float Stack::top() {
    if (t != NULL)
        return t -> value;
    else
        return 0;
}

//czy stos jest pusty, czy nie?
bool Stack::empty() {
    return (t == NULL);
}

//polozenie wartosci na wierzchu stosu
void Stack::push(float w) {
    Element* now = new Element;
    t = now;
    now -> value = w;
    now -> prev = t;
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
