#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;
/*czy pierwszy argument funkcji jest większy od drugiego*/
bool grt(string a, string b ) {
    if(a.size()>b.size())
        return true;
    if(a.size()<b.size())
        return false;
    else{
        for(int i=0; i<a.size();++i){
            if(a[i]>b[i])
                return true;
            if(a[i]<b[i])
                return false;
        }
        return false;
    }
}

int main(){

string a, b, opr;

/*możliwe operatory ==, != , < , > , <=, >= */

cin >>a >>opr >> b;


/*wieksza*/
if(opr==">"){
    if(grt(a,b))
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;

}

/*mniejsza*/
if(opr=="<"){
    if(grt(b,a))
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}

/*rowna*/
if(opr=="=="){
    bool eq = (grt(a,b)==false && grt(b,a) == false);
    if(eq)
        cout<< "TAK" << endl;
    else
        cout << "NIE" << endl;

}
/*nierowna*/
if(opr=="!="){
    if(grt(a,b) || grt(b,a))
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}

/*mniejsza równa*/
if(opr=="<="){
    bool eq = (grt(a,b)==false && grt(b,a) == false);
    if(grt(a,b)==false || eq )
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}

/*większa równa*/
if(opr==">="){
    bool eq = (grt(a,b)==false && grt(b,a) == false);
    if(grt(a,b) || eq )
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}




}


