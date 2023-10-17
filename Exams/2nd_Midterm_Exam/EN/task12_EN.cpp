#include<iostream>
#include<cstring>
using namespace std;

//your code here

class InvestmentPlan{
    char nameOfInvestitor[80];
    double sumOfInvestments;
    double shares;
    bool current_day;
public:
    InvestmentPlan(char *nameOfInvestitor="", double sumOfInvestments=0.0, double shares=0.0, bool current_day=false){
        strcpy(this->nameOfInvestitor, nameOfInvestitor);
        this->sumOfInvestments=sumOfInvestments;
        this->shares=shares;
        this->current_day=current_day;
    }
    double getSumOfInvestments(){
        return sumOfInvestments;
    }
    bool getCurr(){
        return current_day;
    }
    double getShares(){
        return shares;
    }
};

//==========================================================//

class InvestmentFund{
protected:
    char name[50];
    InvestmentPlan *plans;
    int numOfInvestmentPlans;
    double price;
public:
    InvestmentFund(char *name="", InvestmentPlan *plans= nullptr, int numOfInvestmentPlans=0, double price=0.0){
        strcpy(this->name,name);
        this->numOfInvestmentPlans=numOfInvestmentPlans;
        this->plans=new InvestmentPlan [numOfInvestmentPlans];
        for(int i=0 ; i<numOfInvestmentPlans ; i++){
            this->plans[i]=plans[i];
        }
        this->price=price;
    }
    virtual double profit()=0;
    double totalSumOfInvestments(){
        double total = 0.0;
        for (int i = 0; i < numOfInvestmentPlans; i++) {
            total += plans[i].getShares() * price;
        }
        return total;
    }
    virtual double valueNewPlan(){
        double newInvestment = 0.0;
        for (int i = 0; i < numOfInvestmentPlans; i++) {
            if (plans[i].getCurr()) {
                newInvestment += plans[i].getSumOfInvestments();
            }
        }
        return newInvestment;
    }
};

//==============================================================================//

class MoneyFund:public InvestmentFund{
private:
    const static int Y_PROVISION;
public:
    MoneyFund(char *name="", InvestmentPlan *plans= nullptr, int numOfInvestmentPlans=0, double price=0.0){
        strcpy(this->name,name);
        this->numOfInvestmentPlans=numOfInvestmentPlans;
        this->plans=new InvestmentPlan [numOfInvestmentPlans];
        for(int i=0 ; i<numOfInvestmentPlans ; i++){
            this->plans[i]=plans[i];
        }
        this->price=price;
    }
    double profit() override{
        double p=(totalSumOfInvestments()*Y_PROVISION/100.0)/365.0;
        return p;
    }
};
const int MoneyFund::Y_PROVISION=1;


//==============================================================================//


class ActionFund:public InvestmentFund{
private:
    const static float Y_PROVISION;
    const static int E_PROVISION;
public:
    ActionFund(char *name="", InvestmentPlan *plans= nullptr, int numOfInvestmentPlans=0, double price=0.0){
        strcpy(this->name,name);
        this->numOfInvestmentPlans=numOfInvestmentPlans;
        this->plans=new InvestmentPlan [numOfInvestmentPlans];
        for(int i=0 ; i<numOfInvestmentPlans ; i++){
            this->plans[i]=plans[i];
        }
        this->price=price;
    }

    double profit() override{
        return (totalSumOfInvestments() * Y_PROVISION / 100.0) / 365.0 + (valueNewPlan() * E_PROVISION / 100.0);
    }
};

const float ActionFund::Y_PROVISION=1.5;
const int ActionFund::E_PROVISION=3;


//===================================================================================//


double totalProfit(InvestmentFund** funds, int n){
    double sum=0.0;
    for(int i=0 ; i<n ; i++){
        sum+=funds[i]->profit();
    }
    return sum;
}

    int main(){

    char investitor[80], ime[50];
    double plan, brUdeli, udel;
    bool flag = false;
    int n, m;
    cin >> n;
    InvestmentFund **fondovi = new InvestmentFund*[n];
    for(int i = 0; i < n; i++){
        cin >> ime;
        cin >> m;
        InvestmentPlan *ip = new InvestmentPlan[m];
        for(int j = 0; j < m; j++){
            cin >> investitor >> plan >> brUdeli;
            if(j % 2) flag = true;
            else flag = false;
            InvestmentPlan IP(investitor, plan, brUdeli, flag);
            ip[j] = IP;
        }
        cin >> udel;
        if(i % 2){
            fondovi[i] = new ActionFund(ime, ip, m, udel);

        }
        else{
            fondovi[i] = new MoneyFund(ime, ip, m, udel);
        }
    }
    cout << totalProfit(fondovi, n);
    return 0;
}