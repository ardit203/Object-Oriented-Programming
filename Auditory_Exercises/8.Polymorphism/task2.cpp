#include <iostream>
#include <cstring>
using namespace std;

class HotelReservation{
protected:
    int days;
    int persons;
    char *contactName;
public:
    HotelReservation(char *contactName="Ardit", int days=1, int persons=1){
        this->contactName=new char [strlen(contactName)+1];
        strcpy(this->contactName,contactName);
        this->days=days;
        this->persons=persons;
    }
    virtual int price(){
        return days*persons*25;
    }
    int price(int payment){
        return payment-price();
    }
    virtual void print(){
       cout<<"Hotel Reservation with Contact Name: "<<contactName<<", "<<persons<<" persons"<<" for "<<days<<" days.";
       cout<<" Price: "<<price()<<endl;
    }

//    friend ostream &operator<<(ostream &os, const HotelReservation &reservation) {//Auto generate
//        os << "days: " << reservation.days << " persons: " << reservation.persons << " contactName: "
//           << reservation.contactName;
//        return os;
//    }
};

class BBHotelReservation : public HotelReservation{
public:
    BBHotelReservation(char *contactName="Ardit", int days=1, int persons=1): HotelReservation(contactName, days, persons){}
    int price(){
        return HotelReservation ::price()+days*persons*5;
    }
    void print(){
        cout<<"BB";
        HotelReservation ::print();
    }
};

class Hotel{
private:
    char name[10];
    int balance;
public:
    Hotel(char *name="", int balance=0){
        strcpy(this->name,name);
        this->balance=balance;
    }
    int reserve(HotelReservation &hr, int payment){
        this->balance+=hr.price();
        return hr.price(payment);
    }
};

int main(){
    Hotel A("Ardit");
    HotelReservation **p=new HotelReservation * [3];
    int a=45000000;
    for(int i=0 ; i<3; i++){
        if(i<=1){
            p[i]=new BBHotelReservation("Ardit",3,4);
        } else{
            p[i]=new HotelReservation("Ardit",3,4);
        }
        int amount=a;

        cout<<"Change: "<<A.reserve(*p[i],a)<<endl;
    }
    for(int i=0 ; i<3 ; i++){
        p[i]->print();
    }
}