#include <iostream>
#include <cstring>
using namespace std;

class Film{
private:
    char name[100];
    double rating;
    double revenue;
public:
    Film(char * _name, double _rating, double _revenue){
        strcpy(name,_name);
        rating=_rating;
        revenue=_revenue;
    }
    Film(){
        strcpy(name,"");
        rating=0;
        revenue=0;
    }
    ~Film(){
    }
    void setName(char *n){
        strcpy(name,n);
    }
    void setRating(double r){
        rating=r;
    }
    void setRevenue(double r){
        revenue=r;
    }
    char *getName(){
        return name;
    }
    double getRating(){
        return rating;
    }
    double getRevenue(){
        return revenue;
    }
    void display(){
        cout<<"Name of film: "<<name<<endl<<"Rating: "<<rating<<endl<<"Revenue: "<<revenue<<endl;
    }
};

void printMostPopularFilm(Film *films ,int n){
    Film mostPopular=films[0];
    for(int i=1 ; i<n ; i++){
        if(films[i].getRevenue()>mostPopular.getRevenue()){
            mostPopular=films[i];
        }
    }
    mostPopular.display();
}
// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    Film films[100];

    char name[100];
    double rating;
    double revenue;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> rating;
        cin >> revenue;

        // testing constructor with arguments
        films[i] = Film(name, rating, revenue);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> rating;
    cin >> revenue;
    films[n-1].setName(name);
    films[n-1].setRating(rating);
    films[n-1].setRevenue(revenue);

    cout<<"-->Testing set methods and display()"<<endl;
    films[n-1].display();
    cout<<endl;

    cout<<"-->Testing printMostPopularFilm()"<<endl;
    printMostPopularFilm(films , n);
    return 0;
}