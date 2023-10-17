#include <iostream>
#include <cstring>
using namespace std;

// your code here

class Character{
private:
    char c;
    void copy(const Character &other){
        c=other.c;
    }
public:
    Character(char c=' '){
        this->c=c;
    }
    Character(const Character &other){
        copy(other);
    }
    Character &operator=(const Character &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Character &character) {
        os << character.c;
        return os;
    }
    void setC(char ch){
        c=ch;
    }
    char getC(){
        return c;
    }
};

class CharSequence{
private:
    Character *chars;
    int n;
    void copy(const CharSequence &other){
        this->n=other.n;
        this->chars=new Character [this->n];
        for(int i=0 ; i<n ; i++){
            chars[i]=other.chars[i];
        }
    }
public:
    CharSequence(char *chars=""){
        this->n= strlen(chars);
        this->chars=new Character [n];
        for(int i=0 ; i<n ; i++){
            this->chars[i].setC(chars[i]);
        }
    }
    ~CharSequence(){
        delete [] chars;
    }
    CharSequence(const CharSequence &other){
        copy(other);
    }
    CharSequence &operator=(const CharSequence &other){
        if(this==&other){
            return *this;
        }
        delete [] chars;
        copy(other);
        return *this;
    }
    Character& operator[](int i){
        return chars[i];
    }
    CharSequence& operator +=(const Character &c){
        Character *tmp=new Character [n+1];
        for(int i=0 ; i<n ; i++){
            tmp[i]=chars[i];
        }
        delete [] chars;
        tmp[n++]=c;
        chars=tmp;
        return *this;
    }
    bool operator==(const CharSequence &cs){
        if(this->n!=cs.n){
            return false;
        }
        for(int i=0 ; i<n ; i++){
            if(chars[i].getC()!=cs.chars[i].getC()){
                return false;
            }
        }
        return true;
    }
    int operator[](char c){
        int counter=0;
        for(int i=0 ; i<n ; i++){
            if(chars[i].getC()==c){
                counter++;
            }
        }
        return counter;
    }
    CharSequence toUpperCase(){
        for(int i= 0 ; i<n ; i++){
            chars[i].setC(toupper(chars[i].getC()));
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const CharSequence &sequence) {
        for(int i=0 ; i<sequence.n ; i++){
            os<<sequence.chars[i];
        }
        return os;
    }
};







int main() {
    int n;
    cin >> n;

    if(n == 1) {
        cout << "Testing Character class" << endl;
        cout << "Character constructor" << endl;
        char c;
        cin >> c;
        Character cc(c);
        cout << "OK" << endl;
        cout << "Character operator <<" << endl;
        cout << cc << endl;
    } else if(n == 2) {
        cout << "Testing CharSequence constructors" << endl;
        char word[100];
        cin >> word;
        CharSequence cs1(word);
        cout << cs1 << endl;
    } else if(n == 3) {
        cout << "Testing CharSequence copy constructor and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy(cs);
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if(n == 4) {
        cout << "Testing CharSequence =operator and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy;
        copy = cs;
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if(n == 5) {
        cout << "Testing CharSequence operator+=" << endl;
        CharSequence cs;
        char word[100];
        cin >> word;
        int len = strlen(word);
        for(int i = 0; i < len; ++i) {
            cs += Character(word[i]);
        }
        cout << cs << endl;
    } else if(n == 6) {
        cout << "Testing CharSequence operator[char]" << endl;
        CharSequence cs("If you don't read the newspaper, you're uninformed. If you read the newspaper, you're mis-informed.");
        cout << cs['e'] << endl;
    } else if(n == 7) {
        cout << "Testing CharSequence toUpperCase" << endl;
        CharSequence cs("If you tell the truth, you don't have to remember anything");
        cout << cs.toUpperCase() << endl;
    } else if(n == 8) {
        cout << "Testing CharSequence operator ==" << endl;
        CharSequence cs1("abc");
        CharSequence cs2("abc");
        CharSequence cs3("abcd");
        CharSequence cs4("xyz");
        cout << (cs1 == cs2) << endl;
        cout << (cs1 == cs3) << endl;
        cout << (cs2 == cs4) << endl;
    }

    return 0;
}

