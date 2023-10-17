#include <iostream>
#include <cstring>
using namespace std;

class Pica{
private:
    char name[15];
    int price;
    char *ingredients;
    int price_reduction;
    void copy(const Pica &other){
        strcpy(this->name,other.name);
        this->price=other.price;
        this->ingredients=new char [strlen(other.ingredients)+1];
        strcpy(this->ingredients,other.ingredients);
        this->price_reduction=other.price_reduction;
    }
public:
    Pica(char *name="",int price=0, char *ingredients="",int price_reduction=0 ){
        strcpy(this->name,name);
        this->price=price;
        this->ingredients=new char [strlen(ingredients)+1];
        strcpy(this->ingredients,ingredients);
        this->price_reduction=price_reduction;
    }
    Pica(const Pica &other){
        copy(other);
    }
    Pica &operator=(const Pica &other){
        if(this==&other){
            return *this;
        }
        delete [] ingredients;
        copy(other);
        return *this;
    }
    void pecati(){
        cout<<name<<" - "<<ingredients<<", "<<price;
    }
    bool istiSe(Pica p){
        return strcmp(this->ingredients,p.ingredients)==0;
    }
    int getPriceReduction(){
        return price_reduction;
    }
    int getPrice(){
        return price;
    }
    ~Pica(){
        delete [] ingredients;
    }
};

class Picerija{
private:
    char name[15];
    Pica *picas;
    int numOfPicas;
    void copy(const Picerija &other){
        strcpy(name,other.name);
        numOfPicas=other.numOfPicas;
        picas=new Pica [numOfPicas];
        for(int i=0 ; i<numOfPicas ; i++){
            this->picas[i]=other.picas[i];
        }
    }
public:
    Picerija(char *name){
        strcpy(this->name,name);
        numOfPicas=0;
        this->picas=new Pica[numOfPicas];
    }
    Picerija(const Picerija &other){
        copy(other);
    }
    Picerija &operator=(const Picerija &other){
        if(this==&other){
            return *this;
        }
        delete [] picas;
        copy(other);
        return *this;
    }
    Picerija &operator+=(const Pica &p){
        int flag=1;
        for(int i=0 ; i<numOfPicas ; i++){
            if(picas[i].istiSe(p)){
                flag=0;
                break;
            }
        }
        if(flag){
            Pica *tmp=new Pica[numOfPicas+1];
            for(int i=0 ; i<numOfPicas ; i++){
                tmp[i]=picas[i];
            }
            delete [] picas;
            tmp[numOfPicas]=p;
            picas=tmp;
            numOfPicas++;
        }
    }
//    Picerija& operator+=(Pica &p){
//        bool imaIsta = false;
//        for (int i = 0; i < numOfPicas; i++)
//            if (picas[i].istiSe(p))
//                imaIsta = true;
//        if (!imaIsta){
//            Pica* tmp = new Pica[numOfPicas + 1];
//            for (int i = 0; i < numOfPicas; i++)
//                tmp[i] = picas[i];
//            tmp[numOfPicas++] = p;
//            delete[] picas;
//            picas = tmp;
//        }
//        return *this;
//    }

    void setIme(char *str) {
        strcpy(name,str);
    }

    const char *getIme() {
        return name;
    }

    void piciNaPromocija() {
        for(int i=0 ; i<numOfPicas ; i++){
            if(picas[i].getPriceReduction()>0){
                picas[i].pecati();
                float percentage=1-(picas[i].getPriceReduction()/100.0);
                cout<<" "<<picas[i].getPrice()*percentage<<endl;
            }
        }
    }
    ~Picerija(){
        delete [] picas;
    }
};

int main(){
    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1+=p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2+=p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();
    return 0;
}