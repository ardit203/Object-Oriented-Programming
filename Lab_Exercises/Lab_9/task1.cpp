#include <iostream>
#include <cstring>

using namespace std;


//-------------------------------------------------------------------------------//

class Employee{
protected:
    char name[50];
    int age;
public:
    Employee(char *name, int age) :  age(age) {
        strcpy(this->name, name);
    }

    virtual void displayInfo()=0;
};


//-------------------------------------------------------------------------------//

class Payable{
protected:
    float salary;
public:
    Payable(float salary) : salary(salary) {}

    virtual float calculateSalary()=0;
};


//-------------------------------------------------------------------------------//


class Developer:public Employee,public Payable{
private:
    char programmingLanguage[50];
public:

    Developer(char *name="", int age=0, float salary=0, char *programmingLanguage="") : Employee(name, age), Payable(salary){
        strcpy(this->programmingLanguage,programmingLanguage);
    }

    void displayInfo() override {
        cout<<"-- Developer Information --"<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Salary: $"<<calculateSalary()<<endl;
        cout<<"Programming Language: "<<programmingLanguage<<endl;
    }

    float calculateSalary() override {
        return salary*(1-0.1);
    }
};



//-------------------------------------------------------------------------------//


class Manager:public Employee,public Payable{
private:
    int numOfDepartments;
public:
    Manager(char *name="", int age=0, float salary=0, int numOfDepartments=0) : Employee(name, age), Payable(salary),
                                                                       numOfDepartments(numOfDepartments) {}

    void displayInfo() override {
        cout<<"-- Manager Information --"<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Salary: $"<<calculateSalary()<<endl;
        cout<<"Number Of Departments: "<<numOfDepartments<<endl;
    }

    float calculateSalary() override {
        return salary*(1+numOfDepartments*5/100.0);
    }
};



//-------------------------------------------------------------------------------//











double biggestSalary(Payable* payable[], int n) {
    Payable* maxSalaryEmployee = payable[0];

    for (int i = 1; i < n; i++) {
        if (payable[i]->calculateSalary() > maxSalaryEmployee->calculateSalary()) {
            maxSalaryEmployee = payable[i];
        }
    }

    return maxSalaryEmployee->calculateSalary();
}

int main()
{
    Payable* payable[5];
    Developer developers[5];
    Manager managers[5];
    int j=0, k=0;
    for(int i=0; i<5; i++)
    {
        char name[50];
        int age;
        double salary;
        cin>>name>>age>>salary;
        if(i%2==0)
        {
            char programmingLanguage[50];
            cin>>programmingLanguage;
            developers[j]=Developer(name, age, salary, programmingLanguage);
            developers[j].displayInfo();
            payable[i]=&developers[j];
            j++;
        }
        else {
            int numberOfDepartments;
            cin>>numberOfDepartments;
            managers[k]=Manager(name, age, salary, numberOfDepartments);
            managers[k].displayInfo();
            payable[i]=&managers[k];
            k++;
        }
    }
    cout<<endl<<"Biggest Salary: "<<biggestSalary(payable, 5);
    return 0;
}






//--------------------------------------------------------------------------------------------------------------------//


//#include <iostream>
//#include <cstring>
//using namespace std;
//
//class Employee{
//protected:
//    char name[50];
//    int age;
//
//public:
//    Employee() {}
//
//    Employee(char *name, int age)
//    {
//        strcpy(this->name, name);
//        this->age=age;
//    }
//
//    virtual void displayInfo() const {
//        cout << "Name: " << name << endl;
//        cout << "Age: " << age << endl;
//    }
//};
//class Payable {
//protected:
//    double salary;
//
//public:
//    Payable() {}
//
//    Payable(double salary)
//    {
//        this->salary=salary;
//    }
//
//
//    virtual double calculateSalary() const = 0;
//};
//class Developer : public Employee, public Payable {
//private:
//    char programmingLanguage[50];
//public:
//    Developer() {}
//
//    Developer(char *name, int age, double salary, char *programmingLanguage)
//            :Employee(name, age) , Payable(salary)
//    {
//        strcpy(this->programmingLanguage, programmingLanguage);
//    }
//
//
//    void displayInfo() const override {
//        cout << "-- Developer Information --" << endl;
//        Employee::displayInfo();
//        cout << "Salary: $" << calculateSalary() << endl;
//        cout << "Programming Language: " << programmingLanguage << endl;
//    }
//
//
//    double calculateSalary() const override {
//        return salary - (salary * 0.1);
//    }
//};
//
//
//class Manager : public Employee, public Payable {
//private:
//    int numberOfDepartments;
//public:
//    Manager() {}
//
//    Manager(char *name, int age, double salary, int numberOfDepartments)
//            :Employee(name, age) , Payable(salary)
//    {
//        this->numberOfDepartments=numberOfDepartments;
//    }
//
//
//    void displayInfo() const override {
//        cout << "-- Manager Information --" << endl;
//        Employee::displayInfo();
//        cout << "Salary: $" << calculateSalary() << endl;
//        cout << "Number of Departments: " << numberOfDepartments << endl;
//    }
//
//
//    double calculateSalary() const override {
//        double bonus = numberOfDepartments * 0.05 * salary;
//        return salary + bonus;
//    }
//};
//double biggestSalary(Payable* payable[], int n) {
//    Payable* maxSalaryEmployee = payable[0];
//
//
//    for (int i = 1; i < n; i++) {
//        if (payable[i]->calculateSalary() > maxSalaryEmployee->calculateSalary()) {
//            maxSalaryEmployee = payable[i];
//        }
//    }
//
//
//    return maxSalaryEmployee->calculateSalary();
//}
//int main()
//{
//    Payable* payable[5];
//    Developer developers[5];
//    Manager managers[5];
//    int j=0, k=0;
//    for(int i=0; i<5; i++)
//    {
//        char name[50];
//        int age;
//        double salary;
//        cin>>name>>age>>salary;
//        if(i%2==0)
//        {
//            char programmingLanguage[50];
//            cin>>programmingLanguage;
//            developers[j]=Developer(name, age, salary, programmingLanguage);
//            developers[j].displayInfo();
//            payable[i]=&developers[j];
//            j++;
//        }
//        else {
//            int numberOfDepartments;
//            cin>>numberOfDepartments;
//            managers[k]=Manager(name, age, salary, numberOfDepartments);
//            managers[k].displayInfo();
//            payable[i]=&managers[k];
//            k++;
//        }
//    }
//    cout<<endl<<"Biggest Salary: "<<biggestSalary(payable, 5);
//    return 0;
//}