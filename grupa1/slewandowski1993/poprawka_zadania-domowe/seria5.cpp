#include<iostream>
using namespace std;

class Stack
{
    struct Element
    {
        Element* prev;
        float val;
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
}

Stack::~Stack() {

  Element * tmp = t;
    while (t != NULL){
		t = t-> prev;
		delete tmp;
		tmp = t;
	}
}


float Stack::pop(){
    Element* tmp = t;
    float val = t -> val;
    t = t -> prev;
    delete tmp;
    return val;
}


float Stack::top(){
    if(t!=NULL)
    {
    return t -> val;
    }
}

bool Stack::empty(){
	return t == NULL;
}


void Stack::push(float val){
    Element* tmp = new Element();
    tmp -> val = val;
    if (t!=NULL) {
        tmp -> prev=t;
    }
    t = tmp;
}

int main() {
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
