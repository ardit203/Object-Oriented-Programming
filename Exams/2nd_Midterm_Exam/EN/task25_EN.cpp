#include <iostream>
#include <cstring>
using namespace std;

//Your code here

class Tickets{
protected:
    int ID[12];
    char event[100];
    float price;
    static int DISCOUNT;
public:
    Tickets(int *ID= nullptr, char *event="", float price=0.0){
        for(int i=0 ; i<12 ; i++){
            this->ID[i]=ID[i];
        }
        strcpy(this->event,event);
        this->price=price;
    }
    virtual float computedPrice()=0;
    virtual bool falcification(int from,int to){
        int t=0;
        for(int i=8 ; i<12 ; i++){
            t=t*10+ID[i];
        }
        if(t<from || t>to){
            return true;
        }
        return false;
    }
    static void changeDiscount(int d){
        DISCOUNT=d;
    }
    friend ostream &operator<<(ostream &os,  Tickets &tickets){
        for(int i=0 ; i<12 ; i++){
            os<<tickets.ID[i];
        }
        os<<"-"<<tickets.event<<"-"<<tickets.computedPrice();
        return os;
    }
};

int Tickets::DISCOUNT=0;

//========================================================================================//


class Online:public Tickets{
private:
    bool premium;
public:
    Online(int *ID= nullptr, char *event="", float price=0.0, bool premium=false) : Tickets(ID,event,price) {
        this->premium=premium;
    }

    float computedPrice() override {
        float p=price*(1-DISCOUNT/100.0);
        if(premium){
            float t=price*(1-(15+DISCOUNT)/100.0);
            return t;
        }
        return p;
    }
};


//========================================================================================//



class Offline:public Tickets{
private:
    bool reservation;
public:
    Offline(int *ID= nullptr, char *event="", float price=0.0, bool reservation=false) : Tickets(ID,event,price) {
        this->reservation=reservation;
    }

    float computedPrice() override {
        float p=price*(1-DISCOUNT/100.0);
        if(reservation){
            float t=price*(1+(10-DISCOUNT)/100.0);
            return t;
        }
        return p;
    }
};


//=============================================================================================//


void vkupenPrihod(Tickets ** t, int n, int from, int to){
    float sum=0.0;
    for(int i=0 ; i<n ; i++){
        if(!t[i]->falcification(from,to)){
            sum+=t[i]->computedPrice();
        }
    }
    cout<<sum<<endl;
}

// DO NOT CHANGE THE MAIN FUNCTION, EXCEPT THE MARKED PART FOR HANDLING WITH THE EXCEPTION
int main() {
    int testCase;
    cin >> testCase;
    int ID[12];
    char nastan[100];
    float price;
    bool premium;
    bool rezervacija;
    int od, doo;

    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> premium;
        Online o1(ID, nastan, price, premium);
        cout << o1 << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> rezervacija;
        Offline o2(ID, nastan, price, rezervacija);
        cout << o2 << endl;

    }
    else if (testCase == 2) {
        cout << "===== TESTING METHOD vkupenPrihod()  ======" << endl;
        int n;
        cin >> n;
        Tickets** t = new Tickets*[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; j++)
                cin >> ID[j];
            cin >> nastan;
            cin >> price;

            if (i % 2 == 0){
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            }
            else {
                cin >> rezervacija;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        cin >> od;
        cin >> doo;
        vkupenPrihod(t, n, od, doo);
        for (int i = 0; i < n; ++i) {
            delete t[i];
        }
        delete[] t;
    }
    else if (testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        //cout<<n<<endl;
        Tickets** t = new Tickets*[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; ++j)
                cin >> ID[j];
            cin >> nastan;
            //cout<<nastan<<endl;
            cin >> price;
            //cout<<PRC<<endl;
            if (i % 2 == 0){
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            }
            else {
                cin >> rezervacija;
                //cout<<rezervacija<<endl;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        int d;
        cin >> d;
        Tickets::changeDiscount(d);
        for (int i = 0; i < n; ++i)
            cout << *t[i] << endl;

    }
}
