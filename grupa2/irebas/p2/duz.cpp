#include <iostream>
#include <string>
using namespace std;

int main() {
    string wyr;
    string znak;
    string wyr2;
    bool lewy = false;
    bool prawy = false;
    bool rowny = false;
    cin >> wyr;
    cin >> znak;
    cin >> wyr2;
    int dl1 = wyr.length();
    int dl2 = wyr2.length();
    int dl3 = znak.length();
    /* cout << dl1 << " " << dl2 << " " << dl3 << endl; */
    if (dl1 > dl2) {
    	lewy = true;
    	
    }
    else if (dl2 > dl1) {
    	prawy = true;
    	
    }
    
    else {
    	for (int i=0; i<= dl1; i++) {
    		if (wyr[i] > wyr2[i]) {
    			lewy = true;
    			
    			break;
    		}
    		else if (wyr2[i] > wyr[i]) {
    			prawy = true;
    			
    			break;
    		}
    	}
    	if (prawy == false && lewy == false) {
    		rowny = true;
    		
    	}
    }
    
    if (lewy == true) {
    	if (znak == ">" || znak == ">=" || znak == "!=") {
    		cout << "TAK";
    	}
    	else if (znak == "<" || znak == "<=" || znak == "=") {
    		cout << "NIE";
    	}
    }
    
    else if (prawy == true) {
    	if (znak == "<" || znak == "<=" || znak == "!=") {
    		cout << "TAK";
    	}
    	else if (znak == ">" || znak == ">=" || znak == "=") {
    		cout << "NIE";
    	}
    }
    
    else if (rowny == true) {
    	if (znak == ">=" || znak == "<=" || znak == "=") {
    		cout << "TAK";
    	}
    	else if (znak == "<" || znak == ">" || znak == "!=") {
    		cout << "NIE";
    	}
    }
    
    /* cout << lewy << endl;
    cout << prawy << endl;
    cout << rowny << endl; */
    
}
