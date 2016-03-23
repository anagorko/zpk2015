#include <iostream>
#include<math.h>
#include <iomanip>
using namespace std;

int main()
{
 double r,obwod,pole;
 cin>>r;

 cout<<setprecision(3)<<fixed;

 obwod=2*M_PI*r;
 pole=M_PI*r*r;


 cout<<pole<<endl;
 cout<<obwod;

}
