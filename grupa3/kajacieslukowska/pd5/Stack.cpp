#include<iostream>
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

Stack::Stack()
{
    t=NULL;
};

Stack::~Stack()
{
    while(t != NULL)
    {
        Element* tmp = t -> prev;
        delete t;
        t=tmp;
    }
};

float Stack::pop()
{
    if(t == NULL)
        return NULL;
    else
    {
        Element* p = t -> prev;
        float v = t -> value;
        delete t;
        t = p;
        return v;
    }
};

float Stack::top()
{
    if(t == NULL)
        return NULL;
    else
    {
        float v = t -> value;
        return v;
    }
};

bool Stack::empty()
{
    if(t == NULL)
        return true;
    else
        return false;
};

void Stack::push(float v)
{
    Element* p = new Element();

    p -> value = v;
    if(t != NULL)
        p -> prev = t;
    t = p;
};


int main()
{
    Stack s;

    while (!cin.eof()) {
        string token;
        cin >> token;

        if (token == "+")
        {
            float l, r;

            if(!s.empty())
            {
                r = s.pop();
                if(!s.empty())
                {
                    l = s.pop();
                    s.push(l+r);
                }
                else
                {
                    cout << "Podano tylko jedna liczbe";
                    s.push(r);
                }
            }
            else
                cout << "Nie podano zadnego skladnika sumy";
        }
        else if (token == "*")
        {
            float l, r;

            if(!s.empty())
            {
                r = s.pop();
                if(!s.empty())
                {
                    l = s.pop();
                    s.push(l * r);
                }
                else
                {
                    cout << "Podano tylko jedna liczbe";
                    s.push(r);
                }
            }
            else
            {
                cout << "Nie podano zadnego czynnika iloczynu";
            }
        }
        else if (token == "=")
        {
            cout << s.top() << endl;
        }
        else
        {
            s.push(stof(token));
        }
    }
}
