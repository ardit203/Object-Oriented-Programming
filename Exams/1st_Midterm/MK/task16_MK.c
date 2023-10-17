#include <stdio.h>
#include <string.h>

typedef struct WorkingWeek{
    int workingHoursForEveryDay[5];
    int weekNumber;
}workingWeek;

workingWeek readWorkingWeek(){
    workingWeek wk;
    for(int i=0 ; i<5 ; i++){
        scanf("%d",&wk.workingHoursForEveryDay[i]);
    }
    return wk;
}
void printWorkingWeek(workingWeek wk){
    for(int i=0 ; i<5 ; i++){
        printf("%d ",wk.workingHoursForEveryDay[i]);
    }
    printf("\n");
}

typedef struct Worker{
    char name[50];
    workingWeek workingHoursForEveryWeek[4];
}worker;

worker readWorker(){
    worker w;
    scanf("%s",w.name);
    for(int i=0 ; i<4 ; i++){
        w.workingHoursForEveryWeek[i]=readWorkingWeek();
    }
    return w;
}
void printWorker(worker w){
    printf("%s\n",w.name);
    for(int i=0 ; i<4 ; i++){
        printWorkingWeek(w.workingHoursForEveryWeek[i]);
    }
}

int sumOfHoursForOneWeek(workingWeek wk){
    int sum=0;
    for(int i=0 ; i<5 ; i++){
        sum+=wk.workingHoursForEveryDay[i];
    }
    return sum;
}

int maxWeek(worker w){
    int d=sumOfHoursForOneWeek(w.workingHoursForEveryWeek[0]);
    int max=d;
    int maxP=1;
    for(int i=1 ; i<4 ; i++){
        int s=sumOfHoursForOneWeek(w.workingHoursForEveryWeek[i]);
        if(s > max){
            max=s;
            maxP=i+1;
        }
    }
    return maxP;
}

void work(workingWeek *w){
    int sum=0;
    for(int i=0 ; i<4 ; i++){
        printf("%d\t", sumOfHoursForOneWeek(w[i]));
        sum+= sumOfHoursForOneWeek(w[i]);
    }
    printf("%d\n",sum);
}

void table(worker *w, int n){
    printf("TABLE\n");
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(int i=0 ; i<n ; i++){
        printf("%s\t",w[i].name);
        work(w[i].workingHoursForEveryWeek);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    worker workers[100];
    for(int i=0 ; i<n ; i++){
        workers[i]=readWorker();
    }
    table(workers,n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", workers[n / 2].name);
    printf("%d\n", maxWeek(workers[n / 2]));
    //for(int i=0 ; i<n ; i++){
    //    printWorker(workers[i]);
    //}
    return 0;
}