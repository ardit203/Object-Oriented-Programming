#include <stdio.h>
#include <string.h>

typedef struct Transaction{
    int day,month,year;
    int amount;
    char currency[3];
}transaction;

transaction readTransaction(){
    transaction t;
    scanf("%d/%d/%d %d %s",&t.day,&t.month,&t.year,&t.amount,t.currency);
    return t;
}

void printTransaction(transaction t){
    printf("%.2d/%.2d/%d %d %s\n",t.day,t.month,t.year,t.amount,t.currency);
}

int main(){
    int n;
    scanf("%d",&n);
    transaction trsc[500];
    for(int i=0 ; i<n ; i++){
        trsc[i]=readTransaction();
    }
    int sum=0;
    int k=1;
    for(int i=0 ; i<n ; i++){
        if(strcmp(trsc[i].currency,"MKD")==0 && trsc[i].amount>1000 && trsc[i].year>=2013 && trsc[i].year<=2015){
            printf("%d. ",k);
            printTransaction(trsc[i]);
            sum+=trsc[i].amount;
            k++;
        }
    }
    printf("Total: %d MKD",sum);
    return 0;
}
