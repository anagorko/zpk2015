#include<iostream>
#include<string>
using namespace std;

class Stack                //klasa Stos
{
    struct Element      //struktura Element wewnątrz stosu -> nasza karteczka
    {
        Element* prev;  //poprzedni element stosu na górze
        float value;    //wartość danego elementu
    };

    Element* t;         //obecny element stosu na górze

public:
    Stack()
    {
        t=NULL;
    };
    ~Stack()
    {

    };

    float pop();        //usuwa jeden element z góry stosu
    float top();        //zwraca wartość elementu na wierzchu

    bool empty();       //sprawdza czy stos jest pusty
    void push(float);   //wkłada jeden element na górę stosu
};

//implementacja

float Stack::pop()
{
    if(t==NULL)
        return 0;
    else
    {
        Element* ttemp = t -> prev;     //zmienna pomocnicza
        float vtemp =  t -> value;      //zmienna pomocnicza
        delete t;
        t = ttemp;
        return vtemp;
    }
}

float Stack::top()
{
    if(t!=NULL)
        return t -> value;
    else
        return 0;

}

bool Stack::empty()
{
    if(t==NULL)
        return true;
    else
        return false;
}

void Stack::push(float wartosc)
{
    Element* kartka = new Element;
    kartka -> value = wartosc;
    if(t!=NULL)
       kartka -> prev = t;
    t = kartka;
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
