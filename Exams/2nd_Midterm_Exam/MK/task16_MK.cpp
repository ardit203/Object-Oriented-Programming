#include<iostream>
#include<cstring>
using namespace std;

// вашиот код треба да биде тука

//class AvtomobilTransport;
//class KombeTransport;

class Transport{
protected:
    char dest[20];
    int price;
    int distance;
    void copy(const Transport &t){
        strcpy(this->dest,t.dest);
        this->price=t.price;
        this->distance=t.distance;
    }
public:
    Transport(char *dest="", int price=0, int distance=0){
        strcpy(this->dest,dest);
        this->price=price;
        this->distance=distance;
    }
    Transport &operator=(const Transport &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    virtual float cenaTransport()=0;
    bool operator<(Transport &t){
        return dest<t.dest;
    }
    char *getDest(){
        return dest;
    }
    int getD(){
        return distance;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class AvtomobilTransport:public Transport{
private:
    bool paid;
public:
    AvtomobilTransport(char *dest="", int price=0, int distance=0, bool paid= false)
    : Transport(dest,price,distance){
        this->paid=paid;
    }

    float cenaTransport() override {
        float p=price;
        if(paid){
            p*=1.2;
        }
        return p;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class KombeTransport:public Transport{
private:
    int people;
public:
    KombeTransport(char *dest="", int price=0, int distance=0, int people=0)
    : Transport(dest,price,distance){
        this->people=people;
    }
    float cenaTransport() override {
        return price-people*200;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

void sort(Transport **t, int k){
    for(int i=0 ; i<k ; i++){
        for(int j=0 ; j<k-1-i ; j++){
            if(t[j]->getD()>t[j+1]->getD()){
                Transport *tmp=t[j];
                t[j]=t[j+1];
                t[j+1]=tmp;
            }
        }
    }
}

void pecatiPoloshiPonudi(Transport **t, int n, AvtomobilTransport &a){
    Transport **pTransport=new Transport * [n];
    int k=0;
    for(int i=0 ; i<n ; i++){
        if(a.cenaTransport()<t[i]->cenaTransport()){
            pTransport[k++]=t[i];
        }
    }
    sort(pTransport,k);
    for(int i=0 ; i<k ; i++){
        cout<<pTransport[i]->getDest()<<" "<<pTransport[i]->getD()<<" "<<pTransport[i]->cenaTransport()<<endl;
    }
    //cout<<t[i]->getDest()<<" "<<t[i]->cenaTransport()<<" "<<t[i]->getD()<<endl;
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
