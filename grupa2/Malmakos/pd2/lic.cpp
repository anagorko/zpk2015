

#include <iostream>
using namespace std;

int main(){
    int n;
    cin >>n;
    int tak=0;
    int nie=0;
    if(n<2){
        return 0;
        }

        else{
                if(n==2||n==3){
                    cout<<"pierwsza"<<endl;

                }
        else{
            for(int i=2; i*i<=n;i++){
                if(n%i==0){
                nie++;
                }
                else{
                tak++;
                }


            }
            if(nie>0){
                cout<<"zlozona"<<endl;
            }else{
            cout<<"pierwsza"<<endl;
            }
}

        }


}


