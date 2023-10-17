#include <stdio.h>
#include <string.h>
#define MAX 30

//Create struct Employee
typedef struct Employee{
    char name[MAX];
    char ID[MAX];
    char department[MAX];
    int salary;
}employee;

//Function for reading employee
employee readEmployee(){
    employee e;
    scanf("%s %s %s %d",e.name,e.ID,e.department,&e.salary);
    return e;
}

//Function for printing employee
void printEmployee(employee e){
    printf("%s %s %s %d\n",e.name,e.ID,e.department,e.salary);
}

//Create struct company
typedef struct Company{
    char name[MAX];
    int number_employees;
    employee employees[MAX];
}company;

//Function for reading company
company readCompany(){
    company c;
    scanf("%s %d",c.name,&c.number_employees);
    for(int i=0 ; i<c.number_employees ; i++){
        c.employees[i]=readEmployee();
    }
    return c;
}
//Function for printing company (We dont need this function but for testing the reading)
void printCompany(company c){
    printf("%s %d\n",c.name,c.number_employees);
    for(int i=0 ; i<c.number_employees ; i++){
        printEmployee(c.employees[i]);
    }
}
//Function for finding the average salary of a company
float avgSalary(company c){
    float sum=0;
    for(int i=0 ; i<c.number_employees ; i++){
        sum+=(float )c.employees[i].salary;
    }
    return sum/(float )c.number_employees;
}

//Function for printting the employees that have salaries less than the avereage salary for their respective company
void printEmployeesBelowAverageSalary(company *comp, int n){
    for(int i=0 ; i<n ; i++){
        float avg= avgSalary(comp[i]);
        for(int j=0 ; j<comp[i].number_employees ; j++){
            if((float )comp[i].employees[j].salary<avg){
                printEmployee(comp[i].employees[j]);
            }
        }
    }
}
//Function for finding the highest paid employee in a company
employee highestPaid(employee *e, int k){
    employee max=e[0];
    for(int i=1 ; i<k ; i++){
        if(e[i].salary>max.salary){
            max=e[i];
        }
    }
    return max;
}

//Function for printing the highest paid employee in a particular department
void printHighestSalaryEmployee(company *comp, int n, char *department){
    for(int i=0 ; i<n ; i++){
        employee WorkInThatDepartment[100];
        int k=0;
        for(int j=0 ; j<comp[i].number_employees ; j++){
            if(strcmp(comp[i].employees[j].department,department)==0){
                WorkInThatDepartment[k++]=comp[i].employees[j];
            }
        }

        if(k>0){//If there are employees in a company that work in that department
            employee hP= highestPaid(WorkInThatDepartment,k);
            printEmployee(hP);
        } else{//if there are no employees in a company that work in that department we should print the employee of the previous company that has the highest salary
            int h=0;
            for(int j=0 ; j<comp[i-1].number_employees ; j++){
                if(strcmp(comp[i].employees[j].department,department)==0){
                    WorkInThatDepartment[h++]=comp[i].employees[j];
                }
            }
            employee hP= highestPaid(WorkInThatDepartment,k);
            printEmployee(hP);
        }
    }
}
int main(){
    int n;
    scanf("%d",&n);
    company companies[MAX];
    for(int i=0 ; i<n ; i++){
        companies[i]=readCompany();
    }
    printf("Employees with salaries below the average:\n");
    printEmployeesBelowAverageSalary(companies,n);
    printf("Employees with highest salaries for given department:\n");
    char department[20];
    scanf("%s",department);//We read the particular department
    printHighestSalaryEmployee(companies,n, department);
    return 0;
}