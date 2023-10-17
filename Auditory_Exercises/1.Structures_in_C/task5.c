#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct student{
    char name[20];
    char surname[20];
    char index[7];
    int points[4];
}student;

student readStudent(){
    student s;
    scanf("%s %s %s",s.name,s.surname,s.index);
    for(int i=0 ; i<4 ; i++){
        scanf("%d",&s.points[i]);
    }
    return s;
}

void nameSurname(char *name,char *surname){
    name[0]= toupper(name[0]);
    for(int i=1; i< strlen(name) ; i++){
        name[i]= tolower(name[i]);
    }
    surname[0]= toupper(surname[0]);
    for(int i=1; i< strlen(surname) ; i++){
        surname[i]= tolower(surname[i]);
    }
}

int totalPoints(student s){
    int sum=0;
    for(int i=0 ; i<4 ; i++){
        sum+=s.points[i];
    }
    return sum;
}

int grade(int points){
    int grade=points/10+1;
    if (grade > 10) {
        grade = 10;
    }
    if (grade < 5) {
        grade = 5;
    }
    return grade;
}

int studentcmp(student s1, student s2){
    if(totalPoints(s1)> totalPoints(s2)){
        return 1;
    } else if(totalPoints(s1)< totalPoints(s2)){
        return -1;
    } else{
        return 0;
    }
}

void swap(student *s1, student *s2){
    student tmp=*s1;
    *s1=*s2;
    *s2=tmp;
}

void bubbleSort(student s[], int n){
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n-1-i ; j++){
            if(studentcmp(s[j],s[j+1])==-1){
                swap(&s[j],&s[j+1]);
            }
        }
    }
}

void printStudent(student s){
    int points= totalPoints(s);
    int gr= grade(points);
    nameSurname(s.name,s.surname);
    printf("Name: %s, Surname: %s, Index: %s, Points: %d, Grade: %d\n",s.name,s.surname,s.index,points,gr);
}

int main(){
    int n;
    student STUDENTS[100];
    scanf("%d",&n);
    for(int i=0 ; i<n ; i++){
        STUDENTS[i]=readStudent();
    }
    bubbleSort(STUDENTS,n);
    for(int i=0 ; i<n ; i++){
        printStudent(STUDENTS[i]);
    }
    return 0;
}
