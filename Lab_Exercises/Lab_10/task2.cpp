#include<iostream>
#include<cstring>
using namespace std;

class InvalidTimeException{
public:
    InvalidTimeException(){}
    void print(){
        cout<<"The time is not valid"<<endl;
    }
};

class Race{
protected:
    char city[40];
    int year;
    int month;
    float bestTime;
    float length;
public:
    Race(char *city="", int year=0, int month=0, float bestTime=0.0, float length=0.0){
        strcpy(this->city,city);
        this->year=year;
        this->month=month;
        this->bestTime=bestTime;
        this->length=length;
    }
    virtual float heaviness()const{
        return bestTime/length;
    }

    friend ostream &operator<<(ostream &os, const Race &race) {
        os<<race.city<<" "<<race.month<<"."<<race.year<<" "<<race.heaviness()<<endl;
        return os;
    }

};

//-----------------------------------------------------------------------------------------//




class CarRace:public Race{
private:
    float *bestTimes;
    int numOfBestTimes;
    int numOfLaps;
    static float CAR_COEF;
public:
    CarRace(char *city="", int year=0, int month=0, float bestTime=0.0, float length=0.0, float *bestTimes= nullptr, int numOfBestTimes=0, int numOfLaps=0)
    :Race(city,year,month,bestTime,length){
        this->numOfBestTimes=numOfBestTimes;
        this->bestTimes=new float [numOfBestTimes];
        for(int i=0 ; i<numOfBestTimes ; i++){
            this->bestTimes[i]=bestTimes[i];
        }
        this->numOfLaps=numOfLaps;
    }

    float heaviness() const override {
        float p=Race::heaviness()+average()*CAR_COEF;
        if(numOfLaps>15){
            return p*1.1;
        }
        return p;
    }
    float average()const{
        float sum=0.0;
        for(int i=0 ; i<numOfBestTimes ; i++){
            sum+=bestTimes[i];
        }
        return sum/numOfBestTimes;
    }

    friend ostream &operator<<(ostream &os, const CarRace &race) {
        os<<race.city<<" "<<race.month<<"."<<race.year<<" "<<race.heaviness()<<endl;
        return os;
    }

//    Account &operator+=(Transaction *t) {
//        Transaction **tmp = new Transaction *[count + 1];
//        for (int i = 0; i < count; i++) {
//            tmp[i] = transactions[i];
//        }
//        tmp[count++] = t;
//        delete[] transactions;
//        transactions = tmp;
//        return *this;
//    }

     CarRace &operator+=(float time){
        if(time<10){
            throw InvalidTimeException();
        }
        float *tmp=new float [numOfBestTimes+1];
        for(int i=0 ; i<numOfBestTimes ; i++){
            tmp[i]=bestTimes[i];
        }
        tmp[numOfBestTimes++]=time;
        delete [] bestTimes;
        bestTimes=tmp;
         return *this;
    }
    ~CarRace(){
        delete [] bestTimes;
    }
    void setNumberLaps(int n){
        numOfLaps=n;
    }
    static float setKoeficient(float d){
        CAR_COEF=d;
    }
};

float CarRace::CAR_COEF=0.3;














int main(){
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int izbor;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testing the classes ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        Race t(city, year, month, bestTime, length);
        cout<<t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        CarRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        CarRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testing the operator += ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje novo najdobro vreme za prvata CarRace
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            CarRace* nn = dynamic_cast<CarRace*>(niza[i]);
            if (nn != 0){
                flag = 0;
                (*nn) += best;
                break;
            }
        }


        // pecatenje na site Trki
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testing the exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        CarRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float vreme1,vreme2;
        cin>>vreme1>>vreme2;
        try{
            mgt+=vreme1;
            mgt+=vreme2;
        }
        catch(InvalidTimeException e)
        {
            e.print();
        }
        cout<<mgt;
    }
    if (testCase == 5){
        cout << "===== Testing static members ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        CarRace::setKoeficient(0.7);
        // pecatenje na site Trki
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }



    return 0;
}