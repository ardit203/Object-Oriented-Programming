#include <iostream>
using namespace std;

struct politician{
    char pName[20];
    char party[20];
    void readPolitician(){
        cin >> pName >> party;
    }
    void printPolitician(){
        cout << pName << " " << party << " ";
    }
};
struct city{
    char cName[20];
    int population;
    void readCity(){
        cin >> cName >> population;
    }
    void printCity(){
        cout << cName << " " << population << " ";
    }
};

struct country{
    char name[20];
    politician president;
    city capital;
    int population;
    void readCountry(){
        cin>>name;
        president.readPolitician();
        capital.readCity();
        cin>>population;
    }

    void printCountry(){
        cout<<name<<" ";
        president.printPolitician();
        capital.printCity();
        cout<<population<<endl;
    }

    int countrycmp(country other){
        return capital.population>other.capital.population;
    }
};

int main(){
    int n;
    cin>>n;
    country c[100];
    for(int i=0 ; i<n ; i++){
        c[i].readCountry();
    }
    country max;
    max=c[0];
    for(int i=1 ; i<n ; i++){
        if(c[i].countrycmp(max)){
            max=c[i];
        }
    }
    cout<<"The president of the country whose capital city has the largest population is:"<<endl;
    cout<<max.president.pName;
    return 0;
}
