#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde

class Ucesnik{
    char *name;
    bool gender;
    int age;
    void copy(const Ucesnik &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->gender=other.gender;
        this->age=other.age;
    }
public:
    Ucesnik(char *name="", bool gender= false, int age=0){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->gender=gender;
        this->age=age;
    }
    Ucesnik(const Ucesnik &other){
        copy(other);
    }
    Ucesnik &operator=(const Ucesnik &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        copy(other);
        return *this;
    }
    ~Ucesnik(){
        delete [] name;
    }
    bool operator>(Ucesnik &u)const{
        return this->age>u.age;
    }
    friend ostream &operator<<(ostream &out, Ucesnik &u){
        out<<u.name<<endl;
        if(u.gender){
            out<<"mashki"<<endl;
        } else{
            out<<"zhenski"<<endl;
        }
        out<<u.age<<endl;
        return out;
    }
    int getAge(){
        return age;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

class Maraton{
    char location[100];
    Ucesnik *ucs;
    int n;
public:
    Maraton(char *location=""){
        strcpy(this->location,location);
        this->n=0;
        this->ucs=new Ucesnik[n];
    }
    ~Maraton(){
        delete [] ucs;
    }
    Maraton &operator+=(Ucesnik &u){
        Ucesnik *tmp=new Ucesnik [n+1];
        for(int i=0 ; i<n ; i++){
            tmp[i]=ucs[i];
        }
        delete [] ucs;
        tmp[n++]=u;
        ucs=tmp;
        return *this;
    }
    float prosecnoVozrast(){
        double sum=0;
        for(int i=0 ; i<n ; i++){
            sum+=ucs[i].getAge();
        }
        return sum/n;
    }
    void pecatiPomladi(Ucesnik &u){
        for(int i=0 ; i<n ; i++){
            if(u>ucs[i]){
                cout<<ucs[i];
            }
        }
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}