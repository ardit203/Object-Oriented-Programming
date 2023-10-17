#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Employee{
    char name[100];
    char surname[100];
    int salary;
public:
    void printEmployee(){
        cout<<"Employee name: "<<name<<endl;
        cout<<"Employee surname: "<<surname<<endl;
        cout<<"Employee salary: "<<salary<<endl;
    }
    Employee(char *_name, char *_surname, int _salary){
        strcpy(name,_name);
        strcpy(surname,_surname);
        salary=_salary;
    }
    Employee(){
        strcpy(name,"");
        strcpy(surname,"_surname");
        salary=0;
    }
    int getSalary(){
        return salary;
    }
};
class TechCompany{
    char name[100];
    Employee employees[100];
    int numOfEmployees;
public:
    void print(){
        cout<<"Tech company name: "<<name<<" Number of employees"<<endl;
    }
    double getAverageOfEmployeeSalary(){
        double sum=0;
        for(int i=0 ; i<numOfEmployees ; i++){
            sum+=employees[i].getSalary();
        }
        return sum/numOfEmployees;
    }
    TechCompany(){
        strcpy(name, "");
        numOfEmployees=2;
        for(int i=0 ; i<numOfEmployees ; i++){
            employees[i]=Employee();
        }
    }
    TechCompany(char *_name, Employee *_employees, int _numOfEmployees){
        strcpy(name, _name);
        numOfEmployees=_numOfEmployees;
        for(int i=0 ; i<numOfEmployees ; i++){
            employees[i]=_employees[i];
        }
    }
    TechCompany(char *_name){
        strcpy(name,_name);
        numOfEmployees=0;
    }
    TechCompany(const TechCompany &other){
        strcpy(name, other.name);
        numOfEmployees=other.numOfEmployees;
        for(int i=0 ; i<numOfEmployees ; i++){
            employees[i]=other.employees[i];
        }
    }
    double VAR(){
        double avg=getAverageOfEmployeeSalary();
        double sum=0;
        for(int i=0 ; i<numOfEmployees ; i++){
            double square=(employees[i].getSalary()-avg)*(employees[i].getSalary()-avg);
            sum+=square;
        }
        double var=sum/(numOfEmployees-1);
        return var;
    }

    double STD(){
        double std=sqrt(VAR());
        return std;
    }
    char *getName(){
        return name;
    }
    int getNumOfEmployees(){
        return numOfEmployees;
    }
    void setName(char *other){
        strcpy(name,other);
    }
    Employee getEmployee(int n){
        return employees[n];
    }
    void addEmployee(const Employee& employee) {
        if (numOfEmployees < 20) {
            employees[numOfEmployees++] = employee;
        }
    }
};

TechCompany printCompanyWithHighestAverageSalary(TechCompany companies[], int n){
    TechCompany highest=companies[0];
    for(int i=1 ; i<n ; i++){
        double avg=companies[i].getAverageOfEmployeeSalary();
        double highestAVG=highest.getAverageOfEmployeeSalary();
        if(avg>highestAVG){
            highest=companies[i];
        }
    }
    return highest;
}

TechCompany printCompanyWithHighestStdSalary(TechCompany companies[], int n){
    TechCompany highest=companies[0];
    for(int i=1 ; i<n ; i++){
        if(companies[i].STD()>highest.STD()){
            highest=companies[i];
        }
    }
    return highest;
}

bool isSameCompany(TechCompany company1, TechCompany company2){
    return strcmp(company1.getName(),company2.getName())==0;
}

//DO NOT CHANGE main()




int main() {
    const int MAX_COMPANIES = 10;
    const int MAX_EMPLOYEES = 20;

    TechCompany companies[MAX_COMPANIES];

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        char name[100];
        std::cin >> name;

        TechCompany company(name);

        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++) {
            char name[100];
            char surname[100];
            int salary;

            std::cin >> name;

            std::cin >> surname;

            std::cin >> salary;

            Employee employee(name, surname, salary);

            company.addEmployee(employee);
        }

        companies[i] = company;
    }

    TechCompany copy = companies[0];

    std::cout<<"-->Testing get and set methods for one object and copy constructor"<<std::endl;
    copy.setName("copy");
    std::cout << copy.getName() << std::endl;


    std::cout<<"-->Testing addEmployee function"<<std::endl;
    Employee newEmployee("John", "Doe", 5000);
    copy.addEmployee(newEmployee);
    std::cout << "Number of employees in copy: " << copy.getNumOfEmployees() << std::endl;


    std::cout<<"-->Testing copy of first employee"<<std::endl;
    Employee firstEmployee = copy.getEmployee(0);
    firstEmployee.printEmployee();


    std::cout<<"-->Testing methods"<<std::endl;
    TechCompany t = printCompanyWithHighestAverageSalary(companies, n);
    TechCompany t1 = printCompanyWithHighestStdSalary(companies, n);

    std::cout << "Tech company with the highest average salary: " << t.getName() << std::endl;
    std::cout << "Tech company with the highest standard deviation for salaries: " <<t1.getName() << std::endl;

    if (isSameCompany(t, t1)){
        std::cout<<"The tech company: "<<t.getName()<<" has the highest standard deviation and highest average salary"<<std::endl;
    }
    return 0;
}
