#include <iostream>
#include <cstring>
using namespace std;
enum Status{
    NOT_WORKING, REPAIRING, WORKING
};

class Airplane{
private:
    char registrationMark[12];
    char *name_airline;
    char airlineHomeAirport[20];
    Status s;
    int totalFlightHours;
    void copy(const Airplane &other){
        strcpy(this->registrationMark,other.registrationMark);
        this->name_airline=new char [strlen(other.name_airline)+1];
        strcpy(this->name_airline,other.name_airline);
        strcpy(this->airlineHomeAirport,other.airlineHomeAirport);
        this->totalFlightHours=other.totalFlightHours;
        this->s=other.s;
    }
public:
    Airplane(char *registrationMark="", char *name_airline="", char *airlineHomeAirport="", int totalFlightHours=0, int s=0){
        strcpy(this->registrationMark,registrationMark);
        this->name_airline=new char [strlen(name_airline)+1];
        strcpy(this->name_airline,name_airline);
        strcpy(this->airlineHomeAirport,airlineHomeAirport);
        this->totalFlightHours=totalFlightHours;
        this->s=Status(s);
    }
    Airplane(const Airplane &other){
        copy(other);
    }
    Airplane &operator=(const Airplane &other){
        if(this==&other){
            return *this;
        }
        delete [] name_airline;
        copy(other);
        return *this;
    }
    ~Airplane(){
        delete [] name_airline;
    }
    void print(){
        cout<<"ID: "<<registrationMark<<" - ";
        if(s==Status(0)){
            cout<<"NOT_WORKING";
        } else if(s==Status(1)){
            cout<<"REPAIRING";
        } else{
            cout<<"WORKING";
        }
        cout<<" "<<name_airline<<", "<<totalFlightHours<<", "<<airlineHomeAirport<<endl;
    }
    Status getStatus(){
        return s;
    }
    bool sameAirlineName(Airplane &a){
        return strcmp(name_airline,a.name_airline)==0;
    }
    int getTotalFlightHours(){
        return totalFlightHours;
    }
    void setStatus(int i){
        s=Status(i);
    }
    char *getHomeAirport(){
        return airlineHomeAirport;
    }
    bool isSame(Airplane &a){
        return strcmp(registrationMark,a.registrationMark)==0 && strcmp(name_airline,a.name_airline)==0 &&
               strcmp(airlineHomeAirport,a.airlineHomeAirport)==0 && s==a.s && totalFlightHours==a.totalFlightHours;
    }
};




class AirportService{
private:
    char name[20];
    Airplane *airplanes;
    int numOfAirplanes;
    void copy(const AirportService &other){
        strcpy(this->name,other.name);
        this->numOfAirplanes=other.numOfAirplanes;
        this->airplanes=new Airplane [this->numOfAirplanes];
        for(int i=0 ; i<this->numOfAirplanes ; i++){
            this->airplanes[i]=other.airplanes[i];
        }
    }
public:
    AirportService(char *name=""){
        strcpy(this->name,name);
        this->numOfAirplanes=0;
        this->airplanes=new Airplane [this->numOfAirplanes];
    }
    AirportService(const AirportService &other){
        copy(other);
    }
    AirportService &operator=(const AirportService &other){
        if(this==&other){
            return *this;
        }
        delete [] airplanes;
        copy(other);
        return *this;
    }
    ~AirportService(){
        delete [] airplanes;
    }
    void addAirplane(Airplane &a){
        if(a.getStatus()!=Status(0)){
            return;
        }
        a.setStatus(1);
        int flag=1;
        for(int i=0 ; i<numOfAirplanes ; i++){
            if(airplanes[i].sameAirlineName(a) && a.getTotalFlightHours() > airplanes[i].getTotalFlightHours()){
                airplanes[i]=a;
                flag=0;
            }
        }
        if(flag){
            Airplane *tmp=new Airplane [numOfAirplanes+1];
            for(int i=0 ; i<numOfAirplanes ; i++){
                tmp[i]=airplanes[i];
            }
            delete [] airplanes;
            tmp[numOfAirplanes++]=a;
            airplanes=tmp;
        }
    }
    Airplane serviceOldestAirplane() {
        Airplane oldest=airplanes[0];
        for(int i=1 ; i<numOfAirplanes ; i++){
            if(airplanes[i].getTotalFlightHours()>oldest.getTotalFlightHours()){
                oldest=airplanes[i];
            } else if(airplanes[i].getTotalFlightHours()==oldest.getTotalFlightHours() && strcmp(airplanes[i].getHomeAirport(),name)==0){
                oldest=airplanes[i];
            }
        }
        Airplane *tmp=new Airplane [numOfAirplanes];
        int k=0;
        for(int i= 0 ; i<numOfAirplanes ; i++){
            if(airplanes[i].isSame(oldest)){
                continue;
            }
            tmp[k++]=airplanes[i];
        }
        delete [] airplanes;
        numOfAirplanes=k;
        airplanes=tmp;
        oldest.setStatus(2);
        return oldest;
    }
    void print(){
        cout<<name<<endl;
        for(int i=0 ; i<numOfAirplanes ; i++){
            airplanes[i].print();
        }
    }
};

int main() {
    int testCase;
    cin >> testCase;
    char ID[12];
    char company_name[20];
    char company_airport[20];
    int flight_hours;
    int state;
    if (testCase == 1) {
        cout << "TESTING CONSTRUCTOR FOR AIRPLANE" << endl;
        Airplane a;
        cout << "TEST FOR DEFAULT CONSTRUCTOR PASSED" << endl;
        Airplane a1("ZHN-96-TY", "FINKI-Airline", "TMF", 13);
        cout << "TEST FOR CONSTRUCTOR WITH 3 ARGUMENTS PASSED" << endl;
        Airplane a2("ZHN-96-TA", "FINKI1-Airline", "TMF", 13, 0);
        cout << "TEST FOR CONSTRUCTOR WITH 4 ARGUMENTS PASSED" << endl;
    } else if (testCase == 2) {
        cout << "TESTING COPY-CONSTRUCTOR AND OPERATOR = (ASSIGNMENT) FOR AIRPLANE" << endl;
        Airplane p("ZHN-96-TA", "FINKI-Airline", "TMF", 13, 0);
        Airplane p1(p);
        cout << "TEST FOR COPY CONSTRUCTOR PASSED" << endl;
        Airplane p2;
        p2 = p;
        cout << "TEST FOR OPERATOR = (ASSIGNMENT) PASSED" << endl;
    } else if (testCase == 3) {
        cout << "TESTING PRINT() FOR AIRPLANE" << endl;
        cin>>ID>>company_name>>company_airport>>flight_hours>>state;
        Airplane p(ID, company_name, company_airport, flight_hours, state);
        p.print();
    } else if (testCase == 4) {
        cout << "TESTING CONSTRUCTOR FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        cout << "TEST PASSED" << endl;
    } else if (testCase == 5) {
        cout << "TESTING ADD() AND PRINT() FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>ID>>company_name>>company_airport>>flight_hours>>state;
            Airplane p(ID, company_name, company_airport, flight_hours, state);
            as.addAirplane(p);
        }
        as.print();
    } else if (testCase == 6) {
        cout << "TESTING serviceOldestAirplane() AND PRINT() FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>ID>>company_name>>company_airport>>flight_hours>>state;
            Airplane p(ID, company_name, company_airport, flight_hours, state);
            as.addAirplane(p);
        }
        Airplane p = as.serviceOldestAirplane();
        cout<<"Removed plane:"<<endl;
        p.print();
        cout<<"-----------------"<<endl;
        as.print();
    }  else if (testCase == 7) {
        cout << "TESTING COPY CONSTRUCTOR AND OPERATOR = FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        Airplane a1("ZHN-96-TY", "FINKI-Airline", "TMF", 13);
        as.addAirplane(a1);

        AirportService s1 = as; //copy constructor
        AirportService s2;
        s2 = s1; //operator =
        s1.print();
        s2.print();
    }
    return 0;
}