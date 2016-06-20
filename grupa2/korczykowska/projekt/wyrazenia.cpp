#include "wyrazenia.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <stack>
#include <sstream>


using namespace std;

bool calculate_operator_1(stack<double> &s, string op) {
    double l, res;

    l = s.top();
    s.pop();

    if (op == "sin") {
        res=sin(l);
    } else if (op == "cos") {
        res=cos(l);
    } else if (op == "tg") {
        res=tan(l);
    } else if (op == "ctg") {
        res=1/tan(l);
    } else if (op == "arcsin") {
        res=asin(l);
    } else if (op == "arccos") {
        res=acos(l);
    } else if (op == "arctg") {
        res=atan(l);
    } else if (op == "arcctg") {
        res=atan(1/l);
    } else if (op == "exp") {
        res=exp(l);
    } else if (op == "ln") {
        res=log(l);
    } else if (op == "sqrt") {
        res=sqrt(l);
    } else {
        return false;
    }

    s.push(res);
    return true;
}

bool calculate_operator_2(stack<double> &s, string op) {
    double l, r, res;

    r = s.top();
    s.pop();

    l = s.top();
    s.pop();

    if (op == "+"){
        res=l+r;
    } else if (op == "-"){
        res=l-r;
    } else if (op == "*"){
        res=l*r;
    } else if (op == "/"){
        res=l/r;
    } else if (op == "^"){
        res=powf(l, r);
    } else{
        return false;
    }

    s.push(res);
    return true;
}

double calculate_expression(string expr, double x) {
    stack<double> s;

    std::stringstream ss(expr);

    while (!ss.eof()) {
        string token;
        ss >> token;

        if (token == "sin" || token == "cos" || token == "tg" || token == "ctg" || token == "sqrt" ||
                   token == "exp" ||token == "ln" ||
                   token == "arcsin" ||token == "arccos" || token == "arctg" || token == "arcctg"){
            calculate_operator_1(s, token);
        }

        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^"){
            calculate_operator_2(s, token);
        }

        else if (token == "x" ){
           s.push(x);
        }

        else {
            s.push(strtod(token.c_str(), NULL));
        }
    }

    return s.top();
}

