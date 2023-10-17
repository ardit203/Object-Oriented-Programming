#include <iostream>
#include <cstring>
using namespace std;


class Exception{
public:
    void show(){
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////

class Trud{
protected:
    char typePaper;
    int years;
    static int POINTS_C;
    static int POINTS_J;
public:
    Trud(char typePaper, int years){
        if(years<2003){
            throw Exception();
        }
        this->typePaper=typePaper;
        this->years=years;
    }
    Trud(){}
    friend istream &operator>>(istream &in, Trud &t){
        in>>t.typePaper>>t.years;
        return in;
    }
    int getYears(){
        return years;
    }
    char getPaper(){
        return typePaper;
    }
    static void setPointsC(int d){
        POINTS_C=d;
    }
    static void setPointsJ(int d){
        POINTS_J=d;
    }
    static int getC(){
        return POINTS_C;
    }
    static int getJ(){
        return POINTS_J;
    }

};
int Trud::POINTS_C=1;
int Trud::POINTS_J=3;

////////////////////////////////////////////////////////////////////////////////////////////////////////

class Student{
protected:
    char name[30];
    int index;
    int year_enrollment;
    int passed[50];
    int n;
    void copy(const Student &s){
        strcpy(this->name,s.name);
        this->index=s.index;
        this->year_enrollment=s.year_enrollment;
        this->n=s.n;
        for(int i=0 ; i<n ; i++){
            this->passed[i]=s.passed[i];
        }
    }
public:
    Student(char *name="", int index=0, int year_enrollment=0, int *passed= nullptr, int n=0){
        strcpy(this->name,name);
        this->index=index;
        this->year_enrollment=year_enrollment;
        this->n=n;
        for(int i=0 ; i<n ; i++){
            this->passed[i]=passed[i];
        }
    }
    virtual float rang(){
        float sum=0;
        for(int i=0 ; i<n ; i++){
            sum+=passed[i];
        }
        return sum/n;
    }
    friend ostream &operator<<(ostream &out, Student &s){
        out<<s.index<<" "<<s.name<<" "<<s.year_enrollment<<" "<<s.rang()<<endl;
        if(s.n==0){
            out<<"Ne postoi PhD student so indeks "<<s.index<<endl;
        }
        return out;
    }
    int getIndex(){
        return index;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class PhDStudent:public Student{
private:
    Trud *t;
    int n_t;
    void copy(const PhDStudent &other){
        Student::copy(other);
        this->n_t=other.n_t;
        this->t=new Trud [n_t];
        for(int i=0 ; i<n_t ; i++){
            this->t[i]=other.t[i];
        }
    }
public:
    PhDStudent(char *name="", int index=0, int year_enrollment=0, int *passed= nullptr, int n=0,
               Trud *t= nullptr, int n_t=0): Student(name,index,year_enrollment,passed,n){
        this->n_t=n_t;
        this->t=new Trud [n_t];
        for(int i=0 ; i<n_t ; i++){
            this->t[i]=t[i];
        }
    }
    ~PhDStudent(){
        delete [] t;
    }
    float rang() override {
        float p=Student::rang();
        for(int i=0 ; i<n_t ; i++){
            char type=t[i].getPaper();
            if(type=='c' || type=='C'){
                p+=t[i].getC();
            } else if(type=='j' || type=='J'){
                p+=t[i].getJ();
            }
        }
        return p;
    }
    PhDStudent &operator+=(Trud &trud){
        if(trud.getYears()<year_enrollment){
            throw Exception();
        }
        Trud *tmp=new Trud[n_t+1];
        for(int i=0 ; i<n_t ; i++){
            tmp[i]=t[i];
        }
        delete [] t;
        tmp[n_t++]=trud;
        t=tmp;
        return *this;
    }
    int getIndex(){
        return index;
    }
};



int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            try {
                Trud t(tip, god_tr);
                trud[j] = t;
            }catch(Exception &e) {
                e.show();
                --n_tr;
                --j;
            }
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    try {
                        Trud t(tip, god_tr);
                        trud[j] = t;
                    }catch(Exception &e) {
                        e.show();
                        --n_tr;
                        --j;
                    }
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        for(int i=0 ; i<m ; i++){
            PhDStudent *phd=dynamic_cast<PhDStudent *>(niza[i]);
            if(phd && phd->getIndex()==indeks){

                try {
                    *phd+=t;
                    niza[i]=phd;
                }catch(Exception &e) {
                    e.show();
                }
            }else if(niza[i]->getIndex()==indeks){
                cout<<"Ne postoi PhD student so indeks "<<niza[i]->getIndex()<<endl;
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    try {
                        Trud t(tip, god_tr);
                        trud[j] = t;
                    }catch(Exception &e) {
                        e.show();
                        --n_tr;
                        --j;
                    }
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        for(int i=0 ; i<m ; i++){
            PhDStudent *phd=dynamic_cast<PhDStudent *>(niza[i]);

            if(phd && phd->getIndex()==indeks){
                try {
                    *phd+=t;
                    niza[i]=phd;
                }catch(Exception &e) {
                    e.show();
                }


            }else if(niza[i]->getIndex()==indeks){
                cout<<"Ne postoi PhD student so indeks "<<niza[i]->getIndex()<<endl;
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            try {
                Trud t(tip, god_tr);
                trud[j] = t;
            }catch(Exception &e) {
                e.show();
                --n_tr;
                --j;
            }

        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    try {
                        Trud t(tip, god_tr);
                        trud[j] = t;
                    }catch(Exception &e) {
                        e.show();
                        --n_tr;
                        --j;
                    }
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        for(int i=0 ; i<m ; i++){
            PhDStudent *phd=dynamic_cast<PhDStudent *>(niza[i]);

            if(phd && phd->getIndex()==indeks){
                try {
                    *phd+=t;
                    niza[i]=phd;
                }catch(Exception &e) {
                    e.show();
                }

            }else if(niza[i]->getIndex()==indeks){
                cout<<"Ne postoi PhD student so indeks "<<niza[i]->getIndex()<<endl;
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    try {
                        Trud t(tip, god_tr);
                        trud[j] = t;
                    }catch(Exception &e) {
                        e.show();
                        --n_tr;
                        --j;
                    }
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        Trud::setPointsC(conf);
        Trud::setPointsJ(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}