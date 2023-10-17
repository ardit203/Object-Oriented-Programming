#include <iostream>
#include <cstring>
using namespace std;

enum tip{
    pop, rap, rok
};

class Pesna{
private:
    char *name;
    int minutes;
    tip Tip;
    void copy(const Pesna &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->minutes=other.minutes;
        this->Tip=other.Tip;
    }
public:
    Pesna(char *name="", int minutes=0, tip Tip=tip(0)){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->minutes=minutes;
        this->Tip=Tip;
    }
    Pesna(const Pesna &other){
        copy(other);
    }
    Pesna &operator=(const Pesna &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        copy(other);
        return *this;
    }
    void pecati(){
        cout<<'"'<<name<<'"'<<"-"<<minutes<<"min"<<endl;
    }
    int getMinutes(){
        return minutes;
    }
    int getTip(){
        return Tip;
    }
    ~Pesna(){
        delete [ ]name;
    }
};

class CD{
    Pesna pesni[20];
    int brNaPesni;
    int maxDuration;
public:
    CD(int maxDuration){
        this->maxDuration=maxDuration;
        brNaPesni=0;
    }

    void dodadiPesna(Pesna &pesna) {
        if(brNaPesni==10){
            return;
        }
        int sum=0;
        for(int i=0 ; i<brNaPesni ; i++){
            sum+=pesni[i].getMinutes();
        }
        if(sum+pesna.getMinutes()<maxDuration){
            pesni[brNaPesni]=pesna;
            brNaPesni++;
        }
    }

    int getBroj() {
        return brNaPesni;
    }

    Pesna getPesna(int i) {
        return pesni[i];
    }

    void pecatiPesniPoTip(tip tip1) {
        for(int i=0 ; i<brNaPesni ; i++){
            if(pesni[i].getTip()==tip1){
                pesni[i].pecati();
            }
        }
    }
};


int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}