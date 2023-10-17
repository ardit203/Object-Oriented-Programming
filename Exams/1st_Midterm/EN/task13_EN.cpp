#include <iostream>
#include <cstring>
using namespace std;

class Pasta{
private:
    char *name;
    float price;
    int discount;
    int calories;
    void copy(const Pasta &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->price=other.price;
        this->calories=other.calories;
        discount=other.discount;
    }
public:
    Pasta(char *name="", int price=0, int calories=0){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->price=price;
        this->calories=calories;
        discount=0;
    }
    Pasta(const Pasta &other){
        copy(other);
    }
    Pasta &operator=(const Pasta &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        copy(other);
        return *this;
    }

    Pasta light(int ca){
        char *newName=new char [strlen(name)+ strlen("light")+1];
        strcat(newName,name);
        strcat(newName,"Light");
        int newCal=calories-ca;
        float newPrice=price*(1-(20/100.0));
        Pasta newPasta(newName,newPrice,newCal);
        return newPasta;
    }
    int setDiscount(int i){
        discount=i;
    }
    ~Pasta(){
        delete [] name;
    }

    void print(){
        cout<<name<<" "<<calories<<" "<<price;
        if(discount>0){
            cout<<" ("<<price*(1-discount/100.0)<<")";
        }
    }

    void dby5(){
        discount-=5;
    }

    void setName(char *str){
        delete [] name;
        name=new char [strlen(str)+1];
        strcpy(name,str);
    }
};

class ItalianRestaurant{
    char name[50];
    Pasta *pastas;
    int numOfPastas;
    void copy(const ItalianRestaurant &other){
        strcpy(this->name,other.name);
        numOfPastas=other.numOfPastas;
        pastas=new Pasta [numOfPastas];
        for(int i=0 ; i<numOfPastas ; i++){
            pastas[i]=other.pastas[i];
        }
    }
public:
    ItalianRestaurant(char *name){
        strcpy(this->name,name);
        numOfPastas=0;
        pastas=new Pasta [numOfPastas];
    }
    ItalianRestaurant(const ItalianRestaurant &other){
        copy(other);
    }

    void add(Pasta &pasta) {
        Pasta *tmp=new Pasta[numOfPastas+1];
        for(int i=0 ; i<numOfPastas ; i++){
            tmp[i]=pastas[i];
        }
        delete [] pastas;
        tmp[numOfPastas++]=pasta;
        pastas=tmp;
    }

    void setPasta(int i, Pasta &pasta) {
        pastas[i]=pasta;
    }

    void print(){
        cout<<name<<endl;
        for(int i=0 ; i<numOfPastas ; i++){
            pastas[i].print();
            cout<<endl;
        }
    }
    ~ItalianRestaurant(){
        delete [] pastas;
    }
};
int main() {
    char name[100];
    float price;
    int discount;
    int calories;

    int testCase;

    cin >> testCase;

    if(testCase == 1) {
        cout << "====== TESTING Pasta CLASS ======" << endl;
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        cout << "CONSTRUCTOR" << endl;
        Pasta c1(name, price, calories);
        c1.setDiscount(discount);
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        Pasta c2(name, price, calories);
        c2.setDiscount(discount);
        cout << "Print" << endl;
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;
        cout << "Decrease by 5" << endl;
        c1.dby5();
        c1.print();
        cout << endl;
        cout << "Calories" << endl;
        int ca;
        cin >> ca;
        Pasta c3 = c1.light(ca);
        c3.print();
        cout << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING Pasta CONSTRUCTORS ======" << endl;
        cin >> name;
        cin >> price;
        cin >> discount;
        cin >> calories;
        cout << "CONSTRUCTOR" << endl;
        Pasta c1(name, price, calories);
        c1.print();
        cout << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        Pasta c2(c1);
        cin >> name;
        c2.setName(name);
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;
        cout << "OPERATOR =" << endl;
        c1 = c2;
        cin >> name;
        c2.setName(name);
        c1.print();
        cout << endl;
        c2.print();
        cout << endl;

    } else if(testCase == 3) {
        cout << "====== TESTING Italian Restaurant ======" << endl;
        char csName[50];
        cin >> csName;
        cout << "CONSTRUCTOR" << endl;
        ItalianRestaurant cs(csName);
        int n;
        cin >> n;
        cout << "Add" << endl;
        for(int i = 0; i < n; ++i) {
            cin >> name;
            cin >> price;
            cin >> calories;
            Pasta c(name, price, calories);
            cs.add(c);
        }
        cs.print();
        cout << endl;

    } else if(testCase == 4) {
        cout << "====== TESTING Italian Restaurant CONSTRUCTORS ======" << endl;
        char csName[50];
        cin >> csName;
        ItalianRestaurant cs(csName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> name;
            cin >> price;
            cin >> calories;
            Pasta c(name, price, calories);
            cs.add(c);
        }
        Pasta x("Funghi", 260, 275);
        ItalianRestaurant cp = cs;
        cs.setPasta(0, x);
        cs.print();
        cout << endl;
        cp.print();
        cout << endl;
    }
    return 0;
}
