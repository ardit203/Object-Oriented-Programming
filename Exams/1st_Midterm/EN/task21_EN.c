#include<stdio.h>
#include<string.h>

typedef struct SkiLift{
    char name[15];
    int capacity;
    int available;
}skiLift;

skiLift readSkiLift(){
    skiLift s;
    scanf("%s%d%d",s.name,&s.capacity,&s.available);
    return s;
}

void printSkilift(skiLift s){
    printf("%s\n%d\n%d\n",s.name,s.capacity,s.available);
}

typedef struct SkiCenter{
    char name[20];
    char country[20];
    skiLift skiLifts[20];
    int count;
}skiCenter;

skiCenter readSkiCenter(){
    skiCenter sc;
    scanf("%s%s%d",sc.name,sc.country,&sc.count);
    for(int i=0 ; i<sc.count ; i++){
        sc.skiLifts[i]=readSkiLift();
    }
    return sc;
}

void printSkicenter(skiCenter sc){
    printf("%s\n%s\n%d\n",sc.name,sc.country,sc.count);
    for(int i=0 ; i<sc.count ; i++){
        printSkilift(sc.skiLifts[i]);
    }
}

int capacity(skiCenter sc){
    int sum=0;
    for(int i=0 ; i<sc.count ; i++){
        if(sc.skiLifts[i].available==1){
            sum+=sc.skiLifts[i].capacity;
        }
    }
    return sum;
}

int compare(skiCenter s, skiCenter max){
    if(capacity(s) > capacity(max)){
        return 1;
    }else if(capacity(s) < capacity(max)){
        return -1;
    } else{
        if(s.count > max.count){
            return 1;
        } else if(s.count < max.count){
            return -1;
        } else{
            return 0;
        }
    }
}

void biggestCapacity(skiCenter *sc, int n){
    skiCenter max=sc[0];
    for(int i=1 ; i<n ; i++){
        if(compare(sc[i],max)==1){
            max=sc[i];
        }
    }
    printf("%s\n%s\n%d",max.name,max.country, capacity(max));
}

int main(){
    int n;
    scanf("%d", &n);
    skiCenter sc[100];
    for (int i = 0; i < n; i++){
        sc[i]=readSkiCenter();
    }
    biggestCapacity(sc,n);
    return 0;
}
