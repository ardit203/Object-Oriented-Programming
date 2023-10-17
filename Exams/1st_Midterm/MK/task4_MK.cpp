#include<iostream>
#include<cstring>
using namespace std;

class Patnik{
private:
    char name[100];
    int rideClass;
    bool bicycle;
public:
    Patnik(char *name="", int rideClass=0, bool bicycle= false){
        strcpy(this->name, name);
        this->rideClass=rideClass;
        this->bicycle=bicycle;
    }
    friend ostream &operator<<(ostream &out, Patnik &p){
        out<<p.name<<endl<<p.rideClass<<endl<<p.bicycle<<endl;
        return out;
    }
    bool getBic(){
        return bicycle;
    }
    int getRideClass(){
        return rideClass;
    }
};

class Voz{
private:
    char dest[100];
    Patnik *patniks;
    int n;
    int allowedBic;
    int countA;
public:
    Voz(char *dest="", int allowedBic=0){
        strcpy(this->dest,dest);
        this->allowedBic=allowedBic;
        this->n=0;
        this->patniks=new Patnik[n];
        this->countA=0;
    }
    ~Voz(){
        delete [] patniks;
    }
    int numBic(){
        int count=0;
        for(int i=0 ; i<n ; i++){
            if(patniks[i].getBic()){
                count++;
            }
        }
        return count;
    }
    Voz &operator+=(Patnik &p){
        if(allowedBic==0){
            Patnik *tmp=new Patnik[n+1];

            for(int i=0 ; i<n ; i++){
                tmp[i]=patniks[i];
            }
            delete [] patniks;
            if(countA<allowedBic && p.getBic()){
                tmp[n++]=p;
                countA++;
            } else if(!p.getBic()){
                tmp[n++]=p;
            }
            patniks=tmp;
        } else{
            Patnik *tmp=new Patnik[n+1];
            for(int i=0 ; i<n ; i++){
                tmp[i]=patniks[i];
            }
            delete [] patniks;
                tmp[n++]=p;
                patniks=tmp;
        }

        return *this;
    }
    friend ostream &operator<<(ostream &out, Voz &v){
        out<<v.dest<<endl;
        for(int i=0 ; i<v.n ; i++){
            out<<v.patniks[i]<<endl;
        }
        return out;
    }
    void patniciNemaMesto(){
        int count=0, count1=0, count2=0;
        Patnik *p1=new Patnik[n];
        Patnik *p2=new Patnik[n];
        int k1=0,k2=0;
        for(int i=0 ; i<n ; i++){
            if(patniks[i].getRideClass()==1){
                p1[k1++]=patniks[i];
            }
            if(patniks[i].getRideClass()==2){
                p2[k2++]=patniks[i];
            }
        }
        for(int i=0 ; i<k1 ; i++){
            if(count==allowedBic && p1[i].getBic()){
                count1++;
            }
            if(count<allowedBic && p1[i].getBic()){
                count++;
            }
        }
        for(int i=0 ; i<k2 ; i++){
            if(count==allowedBic && p2[i].getBic()){
                count2++;
            }
            if(count<allowedBic && p2[i].getBic()){
                count++;
            }
        }
        cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<count1<<endl;
        cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<count2<<endl;
//        Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0↩
//        Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: 1
    }
};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
