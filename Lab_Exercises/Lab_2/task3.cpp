#include <iostream>
#include <cstring>
using namespace std;

class Country{
private:
    char name[100];
    char capital[100];
    double area;
    double population;
public:
    Country(char *_name, char *_capital, double _area, double _population){
        strcpy(name,_name);
        strcpy(capital,_capital);
        area=_area;
        population=_population;
    }
    Country(){
        strcpy(name,"");
        strcpy(capital,"");
        area=0;
        population=0;
    }

    ~Country(){
    }
    void setName(char *n){
        strcpy(name,n);
    }
    void setCapital(char *c){
        strcpy(capital,c);
    }
    void setArea(double a){
        area=a;
    }
    void setPopulation(double p){
        population=p;
    }
    char *getName(){
        return name;
    }
    char *getCapital(){
        return capital;
    }
    double getArea(){
        return area;
    }
    double getPopulation(){
        return population;
    }
    void display(){
        cout<<"Country: "<<name<<endl;
        cout<<"Capital: "<<capital<<endl;
        cout<<"Area: "<<area<<endl;
        cout<<"Population: "<<population<<endl;
    }
};

void sortCountries(Country *countries,int n){
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n-1-i ; j++){
            if(countries[j].getArea()>countries[j+1].getArea()){
                Country tmp=countries[j];
                countries[j]=countries[j+1];
                countries[j+1]=tmp;
            }
        }
    }
    for(int i=0 ; i<n ; i++){
        countries[i].display();
    }
}

// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    Country countries[100];

    char name[100];
    char capital[100];
    double area;
    double population;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> capital;
        cin >> area;
        cin>>population;

        // testing constructor with arguments
        countries[i] = Country(name, capital, area, population);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> capital;
    cin >> area;
    cin>>population;
    countries[n-1].setName(name);
    countries[n-1].setCapital(capital);
    countries[n-1].setArea(area);
    countries[n-1].setPopulation(population);

    cout<<"-->Testing set methods and display()"<<endl;
    countries[n-1].display();
    cout<<endl;

    cout<<"-->Testing sortCountries()"<<endl;
    sortCountries(countries,n);
    return 0;
}