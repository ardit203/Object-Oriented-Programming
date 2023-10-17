#include <stdio.h>
#include <string.h>

typedef struct Proizvod{
    char code[20];
    int price;
    int availableProducts;
}Proizvod;

Proizvod readProizvod(){
    Proizvod p;
    scanf("%s %d %d",p.code,&p.price,&p.availableProducts);
    return p;
}


///////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct Narachka{
    char name[15];
    Proizvod products[10];
    int orderedProducts[10];
    int n;
}Narachka;

Narachka readNarachka(){
    Narachka n;
    scanf("%s %d",n.name,&n.n);
    for(int i=0 ; i<n.n ; i++){
        n.products[i]=readProizvod();
    }
    for(int i=0 ; i<n.n ; i++){
        scanf("%d",&n.orderedProducts[i]);
    }
    return n;
}

void sortProductsByCode(Proizvod products[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(products[j].code, products[j + 1].code) > 0) {
                Proizvod temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

void pecatiFaktura(Narachka n){
    printf("Faktura za %s\n",n.name);
    int flag=1;
    for(int i=0 ; i<n.n ; i++){
        if(n.products[i].availableProducts-n.orderedProducts[i]<0){
            flag=0;
        }
    }
    if(flag){
        sortProductsByCode(n.products,n.n);
        int sum=0;
        for(int i=0 ; i<n.n ; i++){
            sum+=n.products[i].price*n.orderedProducts[i];
            printf("%s %d %d %d\n",n.products[i].code,n.products[i].price,n.orderedProducts[i],n.products[i].price*n.orderedProducts[i]);
        }
        printf("Vkupnata suma na fakturata e %d",sum);
    } else{
        printf("Fakturata ne moze da se izgotvi");
    }
}

int main(){
    Narachka n;
    n=readNarachka();
    pecatiFaktura(n);
    return 0;
}

