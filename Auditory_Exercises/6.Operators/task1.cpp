#include<iostream>
#include<cstring>

using namespace std;

class Array{
private:
    int *content;
    int size;
    int capacity;
    void copy(const Array &other){
        this->capacity=other.capacity;
        this->size=other.size;
        for(int i=0 ; i<size ; i++){
            this->content[i]=other.content[i];
        }
    }
public:
    Array(int capacity=10){
        this->capacity=capacity;
        this->size=0;
        this->content=new int [capacity];
    }
    Array(const Array &other){
        copy(other);
    }
    Array operator=(const Array &other){
        if(this==&other){
            return *this;
        }
        delete [] content;
        copy(other);
        return *this;
    }
    ~Array(){
        delete [] content;
    }
    void increaseCapacity(){
        int *tmp=new int [2*capacity];
        for(int i=0 ; i<size ; i++){
            tmp[i]=this->content[i];
        }
        delete [] content;
        content=tmp;
        capacity*=2;
    }
    Array &operator+=(int number){
        if(size==capacity){
            increaseCapacity();
        }
        this->content[size++]=number;
        decreaseCapacity();
        return *this;
    }
    friend ostream &operator<<(ostream &out, const Array &a){
        out << "Array with capacity: " << a.capacity << " and size of :" << a.size << " (Percentage of used: "
             << (a.size * 100.0) / a.capacity << "%) Elements: " << endl;
        if (a.size == 0) {
            out << "EMPTY" << endl;
        } else {
            for (int i = 0; i < a.size; i++) {
                out << a.content[i];
                if (i != a.size - 1) {
                    out << ", ";
                }
            }
            out << endl;
        }
        return out;
    }
    void replaceAll(int a, int b){
        for(int i=0 ; i<size ; i++){
            if(content[i]==a){
                content[i]=b;
            }
        }
    }
    Array &operator-=(int number){
        int *tmp=new int[capacity];
        int j=0;
        for(int i=0 ; i<size ; i++){
            if(content[i]!=number){
                tmp[j++]=content[i];
            }
        }
        size=j+1;
        delete [] content;
        content=tmp;
        decreaseCapacity();
        return *this;
    }
    void decreaseCapacity(){
        if(size==capacity){
            return;
        }
        int *tmp=new int [size];
        for(int i=0 ; i<size ; i++){
            tmp[i]=content[i];
        }
        delete [] content;
        content=tmp;
        capacity=size;
    }
    int &operator[](int a){
        return content[a];
    }
    bool operator==(Array &other){
        if(this->size!=other.size){
            return false;
        }
        for(int i=0 ; i<size ; i++){
            if(this->content[i]!=other.content[i]){
                return false;
            }
        }
        return true;
    }
};

int main () {
    Array array;
    cout<<array;
    for (int i = 1; i <= 100; i++) {
        array+=i%2;
    }
    cout<<array;

    array-=-1;

    cout<<array;
    return 0;
}