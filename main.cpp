#include<iostream>
#include<cstring>
using namespace std;

int main(){
    int n;
    cin>>n;

    int *ardit=new int [n];
    for(int i=0 ; i<n ; i++){
        cin>>ardit[i];
    }


    for(int i=0 ; i<n ; i++){
        cout<<ardit[i]<<" ";
    }
    return 0;
}