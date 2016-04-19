#include <iostream>
#include <string>

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
    void push(float x); //zmieni³em push(float) na push(float x)
};

Stack::Stack(){
    t = NULL;
}

Stack::~Stack(){
    while (!empty())
        pop();
}

void Stack::push(float x) {
    Element* tymczasowy = new Element;
    tymczasowy -> value = x;
    tymczasowy -> prev = t;
    t = tymczasowy;
}

float Stack::pop(){
    if(!empty()){
        float tymczasowy = t -> value;
        Element* stary = t;
        t = t -> prev;
        delete stary;
        return tymczasowy;
    }
    return 0;
}

float Stack::top(){
    if(empty()) return NULL;
    return t -> value;
}

bool Stack::empty(){
    return (t == NULL);
}

int main()
{
    Stack s;

    while (!cin.eof()){
        string token;
        cin >> token;

        if (token == "+"){
            float l, r;

            r = s.pop();
            l = s.pop();

            s.push(l + r);
        } else if (token == "*"){
            float l, r;

            r = s.pop();
            l = s.pop();

            s.push(l * r);
        } else if (token == "=") {
            cout << s.top() << endl;
        } else{
            s.push(atof(token.c_str()));
        }
    }
}
