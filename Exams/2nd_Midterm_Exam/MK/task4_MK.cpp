#include <cstring>
#include <iostream>
using namespace std;

// Your Code goes here

class Pizza{
protected:
    char name[20];
    char ingredients[100];
    float prc;
public:
    Pizza(char *name="", char *ingredients="", float prc=0){
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
        this->prc=prc;
    }
    virtual float price()=0;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////

enum Size{small  //==0
        ,large  //==1
        ,family //==2
};

class FoldedPizza;

class FlatPizza:public Pizza{
private:
    Size size;
public:
    FlatPizza(char *name="", char *ingredients="", float prc=0, Size size=Size(0))
    : Pizza(name,ingredients,prc){
        this->size=size;
    }
    float price() override {
        float p;
        if(size==Size(0)){
            p=prc*1.1;
        } else if(size==Size(1)){
            p=prc*1.2;
        }else{
            p=prc*1.3;
        }
        return p;
    }
    friend ostream &operator<<(ostream &out, FlatPizza &fp){
        out<<fp.name<<": "<<fp.ingredients<<", ";
        if(fp.size==Size(0)){
            out<<"small - ";
        }else if(fp.size==Size(1)){
            out<<"large - ";
        }else{
            out<<"family - ";
        }
        out<<fp.price()<<endl;
        return out;
    }
    bool operator<(FlatPizza &p){
        return price()<p.price();
    }
    bool operator<(FoldedPizza &p);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class FoldedPizza:public Pizza{
private:
    bool whiteFlour; //true==white flour,   false==not white Flour;
public:
    FoldedPizza(char *name="", char *ingredients="", float prc=0, bool whiteFlour= true)
    : Pizza(name,ingredients,prc){
        this->whiteFlour=whiteFlour;
    }
    float price() override {
        float p;
        if(whiteFlour){
            p=prc*1.1;
        } else{
            p=prc*1.3;
        }
        return p;
    }
    void setWhiteFlour(bool b){
        whiteFlour=b;
    }
    friend ostream &operator<<(ostream &out, FoldedPizza &fp){
        out<<fp.name<<": "<<fp.ingredients<<", ";
        if(fp.whiteFlour){
            out<<"wf - ";
        } else{
            out<<"nwf - ";
        }
        out<<fp.price()<<endl;
        return out;
    }
    bool operator<(FlatPizza &p){
        return price()<p.price();
    }
    bool operator<(FoldedPizza &p){
        return price()<p.price();
    }
};



bool FlatPizza::operator<(FoldedPizza &p) {
    return price()<p.price();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void expensivePizza(Pizza **pizza, int n){
    Pizza *max=pizza[0];
    for(int i=1 ; i<n ; i++){
        if(pizza[i]->price()>max->price()){
            max=pizza[i];
        }
    }
    FlatPizza *flat=dynamic_cast<FlatPizza *>(max);
    if(flat!= nullptr){
        cout<<*flat;
    }
    FoldedPizza *folded=dynamic_cast<FoldedPizza*>(max);
    if(folded!= nullptr){
        cout<<*folded;
    }
}


// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    }
    else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    }
    else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
