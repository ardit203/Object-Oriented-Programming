#include <iostream>
#include <cstring>
using namespace std;

enum gender{
    male, female
};

class Mate{
private:
    char name[20];
    int age;
    gender g;
public:
    Mate(char *_name, int _age, gender _g){
        strcpy(name,_name);
        age=_age;
        g=_g;
    }
    Mate(){
        strcpy(name,"");
        age=0;
        g=male;
    }
    Mate(const Mate &other){//copy constructor
        cout << "Copy constructor of class Mate is called here!!" << endl;
        strcpy(name,other.name);
        age=other.age;
        g=other.g;
    }
    void print(){
        cout<<name<<" "<<age<<" "<<(g==male ? "Male" : "Female")<<endl;
    }

    const char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    gender getG() const {
        return g;
    }

    bool isSuccess(Mate other){
        return name[0]!=other.name[0] && (abs(age-other.age)<3);
    }
};

class Date{
private:
    Mate boy;
    Mate girl;

public:
    Date(Mate _boy, Mate _girl){
        boy=_boy;
        girl=_girl;
    }
    Date(const Date &other){//copy constructor
        cout << "Copy constructor of class Date is called here!!" << endl;
        boy=other.boy;
        girl=other.girl;
    }
    void print(){
        cout<<"Date between:"<<endl;
        boy.print();
        girl.print();
    }
    bool isSuccess(){
        return boy.isSuccess(girl);//implicit call of the copy constructors
    }
};

int main(){
    Mate b("Stefan", 26, male);
    Mate g("Ana", 24, female);

    Mate m1; //default constructor will be called
    m1.print();


    Date date (b, g); //implicit calls of the copy constructors
    date.print();
    cout << date.isSuccess();
    return 0;
}