#include <iostream>
#include <cstring>
using namespace std;


// your code here


class InvalidDisount{
private:
    int d;
public:
    InvalidDisount(int d=0){
        this->d=d;
    }
    void show(){
        cout<<"Invalid discount value: "<<d;
    }
};

class IceCream{
private:
    char *name;
    char ingredients[200];
    float price;
    int discount;
    void copy(const IceCream &other){
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        strcpy(this->ingredients, other.ingredients);
        this->price = other.price;
        this->discount = other.discount;
    }
public:
    IceCream(char *name="", char *ingredients="", float price=0.0) {
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
        this->price=price;
        this->discount=0;
    }
    ~IceCream(){
        delete [] name;
    }
    IceCream(const IceCream &other) {
        copy(other);
    }

    IceCream &operator=(const IceCream &other) {
        if (this == &other) {
            return *this;
        }
        delete[] name;
        copy(other);
        return *this;
    }

    float calculatedPrice()const{
        return price*(1-discount/100.0);
    }
    friend ostream &operator<<(ostream &os, const IceCream &cream) {
        if(cream.discount>0){
            os<<cream.name<<": "<<cream.ingredients<<" "<<cream.price<<" ("<<cream.calculatedPrice()<<")";
        } else{
            os<<cream.name<<": "<<cream.ingredients<<" "<<cream.price;
        }
        return os;
    }
    IceCream &operator++(){
        discount+=5;
        return *this;
    }
    IceCream& operator+(const char* str) {
        char* tmp = new char[strlen(name) + strlen(str) + 4]; // Allocate enough memory
        strcpy(tmp, name);
        strcat(tmp, " + ");
        strcat(tmp, str);
        delete[] name;
        name = tmp;
        price += 10;
        return *this;
    }
    void setDiscount(int d){
        if(d<0 || d>100){
            throw InvalidDisount(d);
        }
        discount=d;
    }
    void setName(char *n){
        delete [] name;
        this->name=new char [strlen(n)+1];
        strcpy(name,n);
    }
};

//---------------------------------------------------------------------------------------//


class IceCreamShop{
    char name[110];
    IceCream *iceCreams;
    int numOfIceCream;
    void copy(const IceCreamShop &other){
        strcpy(this->name,other.name);
        this->numOfIceCream=other.numOfIceCream;
        this->iceCreams=new IceCream [numOfIceCream];
        for(int i=0 ; i<numOfIceCream ; i++){
            iceCreams[i]=other.iceCreams[i];
        }
    }
public:
    IceCreamShop(char *name=""){
        strcpy(this->name, name);
        numOfIceCream=0;
        this->iceCreams=new IceCream[numOfIceCream];
    }
    ~IceCreamShop(){
        delete [] iceCreams;
    }
    IceCreamShop(const IceCreamShop &other){
        copy(other);
    }
    IceCreamShop &operator=(const IceCreamShop &other){
        if(this==&other){
            return *this;
        }
        delete [] iceCreams;
        copy(other);
        return *this;
    }
    IceCreamShop &operator +=(IceCream &ic){
        IceCream *tmp=new IceCream [numOfIceCream+1];
        for(int i=0 ; i<numOfIceCream ; i++){
            tmp[i]=iceCreams[i];
        }
        delete [] iceCreams;
        tmp[numOfIceCream++]=ic;
        iceCreams=tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const IceCreamShop &shop) {
        os<<shop.name<<endl;
        for(int i=0 ; i<shop.numOfIceCream ; i++){
            os<<shop.iceCreams[i]<<endl;
        }
        return os;
    }
};


// DO NOT CHANGE THE MAIN FUNCTION, EXCEPT THE MARKED PART FOR HANDLING WITH THE EXCEPTION

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR &lt;&lt;" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "TESTING EXCEPTION" << endl;

        // your exception handling code

        cin >> discount;
        try {
            ic1.setDiscount(discount);
        }catch (InvalidDisount &e){
            e.show();
        }



    }
    else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60.0);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}

