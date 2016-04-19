#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
using namespace std;

class Polynomial
{
    vector <double> a;

 //   double findRoot(double, double);

public:
    Polynomial()
    {
        a.push_back(0);
    }
//--------------------------------------------------
    double getA(int x) const
    {
        if (x<=a.size())
        {
            return a[x];
        }
    }

//---------------------------------------------------
    void setA(int k, double x)
    {
        if (k<a.size()) a[k] = x;
        else if (k==a.size()) a.push_back(x);
        else
        {
            for (int i=a.size();i<k;i++)
            {
                a.push_back(0);
            }
            a.push_back(x);
        }

    }
//---------------------------------------------------------
    int deg() const
    {
        if(a.size()==1 && a[0]==0) return -1;
        else if(a.size()==1 && a[0]!=0) return 0;
        else return a.size()-1;
    }

//---------------------------------------------------------------------------------
      const Polynomial operator+(const Polynomial &q) const
      {
          Polynomial wynik;
          if(a.size()>=q.deg())
          {
              for (int i=0;i<a.size();i++)
              {
                  if(i>q.deg()) wynik.setA(i,a[i]);
                  else wynik.setA(i,a[i]+ q.getA(i));
              }
          }
          else
          {
              for (int i=0;i<=q.deg();i++)
              {
                  if(i>a.size()) wynik.setA(i,q.getA(i));
                  else wynik.setA(i,a[i]+ q.getA(i));
              }
          }
       return wynik;
      }

 //-----------------------------------------------------------
      Polynomial& operator+=(const Polynomial &q)
        {
        if(a.size()-1>=q.deg())
          {
              for (int i=0;i<a.size();i++)
              {
                  if(i<=q.deg())  a[i] = a[i] + q.getA(i);
              }
          }
        else
          {
              for (int i=0;i<=q.deg();i++)
              {
                  if(i<a.size()) a[i] = a[i] + q.getA(i);
                  else a[i] = q.getA(i);
              }
          }
        }

//--------------------------------------------------------------------
const Polynomial operator*(const Polynomial &q) const
{
    Polynomial wynik;
    if( (q.deg() >0 || q.getA(0) != 0)    &&   (a.size() > 1 || a[0] != 0) )
    {
        wynik.setA(0, a[0]*q.getA(0));
        for (int i=1; i<= (q.deg() + a.size() - 1);i++)
        {
            double wsp = 0;
            for (int j=0; j<=i; j++)
            {
                if(a.size()>j && q.deg()>=i-j)
                {
                    wsp = wsp + a[j] * q.getA(i-j);
                }
            }
            wynik.setA(i, wsp);
        }
    }
    return wynik;
}
//--------------------------------------------------------------------
Polynomial& operator*=(const Polynomial &q)
{
    vector<double> b;
    if( (q.deg() > 0 || q.getA(0) != 0) && (a.size() > 1 || a[0] != 0) )
    {
        b.push_back(a[0] * q.getA(0));
        for (int i=1; i<= (q.deg() + a.size() -1); i++)
        {
            b.push_back(0);
            for (int j=0; j<=i; j++)
            {
                if(a.size()>j && q.deg()>=i-j)
                {
                    b[i] = b[i] + a[j]*q.getA(i-j);
                }
            }
        }
    }
    a = b;
}

//--------------------------------------------------------------------
  const Polynomial operator-(const Polynomial &q) const
{
          Polynomial wynik;
          if(a.size()>=q.deg())
          {
              for (int i=0;i<a.size();i++)
              {
                  if(i>q.deg()) wynik.setA(i,a[i]);
                  else wynik.setA(i,a[i]- q.getA(i));
              }
          }
          else
          {
              for (int i=0;i<=q.deg();i++)
              {
                  if(i>=a.size()) wynik.setA(i,- q.getA(i));
                  else wynik.setA(i,a[i] - q.getA(i));
              }
          }
       return wynik;
}

//----------------------------------------------------------------------------
Polynomial& operator-=(const Polynomial &q)
{
          if(a.size()>=q.deg())
          {
              for (int i=0;i<a.size();i++)
              {
                  if(i<=q.deg())     a[i] = a[i] - q.getA(i);
              }
          }
          else
          {
              for (int i=0;i<=q.deg();i++)
              {
                  if(i>=a.size()) a[i] = - q.getA(i);
                  else a[i] = a[i] - q.getA(i);
              }
          }
}

//----------------------------------------------------------------------------
    bool operator==(const Polynomial &q) const
    {
        if (q.deg() != a.size()-1) cout << "rozne" << endl; // return false;
        else
        {
            int licz = 0;
            for (int i=0;i<a.size()-1;i++) if (q.getA(i) != a[i]) licz++;
            if (licz==0) cout << "takie same" << endl; //return true;
        }
    }

//----------------------------------------------------------------------------
    bool operator!=(const Polynomial &q) const
    {
        if (q.deg() != a.size()-1) cout << "rozne" << endl; // return true;
        else
        {
            int licz = 0;
            for (int i=0;i<a.size()-1;i++) if (q.getA(i) != a[i]) licz++;
            if (licz==0) cout << "takie same" << endl; //return false;
        }
    }

//--------------------------------------------------------------------------
    double v(double x) const
    {
        double b, c;
        b = a[a.size()-1];
        for (int i=a.size()-2;i>=0;i--)
        {
            c = b * x + a[i];
            b = c;
        }
        cout << endl << b << endl;
        return b;
    }

//----------------------------------------------------------------------
const Polynomial differential() const
{
    Polynomial wynik;
    if(a.size()>=2)
    {
        wynik.setA(0,a[1]);
        for (int i=1; i<a.size()-1; i++)
        {
            wynik.setA(i, a[i+1] * (i+1));
        }
    }
    return wynik;
}
}
//-------------------------------------------------------------------------

    ostream & operator << (ostream &os, Polynomial &w)
    {
       if (w.deg()<=0) cout << w.getA(0);
       else
       {
           for (int i=w.deg();i>=0;i--)
           {

                    if(w.getA(i)!=0)
                    {
                        if(w.getA(i)>0 && i<w.deg()) cout << " + "; //znak + czy -
                        else cout << " ";
                        if(i==0) cout << w.getA(i);
                        else
                        {
                        if(w.getA(i)==-1) cout << "-" ;
                        if(w.getA(i)!=1 && w.getA(i)!=-1) cout << w.getA(i);
                        if(i>1) cout << "x^" << i;
                        else if(i==1) cout << "x";
                        }
                    }
           }
       }
       return os;
    }

    int main()
    {

        return 0;
    }
