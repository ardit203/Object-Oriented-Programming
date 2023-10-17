#include <stdio.h>
#include <string.h>

typedef struct Tanc{
    char name[15];
    char origin[15];
}Tanc;

Tanc readTanc(){
    Tanc t;
    scanf("%s %s",t.name,t.origin);
    return t;
}

void printTanc(Tanc t){
    printf("%s\n",t.name);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Tancer{
    char name[20];
    char surname[20];
    Tanc tancs[3];
}Tancer;

Tancer readTancer(){
    Tancer t;
    scanf("%s %s",t.name,t.surname);
    for(int i=0 ; i<3 ; i++){
        t.tancs[i]=readTanc();
    }
    return t;
}

void printTancer(Tancer t){
    printf("%s %s, ",t.name,t.surname);
}

void tancuvanje(Tancer *t, int n, char *zemja){
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<3 ; j++){
            if(strcmp(t[i].tancs[j].origin,zemja)==0){
                printTancer(t[i]);
                printTanc(t[i].tancs[j]);
                break;
            }
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    Tancer t[100];
    for(int i=0 ; i<n ; i++){
        t[i]=readTancer();
    }
//    for(int i=0 ; i<n ; i++){
//        printTancer(t[i]);
//        printf("\n");
//    }
    char origin[15];
    scanf("%s",origin);
    tancuvanje(t,n,origin);
    return 0;
}