#include<iostream>
#include<cstring>
using namespace std;

// Your code here

class ExistingBill{
private:
    char *billNumber;
public:
    ExistingBill(char *billNumber){
        this->billNumber=new char [strlen(billNumber)+1];
        strcpy(this->billNumber,billNumber);
    }

    void show_message(){
        cout<<"The bill already exists"<<endl;
    }
};


//-------------------------------------------------------------------------

class Bill{
    char *billNumber;
    int price;
    char date[8];
    bool status;
    void copy(const Bill &other){
        this->billNumber=new char [strlen(other.billNumber)+1];
        strcpy(this->billNumber,other.billNumber);
        this->price=other.price;
        strcpy(this->date,other.date);
        this->status=other.status;
    }
public:
    Bill(char *billNumber="", int price=0, char *date="", bool status= false){
        this->billNumber=new char [strlen(billNumber)+1];
        strcpy(this->billNumber,billNumber);
        this->price=price;
        strcpy(this->date,date);
        this->status=status;
    }
    Bill(const Bill &other){
        copy(other);
    }
    Bill &operator=(const Bill &other){
        if(this==&other){
            return *this;
        }
        delete [] billNumber;
        copy(other);
        return *this;
    }
    ~Bill(){
        delete [] billNumber;
    }
    bool operator==(Bill &other){
        return strcmp(this->billNumber,other.billNumber)==0;
    }

    friend ostream &operator<<(ostream &os, const Bill &bill) {
        os<<bill.billNumber<<"("<<bill.date<<")"<<" - "<<bill.price;
        return os;
    }
    char *getBill(){
        return billNumber;
    }
    bool getStatus() const {
        return status;
    }
    char getDate(int i){
        return date[i];
    }
    int getPrice(){
        return price;
    }
    char *getDate(){
        return date;
    }
};


//------------------------------------------------------------------------------


class UserProfile{
    char username[30];
    Bill bills[30];
    int n;
public:
    UserProfile(char *username=""){
        strcpy(this->username,username);
        n=0;
    }
    UserProfile &operator+=(Bill &b){
        int flag=1;
        if(n==0){
            bills[n++]=b;
            return *this;
        }
        for(int i=0 ; i<n ; i++){
            if(bills[i]==b){
                flag=0;
            }
            if(bills[i]==b){
                throw ExistingBill(b.getBill());
            }
        }
        if(flag){
            bills[n++]=b;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const UserProfile &profile) {
        os<<"Unpaid bills of user "<<profile.username<<" are:"<<endl;
        for(int i= 0 ; i<profile.n ; i++){
            if(!profile.bills[i].getStatus()){
                os<<profile.bills[i]<<endl;
            }
        }
        return os;
    }
    int totalDue(int month, int year){
        int sum=0;
        for(int i=0 ; i<n ; i++){
            char str[8];
            strcpy(str,bills[i].getDate());
            int m=(str[0]-'0')*10+(str[1]-'0');
            int y=(str[3]-'0')*1000+(str[4]-'0')*100+(str[5]-'0')*10+(str[6]-'0');
            if(month==m && year==y){
                sum+=bills[i].getPrice();
            }
        }
        return sum;
    }
};





int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator &lt;&lt;-----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout << b;
    } else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;

    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += &&lt;&lt; -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            try{
                Bill s(number, price, month, status);
                up += s;
            } catch (ExistingBill &e) {
                e.show_message();
            }

        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            try {
                Bill s(number, price, month, status);
                up += s;
            }catch (ExistingBill &e) {
                e.show_message();
            }

        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            try{
                Bill s(number, price, month, status);
                up += s;
            }catch (ExistingBill &e) {
                e.show_message();
            }
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}
