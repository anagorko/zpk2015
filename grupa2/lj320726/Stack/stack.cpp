#include<iostream>
#include <string>
#include <sstream>
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
    Stack()	 {t = NULL;}
    ~Stack(){while(t!= NULL) {pop();}}

    float pop()	{ if(t!=NULL){ 
					Element* pom = t-> prev;
					float ile = t-> value;
					delete t;
					t = pom;
					return ile;
	}
	cout << "Niewlasciwie uzyta skladnia. Przyjeto, ze kazda wymagana i niewpisana liczba wynosi zero"<<endl;
	return 0;
	};
    float top(){if(t!=NULL) {
    			return t-> value;
    		    }
    		    else{
    		    return 0;
    		    }
    };

    bool empty() {if(t!=NULL){
    			return false;
    			}
    			else {
    			return true;
    			}
    };
    
    void push(float ile) { 	Element* pom = t;
    						t = new Element;
    						t -> prev = pom;
							t -> value = ile;
    						
    };
};

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
