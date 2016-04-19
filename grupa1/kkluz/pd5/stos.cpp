#include<iostream>
#include<stdlib.h>
#include <string>
using namespace std;

class Stack
{
    struct Element
    {
        Element* prev;
        float z;
    };

    Element* t;

public:
    Stack() {
	t=NULL;
    }

    ~Stack() {
	Element* tmp = t;
	while (t != NULL) {
		t = t->prev;
		delete tmp;
		tmp = t;
	}
}

    float pop() {
	Element* tmp =  t;
	float z = t->z;
	t = t->prev;
	delete tmp;
	return z;
    }

    float top() {
      if(t!=NULL)
      {
      return t -> z;
      }
    }

    bool empty() {
       if (t==NULL)
       {
           return true;
       }
       else
       {
           return false;
       }
    }

    void push(float z){
	Element* tmp = new Element();
	tmp->z = z;

	if (t != NULL){
		tmp->prev = t;
	}

	t = tmp;
};

int main() {
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
            s.push(atof(token));
    		}
	}
  }
}
