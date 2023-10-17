#include <iostream>
#include <cstring>
using namespace std;


class Square {
protected:
    double a;

public:
    //TODO default constructor & constructor with arguments
    Square(double a=1.0){
        this->a=a;
    }


    //TODO copy constructor
    Square(const Square &other){
        this->a=other.a;
    }

    //TODO double perimeter() {}
    double perimeter()const {
        return 4.0*a;
    }

    //TODO double area() {}
    double area()const {
        return a*a;
    }

    //TODO void print();
    void print(){
        cout<<"Square with side a="<<a<<" has area P="<<area()<<" and perimeter L="<<perimeter()<<endl;
    }
};

class Rectangle : public Square{ //TODO insert inheritance
private:
    double x,y;
public:
    //TODO default constructor
    Rectangle(): Square(){
        this->x=1.0;
        this->y=1.0;
    }
    //TODO constructor
    Rectangle(const Square &s, double x, double y): Square(s){
        this->x=x;
        this->y=y;
    }

    //TODO copy constructor
    Rectangle(const Rectangle &other){
        this->a=other.a;
        this->x=other.x;
        this->y=other.y;
    }
    //TODO methods override
    double perimeter(){
        return 2*(a+x)+2*(a+y);
    }
    double area(){
        return (a+x)*(a+y);
    }
    void print(){
        if(x==y){
            a+=x;
            Square::print();

//            or
//            Square s(a+x);
//            s.print();
            return;
        }
        cout<<"Rectangle with sides: "<<a+x<<" and "<<a+y<<"  P="<<area()<<" and perimeter L="<<perimeter()<<endl;

    }
};

int main() {
    int n;
    double a,x,y;
    Square * kvadrati;
    Rectangle * pravoagolnici;

    cin>>n;

    kvadrati = new Square [n];
    pravoagolnici = new Rectangle [n];

    for (int i=0;i<n;i++){
        cin>>a;

        kvadrati[i] = Square(a);
    }

    for (int i=0;i<n;i++){
        cin>>x>>y;

        pravoagolnici[i]=Rectangle(kvadrati[i], x, y);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===Testing class Square==="<<endl;
        for (int i=0;i<n;i++)
            kvadrati[i].print();
    }
    else {
        cout<<"===Testing class Rectangle==="<<endl;
        for (int i=0;i<n;i++)
            pravoagolnici[i].print();
    }
}