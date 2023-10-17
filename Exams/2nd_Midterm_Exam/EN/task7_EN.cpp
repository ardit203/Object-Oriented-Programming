#include<iostream>
#include <cstring>
using namespace std;

//your code

class IdException1{
public:
    IdException1(){}
    void digits(){
        cout<<"The id number has a non-digit character"<<endl;
    }
};

class IdException2{
public:
    IdException2(){}
    void length(){
        cout<<"The id number has more than 9 characters"<<endl;
    }
};

//===================================================================================================

class DonationAction{
private:
    char *name;
    char id[50];
    int collected_fund;
    int needed_fund;
    void copy(const DonationAction &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        strcpy(this->id,other.id);
        this->collected_fund=other.collected_fund;
        this->needed_fund=other.needed_fund;
    }
public:
    bool check1(char *str){
        for(int i=0 ; i< strlen(str) ; i++){
            if(str[i]<'0' || str[i]>'9'){
                return true;
            }
        }
        return false;
    }
    bool check2(char *str){
        return strlen(str)>9;
    }
    DonationAction(char *name="",char *id="", int needed_fund=0){
        this->name=new char [strlen(name)+1];
        if(check2(id)){
            throw IdException2();
        } else if(check1(id)){
            throw IdException1();
        }
        strcpy(this->name,name);
        strcpy(this->id,id);
        this->needed_fund=needed_fund;
        this->collected_fund=0;
    }
    DonationAction(const DonationAction &other){
        copy(other);
    }
    DonationAction &operator=(const DonationAction &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        copy(other);
        return *this;
    }
    ~DonationAction(){
        delete [] name;
    }
    friend ostream &operator<<(ostream &out, const DonationAction &d){
        out<<d.id<<" "<<d.name<<" ";
        bool c=(d.needed_fund<=d.collected_fund);
        if(c){
            out<<"collected"<<endl;
        } else{
            out<<d.needed_fund-d.collected_fund<<" more denars are needed"<<endl;
        }
        return out;
    }
    DonationAction &operator+=(int d){
        collected_fund+=d;
        return *this;
    }
    int idNum(){
        int n= strlen(id);
        int idNumber=0;
        for(int i=0 ; i<n ; i++){
            idNumber=idNumber*10+(id[i]-'0');
        }
        return idNumber;
    }
    bool operator<(DonationAction &d){
        int thisClass=needed_fund-collected_fund;
        int dClass=d.needed_fund-d.collected_fund;
        if(thisClass<dClass){
            return true;
        } else if(thisClass==dClass && idNum()>d.idNum()){
            return true;
        }
        return false;
    }
    char *getID(){
        return id;
    }
};

//=========================================================================================================

class DonationSociety{
    char president[30];
    DonationAction *actions;
    int numOfActions;
    void copy(const DonationSociety &other){
        strcpy(this->president,other.president);
        this->numOfActions=other.numOfActions;
        this->actions=new DonationAction [this->numOfActions];
        for(int i=0 ; i<numOfActions ; i++){
            this->actions[i]=other.actions[i];
        }
    }
public:
    DonationSociety(char *president=""){
        strcpy(this->president,president);
        this->numOfActions=0;
        this->actions=new DonationAction[numOfActions];
    }
    DonationSociety(const DonationSociety &other){
        copy(other);
    }
    DonationSociety &operator=(const DonationSociety &other){
        if (this==&other){
            return *this;
        }
        delete [] actions;
        copy(other);
        return *this;
    }
    ~DonationSociety(){
        delete [] actions;
    }
    bool takenDonation(char *id, int donatedFund){
        for(int i=0 ; i<numOfActions ; i++){
            if(strcmp(actions[i].getID(),id)==0){
                actions[i]+=donatedFund;
                return true;
            }
        }
        return false;
    }
    DonationSociety &operator +=(DonationAction &d){
        for(int i=0 ; i<numOfActions ; i++){
            if(strcmp(actions[i].getID(),d.getID())==0){
                return *this;
            }
        }
        DonationAction *tmp=new DonationAction[numOfActions+1];
        for(int i=0 ; i<numOfActions ; i++){
            tmp[i]=actions[i];
        }
        delete [] actions;
        tmp[numOfActions++]=d;
        actions=tmp;
        return *this;
    }
    DonationSociety &bubbleSort(){
        DonationAction *tmp=new DonationAction [numOfActions];
        DonationAction temporary;
        for(int i=0 ; i<numOfActions ; i++){
            tmp[i]=actions[i];
        }
        for(int i=0 ; i<numOfActions ; i++){
            for(int j=0 ; j<numOfActions-1-i ; j++){
                if(tmp[j]<tmp[j+1]){
                    temporary=tmp[j+1];
                    tmp[j+1]=tmp[j];
                    tmp[j]=temporary;

                }
            }
        }
        delete [] actions;
        actions=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, DonationSociety &d){
        d.bubbleSort();
        for(int i=0 ; i<d.numOfActions ; i++){
            out<<d.actions[i];
        }
        out<<"President:"<<d.president;
        return out;
    }
};

int main(){


    DonationSociety donacii("Velko Velkovski");
    int n;
    char naziv[50],id[50];
    int potrebnasuma,doniranasuma;
    cin>>n;

    for (int i=0;i<n;i++){
        cin.get();
        cin.getline(naziv,50);
        cin>>id>>potrebnasuma;
        try{
            DonationAction edna(naziv,id,potrebnasuma);
            donacii+=edna;
        }catch(IdException1 &e) {
            e.digits();
        } catch (IdException2 &e) {
            e.length();
        }
    }

    //donation
    cin>>n;
    for (int i=0;i<n;i++){

        cin>>id>>doniranasuma;

        if(!donacii.takenDonation(id,doniranasuma))
            cout<<"The donation is not taken. Wrong ID."<<endl;
    }
    cout<<"==============="<<endl;
    cout<<donacii;

}
