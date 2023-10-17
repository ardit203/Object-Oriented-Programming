#include <iostream>
#include <cstring>

using namespace std;

class DebitAccount{
protected:
    char owner[100];
    char account_number[17];
    int balance;
public:
    DebitAccount(char *owner="", char *account_number="", int balance=0){
        strcpy(this->owner,owner);
        strcpy(this->account_number,account_number);
        this->balance=balance;
    }

//    DebitAccount(char *owner, char *accountNumber, int balance) :balance(balance) {
//        strcpy(this->owner,owner);
//        strcpy(this->account_number,account_number);
//    }


//    friend ostream &operator<<(ostream &out, const DebitAccount &da){
//        out<<da.owner<<" "<<da.account_number<<" "<<da.balance;
//    }
    friend ostream &operator<<(ostream &os, const DebitAccount &account) {//Auto generate
        os << "Owner: " << account.owner << " || Account_number: " << account.account_number << " || Balance: "
           << account.balance;
        return os;
    }
    void deposit(int amount){
        balance+=amount;
    }
    bool withdraw(int amount){
        if(amount<=balance){
            balance-=amount;
            return true;
        } else{
            return false;
        }
    }
};

class CreditAccount : public DebitAccount{
    float interestRate;
    int limit;
public:
//    CreditAccount(char *owner="", char *account_number="", int balance=0, float interestRate=0, int limit=0){
//        strcpy(this->owner,owner);
//        strcpy(this->account_number,account_number);
//        this->balance=balance;
//        this->interestRate=interestRate;
//        this->limit=limit;
//    }
    CreditAccount(char *owner="", char *account_number="", int balance=0, float interesRate=0, int limit=0): DebitAccount(owner,account_number,balance){
        this->interestRate=interesRate;
        this->limit=limit;
    }
    CreditAccount(DebitAccount &da, float interesRate=0, int limit=0): DebitAccount(da){
        this->interestRate=interesRate;
        this->limit=limit;
    }

    friend ostream &operator<<(ostream &os, const CreditAccount &account) {//AutoGenerate
        os<<"Credit Account ";
        os << DebitAccount (account) << " || InteresRate: " << account.interestRate << " || Limit: "
           << account.limit;
        return os;
    }
    bool withdraw (int amount){
        if (DebitAccount::withdraw(amount)){
            return true;
        } else {
            if (balance>0){
                amount-=balance;
                balance = 0;
            }
            int calculatedInterest = (int) (amount * interestRate);
            if (balance - calculatedInterest - amount < limit){
                return false;
            } else {
                balance-=(calculatedInterest+amount);
                return true;
            }
        }

    }
};

int main(){
    DebitAccount da("Ardit","12345",1000);
    cout<<da<<endl;
    cout<<"---------------"<<endl;
    CreditAccount ca(da,0.1,-10000);
    ca.deposit(1000);
    cout<<ca;
    return 0;
}