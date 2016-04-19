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
        Stack()
        {
            t = NULL;
        }
        ~Stack(){};

        float pop(){
            if(!empty()){
                float x = t->value;
                t = t->prev;
                return x;
            }
            else {
                cout << "Bledne dane wejsciowe" << endl;
            }
        }

        float top(){
            if ( !empty())
                return t->value;
        }

        bool empty(){
            if(t==NULL)
                return true;
            else
                return false;
        }
        void push(float x){
            Element* temp = new Element;
            temp -> value = x;
            temp -> prev = t;
            t = temp;
        }
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
