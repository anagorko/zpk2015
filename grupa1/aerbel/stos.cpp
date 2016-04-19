#include<iostream>
#include <string>
using namespace std;


class Stack
{
    struct Element
    {
        Element* prev;
        float value;
    };

    Element * t;

public:
    Stack();
    ~Stack();

    float pop();
    float top();

    bool empty(void);
    void push(float);
};

Stack::Stack()
{
    t=NULL;
}

Stack::~Stack()
{
   while(t) pop();
}

bool Stack::empty(void)
{
    return !t;
}

float Stack::top(void){

    return t->value;
}

void Stack::push(float v)
{
    Element * e = new Element;
    e->value=v;
    e->prev=t;
    t=e;
}

float Stack::pop(void)
{     float w;
      w = t->value;
      Element *e = t;
      t = t -> prev;
      delete e;
      return w;
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
          s.push(stof(token))
            ;
        }
    }
}
