#include <iostream>
using namespace std;

struct skiLift{
    char name[15];
    int capacity;
    int available;

    void readSkiLift(){
        cin >> name >> capacity >> available;
    }
};

struct skiCenter{
    char name[20];
    char country[20];
    skiLift skiLifts[20];
    int num_skiLifts;
    void readSkiCenter(){
        cin>>name>>country>>num_skiLifts;
        for(int i=0 ; i<num_skiLifts ; i++){
            skiLifts[i].readSkiLift();
        }
    }
    int capacity(skiCenter other){

    }
};

void biggestCapacity(skiCenter *sc, int n){

}

int main(){

    return 0;
}