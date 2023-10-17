#include<iostream>
#include<cstdio>
#include <cstring>
using namespace std;


// Your code here


class Camera{
protected:
    char manufacture[20];
    char model[20];
    int year;
    float resolution;
public:
    Camera(char *manufacture="", char *model="", int year=0, float resolution=0.0){
        strcpy(this->manufacture,manufacture);
        strcpy(this->model,model);
        this->year=year;
        this->resolution=resolution;
    }
    virtual float price()=0;
    virtual float rentalPrice(int days)=0;
    bool operator<(Camera *other){
        return this->price()<other->price();
    }
    char *getModel(){
        return model;
    }
};

class PhotoCamera:public Camera{
    bool rawImage;
public:
    PhotoCamera(char *manufacture="", char *model="", int year=0, float resolution=0.0, bool rawImage= false): Camera(manufacture,model,year,resolution){
        this->rawImage=rawImage;
    }
    float price(){
        float p=100+resolution*20;
        if(rawImage){
            p+=50;
        }
        return p;
    }
    float rentalPrice(int days){
        float p=0.01*price()*days;
        if(days>7){
            return p*(1-20/100.0);
        }
        return p;
    }
};

class VideoCamera:public Camera{
private:
    int max;
public:
    VideoCamera(char *manufacture="", char *model="", int year=0, float resolution=0.0, int max=0): Camera(manufacture,model,year,resolution){
        this->max=max;
    }
    float price(){
        float p=resolution*80;
        if(max>3600){
            p=p*(1+40/100.0);
        }
        return p;
    }
    float rentalPrice(int days){
        float p=0.01*price()*days;
        if(days>7){
            return p*(1-20/100.0);
        }
        return p;
    }
};

class FilmCamera:public Camera{
private:
    int frameRate;
public:
    FilmCamera(char *manufacture="", char *model="", int year=0, float resolution=0.0, int frameRate=0): Camera(manufacture,model,year,resolution){
        this->frameRate=frameRate;
    }
    float price(){
        float p=50000;
        if(frameRate>30){
            p+=frameRate*5000;
        }
        return p;
    }
    float rentalPrice(int days){
        float p=500*days;
        if(frameRate>60){
            return 2*p;
        }
        return p;
    }
};

float production(Camera **pCamera, int n, int days){
    float sum=0.0;
    for(int i=0 ; i<n ; i++){
        sum+=pCamera[i]->rentalPrice(days);
    }
    return sum;
}

char *mostExpensiveCamera(Camera **camera, int n){
    float max=camera[0]->price();
    int index=0;
    for(int i=0 ; i<n ; i++){
        if(camera[i]->price()>max){
            max=camera[i]->price();
            index=i;
        }
    }
    return camera[index]->getModel();
}

int main(int argc, char *argv[])
{
    // Variables for reading input
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;

    int t;

    // Array of cameras
    Camera *c [10];

    // Read number of cameras
    cin>>n;

    for(int i = 0; i < n; ++i){

        // Camera type: 1 - Photo, 2 - Video, 3 - Film
        cin>>t;

        if (t==1){
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        }
        else if (t==2){
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        }
        else if (t==3){
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }


    // Production days
    int days;
    cin >> days;


    cout<<"Price of production is: " << production(c, n, days);
    cout<<"\n" << "Most expensive camera used in production is: " << mostExpensiveCamera(c, n);


    return 0;
}
