#include<iostream>
#include<stdlib.h>
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
    Stack()
    {
        t = NULL;
    }

    ~Stack() {}

    float pop()
    {
        if (t!=NULL)
        {
            float x;
            Element* n;
            x = t -> value;
            n = t -> prev;
            delete t;
            t = n;
            return x;
        }
    }

    float top()
    {
      if(t!=NULL)
      {
      return t -> value;
      }
    }

    bool empty()
    {
       if (t==NULL)
       {
           return true;
       }
       else
       {
           return false;
       }
    }

    void push(float x)
    {
        Element *n = new Element;
        n -> prev = t;
        n -> value = x;
        t = n;
    }

};

int main()
{ Stack s;

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
            s.push(atof(token.c_str()));
        }
    }
    return 0;
}
