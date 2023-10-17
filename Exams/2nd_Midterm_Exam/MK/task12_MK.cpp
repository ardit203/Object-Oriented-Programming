#include <iostream>
#include <cstring>

using namespace std;

enum tip{
    SMARTPHONE,//==0
    COMPUTER//(LAPTOP)==1
};

class Device{
    char model[100];
    tip t;
    static float HOURS;
    int year;
//    void copy(const Device &other){
//        strcpy(this->model,other.model);
//        this->t=other.t;
//        this->year=other.year;
//    }
public:
    Device(char *model="", tip t=tip(0), int year=0){
        strcpy(this->model,model);
        this->t=t;
        this->year=year;
    }
//    Device(const Device &other){
//        copy(other);
//    }
//    Device &operator=(const Device &other){
//        if(this==&other){
//            return *this;
//        }
//        copy(other);
//        return *this;
//    }
    float hours(){
        float h=HOURS;
        if(year>2015){
            h+=2;
        }
        if(t==tip(1)){
            h+=2;
        }
        return h;
    }
    friend ostream &operator<<(ostream &out, Device &d){
        out<<d.model<<endl;
        if(d.t==tip(1)){
            out<<"Laptop ";
        } else{
            out<<"Mobilen ";
        }
        out<<d.hours()<<endl;
        return out;
    }
    static void setPocetniCasovi(float d){
        HOURS=d;
    }
    int getYear(){
        return year;
    }
};

float Device::HOURS=1;

class InvalidProductionDate{
public:
    void show(){
        cout<<"Невалидна година на производство"<<endl;
    }
};

class MobileServis{
private:
    char name[100];
    Device *devices;
    int n;
    void copy(const MobileServis &other){
        strcpy(this->name,other.name);
        this->n=other.n;
        this->devices=new Device[n];
        for(int i=0 ; i<n ; i++){
            devices[i]=other.devices[i];
        }
    }
public:
    MobileServis(char *name=""){
        strcpy(this->name,name);
        n=0;
    }
    MobileServis(const MobileServis &other){
        copy(other);
    }
    MobileServis &operator=(const MobileServis &other){
        if(this==&other){
            return *this;
        }
        delete []devices;
        copy(other);
        return *this;
    }
    ~MobileServis(){
        delete [] devices;
    }
    MobileServis &operator+=(Device &d){
        if(d.getYear()<2000 || d.getYear()>2019){
            throw InvalidProductionDate();
        }
        Device *tmp=new Device [n+1];
        for(int i=0 ; i<n ; i++){
            tmp[i]=devices[i];
        }
        delete [] devices;
        tmp[n++]=d;
        devices=tmp;
        return *this;
    }
    //friend ostream &operator<<(ostream &out, MobileServis &m){}
    void pecatiCasovi(){
        cout<<"Ime: "<<name<<endl;
        for(int i=0 ; i<n ; i++){
            cout<<devices[i];
        }
    }
};



int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch (InvalidProductionDate &e){
                e.show();
                --i;
                --n;
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch (InvalidProductionDate &e){
                e.show();
                --i;
                --n;
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch (InvalidProductionDate &e){
                e.show();
                --i;
                --n;
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            try{
                t+=tmp;
            }catch (InvalidProductionDate &e){
                e.show();
                --i;
                --n;
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch (InvalidProductionDate &e){
                e.show();
                --i;
                --n;
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

