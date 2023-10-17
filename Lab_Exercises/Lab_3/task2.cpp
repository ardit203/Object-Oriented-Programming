#include <iostream>
#include <cstring>
using namespace std;

class SpaceObject{
private:
    char name[100];
    char type[100];
    int distanceFromEarth;
public:
    void print(){
        cout<<name<<" ("<<type<<") - distance: "<<distanceFromEarth<<" light years away from Earth"<<endl;
    }
    SpaceObject(){
        strcpy(name,"");
        strcpy(type,"");
        distanceFromEarth=0;
    }
    SpaceObject(char *_name, char *_type, int _distanceFromEarth){
        strcpy(name,_name);
        strcpy(type,_type);
        distanceFromEarth=_distanceFromEarth;
    }
    int getDistanceFromEarth(){
        return distanceFromEarth;
    }

};
class Alien{
private:
    char name[100];
    int age;
    char homePlanet[100];
    int numObj;
    SpaceObject spaceObjects[100];
public:
    SpaceObject getObjectClosestToEarth(){
        SpaceObject closest=spaceObjects[0];
        for(int i=1 ; i<numObj ; i++){
            if(spaceObjects[i].getDistanceFromEarth()<closest.getDistanceFromEarth()){
                closest=spaceObjects[i];
            }
        }
        return closest;
    }
    void print(){
        cout<<"Alien name: "<<name<<endl;
        cout<<"Alien age: "<<age<<endl;
        cout<<"Alien home planet: "<<homePlanet<<endl;
        cout<<"Favourite space object closest to earth: ";
        getObjectClosestToEarth().print();
    }
    Alien(){
        strcpy(name,"");
        age=0;
        strcpy(homePlanet,"");
        numObj=2;
        for(int i=0 ; i<numObj ; i++){
            spaceObjects[i]=SpaceObject();
        }
    }
    Alien(char *_name, int _age, char *_homePlanet, int _numObj, SpaceObject *_spaceObjects){
        strcpy(name,_name);
        age=_age;
        strcpy(homePlanet,_homePlanet);
        numObj=_numObj;
        for(int i=0 ; i<numObj ; i++){
            spaceObjects[i]=_spaceObjects[i];
        }
    }
    ~Alien(){

    }
    Alien(const Alien & other){
        strcpy(name,other.name);
        age=other.age;
        strcpy(homePlanet,other.homePlanet);
        numObj=other.numObj;
        for(int i=0 ; i<numObj ; i++){
            spaceObjects[i]=other.spaceObjects[i];
        }
    }
};
//DO NOT CHANGE THE MAIN FUNCTION
int main()
{
    char name[100], homePlanet[100];
    int age, numObj;
    cin>>name>>age>>homePlanet>>numObj;
    //Testing default constructor for SpaceObject
    SpaceObject spaceObjects[numObj];
    for(int i=0; i<numObj; i++)
    {
        char spaceObjectName[100], spaceObjectType[100];
        int distanceFromEarth;
        cin>>spaceObjectName>>spaceObjectType>>distanceFromEarth;
        //Testing constructor with arguments for SpaceObject
        spaceObjects[i]=SpaceObject(spaceObjectName, spaceObjectType, distanceFromEarth);
    }
    //Testing default constructor for Alien
    Alien alien;
    //Testing constructor with arguments for Alien and copy constructor for Alien
    alien=Alien(name, age, homePlanet, numObj, spaceObjects);
    Alien alien2 = Alien(alien);

    alien2.print();
    return 0;
}