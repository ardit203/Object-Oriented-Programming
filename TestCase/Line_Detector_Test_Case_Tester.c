#include <stdio.h>
#include <string.h>
#define Max 500

void cleanSTR(char *str1, char *str2){
    if(str1[strlen(str1)-1]=='\n'){
        str1[strlen(str1)-1]='\0';
    }
    if(str2[strlen(str2)-1]=='\n'){
        str2[strlen(str2)-1]='\0';
    }
}

int main(){
    FILE *Exp= fopen("D:\\2nd semester\\Object Oriented Programming\\Programming\\TestCase\\Excpected","r");
    FILE *Gt= fopen("D:\\2nd semester\\Object Oriented Programming\\Programming\\TestCase\\Got","r");
    char Expected[Max];
    char Got[Max];
    int flag=1;
    int i=1;
    char EXX[100];
    char GTT[100];
    while ((fgets(Expected,Max,Exp)!=NULL) && (fgets(Got,Max,Gt)!=NULL)){
        if(strcmp(Expected,Got)!=0){
            strcpy(EXX,Expected);
            strcpy(GTT,Got);
            flag=0;
            break;
        }
        i++;
    }
    if(flag){
        printf("**ALL GOOD**");
    } else{
        printf("--NOT GOOD--\nLine: %d\n",i);
        cleanSTR(EXX,GTT);
        printf("%s  --  %s",EXX,GTT);
    }
    fclose(Exp);
    fclose(Gt);
    return 0;
}