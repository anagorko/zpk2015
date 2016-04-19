#include<iostream>
#include<string>
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

Stack::Stack(){
    t = NULL;
}

Stack::~Stack(){
    while(t != NULL)
        pop();
}

float Stack::top(){
    if(t != NULL)
        return t -> value;
    else
        return NULL;
}

float Stack::pop(){
    if(t != NULL){
        float prev_value = t -> value;
        t = t -> prev;
        return prev_value;
    }
    else
        return NULL;
}

void Stack::push(float new_value){
    Element * new_page = new Element;
    new_page -> value = new_value;
    if(t != NULL)
        new_page -> prev = t;
    t = new_page;
}

bool Stack::empty(){
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
            s.push(stof(token));
        }
    }
}
