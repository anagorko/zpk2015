#include<iostream>
#include <stdlib.h> /*atof function*/
#include<string>
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
/*konstruktor tworzy pusty stos*/
Stack::Stack(){
    t = NULL;
}
/*destruktor zwalnia kolejne warstwy stosu*/
Stack::~Stack(){
        Element * temp = {t -> prev};
        delete t;
        t = temp;
}
/*funkcja zczytuje wartoœæ z wierzchu stosu (popped) i j¹ usuwa*/
float Stack::pop(){
    if(t != NULL){
        Element * temp = {t -> prev};
        float popped = (t -> value);
        delete t;
        t = temp;
        return popped;
    }else{
        return 0;
    }
}
/*funkcja tylko zczytuje (zwraca) wartoœæ z wierzchu stosu (tp) */
float Stack::top(){
    if(t != NULL){
        float tp = (t -> value);
        return tp;
    }else{
        return 0;
    }
}
/*funkcja uk³ada na wierzchu stosu liczbê float*/
void Stack::push(float pushed){
    Element * temp  = {new Element()};
    (temp -> value) = pushed;
    if(t != NULL){
        (temp -> prev)  = t;
    }
    t = temp;
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

            if(!s.empty()){
                r = s.pop();
                if(!s.empty()){
                    l = s.pop();
                    s.push(l + r);
                }else{
                    cout << "podano tylko jeden sk³adnik sumy:";
                    s.push(r);
                }
            }else{
                cout << "nie podano sk³adników sumy";
            }



        } else if (token == "*") {
            float l, r;
            if(!s.empty()){
                r = s.pop();
                if(!s.empty()){
                    l = s.pop();
                    s.push(l + r);
                }else{
                    cout << "podano tylko jeden z czynników iloczynu:";
                    s.push(r);
                }
            }else{
                cout << "nie podano czynników iloczynu";
            }


        } else if (token == "=") {
            cout << s.top() << endl;
        } else {
            float Result;          //number which will contain the result
            Result = atof(token.c_str());
            s.push(Result);
        }
    }
}
