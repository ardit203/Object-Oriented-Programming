#include <iostream>
#include <cstring>
using namespace std;

// Your code here!!!


class MonthlyInvoice{
protected:
    char username[100];
    int userNumber;
    float initial_price;
    int spent_gigabytes;
    void copy(const MonthlyInvoice &other){
        strcpy(this->username,other.username);
        this->userNumber=other.userNumber;
        this->initial_price=other.initial_price;
        this->spent_gigabytes=other.spent_gigabytes;
    }
public:
    MonthlyInvoice(char *username="", int userNumber=0, float initial_price=0, int spent_gigabytes=0){
        strcpy(this->username,username);
        this->userNumber=userNumber;
        this->initial_price=initial_price;
        this->spent_gigabytes=spent_gigabytes;
    }
    MonthlyInvoice(const MonthlyInvoice &other){
        copy(other);
    }
    virtual float total_price()=0;
    bool operator>(MonthlyInvoice *m){
        bool b=total_price()>m->total_price();
        return b;
    }
};


//======================================================================================================

class BusinessInvoice:public MonthlyInvoice{
private:
    bool line;
    int free_gigabytes;
public:
    BusinessInvoice(char *username="", int userNumber=0, float initial_price=0, int spent_gigabytes=0,
                    bool line= false, int free_gigabytes=0):
            MonthlyInvoice(username,userNumber,initial_price,spent_gigabytes){
        this->line=line;
        this->free_gigabytes=free_gigabytes;
    }
    BusinessInvoice(const BusinessInvoice &other){
        MonthlyInvoice::copy(other);
    }

    float total_price() override {
        int d=spent_gigabytes-free_gigabytes;
        if(d<0){
            d=0;
        }
        float t=initial_price;
        if(line){
            t=t*(1+(50.0/100.0));
        }
        float p=t+d*100.0;
        return p;
    }
    BusinessInvoice operator++(int){
        BusinessInvoice Copy(*this);
        ++spent_gigabytes;
        return Copy;
    }
    friend ostream &operator<<(ostream &out, BusinessInvoice &p){
        out<<p.userNumber<<" - "<<p.username<<", "<<p.initial_price<<endl;
        if(p.line){
            out<<"optical link, ";
        } else{
            out<<"cable link, ";
        }
        int d=p.spent_gigabytes-p.free_gigabytes;
        if(d<0){
            out<<"0"<<endl;
        } else{
            out<<p.spent_gigabytes-p.free_gigabytes<<endl;
        }
        return out;
    }

};


//=========================================================================================================

class PrivateInvoice:public MonthlyInvoice{
private:
    int *movieSizes;
    int n;
    void copy(const PrivateInvoice &other){
        MonthlyInvoice::copy(other);
        this->n=other.n;
        this->movieSizes=new int[n];
        for(int i=0 ; i<n ; i++){
            movieSizes[i]=other.movieSizes[i];
        }

    }
public:
    PrivateInvoice(char *username="", int userNumber=0, float initial_price=0, int spent_gigabytes=0):
            MonthlyInvoice(username,userNumber,initial_price,spent_gigabytes){
        this->n=0;
        this->movieSizes=new int [n];
    }
    PrivateInvoice(const PrivateInvoice &other){
        copy(other);
    }
    ~PrivateInvoice(){
        delete [] movieSizes;
    }
    int totalGigabytes(){
        int sum=0;
        for(int i=0 ; i<n ; i++){
            sum+=movieSizes[i];
        }
        return sum;
    }
    float total_price(){
        float p=initial_price+spent_gigabytes*50+totalGigabytes()*10;
        return p;
    }
    int operator[](int i){
        if(i>=n || i<0){
            return -1;
        }
        return movieSizes[i];
    }
    PrivateInvoice &operator+=(int k){
        int *tmp=new int [n+1];
        for(int i=0 ; i<n ; i++){
            tmp[i]=movieSizes[i];
        }
        delete [] movieSizes;
        tmp[n++]=k;
        movieSizes=tmp;
        return *this;
    }
    PrivateInvoice operator++(int){
        PrivateInvoice Copy(*this);
        ++spent_gigabytes;
        return Copy;
    }
    int getMoviesNo(){
        return n;
    }
    friend ostream &operator<<(ostream &out, PrivateInvoice &p){
        out<<p.userNumber<<" - "<<p.username<<", "<<p.initial_price<<endl;
        out<<p.spent_gigabytes<<endl;
        out<<p.n<<", "<<p.totalGigabytes()<<endl;
        return out;
    }
};

MonthlyInvoice &biggestInvoice(MonthlyInvoice **mi, int n){
    MonthlyInvoice *max=mi[0];
    for(int i=0 ; i<n ; i++){
        if(mi[i]->total_price()>max->total_price()){
            max=mi[i];
        }
    }
    return *max;
}


// Testing the program!!!
int main(){
    int test_case;
    char username[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
    bool optical;
    int free_gigabytes;
    int num_inc;

    cin>>test_case;
    if (test_case == 1){
        // Test Case Business Invoice - Constructor, operator <<
        cin>>username>>userNumber>>basic_price>>spent_gigabytes;
        cin>>optical>>free_gigabytes;
        BusinessInvoice bi(username, userNumber,basic_price, spent_gigabytes, optical, free_gigabytes);
        cout<<"BusinessInvoice Created:\n";
        cout<<bi;
    }
    else if (test_case == 2) {
        // Test Case Business Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice:\n";
        cout << bi;
        cout << "testing operator++\n";

        // Additional spent gigabytes
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i) {
            bi++;
        }
        cout << bi;
    }
    else if (test_case == 3) {
        // Test Case Business Invoice - Constructor, total_price, operators <<, ++,
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "Testing total_price()\n";
        cout << bi;
        cout<<bi.total_price()<<endl;
        bi++;
        cout << bi;
        cout<<bi.total_price()<<endl;
    }
    else if (test_case == 4){
        // Test Case Private Invoice - Constructor, operator <<
        cin>>username>>userNumber>>basic_price>>spent_gigabytes;

        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cout<<"Private Invoice Created:\n";
        cout<<pi;
    }
    else if (test_case == 5) {
        // Test Case Private Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i) {
            pi++;
        }
        cout << pi;
    }
    else if (test_case == 6) {
        // Test Case Private Invoice - Constructor, operators <<, +=
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cout << pi;
    }
    else if (test_case == 7) {
        // Test Case Private Invoice - Constructor, operators <<, +=, []
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cout << pi;
        cout << "Movie sizes: [";
        for (int i=0; i<pi.getMoviesNo(); ++i){
            cout << pi[i] << " ";
        }
        cout << "]" << endl;
    }
    else if (test_case == 8) {
        // Test Case Private Invoice - Constructor, total_price
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cout<<pi;
        cout<< pi.total_price() <<endl;
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i){
            pi++;
        }
        cout << pi;
        cout<< pi.total_price() <<endl;
    }
    else if (test_case == 9) {
        // Test Case

        int num_invoices;
        int invoice_type;

        cin >>num_invoices;
        MonthlyInvoice ** mi = new MonthlyInvoice*[num_invoices];
        for (int j=0;j<num_invoices; ++j) {

            cin >> invoice_type;
            if (invoice_type == 1){
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                cin >> optical >> free_gigabytes;
                BusinessInvoice * bip;
                bip = new BusinessInvoice(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
                cin >> num_inc;
                for (int i=0; i<num_inc; ++i) {
                    (*(bip))++;
                }
                cout << *(bip);
                cout<<bip->total_price()<<endl;

                mi[j] = bip;
            }
            if (invoice_type == 2) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                PrivateInvoice* pip = new PrivateInvoice(username, userNumber, basic_price, spent_gigabytes);
                cin >> num_inc;
                int film_length;
                for (int i = 0; i < num_inc; ++i) {
                    cin >> film_length;
                    (*pip) += film_length;
                }
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*pip)++;
                }
                cout << (*pip);
                cout << pip->total_price() << endl;
                mi[j] = pip;
            }
        }

        cout << "The biggest invoice is:\n";
        MonthlyInvoice& invoice = biggestInvoice(mi, num_invoices);

        MonthlyInvoice* m = &invoice;
        BusinessInvoice* bip;
        PrivateInvoice* pip;
        if (dynamic_cast<BusinessInvoice *> (m)){
            bip = dynamic_cast<BusinessInvoice *> (m);
            cout<<*bip << bip->total_price();
        }
        if (dynamic_cast<PrivateInvoice *> (m)){
            pip = dynamic_cast<PrivateInvoice *> (m);
            cout<<*pip << pip->total_price();
        }

    }
    return 0;
}