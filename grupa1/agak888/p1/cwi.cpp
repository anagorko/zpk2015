#include <iostream>
using namespace std;

/* program, kt�ry dla danego punktu na p�aszczy�nie sprawdzi, w kt�rej �wiartce uk�adu wsp�rz�dnych
si� on znajduje. Moze jednak byc tak, �e punkt nie znajduje si� w �adnej �wiartce � le�y na jednej z osi lub
w �rodku uk�adu wsp�rz�dnych. W�wczas program powinien to stwierdzi�. */


int main() {
    int x, y; /* wspolrzedne punktu*/
    cin >> x >> y;
    
    if (x>0 && y>0)  			/* && - operator "and" */
    cout << "I" << endl;
        
	    else if (x<0 && y>0)
		cout << "II" << endl;
	        
	 		else if (x<0 && y<0)
	    	cout << "III" << endl;
	        
			    else if (x>0 && y<0)
			    cout << "IV" << endl;
				        
				    else if (x==0 && y==0) 		/*gdy w srodku ukladu*/
				    cout << "0" << endl;
				        
					    else if (x==0 && y!=0)		/*gdy na osi y */
					    cout << "OY" << endl;
					        
						    else
					        cout << "OX" << endl;
}
