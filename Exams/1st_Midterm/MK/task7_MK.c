#include <stdio.h>

typedef struct Ride{
    char name[100];
    int duration;
    float price;
    int student_discount;
}ride;

ride readRide(){
    ride r;
    scanf("%s %d %f %d",r.name,&r.duration,&r.price,&r.student_discount);
    return r;
}
void printRide(ride r){
    printf("%s %d %.2f\n",r.name,r.duration,r.price);
}

typedef struct AmusementPark{
    char name[100];
    char location[100];
    ride rides[100];
    int number_rides;
}amusementPark;

amusementPark readAmusementPark(){
    amusementPark ap;
    scanf("%s %s %d",ap.name,ap.location,&ap.number_rides);
    for(int i=0 ; i<ap.number_rides ; i++){
        ap.rides[i]=readRide();
    }
    return ap;
}

void printAMP(amusementPark ap){
    printf("%s %s\n",ap.name,ap.location);
    for(int i=0 ; i<ap.number_rides ; i++){
        printRide(ap.rides[i]);
    }
}
int studentDiscount(amusementPark ap){
    int sum=0;
    for(int i=0 ; i<ap.number_rides ; i++){
        if(ap.rides[i].student_discount==1){
            sum++;
        }
    }
    return sum;
}

int duration(amusementPark ap){
    int sum=0;
    for(int i=0 ; i<ap.number_rides ; i++){
        sum+=ap.rides[i].duration;
    }
    return sum;
}

int AMPcmp(amusementPark ap1, amusementPark ap2){
    if(studentDiscount(ap1)> studentDiscount(ap2)){
        return 1;
    } else if(studentDiscount(ap1)== studentDiscount(ap2)){
        return duration(ap1)> duration(ap2);
    }
}

void best_park(amusementPark *ap, int n){
    amusementPark bestPark=ap[0];
    for(int i=1 ; i<n ; i++){
        if(AMPcmp(ap[i],bestPark)==1){
            bestPark=ap[i];
        }
    }
    printf("Najdobar park: %s %s\n",bestPark.name,bestPark.location);
}


int main(){
    int n;
    scanf("%d",&n);
    amusementPark ap[100];
    for(int i=0 ; i<n ; i++){
        ap[i]=readAmusementPark();
    }
    for(int i=0 ; i<n ; i++){
        printAMP(ap[i]);
    }
    best_park(ap,n);
    return 0;
}
