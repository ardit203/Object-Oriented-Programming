#include <iostream>
#include <cstring>
using namespace std;

class SMS{
protected:
    float price;
    char tel[20];
    static const int TAX;
public:
    SMS(char *tel="", float price=0){
        strcpy(this->tel,tel);
        this->price=price;
    }
    virtual float SMS_cena()=0;
    friend ostream &operator<<(ostream &out, SMS &s);
    char *getTel(){
        return tel;
    }
};

const int SMS::TAX=18;

//////////////////////////////////////////////////////////////////////////////////////////////////////////

class RegularSMS:public SMS{
private:
    char *msg;
    bool roaming;
    static int REGULAR;
public:
    RegularSMS(char *tel="", float price=0,char *msg="", bool roaming= false) : SMS(tel,price){
        this->msg=new char [strlen(msg)+1];
        strcpy(this->msg,msg);
        this->roaming=roaming;
    }

    float SMS_cena() override {
        float p=price;
        if(roaming){
            p=p*(1+REGULAR/100.0);
        } else{
            p=p*(1+TAX/100.0);
        }
        float n= strlen(msg)/160.0;
        float quantity=int(n);
        if(n-int(n)>0){
            quantity+=1;
        }
        return quantity*p;
    }
    static void set_rProcent(int p){
        REGULAR=p;
    }
};

int RegularSMS::REGULAR=300;

//////////////////////////////////////////////////////////////////////////////////////////////////////////

class SpecialSMS:public SMS{
private:
    bool humanitarian;
    static int SPECIAL;
public:
    SpecialSMS(char *tel="", float price=0,bool humanitarian= false):SMS(tel,price){
        this->humanitarian=humanitarian;
    }

    float SMS_cena() override {
        float p=price;
        if(!humanitarian){
            p=p*(1+SPECIAL/100.0);
        }
        return p;
    }
    static void set_sProcent(int p){
        SPECIAL=p;
    }
};

int SpecialSMS::SPECIAL=150;

ostream &operator<<(ostream &out, SMS &s){
    RegularSMS *rSMS=dynamic_cast<RegularSMS *>(&s);
    SpecialSMS *sSMS=dynamic_cast<SpecialSMS *>(&s);
    if(rSMS){
        cout<<"Tel: "<<rSMS->tel<<" - cena: "<<rSMS->SMS_cena()<<"den."<<endl;
    } else{
        cout<<"Tel: "<<sSMS->tel<<" - cena: "<<sSMS->SMS_cena()<<"den."<<endl;
    }
    return out;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void vkupno_SMS(SMS **s, int n){
    int countR=0, countS=0;
    float sumR=0, sumS=0;
    for(int i=0 ; i<n ; i++){
        RegularSMS *rSMS=dynamic_cast<RegularSMS *>(s[i]);
        if(rSMS){
            countR++;
            sumR+=rSMS->SMS_cena();
        } else{
            countS++;
            sumS+=s[i]->SMS_cena();
        }
    }
    //Vkupno ima 0 regularni SMS poraki i nivnata cena e: 0
    //Vkupno ima 3 specijalni SMS poraki i nivnata cena e: 412.5
    cout<<"Vkupno ima "<<countR<<" regularni SMS poraki i nivnata cena e: "<<sumR<<endl;
    cout<<"Vkupno ima "<<countS<<" specijalni SMS poraki i nivnata cena e: "<<sumS<<endl;
}


int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
