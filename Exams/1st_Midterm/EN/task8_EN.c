#include <stdio.h>

typedef struct Driver{
    char name[100];
    int time;
}driver;

driver readDriver(){
    driver d;
    scanf("%s %d",d.name,&d.time);
    return d;
}

typedef struct Race{
    char location[100];
    int nDrivers;
    driver drivers[100];
}race;

race readRace(){
    race r;
    scanf("%s %d",r.location,&r.nDrivers);
    for(int i=0 ; i<r.nDrivers ; i++){
        r.drivers[i]=readDriver();
    }
    return r;
}

int driverscmp(driver d1, driver d2){
    return d1.time>d2.time;
}

void sort(driver *d, int n){
    for(int i= 0 ; i<n ; i++){
        for(int j=0 ; j<n-1-i ; j++){
            if(driverscmp(d[j],d[j+1])){
                driver tmp=d[j];
                d[j]=d[j+1];
                d[j+1]=tmp;
            }
        }
    }
}

void top3(race *race) {
    sort(race->drivers,race->nDrivers);
    for(int i=0 ; i<3 ; i++){
        int time=race->drivers[i].time;
        int min=time/60;
        int sec=time%60;
        printf("%d. %s %2d:%.2d\n",i+1,race->drivers[i].name,min,sec);
    }

}

int main() {
    int n;
    scanf("%d", &n);
    race races[100];
    for(int i=0 ; i<n ; i++){
        races[i]=readRace();
    }
    for(int i=0 ; i<n ; i++){
        printf("%s (%d Drivers)\n", races[i].location, races[i].nDrivers);
        top3(races+i);
    }
    return 0;
}
