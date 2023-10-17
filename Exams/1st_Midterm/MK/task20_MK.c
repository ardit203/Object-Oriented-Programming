#include <stdio.h>

typedef struct Pacient{
    char name_surname[100];
    int insurance;
    int numOfViews;
}Pacient;

Pacient readPacient(){
    Pacient p;
    scanf("%s %d %d",p.name_surname,&p.insurance,&p.numOfViews);
    return p;
}

void printPacient(Pacient p){
    printf("%s %d %d\n",p.name_surname,p.insurance,p.numOfViews);
}

typedef struct MaticenDoktor{
    char name[100];
    int numOfPacients;
    Pacient pacients[200];
    float price;
}MaticenDoktor;

MaticenDoktor readMaticenDoktor(){
    MaticenDoktor d;
    scanf("%s %d %f",d.name,&d.numOfPacients,&d.price);
    for(int i=0 ; i<d.numOfPacients ; i++){
        d.pacients[i]=readPacient();
    }
    return d;
}

void printMaticenDoktor(MaticenDoktor d){
    printf("%s\n%d\n%.2f\n",d.name,d.numOfPacients,d.price);
    for(int i=0 ; i<d.numOfPacients ; i++){
        printPacient(d.pacients[i]);
    }
}

float notInsurance(MaticenDoktor d){
    float sum=0;
    for(int i=0 ; i<d.numOfPacients ; i++){
        if(d.pacients[i].insurance==0){
            sum+=(float )d.price*d.pacients[i].numOfViews;
        }
    }
    return sum;
}

int numOfExaminations(MaticenDoktor d){
    int sum=0;
    for(int i=0 ; i<d.numOfPacients ; i++){
            sum+=d.pacients[i].numOfViews;
    }
    return sum;
}

int mdCMP(MaticenDoktor d1, MaticenDoktor d2){
    if(notInsurance(d1)> notInsurance(d2)){
        return 1;
    } else if(notInsurance(d1)< notInsurance(d2)){
        return -1;
    } else{
        return numOfExaminations(d1)> numOfExaminations(d2);
    }
}

void najuspesen_doktor(MaticenDoktor *md, int n){
    MaticenDoktor max=md[0];
    for(int i=1 ; i<n ; i++){
        if(mdCMP(md[i],max)==1){
            max=md[i];
        }
    }
    printf("%s %.2f %d",max.name, notInsurance(max), numOfExaminations(max));
}

int main(){
    int n;
    scanf("%d",&n);
    MaticenDoktor md[100];
    for(int i=0 ; i<n ; i++){
        md[i]=readMaticenDoktor();
    }
    najuspesen_doktor(md,n);
    return 0;
}