#include <iostream>
using namespace std;
 

int main() {

string a,b,znak;
    cin >> a >> znak >> b;
long int n;
int w=0;

if (a.size()>b.size() && (znak == "!=" || znak == ">" || znak== ">="))
    { cout << "TAK";
    return(0);
    }
if (a.size()<b.size() && (znak != "!=" &&  znak == ">" && znak ==">="))
    { cout << "NIE";
    return(0);
    }    
if (b.size()>a.size() && (znak == "!=" || znak == "<" || znak== "<="))
     { cout << "TAK";
    return(0);
    }
if (b.size()>a.size() && (znak != "!=" && znak != "<" && znak!="<="))
     { cout << "NIE";
    return(0);
    }

n=a.size();   

for(long int i=0;n-1;i++)
    {
        if(a[i]>b[i])
        {w=1;
        break;}
        
        if(a[i]<b[i])
        {w=2;
        break;
        }
    }

if(w==0 && (znak == "==" or znak == "<=" or znak == ">="))
 {cout << "TAK";
 return(0);}
 
if(w==0 && (znak == "!" or znak == "<" or znak == ">"))
 {cout << "NIE";
 return(0);} 
 
 if(w==1 && (znak == "!=" or znak == ">=" or znak == ">"))
 {cout << "TAK";
 return(0);}

 if(w==1 && (znak == "==" or znak == "<=" or znak == "<"))
 {cout << "NIE";
 return(0);}
 
  if(w==2 && (znak == "!=" or znak == "<=" or znak == "<"))
 {cout << "TAK";
 return(0);}
 
  if(w==2 && (znak == "==" or znak == ">=" or znak == ">"))
 {cout << "NIE";
 return(0);}
 
}
