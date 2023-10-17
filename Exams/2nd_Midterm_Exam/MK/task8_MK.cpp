#include<iostream>
#include <cstring>
using namespace std;

//your code

class Koncert{
protected:
    char name[100];
    char location[100];
    static float DISCOUNT;
    float price;
    void copy(const Koncert &o){
        strcpy(this->name,o.name);
        strcpy(this->location,o.location);
        this->price=o.price;
    }
public:
    Koncert(char *name="", char *location="", float price=0){
        strcpy(this->name,name);
        strcpy(this->location,location);
        this->price=price;
    }
    Koncert(const Koncert &other){
        copy(other);
    }
    Koncert &operator=(const Koncert &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    static void setSezonskiPopust(float d){
        DISCOUNT=d;
    }
    static float getSezonskiPopust(){
        return DISCOUNT;
    }
    virtual float cena(){
        float p=price*(1-DISCOUNT);
        return p;
    }
    char *getNaziv(){
        return name;
    }
};

float Koncert::DISCOUNT=0.2;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ElektronskiKoncert:public Koncert{
private:
    char *djName;
    float duration;
    bool isDay;
    void copy(const ElektronskiKoncert &o){
        Koncert::copy(o);
        this->djName=new char [strlen(o.djName)+1];
        strcpy(this->djName,o.djName);
        this->duration=o.duration;
        this->isDay=o.isDay;
    }
public:
    ElektronskiKoncert(char *name="", char *location="", float price=0,
                       char *djName="", float duration=0,bool isDay= false): Koncert(name,location,price){
        this->djName=new char [strlen(djName)+1];
        strcpy(this->djName,djName);
        this->duration=duration;
        this->isDay=isDay;
    }
    ElektronskiKoncert(const ElektronskiKoncert &other){
        copy(other);
    }
    ElektronskiKoncert &operator=(const ElektronskiKoncert &other){
        if(this==&other){
            return *this;
        }
        delete [] djName;
        copy(other);
        return *this;
    }
    ~ElektronskiKoncert(){
        delete [] djName;
    }

    float cena() override {
        float p=Koncert::cena();
        if(duration>7){
            p+=360;
        }else if(duration>5){
            p+=150;
        }
        if(isDay){
            p-=50;
        } else{
            p+=100;
        }
        return p;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void najskapKoncert(Koncert ** koncerti, int n){

    Koncert *max=koncerti[0];
    int count=0;
    for(int i=0 ; i<n ; i++){
        ElektronskiKoncert *eK=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if(eK!= nullptr){
            count++;
        }
        if(koncerti[i]->cena()>max->cena()){
            max=koncerti[i];
        }
    }
    //Najskap koncert: SeaDance 7230
    //Elektronski koncerti: 3 od vkupno 5
    cout<<"Najskap koncert: "<<max->getNaziv()<<" "<<max->cena()<<endl;
    cout<<"Elektronski koncerti: "<<count<<" od vkupno "<<n<<endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
    if(elektronski){
        for(int i=0 ; i<n ; i++){
            ElektronskiKoncert *eK=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
            if(eK!= nullptr && strcmp(eK->getNaziv(),naziv)==0){
                cout<<eK->getNaziv()<<" "<<eK->cena()<<endl;
                return true;
            }
        }
    } else{
        for(int i=0 ; i<n ; i++){
            if(strcmp(koncerti[i]->getNaziv(),naziv)==0){
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                return true;
            }
        }
    }
    return false;
}

//int main(){
//    ElektronskiKoncert e("SeaDance","Budva",9100,"Tiesto",5,true);
//    cout<<e.cena();
//    return 0;
//}


int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
