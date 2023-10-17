#include <iostream>
#include <cstring>

using namespace std;

// YOUR CODE STARTS HERE

class Vehicle{
protected:
    char brand[100];
    char model[100];
    int year;
    int rentalPrice;
    void copy(const Vehicle &other){
        strcpy(this->brand,other.brand);
        strcpy(this->model,other.model);
        this->year=other.year;
        this->rentalPrice=other.rentalPrice;
    }
public:
    Vehicle(char *brand="", char *model="", int year=0, int rentalPrice=0){
        strcpy(this->brand,brand);
        strcpy(this->model,model);
        this->year=year;
        this->rentalPrice=rentalPrice;
    }
    Vehicle(const Vehicle &other){
        copy(other);
    }
    Vehicle &operator=(const Vehicle &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    int getRentPricePerHour(){
        return rentalPrice;
    }
    void print(){
        cout<<brand<<" - "<<model<<endl;
    }
    ~Vehicle(){}
};

class PassengerVehicle : public Vehicle{
private:
    int numberOfSeats;
    int numberOfDoors;
public:
    PassengerVehicle(){
        strcpy(this->brand,"");
        strcpy(this->model,"model");
        this->year=0;
        this->rentalPrice=0;
        this->numberOfSeats=0;
        this->numberOfDoors=0;

    }
    PassengerVehicle(const Vehicle &v, int numberOfSeats, int nuberOfDoors): Vehicle(v){
        this->numberOfSeats=numberOfSeats;
        this->numberOfDoors=nuberOfDoors;
    }
    int getRentPricePerHour(){
        return rentalPrice+rentalPrice*0.1;
    }
    void print(){
        cout<<brand<<" - "<<model<<" - "<<numberOfSeats<<" - "<<getRentPricePerHour()<<" euros"<<endl;
    }
};
class FreightVehicle : public Vehicle{
private:
    int cargoCapacity;
    int horsePower;
public:
    FreightVehicle(){
        strcpy(this->brand,"");
        strcpy(this->model,"model");
        this->year=0;
        this->rentalPrice=0;
        this->cargoCapacity=0;
        this->horsePower=0;

    }
    FreightVehicle(const Vehicle &v, int numberOfSeats, int nuberOfDoors): Vehicle(v){
        this->cargoCapacity=numberOfSeats;
        this->horsePower=nuberOfDoors;
    }
    int getRentPricePerHour(){
        return rentalPrice+rentalPrice*0.5;
    }
    void print(){
        cout<<brand<<" - "<<model<<" - "<<cargoCapacity<<" - "<<getRentPricePerHour()<<" euros"<<endl;
    }
};


// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    char manufacturer[100];
    char model[100];
    int productionYear;
    int rentalPricePerHour;

    for (int i = 0; i < n; i++) {
        cin >> manufacturer;
        cin >> model;
        cin >> productionYear;
        cin >> rentalPricePerHour;

        Vehicle v = Vehicle(manufacturer, model, productionYear, rentalPricePerHour);

        if (i % 2) {
            int cargoCapacity;
            int horsePower;
            cin >> cargoCapacity;
            cin >> horsePower;
            FreightVehicle fv = FreightVehicle(v, cargoCapacity, horsePower);
            fv.print();
        } else {
            int numSeats;
            int numDoors;
            cin >> numSeats;
            cin >> numDoors;
            PassengerVehicle pv = PassengerVehicle(v, numSeats, numDoors);
            pv.print();
        }
    }


    return 0;
}