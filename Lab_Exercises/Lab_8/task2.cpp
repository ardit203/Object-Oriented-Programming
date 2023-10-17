#include <iostream>
#include <cstring>

using namespace std;

class FoodItem{
protected:
    char *type;
    int num;
//    void copy(const FoodItem &other){
//        this->type=new char [strlen(other.type)+1];
//        strcpy(this->type,other.type);
//        this->num=other.num;
//    }
public:
    FoodItem(char *type="", int num=0){
        this->type=new char [strlen(type)+1];
        strcpy(this->type,type);
        this->num=num;
    }
//    FoodItem(const FoodItem &other){
//        copy(other);
//    }
    virtual int getPrice()=0;
    virtual int getTime()=0;
    char *getType(){
        return type;
    }
};

class Pizza :public FoodItem{
private:
    char *dough;
public:
    Pizza(char *type="", int num=0, char *dough=""): FoodItem(type,num){
        this->dough=new char [strlen(dough)+1];
        strcpy(this->dough,dough);
    }
    int getPrice(){
        if(strcmp(dough,"wholeWheat")==0){
            return 250*num;
        } else{
            return 350*num;
        }
    }
    int getTime(){
        return 25;
    }
};

class Steak: public FoodItem{
private:
    bool cooked;
public:
    Steak(char *type="", int num=0, bool cooked= false): FoodItem(type,num){
        this->cooked=cooked;
    }
    int getPrice(){
        return 1300*num;
    }
    int getTime(){
        if(cooked){
            return 20;
        } else{
            return 15;
        }
    }
};

FoodItem *getMaxFoodItem(FoodItem **pItem, int n){
    FoodItem *max=pItem[0];
    for(int i=0 ; i<n ; i++){
        if(pItem[i]->getPrice()>max->getPrice()){
            max=pItem[i];
        }
    }
    return max;
}

int main() {
    FoodItem *p;
    int n;
    cin>>n;

    char type[30];
    char dough[30];
    bool cooked;
    int size;

    FoodItem *items[n];

    for (int i = 0; i <n; ++i) {
        cin>>type;
        cin>>size;


        if(strcmp(type, "pizza")==0 ) {
            cin>>dough;
            items[i] = new Pizza(type, size, dough);
        }else{
            cin>>cooked;
            items[i] = new Steak(type, size, cooked);
        }


    }

    FoodItem *it = getMaxFoodItem(items, n);
    cout<<"Type: "<<it->getType()<<endl;
    cout<<"The max PRC is: "<<it->getPrice()<<endl;
    cout<<"Time to cook: "<<it->getTime();
    return 0;
}