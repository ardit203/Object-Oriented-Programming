#include <iostream>
#include <cstring>

using namespace std;

class DisciplinaryAction{
    char *name;
    int index;
    char *reason;
    int numSessions;
    void copy(const DisciplinaryAction &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->index=other.index;
        this->reason=new char [strlen(other.reason)+1];
        strcpy(this->reason,other.reason);
        this->numSessions=other.numSessions;
    }
public:
    DisciplinaryAction(char *name="", int index=0, char *reason="", int numSessions=0) {
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->index=index;
        this->reason=new char [strlen(reason)+1];
        strcpy(this->reason,reason);
        this->numSessions=numSessions;
    }
    DisciplinaryAction(const DisciplinaryAction &other){
        copy(other);
    }
    DisciplinaryAction &operator=(const DisciplinaryAction &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        delete [] reason;
        copy(other);
        return *this;
    }
    ~DisciplinaryAction(){
        delete [] name;
        delete [] reason;
    }

    int getIndex() const {
        return index;
    }

    void setIndex(int index) {
        this->index = index;
    }
    void print(){
        cout<<"Student: "<<name<<endl;
        cout<<"Student's index: "<<index<<endl;
        cout<<"Reason: "<<reason<<endl;
        cout<<"Sessions: "<<numSessions<<endl;
    }
    friend ostream &operator<<(ostream &out, const DisciplinaryAction &s){
        out<<"Student: "<<s.name<<endl;
        out<<"Student's index: "<<s.index<<endl;
        out<<"Reason: "<<s.reason<<endl;
        out<<"Sessions: "<<s.numSessions<<endl;
        return out;
    }
    DisciplinaryAction &operator++(){
        ++numSessions;
    }
    DisciplinaryAction operator++(int){
        DisciplinaryAction copy(*this);
        ++numSessions;
        return copy;
    }
    bool operator>=(DisciplinaryAction &other){
        return numSessions>=other.numSessions;
    }
};


/// Do NOT edit the main() function

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}