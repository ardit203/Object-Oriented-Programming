#include <iostream>
#include <cstring>
using namespace std;

class Shape{
protected:
    double base;
    double height;
public:
    Shape(double base=1.0, double height=1.0){
        this->base=base;
        this->height=height;
    }
    virtual void print()=0;
    virtual double volume()=0;
};

class Cylinder : public Shape{
public:
    Cylinder(double base=1.0, double height=1.0): Shape(base,height){}
    void print(){
        cout<<"Cylinder with base radius of: "<<base<<" and height of: "<<height<<" ("<<volume()<<")"<<endl;;
    }
    double volume(){
        return base*base*height*3.14;
    }
};

class Cone : public Shape{
public:
    Cone(double base=1.0, double height=1.0): Shape(base,height){}
    void print(){
        cout<<"Cone with base radius of: "<<base<<" and height of: "<<height<<" ("<<volume()<<")"<<endl;
    }
    double volume(){
        return base*base*height*3.14/3;
    }
};

class Cuboid : public Shape{
    double width;
public:
    Cuboid(double base=1.0, double height=1.0, double width=1.0): Shape(base,height){
        this->width=width;
    }
    void print(){
        cout<<"Cuboid with base of: "<<base<<", height of: "<<height<<" and width of: "<<width<<" ("<<volume()<<")"<<endl;
    }
    double volume(){
        return base*height*width;
    }
};

void
maxVolume(Shape *array[], int n){
    Shape *max=array[0];
    for(int i=0 ; i<n ; i++){
        if(array[i]->volume()>max->volume()){
            max=array[i];
        }
    }
    max->print();
}

int shapesWithoutACirlcleBase(Shape **shapes, int n){
    int counter=0;
    for(int i=0 ; i<n ; i++){
        Shape *p=dynamic_cast<Cuboid *>(shapes[i]);
        if(p!= nullptr){
            counter++;
        }
    }
    return counter;
}

int main(){
    Shape **shapes=new Shape * [3];
    for(int i=0 ; i<3 ; i++){
        if(i==0){//cylinder
           shapes[i]=new Cylinder(3,4);
        } else if(i==1){//cone
            shapes[i]=new Cone(5,5);
        } else{//cuboid
            shapes[i]=new Cuboid(6,7,8);
        }
    }
    for(int i=0 ; i<3 ; i++){
        shapes[i]->print();
    }
    cout<<"-------------------"<<endl;
    maxVolume(shapes,3);
    cout<<"-------------------"<<endl;
    cout<<shapesWithoutACirlcleBase(shapes,3);
    return 0;
}