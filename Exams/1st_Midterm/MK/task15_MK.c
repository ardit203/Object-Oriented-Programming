#include <stdio.h>
#include <string.h>

typedef struct RabotnaNedela{
    int workingHForEachDay[5];
    int numberOfTheWeek;
}RabotnaNedela;

RabotnaNedela readRabotnaNedela(){
    RabotnaNedela rn;
    for(int i=0 ; i<5 ; i++){
        scanf("%d",&rn.workingHForEachDay[i]);
    }
    return rn;
}

typedef struct Rabotnik{
    char name[50];
    RabotnaNedela RBN[4];
}Rabotnik;

Rabotnik readRabotnik(){
    Rabotnik r;
    scanf("%s",r.name);
    for(int i=0 ; i<4 ; i++){
        r.RBN[i]=readRabotnaNedela();
    }
    return r;
}

int workingHoursForOneWeek(RabotnaNedela r){
    int sum=0;
    for(int i=0 ; i<5 ; i++){
        sum+=r.workingHForEachDay[i];
    }
    return sum;
}

void maxNedela(Rabotnik *r){
    int max= workingHoursForOneWeek(r->RBN[0]);
    int index=0;
    for(int i=1 ; i<4 ; i++){
        int wk= workingHoursForOneWeek(r->RBN[i]);
        if(wk>max){
            max=wk;
            index=i+1;
        }
    }
    printf("MAX NEDELA NA RABOTNIK: %s\n%d",r->name,index);
}

int workingHForMonth(Rabotnik r){
    int sum=0;
    for(int i=0 ; i<4 ; i++){
        sum+=workingHoursForOneWeek(r.RBN[i]);
    }
    return sum;
}

void table(Rabotnik *r, int n){
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(int i=0 ; i<n ; i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",r[i].name,
               workingHoursForOneWeek(r[i].RBN[0]),
               workingHoursForOneWeek(r[i].RBN[1]),
               workingHoursForOneWeek(r[i].RBN[2]),
               workingHoursForOneWeek(r[i].RBN[3]),
               workingHForMonth(r[i]));
    }
}

int main(){
    int n;
    scanf("%d",&n);
    Rabotnik r[100];
    for(int i=0 ; i<n ; i++){
        r[i]=readRabotnik();
    }
    printf("TABLE\n");
    table(r,n);
    maxNedela(&r[n/2]);
    return 0;
}