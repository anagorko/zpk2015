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
            float top;
            top=t -> value;
            t = t -> prev;
            return top;
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
       return t == NULL;
    }

    void push(float x)
    {
        Element *neww = new Element;
        neww -> prev = t;
        neww -> value = x;
        t = neww;
    }

};

int main()
{ Stack s;

    while (!cin.eof()) {
        string token;
        cin >> token;

        if (token == "+") {
            float x, y;

            y = s.pop();
            x = s.pop();

            s.push(x + y);
        } else if (token == "*") {
            float x, y;

            y = s.pop();
            x = s.pop();

            s.push(x * y);
        } else if (token == "=") {
            cout << s.top() << endl;
        } else {
            s.push(atof(token.c_str()));
        }
    }
    return 0;
}
