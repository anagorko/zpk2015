#include <iostream>
#include <string>
using namespace std;

class Stack				// klasa stos
{
    struct Element
    {
        Element* prev;	// wskazuje na poprzedni element stosu
        float value;	// wartosc elementu
    };

    Element* t;			// wskazuje na obecny element stosu

public:
    Stack();			// konstruktor
    ~Stack();			// destruktor

    float pop();		// zdejmuje element znajdujacy sie na wierzchu stosu
    float top();		// zwraca wartosc elementu, jaki jest na wierzchu stos

    bool empty();		// czy stos jest pusty?
    void push(float);	// dokłada kolejny element na stos
};

Stack::Stack() {
    t = NULL;
}

Stack::~Stack() {								// usuwamy kolejne elementy stosu
    while (t != NULL) {
        Element* pomocniczy = t -> prev;
        delete t;
        t = pomocniczy;
    }
}

float Stack::pop() {
    if (t != NULL) {
        Element* pomocniczy = t -> prev;
        float liczba = t -> value;
        delete t;
        t = pomocniczy;
        return liczba;
    }
    else
        return 0;
}

float Stack::top() {
    if (t != NULL)
        return t -> value;
    else
        return 0;
}

bool Stack::empty() {
    return (t == NULL);
}

void Stack::push(float liczba) {
    Element* nowy = new Element;
    nowy -> value = liczba;
    if (t != NULL)
        nowy -> prev = t;
    t = nowy;
}

int main()
{
    Stack s;
    int i = 0;								// zmienna bedaca licznikiem wprowadzonych liczb

    while (!cin.eof()) {
        string token;
        cin >> token;

        if (token == "+") {					// zostal wprowadzony znak dodawania
            float l, r;

            if (i == 2) {					// jezeli mamy juz dwie liczby...

                r = s.pop();
                l = s.pop();

                s.push(l + r);				// ...to wykonujemy dodawanie

                --i;						// zmniejszamy licznik o jeden,
											// bo mamy teraz tylko jedna liczbe bedaca suma
            }
        } else if (token == "*") {			// zostal wprowadzony znak mnozenia
            float l, r;

            if (i == 2) {					// jezeli mamy juz dwie liczby...

                r = s.pop();
                l = s.pop();

                s.push(l * r);				// ...to wykonujemy mnozenie

                --i;						// zmniejszamy licznik o jeden,
											// bo mamy teraz tylko jedna liczbe bedaca iloczynem
            }
        } else if (token == "=") {			// zostal wprowadzony znak rownosci
            if (i == 1) {					// jezeli mamy jedna liczbe bedaca wynikiem dzialania...
                cout << s.top() << endl;	// ...to mozemy ja wyswietlic
            }
            else
                cout << "Nie można wykonać działania! Wprowadź jeszcze raz poprawne dane.";
            i = 0;
        } else {							// zostala wprowadzona liczba,
            s.push(stof(token));			// wiec wloz ja na stos
            i++;							// i zwieksz licznik o 1
        }
    }
}
