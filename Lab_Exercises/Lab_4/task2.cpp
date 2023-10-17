#include <iostream>
#include <cstring>
using namespace std;

class Student{
private:
    char *name;
    int age;
    char *major;
    void copy(const Student &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->age=other.age;
        this->major=new char [strlen(other.major)+1];
        strcpy(this->major,other.major);
    }
public:

    Student(char *name="", int age=0, char *major="") {
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->age=age;
        this->major=new char [strlen(major)+1];
        strcpy(this->major,major);
    }
    Student(const Student &other){
        copy(other);
    }
    Student & operator=(const Student &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        delete [] major;
        copy(other);
        return *this;
    }
    void print(){
        cout<<name<<" ("<<age<<", "<<major<<")"<<endl;
    }
    bool cmp(char *sName){
        return strcmp(name,sName)==0;
    }
    int getAge(){
        return age;
    }
};

class Classroom{
    Student *students;
    int numOfStudents;
    int capacity;
    void copy(const Classroom &other){
        this->numOfStudents=other.numOfStudents;
        this->students=new Student [numOfStudents];
        for(int i=0 ; i<numOfStudents ; i++){
            students[i]=other.students[i];
        }
        this->capacity=other.capacity;
    }
public:
    Classroom(){
        this->numOfStudents=0;
        this->students=new Student [numOfStudents];
        this->capacity=0;
    }
    Classroom(Student *students, int numOfStudents, int capacity){
        this->numOfStudents=numOfStudents;
        this->students=new Student [this->numOfStudents];
        for(int i=0 ; i<this->numOfStudents ; i++){
            this->students[i]=students[i];
        }
        this->capacity=capacity;
    }
    Classroom(const Classroom &other){
        copy(other);
    }
    Classroom &operator=(const Classroom &other){
        if(this==&other){
            return *this;
        }
        delete [] students;
        copy(other);
        return *this;
    }

    void printStudents() {
        for(int i=0 ; i<numOfStudents ; i++){
            students[i].print();
        }
        cout<<endl;
    }

    void add(Student &s) {
        Student *tmp=new Student [numOfStudents+1];
        for(int i=0 ; i<numOfStudents ; i++){
            tmp[i]=students[i];
        }
        delete [] students;
        tmp[numOfStudents]=s;
        students=tmp;
        numOfStudents++;
    }

    void remove(char *sName) {
        Student *tmp=new Student [numOfStudents];
        int j=0;
        for(int i=0 ; i<numOfStudents ; i++){
            if(!students[i].cmp(sName)){
                tmp[j++]=students[i];
            }
        }
        delete [] students;
        students=tmp;
        numOfStudents=j;
    }
    void bubbleSort(){
        for(int i=0 ; i<numOfStudents ; i++){
            for(int j=0 ; j<numOfStudents ; j++){
                if(students[j].getAge()>students[j+1].getAge()){
                    Student tmp=students[j];
                    students[j]=students[j+1];
                    students[j+1]=tmp;
                }
            }
        }
    }
    int getNumOfStudents(){
        return numOfStudents;
    }
    Student getStudent(int i){
        return students[i];
    }
};

double findMedianAge(Classroom classroom){
    double ages[100];
    int k=0;
    for(int i=0 ; i<classroom.getNumOfStudents() ; i++){
        ages[k++]=classroom.getStudent(i).getAge();
    }
    if(k%2==0){
        double median=(ages[k/2-1]+ages[k/2])/2;
        return median;
    } else{
        double median=ages[k/2];
        return median;
    }
}

int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i*numStudents + j] = student;
        }
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;
    cout<<"After removing the elements:"<<endl; // Added
    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }

    return 0;
}

