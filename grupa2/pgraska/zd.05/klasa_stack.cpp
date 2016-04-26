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


Stack::Stack() {
	t = NULL;
}

Stack::~Stack() {

	if (t != NULL) {
		Element* el = t;
		Element* prev = t->prev;
		while (prev != NULL) {
			delete el;
			el = prev;
			prev = prev->prev;
		}
	}
}

void Stack::push(float v) {
	if (t == NULL) {
		Element* el = new Element();
		el->value = v;
		el->prev = NULL;
		t = el;
	}
	else {
		Element* el = new Element();
		el->value = v;
		el->prev = t;
		t = el;
	}
}

float Stack::pop() {
	Element* el = t;
	t = t->prev;
	float v = el->value;
	delete el;
	return v;
}

float Stack::top() {
	return t->value;
}

bool Stack::empty() {
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
		}
		else if (token == "*") {
			float l, r;

			r = s.pop();
			l = s.pop();

			s.push(l * r);
		}
		else if (token == "=") {
			cout << s.top() << endl;
		}
		else {
			s.push(stof(token));
		}
	}
}

