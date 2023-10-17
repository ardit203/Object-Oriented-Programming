#include <stdio.h>
#include <string.h>
#define Max 100000



int main(){
    FILE *Exp= fopen("D:\\2nd semester\\Object Oriented Programming\\Programming\\TestCase\\Excpected","r");
    FILE *Gt= fopen("D:\\2nd semester\\Object Oriented Programming\\Programming\\TestCase\\Got","r");
    char Expected[Max];
    char Got[Max];
    char c;
    int i=0;
    while ((c=fgetc(Exp))!=EOF){
        Expected[i++]=c;
    }
    int j=0;
    while ((c=fgetc(Gt))!=EOF){
        Got[j++]=c;
    }

    int check= strcmp(Expected,Got);

    if(check==0){
        printf("**ALL GOOD**");
    } else{
        printf("--NOT GOOD--");
    }

    return 0;
}