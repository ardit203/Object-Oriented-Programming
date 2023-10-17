#include <iostream>
#include <cstring>
using namespace std;


// YOUR CODE HERE

class AlcoholicDrink{
protected:
    static int discount;
    char name[100];
    char countryOfOrigin[100];
    float percent_alcohol;
    float price;
    void copy(const AlcoholicDrink &other){
        strcpy(this->name,other.name);
        strcpy(this->countryOfOrigin,other.countryOfOrigin);
        this->percent_alcohol=other.percent_alcohol;
        this->price=other.price;
    }
public:
    AlcoholicDrink(float percent_alcohol=0, char *name="", char *countryOfOrigin="", float price=0){
        strcpy(this->name,name);
        strcpy(this->countryOfOrigin,countryOfOrigin);
        this->percent_alcohol=percent_alcohol;
        this->price=price;
    }
    AlcoholicDrink(const AlcoholicDrink &other){
        copy(other);
    }
    friend ostream &operator<<(ostream &out, AlcoholicDrink &a){
        return out << a.name << " " << a.countryOfOrigin << " " << a.computePrice();
    }
    virtual float computePrice(){
        return price;
    }
//    you can also make the class abstract by making this function pure virtual
//    virtual float computePrice()=0;

    bool operator<(AlcoholicDrink *other){
        return this->computePrice()<other->computePrice();
    }
    char *getName(){
        return name;
    }
    char *getOrigin(){
        return countryOfOrigin;
    }
    static void changeDiscount(int d){
        discount=d;
    }
    static void total(AlcoholicDrink **ad, int n){
        float sum=0.0;
        for(int i=0 ; i<n ; i++){
            sum+=ad[i]->computePrice();
        }
        cout<<"Total PRC: "<<sum<<endl;
        int a=discount;
        sum=sum*(1-(a/100.0));
        cout<<"Total PRC with discount: "<<sum<<endl;
    }

};






class Beer : public AlcoholicDrink{
private:
    bool main_ingredient;
    void copy(const Beer &other){
        strcpy(this->name,name);
        strcpy(this->countryOfOrigin,countryOfOrigin);
        this->percent_alcohol=percent_alcohol;
        this->price=price;
        this->main_ingredient=other.main_ingredient;
    }
public:
    Beer(float percent_alcohol=0, char *name="", char *countryOfOrigin="", float price=0, bool main_ingredient= false): AlcoholicDrink(percent_alcohol,name,countryOfOrigin,price){
        this->main_ingredient=main_ingredient;
    }
    Beer(const Beer &other){
        copy(other);
    }
    float computePrice(){
        if(strcmp(name,"Germanija")==0 && main_ingredient== false){
            return price*1.15;
        }else if(strcmp(name,"Germanija")==0){
            return price*1.05;
        }else if(main_ingredient== false){
            return price*1.1;
        }
        return price;
    }
};






class Wine : public AlcoholicDrink{
private:
    int year;
    char grape_type[20];
    void copy(const Wine &other){
        strcpy(this->name,other.name);
        strcpy(this->countryOfOrigin,other.countryOfOrigin);
        this->percent_alcohol=other.percent_alcohol;
        this->price=other.price;
        this->year=other.year;
        strcpy(this->grape_type,other.grape_type);
    }
public:
    Wine(float percent_alcohol=0, char *name="", char *countryOfOrigin="", float price=0,int year=0, char *grape_type=""): AlcoholicDrink(percent_alcohol,name,countryOfOrigin,price){
        this->year=year;
        strcpy(this->grape_type,grape_type);
    }
    Wine(const Wine &other){
        copy(other);
    }
    float computePrice(){
        if(strcmp(name,"Italija")==0 && year<2005){
            return price*1.2;
        }else if(strcmp(name,"Italija")==0){
            return price*1.05;
        }else if(year<2005){
            return price*1.15;
        }
        return price;
    }

};




void lowestPrice(AlcoholicDrink ** drink, int n){
    float lowestPrice=drink[0]->computePrice();
    int index=0;
    for(int i=1 ; i<n ; i++){
        float price=drink[i]->computePrice();
        if(price<lowestPrice){
            lowestPrice=price;
            index=i;
        }
    }
    cout<<*drink[index];
}

//void lowestPrice(AlcoholicDrink ** drink, int n){
//    int index=0;
//    for(int i=1 ; i<n ; i++){
//        if(drink[index]<drink[i]){
//            index=i;
//        }
//    }
//    cout<<*drink[index];
//}

int AlcoholicDrink::discount=5;

// DO NOT CHANGE THE MAIN FUNCTION


int main() {
    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape [20];
    if(testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> year;
        cin >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;

    } else if(testCase == 2) {
        cout << "===== TESTING LOWEST PRC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;

            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }

        lowestPrice(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    } else if(testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;
            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    }

}

