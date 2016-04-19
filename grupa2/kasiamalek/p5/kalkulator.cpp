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

Stack::Stack()
{
}
Stack::~Stack()
{
}

float Stack::pop()
{
        Element* poprzedni={t->prev};
        float v = {t->value};

        delete t;
        t = poprzedni;
        return v;
}

float Stack::top()
{
    return t->value;
}

bool Stack::empty()
{
    return t==nullptr;
}

void Stack::push(float v)
{
    Element* nowy={new Element};
    nowy->value=v;
    nowy->prev=t;
    t=nowy;
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
        }
        else {
//            s.push(stof(token)); //problem z kompilacją
        }
    }
}
