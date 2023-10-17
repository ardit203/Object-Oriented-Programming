#include <iostream>
#include <cstring>
using namespace std;
#define MAX 50

enum typeC{
    STANDARD//==0
    ,LOYAL//==1
    ,VIP//==2
};

class Customer{
protected:
    char name[MAX];
    char email[MAX];
    typeC typeOfCustomer; //Standard=0,  Loyal=1,  VIP=2;
    static int BASIC_DISCOUNT;
    static const int ADDITIONAL_DISCOUNT;
    int numOfProducts;
public:
    Customer(char *name, char *email, typeC typeOfCustomer, int numOfProducts){
        strcpy(this->name,name);
        strcpy(this->email,email);
        this->typeOfCustomer=typeOfCustomer;
        this->numOfProducts=numOfProducts;
    }
    Customer(){}
    friend ostream &operator<<(ostream &out, Customer &c){
        out<<c.name<<endl;
        out<<c.email<<endl;
        out<<c.numOfProducts<<endl;
        if(c.typeOfCustomer==typeC(2)){
            out<<"vip "<<c.BASIC_DISCOUNT+c.ADDITIONAL_DISCOUNT<<endl;
        } else if(c.typeOfCustomer==typeC(1)){
            out<<"loyal "<<c.BASIC_DISCOUNT<<endl;
        } else{
            cout<<"standard 0"<<endl;
        }
        return out;
    }
    static void setDiscount1(int i){
        BASIC_DISCOUNT=i;
    }
    char *getEmail(){
        return email;
    }
    int getNumProducts(){
        return numOfProducts;
    }
    void setType(int i){
        typeOfCustomer=typeC(i);
    }
    typeC getType(){
        return typeOfCustomer;
    }
};

int Customer::BASIC_DISCOUNT=10;
const int Customer::ADDITIONAL_DISCOUNT=20;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


class UserExistsException{
public:
    UserExistsException(){}
    void show(){
        cout<<"The user already exists in the list!"<<endl;
    }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
class FINKI_bookstore{
private:
    Customer *customers;
    int n;
    void copy(const FINKI_bookstore &other){
        this->n=other.n;
        this->customers=new Customer[n];
        for(int i=0 ; i<n ; i++){
            customers[i]=other.customers[i];
        }
    }
public:
    FINKI_bookstore(){
        n=0;
        this->customers=new Customer[n];
    }
    FINKI_bookstore(const FINKI_bookstore &other){
        copy(other);
    }
    ~FINKI_bookstore(){
        delete[] customers;
    }
    FINKI_bookstore &operator+=(Customer &c){
        for(int i=0 ; i<n ; i++){
            if(strcmp(customers[i].getEmail(),c.getEmail())==0){
                throw UserExistsException();
            }
        }
        Customer *tmp=new Customer[n];
        for(int i=0 ; i<n ; i++){
            tmp[i]=customers[i];
        }
        delete [] customers;
        tmp[n++]=c;
        customers=tmp;
        return *this;
    }

    void setCustomers(Customer *c, int size){
//        for(int i=0 ; i<n ; i++){
//            for(int j=0 ; j<size ; j++){
//                if(strcmp(customers[i].getEmail(),c[j].getEmail())==0){
//                    throw UserExistsException();
//                }
//            }
//        }
        this->customers=new Customer[size];
        for(int i=0 ; i<size ; i++){
            customers[i]=c[i];
        }
        n=size;
    }

    friend ostream &operator<<(ostream &os, const FINKI_bookstore &bookstore) {
        for(int i=0 ; i<bookstore.n ; i++){
            os<<bookstore.customers[i];
        }
        return os;
    }
    void update(){
        for(int i=0 ; i<n ; i++){
            Customer c=customers[i];
            if(c.getType()==typeC(2)){
                continue;
            }
            if(c.getNumProducts()>5){
                customers[i].setType(1);
            }
            if(c.getType()==typeC(1) && c.getNumProducts()>10){
                customers[i].setType(2);
            }
        }
    }
};


int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try{
            fc+=c;
        }catch (UserExistsException &e){
            e.show();
        }


        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        Customer c;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            c=Customer(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }
            fc.setCustomers(customers, n);


        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        try {
            fc+=c;
        }catch (UserExistsException &e){
            e.show();
        }


        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
