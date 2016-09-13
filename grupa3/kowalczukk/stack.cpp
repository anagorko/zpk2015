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
	void push(float);	
};

Stack::Stack() {
	t = NULL;
}

Stack::~Stack() 
{								
	while (t != NULL) 
	{
		Element* e = t->prev;
		delete t;
		t = e;
	}
}

float Stack::pop() 
{
	if (t != NULL) 
	{
		Element* e = t->prev;
		float liczba = t->value;
		delete t;
		t = e;
		return liczba;
	}
	else
		return 0;
}

float Stack::top() 
{
	if (t != NULL)
		return t->value;
	else
		return 0;
}

bool Stack::empty() 
{
	return (t == NULL);
}

void Stack::push(float liczba) 
{
	Element* nowy = new Element;
	nowy->value = liczba;
	if (t != NULL)
		nowy->prev = t;
	t = nowy;
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
