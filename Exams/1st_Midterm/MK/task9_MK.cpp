#include <iostream>
using namespace std;

//create a Laptop structure
struct laptop{
    char brand[100];
    float monitor_dim;
    int has_touch;
    int price;
    void readLaptop(){
        cin>>brand>>monitor_dim>>has_touch>>price;
    }
    void printLaptop(){
        cout<<brand<<" "<<monitor_dim<<" "<<price<<endl;
    }
};

struct ITStore{
    char name[100];
    char location[100];
    laptop laptops[100];
    int number_laptops;
    void readITStore(){
        cin>>name>>location>>number_laptops;
        for(int i=0 ; i<number_laptops ; i++){
            laptops[i].readLaptop();
        }
    }
    void printITStore(){
        cout<<name<<" "<<location<<endl;
        for(int i=0 ; i<number_laptops ; i++){
            laptops[i].printLaptop();
        }
    }
    laptop cheapestWithTouch(){
        laptop hasTouch[100];
        int k=0;
        for(int i=0 ; i<number_laptops ; i++){
            if(laptops[i].has_touch==1){
                hasTouch[k++]=laptops[i];
            }
        }
        laptop cheapest_with_touch=hasTouch[0];
        for(int i=1; i<k ; i++){
            if(hasTouch[i].price<cheapest_with_touch.price){
                cheapest_with_touch=hasTouch[i];
            }
        }
        return cheapest_with_touch;
    }
int ITScmp(ITStore other){
    return cheapestWithTouch().price<other.cheapestWithTouch().price;
    }

};

void cheapest_offer(ITStore *stores, int n){
    ITStore min=stores[0];
    for(int i=1 ; i<n ; i++){
        if(stores[i].ITScmp(min)==1){
            min=stores[i];
        }
    }
    laptop l=min.cheapestWithTouch();
   // Najeftina ponuda ima prodavnicata:
   // Anhoch Skopje
   // Najniskata cena iznesuva: 32000
   cout<<"Najeftina ponuda ima prodavnicata:"<<endl<<min.name<<" "<<min.location<<endl<<"Najniskata cena iznesuva: "<<l.price;
}

int main(){
    int n;
    cin>>n;
    ITStore stores[100];
    for(int i= 0 ;i<n ; i++){
        stores[i].readITStore();
    }
    for (int i = 0; i < n; i++) {
        stores[i].printITStore();
    }
    cheapest_offer(stores,n);
    return 0;
}