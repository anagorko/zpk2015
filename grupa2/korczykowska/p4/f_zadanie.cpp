#include <iostream>
#include <math.h>
using namespace std;
#define PI 3.14159265358979323846


class Figure
{
    virtual ostream& output(ostream&) const = 0;

public:
    virtual double area() = 0;

    virtual Figure* scale(double) = 0;
    virtual Figure* translate(double, double) = 0;
    virtual Figure* rotate(double) = 0;

    friend ostream& operator<<(ostream& os, const Figure& f);
};

ostream& operator<<(ostream& os, const Figure& f)
{
    return f.output(os);
}

class Point : public Figure
{
    double x, y;

    virtual ostream& output(ostream& os) const {
        return os << "(" <<  x << "," << y << ")";
    }

public:
    Point() : Point(0.0, 0.0) {
    }
    Point(double _x, double _y) {
        x = _x; y = _y;
    }

    virtual double area() {
        return 0;
    }

    virtual Figure* scale(double k) {
        x = k * x;
        y = k * y;

        return this;
    };

    virtual Figure* translate(double dx, double dy) {
        x = x + dx;
        y = y + dy;

        return this;
    }

    virtual Figure* rotate(double alpha) {
        double nx = cos(alpha) * x - sin(alpha) * y;
        double ny = sin(alpha) * x + cos(alpha) * y;

        x = nx;
        y = ny;

        return this;
    }

    double distanceTo(Point p)
    {
        double dx = x - p.x;
        double dy = y - p.y;

        return sqrt(dx*dx + dy*dy);
    }

    double getX() const { return x; }
    double getY() const { return y; }
};


class Square : public Figure
{
    Point a,b,c,d;

    virtual ostream& output(ostream& os) const {
        return os << "[" << a << ";" << b << ";" << c << ";" << d << "]";
    }

public:
    Square(Point p, double x) {
        a = b = c = d = p;

        b.translate(x,0);
        c.translate(x,x);
        d.translate(0,x);
    }

    virtual double area() {
        return a.distanceTo(b) * a.distanceTo(b);
    }

    virtual Figure* scale(double k) {
        a.scale(k);
        b.scale(k);
        c.scale(k);
        d.scale(k);

        return this;
    }

    virtual Figure* translate(double dx, double dy) {
        a.translate(dx, dy);
        b.translate(dx, dy);
        c.translate(dx, dy);
        d.translate(dx, dy);

        return this;
    }

    virtual Figure* rotate(double alpha) {
        a.rotate(alpha);
        b.rotate(alpha);
        c.rotate(alpha);
        d.rotate(alpha);

        return this;
    }
};



class Circle : public Figure
{
    Point o;
    double r; //o oznacza srodek okregu (punkt), r jego promien (liczba)

    virtual ostream& output(ostream& os) const {
        return os << "[" << o << ";" << r << ";" << "]";
    }

public:
    Circle(Point _o, double _r) {
        o = _o;
        r = _r;

    }

    virtual double area() {
        return PI * r * r;
    }

    virtual Figure* scale(double k) {
        o.scale(k);
        r = r*k;
              return this;
    }

    virtual Figure* translate(double dx, double dy) {
        o.translate(dx, dy);
        return this;
    }

    virtual Figure* rotate(double alpha) {
        o.rotate(alpha);
        return this;
    }
};



class Line : public Figure
{
    Point p1, p2; //linia wyznaczana przez dwa punkty, przez ktore przechodzi

    virtual ostream& output(ostream& os) const {
        return os << "[" << p1 << ";" << p2 << ";" << "]";
    }

public:
    Line(Point _p1, Point _p2) {
        p1 = _p1;
        p2 = _p2;

    }

    virtual double area() {
        return 0; //tu nie ma pola powierzchni
    }

    virtual Figure* scale(double k) {
        p1.scale(k);
        p2.scale(k);
              return this;
    }

    virtual Figure* translate(double dx, double dy) {
        p1.translate(dx, dy);
        p2.translate(dx, dy);
        return this;
    }

    virtual Figure* rotate(double alpha) {
        p1.rotate(alpha);
        p2.rotate(alpha);

        return this;
    }
};


int main(int argc, char ** argv)
{
    Figure* f = new Square(Point(10.0, 20.0), 30.0);
    Figure* g = new Point(-5.0, 15.0);

    cout << *f << " ma pole " << f -> area() << endl;
    cout << *g << " ma pole " << g -> area() << endl;

    // Napisz klasy Circle i Line powyżej tak, by poniższy kod się kompilował


    Figure* c = new Circle(Point(40.0, 50.0), 5.0);
    c -> translate(10.0, 5.0);
    c -> rotate(0.5);
    cout << *c << endl;
    Figure* l = new Line(Point(5.0, 7.0), Point(3.0, 2.0));
    l -> rotate(-0.2);
    l -> translate(3.0, 5.0);
    cout << *l << endl;

}
