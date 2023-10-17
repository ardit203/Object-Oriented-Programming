#include <iostream>
#include <cstring>
using namespace std;

// your code here

class IndexOutOfBounds{
private:
    int i;
public:
    IndexOutOfBounds(int i){
        this->i=i;
    }
    void show(){
        cout<<"Index '"<< i <<"' is out of bounds"<<endl;
    }
};

//=================================================================================

class String{
    char *content;
    int n;
    void copy(const String &o){
        this->n=o.n;
        this->content=new char [n];
        strcpy(this->content,o.content);
    }
public:
    String(char *content=""){
        this->content=new char [strlen(content)+1];
        strcpy(this->content,content);
        this->n= strlen(content);
    }
    String(const String &o){
        copy(o);
    }
    String operator=(const String &o){
        if(this==&o){
            return *this;
        }
        delete [] content;
        copy(o);
        return *this;
    }
    ~String(){
        delete [] content;
    }
    char &operator[](int i){
        if(i<0 || i>=n){
            throw IndexOutOfBounds(i);
        }
        return content[i];
    }
    int getSize(){
        return n;
    }
    char *getContent(){
        return content;
    }
};

//=============================================================================

class StringBuilder{
private:
    char *contents;
    int n;
    int capacity;
    void copy(const StringBuilder &o){
        this->capacity=o.capacity;
        this->n=o.n;
        this->contents=new char [n];
        strcpy(this->contents,o.contents);
    }
public:
    StringBuilder(int capacity){
        this->capacity=capacity;
        this->n=0;
        this->contents=new char [n];
        contents= nullptr;
    }
    StringBuilder(const StringBuilder &o){
        copy(o);
    }
    StringBuilder &operator=(const StringBuilder &o){
        if(this==&o){
            return *this;
        }
        delete contents;
        copy(o);
        return *this;
    }
    ~StringBuilder(){
        delete [] contents;
    }
    StringBuilder &operator+=(String &s){
        int c=n+s.getSize();
        if(capacity<=c+1){
            capacity*=2;
        }
        if(capacity<=c+1){
            int d=c-capacity;
            if(d==-1){
                d=1;
            }

            capacity=capacity+d;
        }
        char *tmp=new char [c+1];
        int flag=1;
        if(contents!= nullptr){
            strcpy(tmp,contents);
            flag=0;
        }
        delete[] contents;
        if(flag){
            strcpy(tmp,s.getContent());
        } else{
            strcat(tmp,s.getContent());
        }
        n=c;
        contents=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const StringBuilder &s){
        out<<"Capacity: "<<s.capacity<<endl;
        out<<"Size: "<<s.n<<endl;
        out<<"Contents: "<<s.contents<<endl;
        return out;
    }
};

//int main(){
//    StringBuilder s(20);
//    String string("ArditSelmaniNgaFshatiLikove");
//    String s2("ARDIRTSELMANIPREJLIKOVEPOVJEN");
//    s+=string;
//    s+=s2;
//    cout<<s;
//    return 0;
//}

int main() {
    int n;
    cin >> n;
    StringBuilder sb(n);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        char input[100];
        cin >> input;
        String s(input);
        int x;
        cin >> x;
        try {
            cout << "s[" << x << "] = " << s[x] << endl;
        }catch (IndexOutOfBounds &e){
            e.show();
        }



        sb += s;
    }
    cout << sb;
    return 0;
}