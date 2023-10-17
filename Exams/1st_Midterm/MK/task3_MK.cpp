#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde

class StockRecord{
    char ID[12];
    char name[50];
    double price;
    double newPrice;
    int shares;
public:
    StockRecord(char *ID="", char *name="", double price=0, int shares=0){
        strcpy(this->ID,ID);
        strcpy(this->name, name);
        this->price=price;
        this->shares=shares;
    }
    void setNewPrice(double d){
        newPrice=d;
    }
    double value() const{
     double v=shares*newPrice;
        return v;
    }
    double profit() const{
        double p=shares*(newPrice-price);
        return p;
    }
    friend ostream &operator<<(ostream &out, StockRecord &s){
        out<<s.name<<" "<<s.shares<<" "<<s.price<<" "<<s.newPrice<<" "<<s.profit()<<endl;
        return out;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////

class Client{
private:
    char name[60];
    int ID;
    StockRecord *stocks;
    int n;
public:
    Client(char *name="", int ID=0){
        strcpy(this->name,name);
        this->ID=ID;
        this->n=0;
        this->stocks=new StockRecord[n];
    }
    ~Client(){
        delete [] stocks;
    }
    double totalValue(){
        double sum=0;
        for(int i=0 ; i<n ; i++){
            sum+=stocks[i].value();
        }
        return sum;
    }
    Client &operator+=(StockRecord &s){
        StockRecord *tmp=new StockRecord[n+1];
        for(int i=0 ; i<n ; i++){
            tmp[i]=stocks[i];
        }
        delete [] stocks;
        tmp[n++]=s;
        stocks=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, Client &c){
        out<<c.ID<<" "<<c.totalValue()<<endl;
        for(int i=0 ; i<c.n ; i++){
            out<<c.stocks[i];
        }
        return out;
    }
};

// ne menuvaj vo main-ot

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}