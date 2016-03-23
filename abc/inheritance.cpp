#include <iostream>
using namespace std;

class A
{
public:    
    string name;

    A() {
        name = "A"; 
    }

    void hello() {
        cout << "My name is " << name << "!" << endl;
    };
};

class B : public A
{
public:
    B() {
        name = "B";
    }
    
    void hello() {
        cout << "Hi! ";
        A::hello();
    };    
};

int main()
{
    A a; 
    a.hello();

    B b;
    b.hello();
}
