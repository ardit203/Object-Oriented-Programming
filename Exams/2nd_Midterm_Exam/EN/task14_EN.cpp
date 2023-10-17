#include<iostream>
#include<string.h>
using namespace std;


//class RatingMissingException{
//public:
//    RatingMissingException(){}
//    void show(){
//
//    }
//};


//==============================================================================================//

class Person {
private:
    char name[20];
    int year;
public:
    Person (char *name, int year) {
        strcpy(this->name, name);
        this->year = year;
    }
    Person () {
        strcpy(this->name, "");
    }
    bool operator==(char *name) {
        return strcmp(this->name, name) == 0;
    }
    char const * getName() {
        return name;
    }
    void print() {cout << name << " (" << year << ")";}
};


//=========================================================================================//



class Song {
private:
    Person performers[10];
    int numberPerformers;
    int *ratings;
    int numberRatings;

protected:
    char title[30];

public:
    Song(char *title, Person *performers, int numberPerformers, int *ratings, int numberRatings) {
        strcpy(this->title, title);
        this->numberPerformers = numberPerformers;
        for (int i = 0; i < numberPerformers; i++) this->performers[i] = performers[i];
        this->numberRatings = numberRatings;
        this->ratings = new int[numberRatings];
        for (int i = 0; i < numberRatings; i++) this->ratings[i] = ratings[i];

    }
    Song(const Song &k) {
        strcpy(this->title, k.title);
        this->numberPerformers = k.numberPerformers;
        for (int i = 0; i < k.numberPerformers; i++) this->performers[i] = k.performers[i];
        this->numberRatings = k.numberRatings;
        this->ratings = new int[k.numberRatings];
        for (int i = 0; i < k.numberRatings; i++) this->ratings[i] = k.ratings[i];

    }
    Song operator=(const Song &k) {
        if (&k == this) return *this;
        strcpy(this->title, k.title);
        this->numberPerformers = k.numberPerformers;
        for (int i = 0; i < k.numberPerformers; i++) this->performers[i] = k.performers[i];
        this->numberRatings = k.numberRatings;
        delete [] ratings;
        this->ratings = new int[k.numberRatings];
        for (int i = 0; i < k.numberRatings; i++) this->ratings[i] = k.ratings[i];
        return *this;
    }

    int getnumberPerformers() {return numberPerformers;}
    Person operator[](int i) {if (i < numberPerformers && i >= 0) return performers[i]; else return Person();
    }

    // complete the class
    virtual ~Song(){
        delete [] ratings;
    }
    virtual float getTotalRating(){
        int max=ratings[0],min=ratings[0];
        for(int i=0 ; i<numberRatings ; i++){
            if(ratings[i]>max){
                max=ratings[i];
            }
            if(ratings[i]<min){
                min= ratings[i];
            }
        }
        float avg=(max+min)/2.0;
        return avg;
    }
    virtual void print(){
        for(int i=0 ; i<numberPerformers ; i++){
            performers[i].print();
            if(i+1!=numberPerformers){
                cout<<",";
            }
        }
        cout<<":"<<title<<endl;
    }
    int getNumRatings(){
        return numberRatings;
    }
    char const *getP(int j){
        return performers[j].getName();
    }
};

//=========================================================================================//


class Movie {
private:
    char *title;
protected:
    int popularity;
public:
    Movie(char *title, int popularity) {
        this->popularity = popularity;
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
    }
    Movie(const Movie &v) {
        this->popularity = v.popularity;
        this->title = new char[strlen(v.title) + 1];
        strcpy(this->title, v.title);
    }
    Movie operator=(const Movie &v) {
        if (this == &v) return *this;
        this->popularity = v.popularity;
        delete [] title;
        this->title = new char[strlen(v.title) + 1];
        strcpy(this->title, v.title);
        return *this;
    }
    virtual void print()  {cout << "Movie:" << title << endl;}
    virtual ~Movie() {delete [] title;}

};

//=========================================================================================//


class MovieSong:public Song,public Movie{
private:
    int songPopularity;
public:
    //MovieSong ok(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity, songPopularity);
    MovieSong(char *Stitle, Person *performers, int numberPerformers, int *ratings, int numberRatings,char *Mtitle, int popularity, int songPopularity): Song(Stitle,performers,numberPerformers,ratings,numberRatings),
                                                                                                                                    Movie(Mtitle,popularity){
        this->songPopularity=songPopularity;
    }

    float getTotalRating() override {
//        if(getNumRatings()==0){
//            throw RatingMissingException();
//        }
        float avg=Song::getTotalRating();
        float c=float(songPopularity)/popularity;
        float r=avg*c;
        return r;
    }
    void print(){
        Song::print();
        Movie::print();
    }
};

//===================================================================================================//


float averageRating(Song** songs, int n){
    MovieSong *p;
    float sum=0.0;
    int count=0;
    for(int i=0 ; i<n ; i++){
        p=dynamic_cast<MovieSong *>(songs[i]);
        if(p!= nullptr){
            if(p->getNumRatings()==0){
                sum+=5;
            } else{
                sum+=p->getTotalRating();
            }
            count++;
        }
    }
    return sum/count;
}


//=======================================================================================//

void printSongs(char* performer, Song** songs, int n){
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<songs[i]->getnumberPerformers() ; j++){
            if(strcmp(performer,songs[i]->getP(j))==0){
                songs[i]->print();
            }
        }
    }
}

//=======================================================================================//



int main() {

    Person performers[10];
    int year, numberOfPerformers, ratings[20], rating, numberOfRatings, type, popularity, songPopularity;
    char name[40], Stitle[30], perfomer[30], Mtitle[30];

    cin >> type;

    if (type == 1) //test class MovieSong
    {
        cout << "-----TEST MovieSong-----" << endl;
        cin >> Stitle >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++) {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++) {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> Mtitle >> popularity >> songPopularity;


        MovieSong ok(Stitle, performers, numberOfPerformers, ratings, numberOfRatings, Mtitle, popularity, songPopularity);
        cout << "Object of class MovieSong is created";

    } else if (type == 2) // function print in song
    {
        cout << "-----TEST print-----" << endl;
        cin >> Stitle >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }

        Song k(Stitle, performers, numberOfPerformers, ratings, numberOfRatings);
        k.print();

    } else if (type == 3) // function getTotalRating
    {
        cout << "-----TEST getTotalRating-----" << endl;
        cin >> Stitle >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }

        Song k(Stitle, performers, numberOfPerformers, ratings, numberOfRatings);
        cout << "Total rating: " << k.getTotalRating() << endl;

    } else if (type == 4) //funkcija getTotalRating vo MovieSong
    {
        cout << "-----TEST getTotalRating-----" << endl;
        cin >> Stitle >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> Mtitle >> popularity >> songPopularity;

        MovieSong fp(Stitle, performers, numberOfPerformers, ratings, numberOfRatings, Mtitle, popularity, songPopularity);
        cout << "Total rating: " << fp.getTotalRating() << endl;

    } else if (type == 5) //funkcija print vo MovieSong
    {
        cout << "-----TEST print -----" << endl;
        cin >> Stitle >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> Mtitle >> popularity >> songPopularity;

        MovieSong fp(Stitle, performers, numberOfPerformers, ratings, numberOfRatings, Mtitle, popularity, songPopularity);
        fp.print();

    } else if (type == 6) //all classes
    {
        cout << "-----TEST Song and MovieSong-----" << endl;
        cin >> Stitle >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> Mtitle >> popularity >> songPopularity;

        Song *p = new MovieSong(Stitle, performers, numberOfPerformers, ratings, numberOfRatings, Mtitle, popularity, songPopularity);
        p->print();
        cout << "Total rating: " << p->getTotalRating() << endl;
        delete p;


    } else if (type == 7) // function average rating
    {
        cout << "-----TEST average rating-----" << endl;
        int k, opt;
        cin >> k;
        Song **pesni = new Song*[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Song 2 MovieSong
            cin >> Stitle >> numberOfPerformers;
            for (int i = 0; i < numberOfPerformers; i++)
            {
                cin >> name >> year;
                performers[i] = Person(name, year);
            }
            cin >> numberOfRatings;
            for (int i = 0; i < numberOfRatings; i++)
            {
                cin >> rating;
                ratings[i] = rating;
            }
            if (opt == 1) {
                pesni[j] = new Song(Stitle, performers, numberOfPerformers, ratings, numberOfRatings);
            } else {
                cin >> Mtitle >> popularity >> songPopularity;
                pesni[j] = new MovieSong(Stitle, performers, numberOfPerformers, ratings, numberOfRatings, Mtitle, popularity, songPopularity);
            }
        }

        cout << "Average rating of the songs is " << averageRating(pesni, k);
        for (int j = 0; j < k; j++) delete pesni[j];
        delete [] pesni;

    } else if (type == 8) // function print songs
    {
        cout << "-----TEST print songs-----" << endl;
        int k, opt;
        cin >> k;
        Song **pesni = new Song*[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Song 2 MovieSong
            cin >> Stitle >> numberOfPerformers;
            for (int i = 0; i < numberOfPerformers; i++)
            {
                cin >> name >> year;
                performers[i] = Person(name, year);
            }
            cin >> numberOfRatings;
            for (int i = 0; i < numberOfRatings; i++)
            {
                cin >> rating;
                ratings[i] = rating;
            }
            if (opt == 1) {
                pesni[j] = new Song(Stitle, performers, numberOfPerformers, ratings, numberOfRatings);
            } else {
                cin >> Mtitle >> popularity >> songPopularity;
                pesni[j] = new MovieSong(Stitle, performers, numberOfPerformers, ratings, numberOfRatings, Mtitle, popularity, songPopularity);
            }
        }
        cin >> perfomer;
        cout << "Songs of " << perfomer << " are:" << endl;
        printSongs(perfomer, pesni, k);
        for (int j = 0; j < k; j++) delete pesni[j];
        delete [] pesni;

    }


    return 0;
}

