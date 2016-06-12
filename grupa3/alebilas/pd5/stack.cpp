#include<iostream>
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
	while(!empty())
		pop();
}

float Stack::pop(){
	if(!empty()){
		Element* temporary = {t -> prev};
		float val = {t -> value};
		delete t;
		t = temporary;
		return val;
	}
	return 0;
}

float Stack::top(){
	if(empty()) return NULL;
	return t -> value;
}

bool Stack::empty(){
	return t == NULL;
}

void Stack::push(float u){
	Element* temporary = new Element;
	temporary -> value = u;
	temporary -> prev = t;
	t = temporary;
}

int main()
{
    Stack s;

    while (!cin.eof()) {
        string token;
        cin >> token;

        if (token == "+") {
            float l, r;

			if(!s.empty()){
				r = s.pop();
				if(!s.empty()){
					l = s.pop();
					s.push(l + r);
				}
				else{
					cout << "Podaj drugi skladnik sumy";
					s.push(r);
				}
			}
			else { cout << "Nie podano zadnych wartosci";
			}
        }
			else if (token == "*") {
            float l, r;

            if(!s.empty()){
				r = s.pop();
				if(!s.empty()){
					l = s.pop();
					s.push(l * r);
				}
				else{
					cout << "Podaj drugi czynnik iloczynu";
					s.push(r);
				}
			}
			else { cout << "Nie podano zadnych wartosci";
			}

        } else if (token == "=") {
            cout << s.top() << endl;
        } else {
            s.push(atof(token.c_str()));
        }
    }
}
