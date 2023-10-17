#include <stdio.h>
#define MAX 100

//Create struct transaction
typedef struct Transaction{
    int ID;
    int amount;
    int commissions;
    int debit_credit;
}transaction;

//Function for reading the transaction
transaction readTransaction(){
    transaction t;
    scanf("%d %d %d %d",&t.ID,&t.amount,&t.commissions,&t.debit_credit);
    return t;
}

int main(){
    int n;
    scanf("%d",&n);
    transaction transactions[MAX];
    for(int i=0 ; i<n ; i++){
        transactions[i]=readTransaction();
    }
    int flag=1;//We reaise the flag
    for(int i=0 ; i<n ; i++){
        if(transactions[i].debit_credit==0){
            continue;
        }
        flag=0;//If we find one transaction that is paid with credit card then we lower the flag
        printf("%d %d\n",transactions[i].ID,transactions[i].amount+transactions[i].commissions);
    }
    if(flag){//If the flag is up then we print otherwise no!
        printf("No credit card transaction");
    }
    return 0;
}