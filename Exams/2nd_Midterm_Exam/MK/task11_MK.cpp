#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код

class Delo{
private:
    char name[50]; //ime
    int year; //godina
    char originCounty[50]; //zemja
public:
    Delo(char *name="", int year=0, char *originCountry=""){
        strcpy(this->name,name);
        strcpy(this->originCounty,originCountry);
        this->year=year;
    }
    bool operator==(Delo &d){
        return strcmp(name,d.name)==0;
    }
    char *getIme(){
        return name;
    }
    int getYear(){
        return year;
    }
    char *getOrigin(){
        return originCounty;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class Pretstava{
protected:
    Delo delo;
    int numTickets;
    char date[15];
public:
    Pretstava(Delo &delo, int numTickets, char *date){
        this->delo=delo;
        this->numTickets=numTickets;
        strcpy(this->date,date);
    }
    Pretstava(){}
    virtual int cena(){
        int M,N=80;
        if(delo.getYear()>=1800 && delo.getYear()<1900){
            M=75;
        } else if(delo.getYear()<1800){
            M=100;
        } else{
            M=50;
        }
        if(strcmp(delo.getOrigin(),"Italija")==0){
            N=100;
        } else if(strcmp(delo.getOrigin(),"Rusija")==0){
            N=150;
        }
        int cena=M+N;
        return cena;
    }
    Delo getDelo(){
        return delo;
    }
    int getMonth(){
        int month=(date[3]-'0')*10+(date[4]-'0');
        return month;
    }
    int getNumT(){
        return numTickets;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class Balet:public Pretstava{
private:
    static int BALET_CENA;
public:
    Balet(Delo &delo, int numTickets, char *date) : Pretstava(delo, numTickets, date) {}
    static void setCenaBalet(int d){
        BALET_CENA=d;
    }

    int cena() override {
        return Pretstava::cena()+BALET_CENA;
    }
};

int Balet::BALET_CENA=150;

////////////////////////////////////////////////////////////////////////////////////////////////////

class Opera:public Pretstava{
public:
    Opera(Delo &delo, int numTickets, char *date) : Pretstava(delo, numTickets, date) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////

int prihod(Pretstava **p, int n){
    int sum=0;
    for(int i=0; i<n ; i++){
        sum+=p[i]->cena()*p[i]->getNumT();
    }
    return sum;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

int brojPretstaviNaDelo(Pretstava **p, int n, Delo &d){
    int count=0;
    for(int i=0 ; i<n ; i++){
        if(p[i]->getDelo()==d){
            count++;
        }
    }
    return count;
}


//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
