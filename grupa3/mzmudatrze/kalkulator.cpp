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

    Element* t;

public:
    Stack(); 
    ~Stack(); 

    float pop(); 
    float top();

    bool empty();
    void push(float); 
};

Stack::Stack (){
}

Stack::~Stack(){

    while (t!=nullptr){
    Element* p = (t -> prev);

    delete t;
    t = p;
    }
}

float Stack::pop() {

    Element* p = t;
    float value = t -> value;

    t = t -> prev;

    delete p;

    return value;

    }

float Stack::top() {

    return (t -> value);
    }


bool Stack::empty(){
return (t == nullptr);

    }

void Stack::push(float n_value) {

    Element* p = new Element;
    p -> value = n_value;

        if (t != nullptr) {
        p -> prev = t;
        }
t = p;
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
