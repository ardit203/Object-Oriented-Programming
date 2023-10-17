#include<iostream>
#include<cstring>
using namespace std;

class StudentKurs{
protected:
    char ime[30];
    int ocn;
    bool daliUsno;
    static const int MINOCENKA;
    static int MAX;
public:
    StudentKurs(char* ime,int finalenIspit){
        strcpy(this->ime,ime);
        this->ocn=finalenIspit;
        this->daliUsno=false;
    }
    //дополни ја класата
    bool getDaliUsno(){
        return daliUsno;
    }
    friend ostream &operator<<(ostream &out, StudentKurs &s){
        //Ime --- ocenka
        out<<s.ime<<" --- "<<s.ocenka()<<endl;
        return out;
    }
    virtual int ocenka(){
        return ocn;
    }
    static void setMAX(int d){
        MAX=d;
    }
    static int getMIN(){
        return MINOCENKA;
    }
    char *getIme(){
        return ime;
    }
};

const int StudentKurs::MINOCENKA=6;
int StudentKurs::MAX=10;

//////////////////////////////////////////////////////////////////////////////////////////////////////////


//вметни го кодот за StudentKursUsno

class StudentKursUsno:public StudentKurs{
private:
    char *usno;
public:
    StudentKursUsno(char* ime,int finalenIspit): StudentKurs(ime,finalenIspit){
        this->daliUsno=true;
        this->usno=new char [0];
    }
    ~StudentKursUsno(){
        delete [] usno;
    }
    friend ostream &operator<<(ostream &out, StudentKursUsno &s){
        out<<s.ime<<" --- "<<s.ocenka()<<endl;
        return out;
    }
    void transform(){
        int count=0;
        for(int i=0 ; i< strlen(usno) ; i++){
            if(!isalpha(usno[i])){
                count++;
            }
        }
        if(count==0){
            return;
        }
        char *tmp=new char [strlen(usno)+1-count];
        int k=0;
        for(int i=0 ; i< strlen(usno) ; i++){
            if(isalpha(usno[i])){
                tmp[k++]=usno[i];
            }
        }
        delete [] usno;
        tmp[k]='\0';
        usno=tmp;
    }
    int ocenka() override {
        transform();
        if(strcmp(usno,"odlicen")==0){
            if(ocn+2>MAX){
                return MAX;
            } else{
                return ocn+2;
            }
        } else if(strcmp(usno,"dobro")==0){
            if(ocn+1>MAX){
                return MAX;
            } else{
                return ocn+1;
            }
        }
        return ocn-1;
    }
    StudentKursUsno &operator+=(char *string1){
        this->usno=new char [strlen(string1)+1];
        strcpy(this->usno,string1);
        return *this;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

class Invalid{
public:
    void show(){
        cout<<"Greshna opisna ocenka"<<endl;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////


class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }

    //дополни ја класата
    void pecatiStudenti(){
        cout<<"Kursot OOP go polozile:"<<endl;
        for(int i=0 ; i<broj ; i++){
            if(studenti[i]->ocenka()>=StudentKurs::getMIN()){
                StudentKursUsno *sku=dynamic_cast<StudentKursUsno *>(studenti[i]);
                if(sku){
                    cout<<*sku;
                } else{
                    cout<<*studenti[i];
                }
            }
        }
    }
    void postaviOpisnaOcenka(char * ime, char* opisnaOcenka){
        int flag=0;
        for(int i=0 ; i< strlen(opisnaOcenka) ; i++){
            if(!isalpha(opisnaOcenka[i])){
                flag=1;
            }
        }
        for(int i=0 ; i<broj ; i++){
            StudentKursUsno *sku=dynamic_cast<StudentKursUsno *>(studenti[i]);
            if(sku && strcmp(ime,sku->getIme())==0){
                *sku+=opisnaOcenka;
            }
        }
        if(flag){
            throw Invalid();
        }
    }
};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        try{
            programiranje.postaviOpisnaOcenka(ime,opisna);
        }catch (Invalid &e){
            e.show();
        }

    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
