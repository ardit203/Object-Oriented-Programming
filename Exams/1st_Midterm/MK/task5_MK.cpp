#include <iostream>
#include <cstring>
using namespace std;

class Gitara{
private:
    char serialNumber[25];
    double price;
    int year;
    char type[40];
    void copy(const Gitara &other){
        strcpy(serialNumber,other.serialNumber);
        price=other.price;
        year=other.year;
        strcpy(type,other.type);
    }
public:
    Gitara(char *type="",char *serialNumber="", int year=0,double price=0){
        strcpy(this->serialNumber,serialNumber);
        this->price=price;
        this->year=year;
        strcpy(this->type,type);
    }
    Gitara(const Gitara &other){
        copy(other);
    }
    Gitara &operator=(const Gitara &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    bool daliIsti(Gitara &other){
        return strcmp(serialNumber,other.serialNumber)==0;
    }
    void pecati(){
        cout<<serialNumber<<" "<<type<<" "<<price<<endl;
    }
    double getPrice(){
        return price;
    }
    ~Gitara(){

    }

    char *getTip() {
        return type;
    }
    char *getSeriski(){
        return serialNumber;
    }

    int getGodina() {
        return year;
    }

    double getNabavna() {
        return price;
    }
};

class Magacin{
    char name[30];
    char location[60];
    Gitara *gitars;
    int numOfGitars;
    int yearOfOpening;
    void copy(const Magacin &other){
        strcpy(this->name,other.name);
        strcpy(this->location,other.location);
        this->yearOfOpening=other.yearOfOpening;
        numOfGitars=other.numOfGitars;
        this->gitars=new Gitara [other.numOfGitars];
        for(int i=0 ; i<numOfGitars ; i++){
            gitars[i]=other.gitars[i];
        }
    }
public:
    Magacin(char *name="", char *location="", int yearOfOpening=0){
        strcpy(this->name,name);
        strcpy(this->location,location);
        this->yearOfOpening=yearOfOpening;
        numOfGitars=0;
        this->gitars=new Gitara [numOfGitars];
        //TODO
    }
//    Magacin(char *name, char *location){
//        strcpy(this->name,name);
//        strcpy(this->location,location);
//        this->yearOfOpening=0;
//        numOfGitars=0;
//        this->gitars=new Gitara [numOfGitars];
//    }
    Magacin(const Magacin &other){
        copy(other);
    }
    Magacin &operator=(const Magacin &other){
        if(this==&other){
            return *this;
        }
        delete [] gitars;
        copy(other);
        return *this;
    }
    ~Magacin(){
        delete [] gitars;
    }
    double vrednost(){
        double value=0;
        for(int i=0 ; i<numOfGitars ; i++){
            value+=gitars[i].getPrice();
        }
        return value;
    }
    void dodadi(Gitara d){
        Gitara *tmp=new Gitara [numOfGitars+1];
        for(int i=0 ; i<numOfGitars ; i++){
            tmp[i]=gitars[i];
        }
        delete [] gitars;
        tmp[numOfGitars]=d;
        gitars=tmp;
        numOfGitars++;
    }
    void prodadi(Gitara p){
        Gitara *tmp=new Gitara [numOfGitars];
        int k=0;
        for(int i=0 ; i<numOfGitars ; i++){
            if(!gitars[i].daliIsti(p)){
                tmp[k++]=gitars[i];
            }
        }
        delete [] gitars;
        gitars=tmp;
        numOfGitars=k;
    }
    void pecati(bool t){
        cout<<name<<" "<<location<<endl;
        if(t== true){
            for(int i=0 ; i<numOfGitars ; i++){
                if(gitars[i].getGodina()>yearOfOpening){
                    gitars[i].pecati();
                }
            }
        } else{
            for(int i=0 ; i<numOfGitars ; i++){
                gitars[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}
