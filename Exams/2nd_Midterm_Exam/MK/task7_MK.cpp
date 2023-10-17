#include<iostream>
#include<string.h>
using namespace std;

class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(char* smetka="",int pin=0){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    // дополниете ја класата
    virtual int tezinaProbivanje(){
        return countOfDigits();
    }
    friend ostream &operator<<(ostream &out, Karticka &s){
        out<<s.smetka<<": "<<s.tezinaProbivanje()<<endl;
        return out;
    }
    bool getDopolnitelenPin(){
        return povekjePin;
    }
    char *getSmetka(){
        return smetka;
    }
    int countOfDigits(){
        int tmp=pin;
        int count=0;
        while (tmp){
            count++;
            tmp/=10;
        }
        return count;
    }
};

//вметнете го кодот за SpecijalnaKarticka

class OutOfBoundException{
public:
    void show(){
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }
};

class SpecijalnaKarticka:public Karticka{
    int *addPinCodes;
    int n;
    static const int P;
    void copy(const SpecijalnaKarticka &other){
        strcpy(this->smetka,other.smetka);
        this->pin=other.pin;
        this->povekjePin=true;
        this->n=other.n;
        for(int i=0 ; i<n ; i++){
            this->addPinCodes[i]=other.addPinCodes[i];
        }
    }
public:
    SpecijalnaKarticka(char* smetka,int pin): Karticka(smetka,pin){
        this->povekjePin= true;
        this->n=0;
        this->addPinCodes=new int [n];
    }
    SpecijalnaKarticka(const SpecijalnaKarticka &other){
        copy(other);
    }
    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &other){
        if(this==&other){
            return *this;
        }
        delete [] addPinCodes;
        copy(other);
        return *this;
    }
    ~SpecijalnaKarticka(){
        delete [] addPinCodes;
    }
    int tezinaProbivanje(){
        return Karticka::tezinaProbivanje()+n;
    }
    friend ostream &operator<<(ostream &out, SpecijalnaKarticka &s){
        out<<s.smetka<<": "<<s.tezinaProbivanje()<<endl;
        return out;
    }
    SpecijalnaKarticka &operator+=(int pin){
        if(n==P){
            throw OutOfBoundException();
        }
        int *tmp=new int[n+1];
        for(int i=0 ; i<n ; i++){
            tmp[i]=addPinCodes[i];
        }
        delete [] addPinCodes;
        tmp[n++]=pin;
        addPinCodes=tmp;
        return *this;
    }
};

const int SpecijalnaKarticka::P=4;

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    //да се дополни класата
    static void setLIMIT(int d){
        LIMIT=d;
    }
    void pecatiKarticki(){
        //Vo bankata XXXXX moze da se probijat kartickite:
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for(int i=0 ; i<broj ; i++){
            if(karticki[i]->tezinaProbivanje()>LIMIT){
                continue;
            }
            SpecijalnaKarticka *s=dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
            if(s){
                cout<<*s;
            } else{
                cout<<*karticki[i];
            }
        }
    }
    void dodadiDopolnitelenPin(char * smetka, int novPin){
        for(int i=0 ; i<broj ; i++){
            SpecijalnaKarticka *s=dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
            if(s && strcmp(smetka,s->getSmetka())==0){
                try {
                    *s+=novPin;
                }catch (OutOfBoundException &e){
                    e.show();
                }
            }
        }
    }
};

int Banka::LIMIT=7;



int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        komercijalna.dodadiDopolnitelenPin(smetka,pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
