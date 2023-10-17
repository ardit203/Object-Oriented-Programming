#include <iostream>
#include <cstring>
using namespace std;

class MobilePhone{
private:
    char model[20];
    int model_number;
    int yearOfRelease;
public:
    MobilePhone(){
        strcpy(model,"");
        model_number=0;
        yearOfRelease=0;
    }
    MobilePhone(char *_model, int _model_number, int _yearOfRelease){
        strcpy(model,_model);
        model_number=_model_number;
        yearOfRelease=_yearOfRelease;
    }

    MobilePhone(const MobilePhone &other){
        strcpy(model,other.model);
        model_number=other.model_number;
        yearOfRelease=other.yearOfRelease;
    }
    ~MobilePhone(){

    }
    void print(){
        cout<<model<<" "<<model_number<<" release year: "<<yearOfRelease<<endl;
    }
};

class Owner{
private:
    char name[20];
    char surname[20];
    MobilePhone phone;
public:
    Owner(char *_name, char *_surname, MobilePhone _phone){
        strcpy(name,_name);
        strcpy(surname,_surname);
        phone=_phone;
    }
    Owner(){
        strcpy(name,"");
        strcpy(surname,"");
        phone=MobilePhone();
    }
    ~Owner(){

    }
    void print(){
        cout<<name<<" "<<surname<<" has a mobile phone:"<<endl;
        phone.print();
    }
};

//DO NOT CHANGE THE MAIN FUNCTION
int main() {
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];

    int testCase;

    cin>>testCase;

    cin>>model;
    cin>>modelNumber;
    cin>>year;
    cin>>name;
    cin>>surname;

    if(testCase==1){
        MobilePhone mobilePhone(model,modelNumber,year);

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }
    if(testCase==2){
        MobilePhone mobilePhone(MobilePhone(model,modelNumber,year));

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }

}
