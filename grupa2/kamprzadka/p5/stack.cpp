#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Stack
{
    struct Element
    {
        Element* prev;
        float value;
    };

    Element* t;
    Element* t1;
    int n = 0;

public:
    Stack(){}
    ~Stack(){}

    float pop()
    {
        if (n!=0)
        {
            n--;
            float tmp=t->value;
            t=t->prev;
            return tmp;
        }
        else {
            cout<<"Podano bledne dane wejsciowe\nZostanie zwrocona wartosc 0\n";
            return 0;
        }

    };


    float top()
    {
        return t->value;
    };

    bool empty();

    void push(float a)
    {
        t1=t;
        t=new Element;
        t->prev=t1;
        t->value=a;
        n++;
    };
};

int main()
{
    Stack s;
    float q;

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
            q=strtof(token.c_str(),0);
            s.push(q);
        }
    }
}
