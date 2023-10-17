#include <stdio.h>

typedef struct Date{
    int day,month,year;
}date;

date readDate(){
    date date;
    scanf("%d.%d.%d",&date.day,&date.month,&date.year);
    return date;
}

void printDate(date date){
    printf("%.2d.%.2d.%.2d",date.day,date.month,date.year);
}

int compare(int int1, int int2){
    if(int1>int2){
        return 1;
    } else if(int2>int1){
        return -1;
    } else{
        return 0;
    }
}

int datecmp(date date1, date date2){
    int cmpYear= compare(date1.year,date2.year);
    if(cmpYear!=0){
        return cmpYear;
    } else{
        int cmpMonth= compare(date1.month,date2.month);
        if(cmpMonth!=0){
            return cmpMonth;
        } else{
            return compare(date1.day,date2.day);
        }
    }
}

int days(date date1, date date2){
    int days=date1.day-date2.day;
    days+=(date1.month-date2.month)*30;
    days+=(date1.year-date2.year)*365;
    return days;
}

int main(){
    date date1=readDate();
    date date2=readDate();
    if(datecmp(date1,date2)==0){
        printf("The dates are equal");
        return 0;
    }
    if(datecmp(date1,date2)==1){
        printDate(date1);
        printf(" is greater than ");
        printDate(date2);
        printf(" by %d days.", days(date1,date2));
    } else{
        printDate(date2);
        printf(" is greater than ");
        printDate(date1);
        printf(" by %d days.", days(date2,date1));
    }
    return 0;
}
