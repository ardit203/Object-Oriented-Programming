#include <stdio.h>

typedef struct City{
    char name[20];
    int population;
}capital;

void printCapital(capital c){
    printf("%s %d ",c.name,c.population);
}

typedef struct President{
    char name[20], party[10];
}president;

void printPresident(president p){
    printf("%s %s ",p.name,p.party);
}

typedef struct Country{
    char name[20];
    president president;
    capital capital;
    int population;
}country;

void printCountry(country c){
    printf("%s ",c.name);
    printPresident(c.president);
    printCapital(c.capital);
    printf("%d\n",c.population);
}

capital readCapital(){
    capital c;
    scanf("%s %d",c.name,&c.population);
    return c;
}

president readPresident(){
    president p;
    scanf("%s %s",p.name,p.party);
    return p;
}

country readCountry(){
    country country;
    scanf("%s",&country.name);
    country.president=readPresident();
    country.capital=readCapital();
    scanf("%d",&country.population);
    return country;
}

int countryCmp(country c1, country c2){
    return c1.capital.population>c2.capital.population;
}

void printMax(country max){
    printf("%s",max.president.nameOfInvestitor);
}

int main(){
    int n;
    scanf("%d",&n);
    int flag=1;
    country max;
    for(int i=0 ; i<n ; i++){
        country COUNTRY=readCountry();
        printCountry(COUNTRY);
        if(flag){
            max=COUNTRY;
            flag=0;
        } else if(countryCmp(COUNTRY,max)==1){
            max=COUNTRY;
        }
    }
    printf("The president of the country whose capital has largest population: ");
    printMax(max);
    //printf("%s",max.president.name);
    return 0;
}
