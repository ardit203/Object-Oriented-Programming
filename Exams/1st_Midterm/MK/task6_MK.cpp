#include<iostream>
#include <cstring>
using namespace std;

struct train{
    char route[50];
    float distance;
    int pasengers;

    void readTrain(){
        cin>>route>>distance>>pasengers;
    }
    void printTrain(){
        cout<<route<<" "<<distance<<" "<<pasengers<<endl;
    }
};

struct railwayStation{
    char city[20];
    train trains[30];
    int number_trains;

    void readRailwayStation(){
        cin>>city>>number_trains;
        for(int i=0 ; i<number_trains ; i++){
            trains[i].readTrain();
        }
    }
    void printRailwayStation(){
        cout<<city<<endl<<number_trains<<endl;
        for(int i=0 ; i<number_trains ; i++){
            trains[i].printTrain();
        }
    }
    train shortestRoute(){
        train min=trains[0];
        for(int i=0 ; i<number_trains ; i++){
            if(trains[i].distance<=min.distance){
                min=trains[i];
            }
        }
        return min;
    }
};

void shortestDistance(railwayStation *rs,int n, char *city){
    railwayStation shortestDistance;
    for(int i=0 ; i<n ; i++){
        if(strncmp(city,rs[i].city, strlen(city))==0){
            shortestDistance=rs[i];
            break;
        }
    }
    train t=shortestDistance.shortestRoute();
    cout<<"Najkratka relacija: "<<t.route<<" ("<<t.distance<<" km)";
}

int main(){
    int n;
    cin>>n;
    railwayStation rs[100];
    for(int i=0 ; i<n ; i++){
        rs[i].readRailwayStation();
    }
    //for(int i=0 ; i<n ; i++){
    //    rs[i].printRailwayStation();
    //}
    char city[25];
    cin>>city;
    shortestDistance(rs,n,city);
    return 0;
}