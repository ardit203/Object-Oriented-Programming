#include <iostream>
#include <cstring>
using namespace std;

class Student{
private:
    char *name;
    int *grades;
    int numOfGrades;
    int academicYear;
    void copy(const Student &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->numOfGrades=other.numOfGrades;
        this->grades=new int [this->numOfGrades];
        for(int i=0 ; i<this->numOfGrades ; i++){
            this->grades[i]=other.grades[i];
        }
        this->academicYear=other.academicYear;
    }
public:
    Student(char *name="", int academicYear=1){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->academicYear=academicYear;
        this->numOfGrades=0;
        this->grades=new int [this->numOfGrades];
    }
    ~Student(){
        delete[]name;
        delete []grades;
    }
    Student(const Student &other){
        copy(other);
    }
    Student &operator=(const Student &other){
        if(this==&other){
            return *this;
        }
        delete[]name;
        delete[]grades;
        copy(other);
        return *this;
    }

    double avg()const{
        if(numOfGrades==0){
            return 5;
        }
        double sum=0.0;
        for(int i=0 ; i<numOfGrades ; i++){
            sum+=grades[i];
        }
        return sum/numOfGrades;
    }
    friend ostream &operator<<(ostream &out,const Student &s){
        out<<s.name<<" - "<<s.academicYear<<" ("<<s.avg()<<")";
        return out;
    }
    friend istream &operator>>(istream &in, Student s){
        return in>>s.name>>s.academicYear;
    }

    Student &operator+=(int grade){
        int *tmp=new int[numOfGrades+1];
        for(int i=0 ; i<numOfGrades ; i++){
            tmp[i]=grades[i];
        }
        delete []grades;
        tmp[numOfGrades++]=grade;
        grades=tmp;
        return *this;
    }

    //Prefix
    Student &operator++(){
        ++academicYear;
        return *this;
    }

    //Postfix
    Student operator++(int){
        Student copy(*this);
        ++academicYear;
        return copy;
    }
    bool operator>(Student &s){
        return avg()>s.avg();
    }
};

class Faculty{
private:
    Student *students;
    int numOfStudents;
    void copy(const Faculty &other){
        numOfStudents=other.numOfStudents;
        students=new Student [numOfStudents];
        for(int i=0 ; i<numOfStudents ; i++){
            students[i]=other.students[i];
        }
    }
public:
    Faculty(){
        students=new Student[0];
        numOfStudents=0;
    }
    ~Faculty(){
        delete [] students;
    }
    Faculty(const Faculty &other){
        copy(other);
    }
    Faculty &operator+=(Student &s){
        Student *tmp=new Student[numOfStudents+1];
        for(int i=0 ; i<numOfStudents ; i++){
            tmp[i]=students[i];
        }
        delete [] students;
        tmp[numOfStudents++]=s;
        students=tmp;
        return *this;
    }
    //Prefix
    Faculty &operator++(){
        for(int i=0 ; i<numOfStudents ; i++){
            ++students[i];
        }
        return *this;
    }
    //Postfix
    Faculty operator++(int){
        Faculty copy(*this);
        for(int i=0 ; i<numOfStudents ; i++){
            ++students[i];
        }
        return copy;
    }

    friend ostream &operator<<(ostream &out,const Faculty &f){
        for(int i= 0 ; i<f.numOfStudents ; i++){
            out<<f.students[i]<<endl;
        }
        return out;
    }
    void reward(){
        for(int i=0 ; i<numOfStudents ; i++){
            if(students[i].avg()>9){
                cout<<students[i]<<endl;
            }
        }
    }
    void  highestAverage(){
        Student max=students[0];
        for(int i=1 ; i<numOfStudents ; i++){
            if(students[i]>max){
                max=students[i];
            }
        }
        cout<<max<<endl;
    }
};

int main(){
    Faculty f;
    for(int i=0 ; i<5 ; i++){
        char name[10];
        cin>>name;
        Student s(name);
        for(int j=0 ; j<5 ; j++){
            int n;
            cin>>n;
            s+=n;
        }
        f+=s;
    }
    f++;
    cout<<f;
    cout<<"------------------"<<endl;
    cout<<++f;
    cout<<"------------------"<<endl;
    f.reward();
    cout<<"------------------"<<endl;
    f.highestAverage();
    return 0;
}