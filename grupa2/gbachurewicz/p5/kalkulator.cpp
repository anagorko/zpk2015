#include <iostream>

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

Stack::Stack (){} //konstruktor jednynie tworzy pusty stos

Stack::~Stack(){ // destruktor sprawia, że stos jest pusty
    while (t!=nullptr){ //dopóki są kartki, to je usuwamy
        Element* kartka = (t -> prev);
        delete t;
        t = kartka;
    }
}

bool Stack::empty(){ //sprawdza, czy stos jest pusty
    return (t == nullptr);
}

float Stack::top() { //wzraca wartość kartki na górze stosu
    return (t -> value);
}

void Stack::push(float value_pushed) { //tworzy nową kartkę na górze stosu z podaną wartością
    Element* kartka = new Element;
    kartka -> value = value_pushed;
        if (t != nullptr) { //jezeli sa juz jakies kartki na stosie
            kartka -> prev = t; //to dajemy wkskaznik prev nowej kartki na tę starą t, jak nie ma to wskaznik prev bedzie nadal NULLem
        }
        t = kartka; //ustawiamy wskaznik górnej kartki, na tę nowo stworzoną
}

float Stack::pop(){ //usuwa górną kartkę na stosie i zwraca jej wartosc
    Element* kartka =  t;
	float value = t -> value;
	t = t -> prev; //górna kartka staje sie o 1 niższą
	delete kartka; //usuwamy stworzona kartke
	return value; //zwracamy wartosc górnej kartki, którą usuwamy
}


int main()
{
    Stack s;

    while (!cin.eof()) {
        string token;
        cin >> token;


		if (token == "+") {

			float l, r;
			if (!s.empty()) { //sprawdzamy, czy jakies (nowe) liczby zostały umieszczone na stosie

				l = s.pop(); //wstawiamy na góre stosu to co już podano
				if (!s.empty()) {

					r = s.pop();
                    s.push(l + r);
                    }
                else {
                    cout<<"Blad: nie podano drugiej liczby.";
                    s.push(l);
                }
			}
			else {
                cout<<"Blad: nie podano obu liczb.";
            }


        } else if (token == "*") {

            float l, r;
			if (!s.empty()) {

				l = s.pop();
				if (!s.empty()) {

					r = s.pop();
                    s.push(l * r);
                }
                else {
                    cout<<"Blad: nie podano drugiej liczby.";
                    s.push(l);
                }
			}
			else {
                cout<<"Blad: nie podano obu liczb.";
            }

        } else if (token == "=") {

            cout << s.top() << endl;
            }

            else {

            s.push(stof(token));
            }
    }
}
