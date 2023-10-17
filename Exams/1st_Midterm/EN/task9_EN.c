#include <stdio.h>

typedef struct Film{
    char title[100];
    int duration;
    float price;
    int student_discount;
}film;

film readFilm(){
    film f;
    scanf("%s %d %f %d",f.title,&f.duration,&f.price,&f.student_discount);
    return f;
}

void printFilm(film f){
    printf("%s %d %.2f\n",f.title,f.duration,f.price);
}

typedef struct FilmFestival{
    char name[100];
    char place[100];
    film listOfFilms[100];
    int numberOfFilms;
}filmFestival;

filmFestival readFilmFestival(){
    filmFestival ff;
    scanf("%s %s %d",ff.name,ff.place,&ff.numberOfFilms);
    for(int i=0 ; i<ff.numberOfFilms ; i++){
        ff.listOfFilms[i]=readFilm();
    }
    return ff;
}

void print(filmFestival ff){
    printf("%s %s\n",ff.name,ff.place);
    for(int i=0 ; i<ff.numberOfFilms ; i++){
        printFilm(ff.listOfFilms[i]);
    }
}

int compare(int n1, int n2){
    if(n1>n2){
        return 1;
    } else if(n1<n2){
        return -1;
    } else{
        return 0;
    }
}

int student_discount(filmFestival ff){
    int sum=0;
    for(int i=0 ; i<ff.numberOfFilms ; i++){
        if(ff.listOfFilms[i].student_discount==1){
            sum++;
        }
    }
    return sum;
}

int duration(filmFestival ff){
    int sum=0;
    for(int i=0 ; i<ff.numberOfFilms ; i++){
        sum+=ff.listOfFilms[i].duration;
    }
    return sum;
}

void bestFestival(filmFestival *ff,int n){
    filmFestival bestFilmFestival=ff[0];
    for(int i=1 ; i<n ; i++){
        if(compare(student_discount(ff[i]), student_discount(bestFilmFestival))==1){
            bestFilmFestival=ff[i];
        } else if(compare(student_discount(ff[i]), student_discount(bestFilmFestival))==0 && compare(duration(ff[i]),duration(bestFilmFestival))==1){
            bestFilmFestival=ff[i];
        }
    }
    printf("Najdobar festival: %s %s",bestFilmFestival.name,bestFilmFestival.place);
}

int main(){
    int n;
    filmFestival ff[50];
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        ff[i]=readFilmFestival();
    }

    for(int i=0; i<n; i++){
        print(ff[i]);
    }

    bestFestival(ff, n);
    return 0;
}
