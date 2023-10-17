#include<iostream>
#include<string.h>
using namespace std;

//your code here

class InvalidTimeException{
public:
    InvalidTimeException(){}
    void show(){
        cout<<"Invalid Time"<<endl;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////

class Race{
protected:
    char city[40];
    int year;
    int month;
    float bestTime;
    float length;
public:
    Race(char *city="", int year=0, int month=0, float bestTime=0, float length=0){
        strcpy(this->city,city);
        this->year=year;
        this->month=month;
        this->bestTime=bestTime;
        this->length=length;
    }
    virtual float complexity(){
        float p=bestTime/length;
        return p;
    }
    friend ostream &operator<<(ostream &out, Race &r){
        out<<r.city<<" "<<r.month<<"."<<r.year<<" "<<r.complexity()<<endl;
        return out;
    }
};

//===============================================================================================

class MotoGPRace:public Race{
private:
    float *bestTimes;
    int n;
    int laps;
    static float COEFF;
    void copy(const MotoGPRace &o){
        strcpy(this->city,city);
        this->year=o.year;
        this->month=o.month;
        this->bestTime=o.bestTime;
        this->length=o.length;
        this->n=o.n;
        this->bestTimes=new float [n];
        for(int i=0 ; i<n ; i++){
            this->bestTimes[i]=o.bestTimes[i];
        }
        this->laps=o.laps;
    }
public:
    MotoGPRace(char *city="", int year=0, int month=0, float bestTime=0, float length=0,
               float *bestTimes= nullptr, int n=0, int laps=0): Race(city,year,month,bestTime,length){
        this->n=n;
        this->bestTimes=new float [n];
        for(int i=0 ; i<n ; i++){
            this->bestTimes[i]=bestTimes[i];
        }
        this->laps=laps;
    }
    MotoGPRace(const MotoGPRace &other){
        copy(other);
    }
    static void setK(float d){
        COEFF=d;
    }
    void setNumberLaps(int d){
        laps=d;
    }
    float avg(){
        float sum=0;
        for(int i=0 ; i<n ; i++){
            sum+=bestTimes[i];
        }
        return sum/n;
    }
    float complexity(){
        float c=Race::complexity()+avg()*COEFF;
        if(laps>22){
            c=c*1.2;
        }
        return c;
    }
    ~MotoGPRace(){
        delete [] bestTimes;
    }
    MotoGPRace &operator+=(float time){
        if(time<9.5){
            throw InvalidTimeException();
        }
        float *tmp=new float [n+1];
        for(int i=0 ; i<n ; i++){
            tmp[i]=bestTimes[i];
        }
        delete [] bestTimes;
        tmp[n++]=time;
        bestTimes=tmp;
        return *this;
    }
    MotoGPRace operator++(int){
        MotoGPRace Copy(*this);
        ++laps;
        return Copy;
    }
    int getNumberLaps(){
        return laps;
    }
};

float MotoGPRace::COEFF=0.4;

//int main(){
//    char city[50];
//    int year;
//    int month;
//    float bestTime;
//    float length;
//    float bestTimes[50];
//    int n;
//    int choice;
//    int numberLaps;
//    cin>>city>>year>>month>>bestTime>>length>>numberLaps>>n;
//    for(int i=0 ; i<n ; i++){
//        cin>>bestTimes[i];
//    }
////    MotoGPRace(char *city="", int year=0, int month=0, float bestTime=0, float length=0,
////            float *bestTimes= nullptr, int n=0, int laps=0): Race(city,year,month,bestTime,length)
//    MotoGPRace m(city,year,month,bestTime,length,bestTimes,n,numberLaps);
//    float c=m.complexity();
//    cout<<c;
//    return 0;
//}

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
    int choice;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testing - classes ======" << endl;
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
        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes, n, numberLaps);
        cout << mgt;
        MotoGPRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testing - operatorot += ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        // add a new best time
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace* nn = dynamic_cast<MotoGPRace*>(rArray[i]);
            if (nn != 0){
                flag = 0;
                try{
                    (*nn) += best;//EXCEPTION
                }catch (InvalidTimeException &e){
                    e.show();
                }

                break;
            }
        }

        // print the races
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    if (testCase == 3){
        cout << "===== Testing - exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        MotoGPRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float time1,time2;
        cin>>time1>>time2;
        try{
            mgt+=time1;//EXCEPTION
        }catch (InvalidTimeException &e){
            e.show();
        }
        try{
            mgt+=time2;//EXCEPTION
        }catch (InvalidTimeException &e){
            e.show();
        }


        cout<<mgt;
    }
    if (testCase == 4){
        cout <<"===== Testing - operator++ ======"<<endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];

        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes,n,numberLaps);
        float v,koef2;
        cout<<(mgt++).getNumberLaps()<<endl;
        cout<<mgt;
        mgt++;
        cout<<mgt;
    }
    if (testCase == 5){
        cout << "===== Testing - coefficient ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        MotoGPRace::setK(0.7);
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    if (testCase == 6){
        cout << "===== Testing - full functionality ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        float newCoef;
        cin>>newCoef;
        MotoGPRace::setK(newCoef);
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        // print the races
        float newBest;
        cin>>newBest;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace * pok= dynamic_cast<MotoGPRace *>(rArray[i]);
            if(pok!=0)
            {
                (*pok)++;
                try{
                    (*pok)+=newBest;//EXCEPTION
                }catch (InvalidTimeException &e){
                    e.show();
                }

                if(flag==1)
                {
                    flag = 0;
                    try{
                        *pok+=1.4;//EXCEPTION
                    }catch (InvalidTimeException &e){
                        e.show();
                    }


                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    return 0;
}
