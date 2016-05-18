#include<iostream>
#include<cstdlib>
using namespace std;

int pierwsza(int tab[], int l, int p, int szukana)
{
  int sr;
  while(l<=p)
  {
    sr = (l+p)/2;
    {
    if(tab[sr] > szukana || tab[sr]==szukana)
      p = sr-1;
    else
      l = sr+1;
    }
  }
  return sr;
}

int ostatnia(int tab[], int l, int p, int szukana)
{
  int sr;
  while(l<=p)
  {
    sr = (l+p)/2;
    {
    if(tab[sr] < szukana || tab[sr]==szukana)
      l = sr+1;
    else
      p = sr-1;
    }
  }
  return sr;
}

int main()
{
  int n;
  cin>>n;
  
  int tab[n];
  for(int i=0;i<n;i++)
    cin>>tab[i];
  
  int szukane;
  cin>>szukane;
  
  int tab2[szukane];
  for(int i=0;i<szukane;i++)
    cin>>tab2[i];
    
  int wynik[szukane];
  
  for(int i=0;i<szukane;i++)
  {
      int pierwszal = pierwsza(tab, 0, n-1, tab2[i]);
      int ostatnial = ostatnia(tab, 0, n-1, tab2[i]);
      
      wynik[szukane]=ostatnial-pierwszal+1;
  }
    
    cout<<wynik[szukane]<<endl;
}
