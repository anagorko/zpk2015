#include<iostream>
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

//konstruktor - pusty stos
Stack:: Stack() {
    
}

// destruktor - usunięcie wszystkiego ze stosu
Stack:: ~Stack() {
 
  Element* parm = t;
    while (t != NULL){
		t = t->prev;
		delete parm;
		parm = t;
	}  
}

//Zdejmuje istniejący element ze szczytu stosu. 
float Stack::pop(){
    Element* parm = t;
    float value = t -> value;
    t = t -> prev;
    delete parm;
    return value;  
}

//zwraca wartość z góry stosu
float Stack::top(){
    return t->value;
}

//Sprawdza czy stos jest pusty.
bool Stack::empty(){  
	return t == NULL;
}

   
//dodanie elementu na górę stosu
void Stack::push(float value){
    Element* parm = new Element();
    parm -> value = value;
    if (t!=NULL) {
        parm -> prev=t;
    }
    t = parm;
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
					cout << "blad";
					s.push(r);
				}
			}
			else{
				cout << "blad";
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
					cout << "blad";
					s.push(r);
				}
			}
			else{
				cout << "blad";
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
