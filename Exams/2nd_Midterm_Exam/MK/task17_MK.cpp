#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde

class FudbalskaEkipa{
protected:
    char coach[100];
    int goals[10];
public:
    FudbalskaEkipa(char *coach, int *goals){
        strcpy(this->coach, coach);
        for(int i=0 ; i<10 ; i++){
            this->goals[i]=goals[i];
        }
    }
    void transform(){
        for(int i=0 ; i<10 ; i++){
            goals[i]=goals[i+1];
        }
    }
    FudbalskaEkipa(){}
    virtual int succes()=0;
    friend ostream &operator<<(ostream &out, FudbalskaEkipa &f);
    FudbalskaEkipa &operator+=(int d){
        transform();
        goals[9]=d;
        return *this;
    }
    bool operator>(FudbalskaEkipa &f){
        return succes()>f.succes();
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////

class Klub:public FudbalskaEkipa{
    char name[100];
    int titles;
public:
    Klub(char *coach, int *goals, char *name, int titles):FudbalskaEkipa(coach,goals){
        strcpy(this->name,name);
        this->titles=titles;
    }
    int succes(){
        int sum=0;
        for(int i=0 ; i<10 ; i++){
            sum+=goals[i];
        }
        return sum*3+titles*1000;
    }
    friend ostream &operator<<(ostream &out, Klub &r){
        out<<r.name<<endl;
        out<<r.coach<<endl;
        out<<r.succes()<<endl;
        return out;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////

class Reprezentacija:public FudbalskaEkipa{
    char name[100];
    int appearances;
public:
    Reprezentacija(char *coach, int *goals, char *name, int appearances):FudbalskaEkipa(coach,goals){
        strcpy(this->name,name);
        this->appearances=appearances;
    }
    int succes(){
        int sum=0;
        for(int i=0 ; i<10 ; i++){
            sum+=goals[i];
        }
        return sum*3+appearances*50;
    }
    friend ostream &operator<<(ostream &out, Reprezentacija &r){
        out<<r.name<<endl;
        out<<r.coach<<endl;
        out<<r.succes()<<endl;
        return out;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

ostream &operator<<(ostream &out, FudbalskaEkipa &f){
    Klub *k=dynamic_cast<Klub *>(&f);
    Reprezentacija *r=dynamic_cast<Reprezentacija *>(&f);
    if(k){
        out<<*k;
    } else{
        out<<*r;
    }
    return out;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void najdobarTrener(FudbalskaEkipa **f, int n){
    FudbalskaEkipa *best=f[0];
    for(int i=1 ; i<n ; i++){
        if(*f[i]>*best){
            best=f[i];
        }
    }
    cout<<*best;
}


int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}