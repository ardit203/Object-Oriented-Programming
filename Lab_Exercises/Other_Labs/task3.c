#include <stdio.h>

typedef struct product{
    char name[20];
    float price;
    int quantity;
}product;

product readProduct(){
    product p;
    scanf("%s %f %d",p.name,&p.price,&p.quantity);
    return p;
}

void printProduct(product p){
    printf("%s\t%.2f x %d = %.2f\n",p.name,p.price,p.quantity,p.price*p.quantity);
}

int main(){
    int n;
    scanf("%d",&n);
    product products[100];
    for(int i=0 ; i<n ; i++){
        products[i]=readProduct();
    }
    float total=0;
    for(int i=0 ; i<n ; i++){
        printf("%d. ",i+1);
        printProduct(products[i]);
        total+=products[i].price*products[i].quantity;
    }
    printf("Total: %.2f",total);
    return 0;
}