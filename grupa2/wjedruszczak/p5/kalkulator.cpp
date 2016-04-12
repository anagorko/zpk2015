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
	while (t != nullptr) {
		// zwalnianie kolejnych warstw stosu
		Element * poprzedniElement = { t->prev };
		delete t;
		t = poprzedniElement;
	}
}

// zdejmuje element ze stosu
float Stack::pop() {
	if (t == nullptr)
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
	if (t == nullptr)
		return 0;
	else
		return t->value;
}

// czy stos jest pusty?
bool Stack::empty() {
	return (t == nullptr);
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

	// zmienna, ktora dba o to, zeby wprowadzone dane byly poprawne,
	// tzn. kazde dzialanie musi sie skladac z trzech elementow:
	// liczba_r liczba_l dzialanie (w tej kolejnosci) i dopiero "=" (ten znak nie jest jednak zliczany)
	int trzyElementy = { 0 };

	while (!cin.eof()) {
		string token;
		cin >> token;

		if (token == "+") {
			float l, r;

			++trzyElementy;
			
			if (trzyElementy != 3)
				trzyElementy = 0;
			else {
				r = s.pop();
				l = s.pop();
				
				s.push(l + r);
			}
		}
		else if (token == "*") {
			float l, r;

			++trzyElementy;

			if (trzyElementy != 3)
				trzyElementy = 0;
			else {
				r = s.pop();
				l = s.pop();

				s.push(l * r);
			}
		}
		else if (token == "=") {
			if (trzyElementy == 3)
				cout << s.top() << endl;
			else
				cout << "Wprowadzono nieprawidlowe dane. Podaj ponownie cale dzialanie." << endl;
			trzyElementy = 0;
		}
		else {
			s.push(stof(token));
			++trzyElementy;
		}
	}
}
