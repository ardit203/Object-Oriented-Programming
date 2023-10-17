#include <iostream>
#include <cstring>
using namespace std;


// vashiot kod ovde

class Pair{
    char *key;
    int value;
    void copy(const Pair &other){
        this->key=new char [strlen(other.key)+1];
        strcpy(this->key,other.key);
        this->value=other.value;
    }
public:
    Pair(char *key="", int value=0){
        this->key=new char [strlen(key)+1];
        strcpy(this->key,key);
        this->value=value;
    }
    Pair(const Pair &other){
        copy(other);
    }
    Pair &operator=(const Pair &other){
        if(this==&other){
            return *this;
        }
        delete [] key;
        copy(other);
        return *this;
    }
    ~Pair(){
        delete [] key;
    }
    friend ostream &operator<<(ostream &out, Pair p){
        out<<"('"<<p.key<<"'"<<", "<<p.value<<")"<<endl;
        return out;
    }
    int getValue(){
        return value;
    }
    Pair &operator++(){
        ++value;
        return *this;
    }
    Pair operator++(int){
        Pair Copy(*this);
        ++value;
        return Copy;
    }
    Pair operator +(Pair &p1){
        int add=this->value+p1.value;
        int l1= strlen(this->key);
        int l2= strlen(p1.key);
        if(l1>=l2){
            Pair P(this->key,add);
            return P;
        } else{
            Pair P(p1.key,add);
            return P;
        }
    }
    bool operator==(const Pair &p){
        return strcmp(key,p.key)==0 && value==p.value;
    }
    char *getKey(){
        return key;
    }
};

//==============================================================================================================================================================//
//==============================================================================================================================================================//


class Collection{
private:
    Pair *pairs;
    int numOfPairs;
    void copy(const Collection &other){
        this->numOfPairs=other.numOfPairs;
        this->pairs=new Pair[this->numOfPairs];
        for(int i=0 ; i<numOfPairs ; i++){
            pairs[i]=other.pairs[i];
        }
    }
public:
    Collection(){
        this->numOfPairs=0;
        this->pairs=new Pair[this->numOfPairs];
    }
    Collection(const Collection &other){
        copy(other);
    }
    Collection &operator=(const Collection &other){
        if(this==&other){
            return *this;
        }
        delete [] pairs;
        copy(other);
        return *this;
    }
    ~Collection(){
        delete [] pairs;
    }
    Collection &operator +=(Pair &p){
        Pair *tmp=new Pair[numOfPairs+1];
        for(int i=0 ; i<numOfPairs ; i++){
            tmp[i]=pairs[i];
        }
        delete [] pairs;
        tmp[numOfPairs++]=p;
        pairs=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, Collection &c){
        out<<"Size: "<<c.numOfPairs<<endl;
        for(int i=0 ; i<c.numOfPairs ; i++){
            out<<c.pairs[i];
        }
        return out;
    }
    int values(){
        int product=1;
        for(int i=0 ; i<numOfPairs ; i++){
            product*=pairs[i].getValue();
        }
        return product;
    }
    bool operator==(const Collection &c){
        if(numOfPairs!=c.numOfPairs){
            return false;
        }
        for(int i=0 ; i<numOfPairs ; i++){
            if(!(pairs[i]==c.pairs[i])){
                return false;
            }
        }
        return true;
    }
    Pair *find(const char *key){
        Pair *p= nullptr;
        for(int i=0 ; i<numOfPairs ; i++){
            if(strcmp(pairs[i].getKey(),key)==0){
                p=&pairs[i];
                break;
            }
        }
        return p;
    }
};


void read(char *k, float *v) {
    cin >> k;
    cin >> *v;
}
int main() {
    char key[50];
    float value;
    cout << "----- class Pair -----" << endl;
    read(key, &value);
    cout << "----- constructor -----" << endl;
    Pair p1(key, value);//==(some-key 55);
    read(key, &value);
    Pair p2(key, value);//==(other-key 20);
    Pair p3(p1);//==(some-key 55)
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator ++(int) -----" << endl;
    cout << p1++;//==(some-key 55);
    cout << p1;//==(some-key 56);
    cout << "----- operator ++ -----" << endl;
    cout << ++p2;//==(other-key 21);
    cout << "----- operator + -----" << endl;
    Pair p = p1 + p2;//==(
    cout << "----- operator = -----" << endl;
    p3 = p;//==(other-key 77)
    cout << p3;

    cout << "----- class Collection -----" << endl;
    cout << "----- constructor -----" << endl;
    Collection k;
    cout << "----- operator += -----" << endl;
    k += p1;
    k += p2;
    k += p3;
    cout << "----- operator << -----" << endl;
    cout << k;
    cout << "----- copy constructor -----" << endl;
    Collection k2(k);
    cout << "----- operator == -----" << endl;
    if(k == k2) {
        cout << "k == k2" << endl;
    }
    k2 += p1;
    if(k == k2) {
        // not equal
        cout << "k == k2" << endl;
    }
    cout << "----- find -----" << endl;
    Pair* f = k.find(key);
    cout << *f;
    strcat(key, "other");
    f = k.find(key);
    if(f == NULL) {
        cout << key << " not found" << endl;
    }
    return 0;
}
