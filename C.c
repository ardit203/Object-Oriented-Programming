#include <stdio.h>
#include <string.h>
#define MAX 100

//ne menuvaj!
void wtf() {
    FILE *f = fopen("numbers.txt", "w");
    char c;
    while((c = getchar()) != EOF) {
        fputc(c, f);
    }
    fclose(f);
}

int countOfDigits(int n){
    int count=1;
    while (n){
        count*=10;
        n/=10;
    }
    count/=10;
    return count;
}

int largestNumber(int *a, int n){
    int maxNum=a[0], maxDigit=a[0]/ countOfDigits(a[0]);
    for(int i=1 ; i<n ; i++){
        int c= countOfDigits(a[i]);
        if(a[i]/c>maxDigit){
            maxNum=a[i];
            maxDigit=a[i]/c;
        }
    }
    return maxNum;
}

int main(){
    wtf();
    FILE *f= fopen("numbers.txt","r");

    for(int i=0 ;; i++){
        int n;
        fscanf(f,"%d",&n);
        if(n==0){
            break;
        }
        int array[100];
        for(int j=0 ; j<n ; j++){
            fscanf(f,"%d",&array[j]);
        }
        printf("%d\n", largestNumber(array,n));
    }
    return 0;
}