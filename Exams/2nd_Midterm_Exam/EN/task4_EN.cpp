#include<iostream>
#include<string.h>
using namespace std;

class Cinema{
private:
    char name[20];
    int hall_number;
    static float student_discount;
    float t_price;
public:
    Cinema(char *name="", int hall_number=0, float price=0){
        strcpy(this->name,name);
        this->hall_number=hall_number;
        this->t_price=price;
    }
    static float getStudentDiscount(){
        return student_discount;
    }
    static void setStudentDiscount(float d){
        student_discount=d;
    }
    virtual float price(bool isStudent){
        if(isStudent){
            return t_price*(1-student_discount);
        } else{
            return t_price;
        }
    }
    char *getname(){
        return name;
    }
};
float Cinema::student_discount=0.17;

class ThreeDCinema: public Cinema{
private:
    char *movieName;
    float duration;
    bool premiere;
public:
    ThreeDCinema(char *name, int hall_number, float price, char *movieName, float duration, bool premiere): Cinema(name,hall_number,price){
        this->movieName=new char [strlen(movieName)+1];
        strcpy(this->movieName,movieName);
        this->duration=duration;
        this->premiere=premiere;
    }
    bool getpremiere(){
        return premiere;
    }
    float price(bool isStudent){
        float p=Cinema::price(isStudent);
        if(duration>3){
            p+=70;
        } else if(duration>2.5){
            p+=50;
        }
        if(premiere){
            p+=60;
        }
        return p;
    }
    ~ThreeDCinema(){
        delete [] movieName;
    }
};

bool searchCinema(Cinema ** halls,int n, const char * name, bool premiere, bool isStudent){
    bool found = false;

    for(int i=0 ; i<n ; i++){
        ThreeDCinema * s = dynamic_cast<ThreeDCinema *>(halls[i]);
        if(premiere&&strcmp(halls[i]->getname(),name)==0&&s!=0&&s->getpremiere()==true){
            found = true;
            cout<<halls[i]->getname()<<" "<<halls[i]->price(isStudent)<<endl;

        }
        else{
            if(strcmp(halls[i]->getname(),name)==0){
                found = true;
                cout<<halls[i]->getname()<<" "<<halls[i]->price(isStudent)<<endl;
            }
        }
    }

    return found;
}

void cheapestCinema(Cinema ** halls, int n,bool isStudent)
{
    int ThreeD=0;
    float min =halls[0]->price(isStudent);
    int minIndex =0;
    for(int i=0;i<n;i++)
    {
        if(halls[i]->price(isStudent)<min)
        {
            min = halls[i]->price(isStudent);
            minIndex = i;
        }

        if(dynamic_cast<ThreeDCinema *>(halls[i])!=0)
        {
            ThreeD++;
        }
    }
    cout<<"Cheapest movie hall: ";
    cout<<halls[minIndex]->getname()<<" "<<halls[minIndex]->price(isStudent)<<endl;
    cout<<"3D cinema halls: "<<ThreeD<<" from total "<<n<<endl;
}

int main(){

    int tip,n;
    char name[100], movieName[40];
    int no;
    bool premiere;
    float ticketPrice;
    float hours;
    bool isStudent;

    cin>>tip;
    if (tip==1){//Cinema
        cin>>name>>no>>ticketPrice;
        Cinema k1(name,no,ticketPrice);
        cout<<"Cinema created with name: "<<k1.getname()<<endl;
    }
    else if (tip==2){//PRC - Cinema
        cin>>name>>no>>ticketPrice>>isStudent;
        Cinema k1(name,no,ticketPrice);
        cout<<"Initial PRC for the cinema with name "<<k1.getname()<< " is: " <<k1.price(isStudent)<<endl;
    }
    else if (tip==3){//3D Cinema
        cin>>name>>no>>ticketPrice>>movieName>>hours>>premiere;
        ThreeDCinema s(name,no,ticketPrice,movieName,hours,premiere);
        cout<<"Cinema created with name "<<s.getname()<<" and discount "<<s.getStudentDiscount()<<endl;
    }
    else if (tip==4){//PRC - 3DCinema
        cin>>name>>no>>ticketPrice>>movieName>>hours>>premiere>>isStudent;
        ThreeDCinema s(name,no,ticketPrice,movieName,hours,premiere);
        cout<<"The PRC for the cinema "<<s.getname()<<" is: "<<s.price(isStudent)<<endl;
    }
    else if (tip==5) {//cheapest Cinema
        Cinema ** halls = new Cinema *[5];
        int n;
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[2] = new ThreeDCinema("Home",44,299,"Godfather",5,false);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);
        cheapestCinema(halls,5,true);
    }
    else if (tip==6){//search
        Cinema ** halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);

        if(searchCinema(halls,5, "Milenium3D",true,true))
            cout<<"Found"<<endl;
        else cout<<"Not found"<<endl;

        if(searchCinema(halls,5, "CinePlexx1",false,false))
            cout<<"Found"<<endl;
        else cout<<"Not found"<<endl;

    }
    else if (tip==7){//change PRC
        Cinema ** halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[2] = new ThreeDCinema("Domasno",44,299,"Godfather",5,false);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);
        halls[2] -> setStudentDiscount(0.9);
        cheapestCinema(halls,4,true);
    }

    return 0;
}

//Faculty Solution
//class Cinema{
//private:
//    char name[20];
//    int no;
//    float ticketPrice;
//    static float studentDiscount;
//public:
//    static void setStudentDiscount(float sd){
//        studentDiscount = sd;
//    }
//
//    static float getStudentDiscount(){
//        return studentDiscount;
//    }
//
//    Cinema(const char* name = "", int no = 0, float ticketPrice = 0){
//
//        strcpy(this->name,name);
//        this->no = no;
//        this->ticketPrice = ticketPrice;
//    }
//
//    virtual float PRC(bool isStudent){
//        if(isStudent)
//            return ticketPrice * (1-studentDiscount);
//        return ticketPrice;
//    }
//    char* getname(){
//        return name;
//    }
//
//};
//float Cinema::studentDiscount=0.17;
//
//class ThreeDCinema:public Cinema{
//private:
//    char movieName[100];
//    float hours;
//    bool premiere;
//public:
//    bool getpremiere()
//    {
//        return premiere;
//    }
//    ThreeDCinema(const char* name = "", int no = 0, float ticketPrice = 0, const char * movieName = "", float hours = 0, bool premiere = false):Cinema(name, no, ticketPrice){
//        strcpy(this->movieName,movieName);
//        this->hours = hours;
//        this->premiere = premiere;
//    }
//
//    float PRC(bool isStudent){
//        float original = Cinema::PRC(isStudent);
//        if(hours>3)
//        {
//            original+=70;
//        }
//        else if(hours>2.5)
//        {
//            original+=50;
//        }
//        if(premiere)
//            original+=60;
//        return original;
//    }
//};
//
//void cheapestCinema(Cinema ** halls, int n,bool isStudent)
//{
//    int ThreeD=0;
//    float min =halls[0]->PRC(isStudent);
//    int minIndex =0;
//    for(int i=0;i<n;i++)
//    {
//        if(halls[i]->PRC(isStudent)<min)
//        {
//            min = halls[i]->PRC(isStudent);
//            minIndex = i;
//        }
//
//        if(dynamic_cast<ThreeDCinema *>(halls[i])!=0)
//        {
//            ThreeD++;
//        }
//    }
//    cout<<"Cheapest movie hall: ";
//    cout<<halls[minIndex]->getname()<<" "<<halls[minIndex]->PRC(isStudent)<<endl;
//    cout<<"3D cinema halls: "<<ThreeD<<" from total "<<n<<endl;
//}
//
//bool searchCinema(Cinema ** halls,int n, const char * name, bool premiere, bool isStudent)
//{
//    bool found = false;
//
//    for(int i=0;i<n;i++)
//    {
//        ThreeDCinema * s = dynamic_cast<ThreeDCinema *>(halls[i]);
//        if(premiere&&strcmp(halls[i]->getname(),name)==0&&s!=0&&s->getpremiere()==true)
//        {
//            found = true;
//            cout<<halls[i]->getname()<<" "<<halls[i]->PRC(isStudent)<<endl;
//
//        }
//        else
//        {
//            if(strcmp(halls[i]->getname(),name)==0)
//            {
//                found = true;
//                cout<<halls[i]->getname()<<" "<<halls[i]->PRC(isStudent)<<endl;
//            }
//        }
//    }
//
//    return found;
//}


