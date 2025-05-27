#include<bits/stdc++.h>
using namespace std;
int main(){
    short opt;
    bool loop = true;
    while(loop){
        cout<<"\n---------------RAM TAXI BOOKING AGENCY-----------------\n";
        cout<<" 1. Book Taxi\n 2. Display Details\n 3. Exit\n";
        cout<<"Enter your option :\n";
        cin>>opt;
        switch(opt){
            case 1:{
                cout<<"Book Taxi";
                break;
            }
            case 2:{
                cout<<"Display Details";
                break;
            }
            case 3:{
                loop = false;
                break;
            }
            default:{
                cout<<"Invalid Input";
            }
        }
    }
    return 0;
}