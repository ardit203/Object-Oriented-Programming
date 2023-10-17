#include <iostream>
#include <cstring>

using namespace std;

class Piano{
    char serialNumber[25];
    double price;
    int year;
public:
    Piano(char *serialNumber="", double price=0, int year=0){
        strcpy(this->serialNumber,serialNumber);
        this->price=price;
        this->year=year;
    }
    bool equals(Piano &other){
        return strcmp(this->serialNumber,other.serialNumber)==0;
    }
    void print(){
        cout<<serialNumber<<" "<<year<< " "<<price<<endl;
    }
    double getPrice()const{
        return price;
    }
    char *getSerial(){
        return serialNumber;
    }
    void setSerial(char *other){
        strncpy(serialNumber,other,24);
        serialNumber[24]=0;
    }
};





class PShop{
private:
    char name[50];
    Piano *pianos;
    int numOfPianos;

    void copy(const PShop &other){
        strcpy(name,other.name);
        numOfPianos=other.numOfPianos;
        pianos=new Piano [numOfPianos];
        for(int i=0 ; i<numOfPianos ; i++){
            pianos[i]=other.pianos[i];
        }
    }
public:
    PShop(char *name=""){
        strcpy(this->name,name);
        numOfPianos=0;
        pianos=new Piano [numOfPianos];
        pianos=NULL;
    }
    PShop(const PShop &other){
        copy(other);
    }

    PShop operator=(const PShop &other){
        if(this==&other){
            return *this;
        }
        delete [] pianos;
        copy(other);
        return *this;
    }

    double value(){
        double sum=0;
        for(int i=0 ; i<numOfPianos ; i++){
            sum+=pianos[i].getPrice();
        }
        return sum;
    }
    void add(Piano p){
        Piano *tmp=new Piano[numOfPianos+1];
        for(int i=0 ; i<numOfPianos ; i++){
            tmp[i]=pianos[i];
        }
        tmp[numOfPianos++]=p;
        delete []pianos;
        pianos=tmp;
    }
    void sell(Piano p){
        Piano *tmp=new Piano[numOfPianos];
        int j=0;
        for(int i=0 ; i<numOfPianos ; i++){
            if(!pianos[i].equals(p)){
                tmp[j++]=pianos[i];
            }
        }
        numOfPianos=j;
        delete [] pianos;
        pianos=tmp;
    }
    void print(){
        cout<<name<<endl;
        for(int i=0 ; i<numOfPianos ; i++){
            cout<<i+1<<". ";
            pianos[i].print();
        }
    }
    Piano getP(int n){
        return pianos[n];
    }
    ~PShop(){
        delete [] pianos;
    }
};

int main() {

    int n;
    cin >> n;


    if(n == 1) {
        cout << "---Class Piano---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin>>serialNo>>price>>pYear;
        Piano p(serialNo,price,pYear);
        p.print();
    } else if(n == 2) {
        cout << "---Equals---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        Piano p2(p1);
        if (p1.equals(p2))
            cout<<"Equality"<<endl;
        else
            cout<<"Inequality"<<endl;
        p2.setSerial("12344");
        if (p1.equals(p2))
            cout<<"Equality"<<endl;
        else
            cout<<"Inequality"<<endl;
    }  else if(n == 3) {
        cout << "---Class PShop---" << endl;
        char name[50];
        cin >> name;
        PShop ps(name);
        ps.print();
    } else if(n == 4) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        ps.print();
    } else if(n == 5) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        PShop ps2(ps), ps3;

        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin>>serialNo>>price>>pYear;
        Piano p2(serialNo,price,pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

    } else if(n == 6) {
        cout << "---value method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        cout<<"Total PRC: "<<ps.value()<<endl;
    }
    else if(n == 7) {
        cout << "---sell method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        int d;
        cin>>d;
        Piano p1(ps.getP(d).getSerial());
        ps.sell(p1);
        ps.print();
    } else if(n == 8) {
        cout << "---Full Test---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin>>no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i=0;i<no;i++) {
            cin>>serialNo>>price>>pYear;
            Piano p(serialNo,price,pYear);
            ps.add(p);
        }
        ps.print();

        cout<<endl;

        PShop ps2(ps), ps3;

        cin>>serialNo>>price>>pYear;
        Piano p1(serialNo,price,pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin>>serialNo>>price>>pYear;
        Piano p2(serialNo,price,pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

        cout<<endl;

        cout<<"Total PRC: "<<ps.value()<<endl;

        cout<<endl;

        int d;
        cin>>d;
        Piano p3(ps.getP(d).getSerial());
        ps.sell(p3);
        ps.print();

        cout<<"Total PRC: "<<ps.value()<<endl;
    }
    return 0;
}