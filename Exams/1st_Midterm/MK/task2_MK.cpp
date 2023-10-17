#include <iostream>
#include <cstring>
using namespace std;

class List{
private:
    int *list;
    int numOfElements;
    void copy(const List &other){
        this->numOfElements=other.numOfElements;
        this->list=new int [other.numOfElements];
        for(int i=0 ; i<numOfElements ; i++){
            this->list[i]=other.list[i];
        }
    }
public:
    List(int *list, int numOfElements){
        this->numOfElements=numOfElements;
        this->list=new int [numOfElements];
        for(int i=0 ; i<numOfElements ; i++){
            this->list[i]=list[i];
        }
    }
    List(){
        this->numOfElements=0;
        this->list=new int [numOfElements];
    }
    List(const List &other){
        copy(other);
    }
    List &operator=(const List &other){
        if(this==&other){
            return *this;
        }
        delete [] list;
        copy(other);
        return *this;
    }
    int sum(){
        int sum=0;
        for(int i=0 ; i<numOfElements ; i++){
            sum+=list[i];
        }
        return sum;
    }
    double avg(){
        double avg=sum()/double (numOfElements);
        return avg;
    }
    void pecati(){
        cout<<numOfElements<<": ";
        for(int i=0 ; i<numOfElements ; i++){
            cout<<list[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<avg();
    }
    int getNumOfElements()const {
        return numOfElements;
    }
    ~List(){
        delete [] list;
    }
};

class ListContainer{
    List *ArrayOfLists;
    int numOfLists;
    int attempts;
    int failed;
    void copy(const ListContainer &other){
        this->numOfLists=other.numOfLists;
        this->ArrayOfLists=new List [this->numOfLists];
        for(int i=0 ; i<numOfLists ; i++){
            ArrayOfLists[i]=other.ArrayOfLists[i];
        }
        this->attempts=other.attempts;
        this->failed=other.failed;
    }
public:
    ListContainer(){
        numOfLists=0;
        attempts=0;
        failed=0;
        this->ArrayOfLists=new List [numOfLists];
    }
    ListContainer(const ListContainer &other) {
        copy(other);
    }
    ListContainer &operator = (const ListContainer &other){
        if(this==&other){
            return *this;
        }
        delete [] ArrayOfLists;
        copy(other);
        return *this;
    }
    void print(){
        if(numOfLists==0){
            cout<<"The list is empty"<<endl;
            return;
        }
        for(int i=0 ; i<numOfLists ; i++){
            cout<<"List number: "<<i+1<<" List info: ";
            ArrayOfLists[i].pecati();
            cout<<endl;
        }
        cout<<"Sum: "<<Sum();
        cout<<" Average: "<<Average();
        cout<<endl;
        cout<<"Successful attempts: "<<attempts<<" Failed attempts: "<<failed;
        cout<<endl;
    }
    bool isSame(List & l){
        for(int i=0 ; i<numOfLists ; i++){
            if(ArrayOfLists[i].sum()==l.sum()){
                return true;
            }
        }
        return false;
    }
    void addNewList(List l){
        if(isSame(l)){
            failed++;
            return;
        }
        List *tmp=new List[numOfLists+1];
        for(int i=0 ; i<numOfLists ; i++){
            tmp[i]=ArrayOfLists[i];
        }
        delete [] ArrayOfLists;
        tmp[numOfLists]=l;
        ArrayOfLists=tmp;
        numOfLists++;
        attempts++;
    }
    int Sum(){
        int s=0;
        for(int i=0 ; i<numOfLists ; i++){
            s+=ArrayOfLists[i].sum();
        }
        return s;
    }
    double Average(){
        int s=Sum();
        int count=0;
        for(int i=0 ; i<numOfLists ; i++){
            for(int j=0 ; j<ArrayOfLists[i].getNumOfElements() ; j++){
                count++;
            }
        }
        double average=double (s)/count;
        return average;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.Sum()<<" "<<lc.Sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.Sum()<<" "<<lc.Sum()<<endl;
        lc1.Sum();
        lc1.Average();

    }
    else {
        lc.print();
    }
}