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
	Stack(); // konstruktor
	~Stack(); // destruktor

	float pop();
	float top();

	bool empty();
	void push(float);
};
// konstruktor
Stack::Stack(){
	
}
// destruktor
Stack::~Stack(){
	Element* tmp = t;
	while (t != NULL){
		t = t->prev;
		delete tmp;
		tmp = t;
	}
}

float Stack::pop() {
	Element* tmp =  t;
	float value = t->value;
	t = t->prev;
	delete tmp;
	return value;
}

float Stack::top() {
	return t->value;
}

void Stack::push(float value){
	Element* tmp = new Element();
	tmp->value = value;
	
	if (t != NULL){
		tmp->prev = t;
	}
	t = tmp;
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
			if (!s.empty()) {
				r = s.pop();
				if (!s.empty()) {
					l = s.pop();
					s.push(l + r);
				}
				else{
					cout << "blad skladni: podaj 2 liczbe i dzialanie";
					s.push(r);
				}
			}
			else{
				cout << "blad skladni: podaj 2 liczby i dzialanie";
			}
		}
		else if (token == "*") {
			float l, r;
			if (!s.empty()) {
				r = s.pop();
				if (!s.empty()) {
					l = s.pop();
					s.push(l * r);			
				}
				else{
					cout << "blad skladni:podaj 2 liczbe i dzialanie";
					s.push(r);
				}
			}
			else{
				cout << "blad skladni:podaj  2 liczby i dzialanie";
			}					
		}
		else if (token == "=") {
			cout << s.top() << endl;
		}
		else {
			s.push(stof(token));
		}
	}
}
