#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

//место за вашиот код

class Oglas{
protected:
    char title[50]; //naslov
    char category[30]; //kategorija
    char description[100]; //opis
    float price; //cena
public:
    Oglas(char *title="", char *category="", char *description="", float price=0){
        strcpy(this->title,title);
        strcpy(this->category,category);
        strcpy(this->description,description);
        this->price=price;
    }
    bool operator>(Oglas &o) const{
        return price>o.price;
    }
    friend ostream &operator<<(ostream &out, Oglas &o){
        out<<o.title<<endl;
        out<<o.description<<endl;
        out<<o.price<<" evra"<<endl;
        return out;
    }
    float getPrice(){
        return price;
    }
    char *getCategory(){
        return category;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////

class NegativnaVrednost{
public:
    NegativnaVrednost(){}
    void show(){
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

class Oglasnik{
private:
    char name[20]; //naziv
    Oglas *ogls;
    int n;
public:
    Oglasnik(char *name=""){
        strcpy(this->name,name);
        this->n=0;
        this->ogls=new Oglas [this->n];
    }
    ~Oglasnik(){
        delete [] ogls;
    }
    Oglasnik &operator+=(Oglas &o){
        if(o.getPrice()<0){
            throw NegativnaVrednost();
        }
        Oglas *tmp=new Oglas [n+1];
        for(int i=0 ; i<n ; i++){
            tmp[i]=ogls[i];
        }
        delete [] ogls;
        tmp[n++]=o;
        ogls=tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Oglasnik &oglasnik) {
        out << oglasnik.name << endl;
        for(int i=0 ; i<oglasnik.n ; i++){
            out << oglasnik.ogls[i] << endl;
        }
        return out;
    }

    void oglasiOdKategorija(const char *c){
        for(int i=0 ; i<n ; i++){
            if(strcmp(ogls[i].getCategory(),c)==0){
                cout<<ogls[i]<<endl;
            }
        }
    }
    void najniskaCena(){
        Oglas min=ogls[0];
        for(int i=1 ; i<n ; i++){
            if(ogls[i].getPrice()<min.getPrice()){
                min=ogls[i];
            }
        }
        cout<<min<<endl;
    }
};


int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch (NegativnaVrednost &e){
                e.show();
                --i;
                --n;
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch (NegativnaVrednost &e){
                e.show();
                --i;
                --n;
            }
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch (NegativnaVrednost &e){
                e.show();
                --i;
                --n;
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch (NegativnaVrednost &e){
                e.show();
                --i;
                --n;
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch (NegativnaVrednost &e){
                e.show();
                --i;
                --n;
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}
