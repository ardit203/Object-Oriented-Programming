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
        out<<"'"<<p.key<<"'"<<" -> "<<p.value<<endl;
        return out;
    }
    Pair &operator--(){
        --value;
        return *this;
    }
    Pair operator--(int){
        Pair Copy(*this);
        --value;
        return Copy;
    }
    Pair operator * (Pair &p1){
        int product=this->value*p1.value;
        int l1= strlen(this->key);
        int l2= strlen(p1.key);
        if(l1>=l2){
            Pair P(p1.key,product);
            return P;
        } else{
            Pair P(this->key,product);
            return P;
        }
    }
    int getValue(){
        return value;
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
    bool operator<(Collection &c){
        return this->values()<c.values();
    }
    int values(){
        int product=1;
        for(int i=0 ; i<numOfPairs ; i++){
            product*=pairs[i].getValue();
        }
        return product;
    }
    int greater(int value){
        int count=0;
        for(int i=0 ; i<numOfPairs ; i++){
            if(pairs[i].getValue()>value){
                count++;
            }
        }
        return count;
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
    Pair p1(key, value);
    read(key, &value);
    Pair p2(key, value);
    Pair p3(p1);
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator --(int) -----" << endl;
    cout << p1--;
    cout << p1;
    cout << "----- operator -- -----" << endl;
    cout << --p2;
    cout << "----- operator * -----" << endl;
    Pair p = p1 * p2;
    cout << "----- operator = -----" << endl;
    p3 = p;
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
    cout << "----- operator < -----" << endl;
    if(k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    k2 += p1;
    if(k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    cout << "----- greater -----" << endl;
    int x;
    cin >> x;
    int pp = k.greater(x);
    cout << pp;
    return 0;
}
