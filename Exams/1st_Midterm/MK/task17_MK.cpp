#include <iostream>
#include <cstring>
using namespace std;

enum Tip{
    LINUX,UNIX,WINDOWS
};

class OperativenSistem{
private:
    char *name;
    float version;
    Tip tip;
    float size;
    void copy(const OperativenSistem &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->version=other.version;
        this->tip=other.tip;
        this->size=other.size;
    }
public:
    OperativenSistem(char *name="",float version=0, Tip tip=Tip(0),float size=0){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->version=version;
        this->tip=tip;
        this->size=size;
    }
    OperativenSistem(const OperativenSistem &other){
        copy(other);
    }
    OperativenSistem &operator=(const OperativenSistem &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        copy(other);
        return *this;
    }
    void print(){
        cout<<"Ime: "<<name<<" Verzija: "<<version<<" Tip: "<<tip<<" Golemina:"<<size<<"GB"<<endl;
    }
    bool ednakviSe(const OperativenSistem &os){
        return strcmp(name,os.name)==0 && version==os.version && tip==os.tip && size==os.size;
    }
    int sporediVerzija(const OperativenSistem &os){
        if(version==os.version){
            return 0;
        } else if(os.version>version){
            return -1;
        } else{
            return 1;
        }
    }
    bool istaFamily(const OperativenSistem &sporedba){
        return strcmp(name,sporedba.name)==0 && tip==sporedba.tip;
    }
    ~OperativenSistem(){
        delete [] name;
    }
};

class Repozitorium{
    char name[20];
    OperativenSistem *os;
    int numOfOs;
public:
    Repozitorium(const char *name=""){
        strcpy(this->name,name);
        this->numOfOs=0;
        this->os=new OperativenSistem [numOfOs];
    }
    ~Repozitorium(){
        delete [] os;
    }

    void dodadi(OperativenSistem &sistem) {
        int flag=1;
        for(int i=0 ; i<numOfOs ; i++){
            if(os[i].istaFamily(sistem) && os[i].sporediVerzija(sistem)==-1){
                flag=0;
                os[i]=sistem;
                break;
            }
        }
        if(flag){
            OperativenSistem *tmp=new OperativenSistem [numOfOs+1];
            for(int i=0 ; i<numOfOs ; i++){
                tmp[i]=os[i];
            }
            delete [] os;
            tmp[numOfOs++]=sistem;
            os=tmp;
        }
    }

    void pecatiOperativniSistemi() {
        cout<<"Repozitorium: "<<name<<endl;
        for(int i=0 ; i<numOfOs ; i++){
            os[i].print();
        }
    }

    void izbrishi(OperativenSistem &sistem) {
        OperativenSistem *tmp=new OperativenSistem [numOfOs];
        int k=0;
        for(int i=0 ; i<numOfOs ; i++){
            if(!os[i].ednakviSe(sistem)){
                tmp[k++]=os[i];
            }
        }
        delete[] os;
        numOfOs=k;
        os=tmp;
    }
};


int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}