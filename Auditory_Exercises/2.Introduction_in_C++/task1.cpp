#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

struct student{
    char name[20];
    char surname[20];
    char index[6];
    int points[4];
    void readStudent(){
        cin>>name>>surname>>index;
        for(int i=0 ; i<4 ; i++){
            cin>>points[i];
        }
    }
    void Normalize(char *str){
        str[0]= toupper(str[0]);
        for(int i=1 ; i< strlen(str) ; i++){
            str[i]= tolower(str[i]);
        }
    }
    int totalPoints(){
        int sum=0;
        for(int i=0 ; i<4 ; i++){
            sum+=points[i];
        }
        return sum;
    }
    int grade(){
        int p=totalPoints();
        int gr=p/10+1;
        if(gr<5){
            gr=5;
        }
        if(gr>10){
            gr=10;
        }
        return gr;
    }
    void printStudent(){
        Normalize(name);
        Normalize(surname);
        int p=totalPoints();
        int g=grade();
        cout<<name<<" "<<surname<<" "<<index<<" "<<p<<" "<<g<<endl;
    }
    int studentCmp(student other){
        return grade()<=other.grade();
    }
};
void swap(student &s1, student &s2){
    student tmp=s1;
    s1=s2;
    s2=tmp;
}
void sort(student *s, int n){
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n-1-i ; j++){
            if(s[j].studentCmp(s[j+1])){
                //student tmp=s[j];
                //s[j]=s[j+1];
                //s[j+1]=tmp;
                swap(s[j],s[j+1]);
            }
        }
    }
}

int main(){
    int n;
    cin>>n;
    student students[100];
    for(int i=0 ; i<n ; i++){
        students[i].readStudent();
    }
    sort(students,n);
    for(int i=0 ; i<n ; i++){
        students[i].printStudent();
    }
    return 0;
}
