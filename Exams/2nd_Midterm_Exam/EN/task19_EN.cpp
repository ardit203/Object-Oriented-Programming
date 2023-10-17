#include <iostream>
#include <cstring>
using namespace std;

// your code here

class Parcel{
protected:
    int id;
    static int PRC;
public:
    Parcel(int id=0){
        this->id=id;
    }
   static void setProcessingPrice(int d){
       PRC=d;
   }
   int getId(){
       return id;
    }
};

int Parcel::PRC=150;


//=================================================================================================

class Envelope:public Parcel{
private:
    char receiver[50];
    int width;
    int length;
    void copy(const Envelope &other){
        this->id=other.id;
        strcpy(this->receiver,other.receiver);
        this->width=other.width;
        this->length=other.length;
    }
public:
    Envelope(int id=0, char *receiver="", int width=0, int length=0){
        this->id=id;
        this->width=width;
        this->length=length;
        strcpy(this->receiver,receiver);
    }
    Envelope(const Envelope &other){
        copy(other);
    }
    Envelope &operator =(const Envelope &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    int price(){
       //C + L * W * 0.3
       float p= PRC + length * width * 0.3;
        return p;
    }
    char *getReceiver(){
        return receiver;
    }
};

//=======================================================================================================


class PostOffice{
    Envelope envelopes[100];
    int n;
public:
    PostOffice(){
        n=0;
    }
    int sendEnvelope(int id, char* receiver, int length, int width){
        Envelope p(id,receiver,width,length);
        envelopes[n++]=p;
        return p.price();
    }
    void printEnvelopsTo(char* receiver){

        cout<<"For "<<receiver<<" are envelops with ids: ";
        for(int i=0 ; i<n ; i++){
            if(strcmp(envelopes[i].getReceiver(),receiver)==0){
                cout<<envelopes[i].getId()<<" ";
            }
        }
        cout<<endl;
    }
};



int main() {

    int type;
    int n;
    int price;
    int id;
    int height, width;
    char receiver[50];

    PostOffice p;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> type;
        if (type == 1) { // send envelope
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:" << p.sendEnvelope(id, receiver, width, height) << endl;
        } else if (type == 2) { // print envelops to
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) { // set processing PRC
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) { // Parcel
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {// Envelope
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId() << " To: " << p2.getReceiver() << " is: " << p2.price() << endl;
        }
    }
    return 0;
}
