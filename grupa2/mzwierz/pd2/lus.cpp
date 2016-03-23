#include <iostream>                                                             
using namespace std;                                                            
                                                                                

int main(){                                                                               
  int a, b;                                                                       
  cin >> a;                                                                       
                                                                                  
  while(a!=0) {                                                                   
          b=a%10;                                                                 
          cout << b;                                                              
          a=(a-b)/10;                                                             
                                                                                  
  
      }                                                                           
                                                                                  
}     
