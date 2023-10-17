#include<iostream>
#include<string.h>
using namespace std;

//ова е место за вашиот код

class Zichara{
    char *place;
    int price;
    void copy(const Zichara &other){
        this->place=new char [strlen(other.place)+1];
        strcpy(this->place,other.place);
        this->price=other.price;
    }
public:
    Zichara(char *place="", int price=0){
        this->place=new char [strlen(place)+1];
        strcpy(this->place,place);
        this->price=price;
    }
    Zichara(const Zichara &other){
        copy(other);
    }
    Zichara &operator+=(const Zichara &other){
        if(this==&other){
            return *this;
        }
        delete [] place;
        copy(other);
        return *this;
    }
    ~Zichara(){
        delete [] place;
    }
    int getPrice(){
        return price;
    }
};

class PlaninarskiDom{
private:
    char name[15];
    int price[2];
    char klasa;
    bool cable;
    Zichara *zichara;
    void copy(const PlaninarskiDom &other){
        strcpy(this->name,other.name);
        for(int i=0 ; i<2 ; i++){
            this->price[i]= other.price[i];
        }
        this->klasa=other.klasa;
        this->cable= other.klasa;
        this->zichara= other.zichara;
    }
public:
    PlaninarskiDom(char *name, int *price, char klasa){
        strcpy(this->name,name);
        for(int i=0 ; i<2 ; i++){
            this->price[i]= price[i];
        }
        this->klasa=klasa;
        this->cable= false;
        this->zichara= nullptr;
    }
    PlaninarskiDom(){}
    PlaninarskiDom (const PlaninarskiDom &other){
        copy(other);
    }
    PlaninarskiDom &operator=(const PlaninarskiDom &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    void setZichara(Zichara &r){
        this->zichara=&r;
        this->cable= true;
    }
    PlaninarskiDom &operator--(){
        if(klasa!='F'){
            klasa+=1;
        }
        return *this;
    }
    bool operator<=(char p)const{
        return klasa>=p;
    }
    friend ostream &operator<<(ostream &out, PlaninarskiDom &p){
        out<<p.name<<" klasa:"<<p.klasa;
        if(p.zichara!= nullptr){
            out<<" so Zichara"<<endl;
        } else{
            out<<endl;
        }
        return out;
    }
    void presmetajDnevenPrestoj(int day, int month, int *prc){
        if(day<0 || day>31 || month<0 || month>12){
            throw 1;
        }

        if(zichara!= nullptr){
            if(month>=4 && month<9){
                *prc=zichara->getPrice()+price[0];
            } else{
                *prc=zichara->getPrice()+price[1];
            }
        } else{
            if(month>=4 && month<9){
                *prc=price[0];
            } else{
                *prc=price[1];
            }
        }
    }
};


int main(){

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,&cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}
