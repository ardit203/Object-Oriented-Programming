#include<iostream>
#include<cstring>

using namespace std;

class ComplexNumber{
    float real;
    float imaginary;
public:
    ComplexNumber(float real=0, float imaginary=0){
        this->real= real;
        this->imaginary=imaginary;
    }
    ComplexNumber operator+(ComplexNumber &c){
        ComplexNumber copy(this->real+c.real,this->imaginary+c.imaginary);
        return copy;
    }
    ComplexNumber operator-(ComplexNumber &c){
        ComplexNumber copy(this->real-c.real,this->imaginary-c.imaginary);
        return copy;
    }
    ComplexNumber operator*(ComplexNumber &c){
        ComplexNumber copy(this->real*c.real-this->imaginary*c.imaginary,this->real*c.imaginary+c.real*this->imaginary);
        return copy;
    }
    ComplexNumber operator/(const ComplexNumber &c) {
        float r = (this->real+this->imaginary*c.imaginary)/(c.real*c.real+c.imaginary+c.imaginary);
        float i = (this->imaginary*c.real-this->real*c.imaginary)/(c.real*c.real+c.imaginary+c.imaginary);
        return ComplexNumber(r,i);
    }
    ComplexNumber &operator+=(ComplexNumber &c){
        this->real+=c.real;
        this->imaginary+=c.imaginary;
        return *this;
    }
    ComplexNumber &operator-=(ComplexNumber &c){
        this->real-=c.real;
        this->imaginary-=c.imaginary;
        return *this;
    }
    ComplexNumber &operator*=(ComplexNumber &c){
        *this=*this*c;
//        this->real=this->real*c.real-this->imaginary*c.imaginary;
//        this->imaginary=this->real*c.imaginary+c.real*this->imaginary;
        return *this;
    }
    ComplexNumber&operator/=(ComplexNumber &c){
        *this=*this/c;
        return *this;
    }
    ComplexNumber operator+(float n) {
        return ComplexNumber(real + n, imaginary);
    }
    friend ostream &operator<<(ostream &out, ComplexNumber &c){
        if(c.real==0){
            if(c.imaginary>0){
                out<<c.imaginary<<"i";
            } else if(c.imaginary<0){
                out<<c.imaginary;
            } else{
                out<<'0';
            }
        } else{
            if(c.imaginary>0){
                out<<c.real<<"+"<<c.imaginary<<"i";
            } else if(c.imaginary<0){
                out<<c.real<<c.imaginary<<"i";
            } else{
                out<<c.real;
            }
        }
        return out;
    }
};

int main(){
    ComplexNumber c1(1,2);
    ComplexNumber c2(2,1);
    cout<<c1<<endl<<c2<<endl;
    cout<<"----------------------"<<endl;
    ComplexNumber c3=c1+c2;
    cout<<c3<<endl;
    cout<<"----------------------"<<endl;
    c3=c1*c2;
    cout<<c3<<endl;
    cout<<"----------------------"<<endl;
    c3*=c1;
    cout<<c3<<endl;
    cout<<"----------------------"<<endl;
    ComplexNumber c4=c1+5;
    cout<<c4<<endl;
    return 0;
}