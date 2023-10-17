#include <iostream>
#include <cstring>
#define MAX 50
using namespace std;

enum position{
    EMPLOYEE,//0
    MANAGER,//1
    OWNER//2
};

class Person{
private:
    char name[MAX];
    int salary;
    position workingPosition;
public:
    Person(char *_name="Aridt", int _salary=18000, position _workingPosition=position(0)){
        strcpy(name,_name);
        salary=_salary;
        workingPosition=_workingPosition;
    }
    void print(){
        cout<<"Employee: "<<name<<" Salary: "<<salary<<" Position: ";
        switch (workingPosition) {
            case EMPLOYEE: cout<<"Employee"<<endl;
                break;
            case MANAGER: cout<<"Manager"<<endl;
                break;
            case OWNER: cout<<"Owner"<<endl;
                break;
        }
    }
    int getSalary(){
        return salary;
    }
};

void swap(Person &p1, Person &p2){
    Person tmp=p1;
    p1=p2;
    p2=tmp;
}

void sort(Person *employees, int n){
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n-1-i ; j++){
            if(employees[j].getSalary()<employees[j+1].getSalary()){
                swap(employees[j],employees[j+1]);
            }
        }
    }
}
int main(){
    int n;
    cin>>n;
    char name[MAX];
    int salary;
    int workingPosition;
    Person employees[MAX];
    for(int i=0 ; i<n ; i++){
        cin>>name>>salary>>workingPosition;
        employees[i]=Person(name,salary,position(workingPosition));
    }
    sort(employees,n);
    for(int i=0 ; i<n ; i++){
        employees[i].print();
    }
    return 0;
}

/*3
Ardit 1500000 2
Hamdi 145000 0
Sabri 12345 0*/