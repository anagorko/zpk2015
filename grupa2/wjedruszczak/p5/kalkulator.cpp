#include<iostream>
#include<string>
using namespace std;

class Stack {
private:
	struct Element {
		Element * prev;
		float value;
	};

	Element * t;

public:
	Stack();
	~Stack();

	float pop();
	float top();

	bool empty();
	void push(float);
};

// konstruktor domyslny
Stack::Stack() {
	// wskaznik pusty
	t = nullptr;
}

// destruktor
Stack::~Stack() {
	while (nullptr != t) {
		// zwalnianie kolejnych warstw stosu
		Element * poprzedniElement = { t->prev };
		delete t;
		t = poprzedniElement;
	}
}

// zdejmuje element ze stosu
float Stack::pop() {
	if (nullptr == t)
		return 0;
	else {
		// podobny mechanizm jak w dekonstruktorze
		Element * poprzedniElement = { t->prev };
		float wartosc = { t->value };
		delete t;
		t = poprzedniElement;
		return wartosc;
	}
}

// wartosc na gorze stosu
float Stack::top() {
	if (nullptr == t)
		return 0;
	else
		return t->value;
}

// czy stos jest pusty?
bool Stack::empty() {
	return (nullptr == t);
}

// odklada element na stos
void Stack::push(float wartosc) {
	// tworzenie kolejnej warstwy stosu
	Element * nowyElement = { new Element };
	nowyElement->value = wartosc;
	nowyElement->prev = t;
	t = nowyElement;
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
