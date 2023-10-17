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
    void add(int number){
        if(size==capacity){
            increaseCapacity();
        }
        this->content[size++]=number;
        decreaseCapacity();
    }
    void print() {
        cout << "Array with capacity: " << capacity << " and size of :" << size << " (Percentage of used: "
             << (size * 100.0) / capacity << "%) Elements: " << endl;
        if (size == 0) {
            cout << "EMPTY" << endl;
        } else {
            for (int i = 0; i < size; i++) {
                cout << content[i];
                if (i != size - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
    void replaceAll(int a, int b){
        for(int i=0 ; i<size ; i++){
            if(content[i]==a){
                content[i]=b;
            }
        }
    }
    void deleteAll(int number){
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
};

int main () {
    Array array;
    array.print();
    for (int i = 1; i <= 100; i++) {
        array.add(i%2);
    }
    array.print();

    array.deleteAll(1);

    array.print();
    return 0;
}