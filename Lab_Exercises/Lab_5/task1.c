#include <stdio.h>
#include <string.h>
//printf("Best streaming service is: %s\n", services[best_index].name);
//printf("No service has movies of the given genre.\n");

typedef struct Movie{
    char title[100];
    float rating;
    char genre[40];
}Movie;

Movie readMovie(){
    Movie m;
    scanf("%s %f %s",m.title,&m.rating,m.genre);
    return m;
}

void printMovie(Movie m){
    printf("%s %.1f\n",m.title,m.rating);
}

typedef struct StreamingService{
    char name[50];
    Movie movies[30];
    int numOfMovies;
}StreamingService;

StreamingService readStreamingService(){
    StreamingService s;
    scanf("%s %d",s.name,&s.numOfMovies);
    for(int i=0 ; i<s.numOfMovies ; i++){
        s.movies[i]=readMovie();
    }
    return s;
}

void printStreamingService(StreamingService s){
    printf("%s\n",s.name);
    for(int i=0 ; i<s.numOfMovies ; i++){
        printMovie(s.movies[i]);
    }
}

int movieCount_genre(StreamingService s,char *gnr){
    int count=0;
    for(int i=0 ; i<s.numOfMovies ; i++){
        if(strcmp(s.movies[i].genre,gnr)==0){
            count++;
        }
    }
    return count;
}

void showBestStreamingService(StreamingService *s, int n, char *gnr){
    int max=-1,index=0;
    int flag=1;
    for(int i=0 ; i<n ; i++){
        if(flag==1 && movieCount_genre(s[i],gnr)>0){
            max= movieCount_genre(s[i],gnr);
            index=i;
            flag=0;
        } else if(movieCount_genre(s[i],gnr)>max){
            max= movieCount_genre(s[i],gnr);
            index=i;
        }
    }
    if(max==-1){
        printf("No service has movies of the given genre.\n");
    } else{
        printf("Best streaming service is: %s\n", s[index].name);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    StreamingService s[50];
    for(int i=0 ; i<n ; i++){
        s[i]=readStreamingService();
    }
    for(int i=0 ; i<n ; i++){
        printStreamingService(s[i]);
    }
    char genre[40];
    scanf("%s",genre);
    showBestStreamingService(s,n,genre);

    return 0;
}