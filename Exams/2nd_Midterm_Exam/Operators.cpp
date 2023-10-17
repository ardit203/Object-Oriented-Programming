#include<iostream>
#include<cstring>

using namespace std;

class Student{
private:
    char *name;
    char index[7]; // 221555 6 + 1 null terminator
    int *grades;
    int numberOfGrades; //How many grades
    int year;
    void copy(const Student &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        strcpy(this->index,other.index);
        this->numberOfGrades=other.numberOfGrades;
        this->grades=new int [this->numberOfGrades];
        for(int i=0 ; i<this->numberOfGrades ; i++){
            this->grades[i]=other.grades[i];
        }
        this->year=other.year;
    }
public:
    Student(char *name="Noname", char *index="000000", int year=1){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->index,index);
        this->numberOfGrades=0;
        this->grades=new int [numberOfGrades];
        this->year=year;
    }
    Student(const Student &other){
        copy(other);
    }
    ~Student(){
        delete [] name;
        delete [] grades;
    }
    float averageGrade(){
        if(numberOfGrades==0){
            return 5;
        }
        float sum=0;
        for(int i=0 ; i<numberOfGrades ; i++){
            sum+=grades[i];
        }
        return sum/numberOfGrades;
    }

    //Operator =
    Student &operator=(const Student &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        delete [] grades;
        copy(other);
        return *this;
    }

    //Operator +=
    Student &operator+=(int ocenka){// add a ocenka
        int *tmp=new int [numberOfGrades+1];
        for(int i=0 ; i<numberOfGrades ; i++){
            tmp[i]=grades[i];
        }
        delete [] grades;

        tmp[numberOfGrades]=ocenka;
        numberOfGrades++;
        grades=tmp;
        return *this;
    }

    //Operator <<
    friend ostream &operator<<(ostream &out, Student s){
        out<<s.name<<" "<<s.index<<" "<<s.year<<endl;
        for(int i=0 ; i<s.numberOfGrades ; i++){
            out<<s.grades[i]<<" ";
        }
        return out;
    }

    //Operator >>
    friend istream &operator>>(istream &in, Student &s){
        in>>s.name>>s.index>>s.year>>s.numberOfGrades;
        for(int i=0 ; i<s.numberOfGrades ; i++){
            in>>s.grades[i];
        }
        return in;
    }

    //Operator []
    int &operator [](int i){
        return grades[i];
    }

    //Operator ==
    bool operator==(Student &s){// if same index
        return strcmp(index,s.index)==0;
    }

    //Operator >
    bool operator >(Student &s){
        return averageGrade()>s.averageGrade();
    }

    //Operator ++ prefix (ex: ++a)
    Student &operator++(){// increment year
        ++year;
        return *this;
    }

    //Operator ++ postfix (ex: a++)
    Student operator++(int){// increment year
        Student ARDIT(*this);// copy constructor
        ++year;
        return ARDIT;
    }

    Student &operator--(){
        --year;
        return *this;
    }

    Student operator--(int){
        Student ARDIT(*this);// copy constructor
        --year;
        return ARDIT;
    }
    char *getName(){
        return name;
    }
    char *getIndex(){
        return index;
    }

};

int main(){
    cout<<"++ DEFAULT CONSTRUCTOR ++"<<endl;
    Student s1,s2,s3;
    cout<<s1<<endl;
    cout<<endl;

    cout<<"==============================================================================="<<endl;
    cout<<"++ OPERATOR >> ++"<<endl;
    cin>>s1>>s2>>s3;

    cout<<"==============================================================================="<<endl;
    cout<<"++ OPERATOR << ++"<<endl;
    cout<<s1<<endl<<endl;
    cout<<s2<<endl<<endl;
    cout<<s3<<endl<<endl;

    cout<<"==============================================================================="<<endl;
    cout<<"++ OPERATOR = ++"<<endl;
    Student x;
    cout<<x<<endl;
    cout<<s1<<endl<<endl;
    x=s1;
    cout<<x<<endl<<endl;
    cout<<s1<<endl<<endl;

    cout<<"==============================================================================="<<endl;
    cout<<"++ OPERATOR += ++"<<endl;
    cout<<s1<<endl<<endl;
    s1+=8;
    cout<<s1<<endl<<endl;

    cout<<s2<<endl<<endl;
    s2+=6;
    s2+=10;
    cout<<s2<<endl<<endl;

    cout<<s3<<endl<<endl;
    s3+=9;
    s3+=7;
    cout<<s3<<endl<<endl;

    cout<<"==============================================================================="<<endl;
    cout<<"++ OPERATOR [] ++"<<endl;
    cout<<s1<<endl;
    cout<<"The grade that is at position with index 1 is: "<<s1[1]<<endl<<endl;
    cout<<s2<<endl;
    cout<<"The grade that is at position with index 3 is: "<<s2[3]<<endl<<endl;
    cout<<s3<<endl;
    cout<<"The grade that is at position with index 4 is: "<<s3[4]<<endl<<endl;

    cout<<"==============================================================================="<<endl;
    cout<<"++ OPERATOR == ++"<<endl;
    cout<<s1<<endl<<endl;
    cout<<s2<<endl<<endl;
    cout<<s3<<endl<<endl;
    if(s1==s2){
        cout<<s1.getName()<<" "<<s1.getIndex()<<" == "<<s2.getName()<<" "<<s2.getIndex()<<endl;
    } else{
        cout<<s1.getName()<<" "<<s1.getIndex()<<" != "<<s2.getName()<<" "<<s2.getIndex()<<endl;
    }
    if(s1==s3){
        cout<<s1.getName()<<" "<<s1.getIndex()<<" == "<<s3.getName()<<" "<<s3.getIndex()<<endl;
    } else{
        cout<<s1.getName()<<" "<<s1.getIndex()<<" != "<<s3.getName()<<" "<<s3.getIndex()<<endl;
    }
    cout<<endl;

    cout<<"==============================================================================="<<endl;
    cout<<"++ OPERATOR > ++"<<endl;
    cout<<s1<<endl<<endl;
    cout<<s2<<endl<<endl;
    cout<<"Student with name: "<<s1.getName()<<" and index number: "<<s1.getIndex()<<" has an average grade of: "<<s1.averageGrade()<<endl;
    cout<<"Student with name: "<<s2.getName()<<" and index number: "<<s2.getIndex()<<" has an average grade of: "<<s2.averageGrade()<<endl;
    if(s1>s2){
        cout<<s1.averageGrade()<<" > "<<s2.averageGrade()<<endl;
    } else{
        cout<<s2.averageGrade()<<" > "<<s1.averageGrade()<<endl;
    }
    cout<<endl;

    cout<<"==============================================================================="<<endl;
    cout<<"++ OPERATOR ++ ++"<<endl;
    cout<<s1<<endl<<endl;
    cout<<s1++<<endl<<endl;
    cout<<s1<<endl<<endl;
    cout<<++s1<<endl<<endl;

    cout<<"==============================================================================="<<endl;
    cout<<"++ OPERATOR -- ++"<<endl;
    cout<<s1<<endl<<endl;
    cout<<s1--<<endl<<endl;
    cout<<s1<<endl<<endl;
    cout<<--s1<<endl<<endl;


    return 0;
}


    /*
     Input:
     Ardit 221555 1 5 6 7 8 9 10
     Hamdi 221589 1 4 6 8 7 6
     Sabri 221555 1 6 6 8 8 8 9 10
     */