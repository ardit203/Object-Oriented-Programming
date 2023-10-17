#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde


class Vozac{
protected:
    char name[100];
    int age;
    int races;
    bool isVeteran;
public:
    Vozac(char *name, int age, int races, bool isVeteran){
        strcpy(this->name,name);
        this->age=age;
        this->races=races;
        this->isVeteran=isVeteran;
    }
    Vozac(){}
    friend ostream &operator<<(ostream &out, Vozac &v){
        out<<v.name<<endl<<v.age<<endl<<v.races<<endl;
        if(v.isVeteran){
            out<<"VETERAN"<<endl;
        }
        return out;
    }
    virtual float earnings()=0;
    virtual float danok()=0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Avtomobilist:public Vozac{
private:
    float price;
public:
    Avtomobilist(char *name, int age, int races, bool isVeteran, float price)
    : Vozac(name,age,races,isVeteran){
        this->price=price;
    }
    Avtomobilist(){}
    float earnings() override {
        return price/5;
    }
    float danok(){
        if(races>10){
            return earnings()*0.15;
        }
        return earnings()*0.1;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////

class Motociklist:public Vozac{
private:
    int enginePower;
public:
    Motociklist(char *name, int age, int races, bool isVeteran, float enginePower)
            : Vozac(name,age,races,isVeteran){
        this->enginePower= enginePower;
    }
    Motociklist(){}
    float earnings() override {
        return enginePower*20;
    }
    float danok(){
        if(isVeteran){
            return earnings()*0.25;
        }
        return earnings()*0.2;
    }
};

int soIstaZarabotuvachka(Vozac **v, int n, Vozac *vx){
    int count=0;
    for(int i=0 ; i<n ; i++){
        if(v[i]->earnings()==vx->earnings()){
            count++;
        }
    }
    return count;
}


int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}