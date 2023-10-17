#include <iostream>
#include <cstring>
using namespace std;

// your code here

class Word{
private:
    char *word;
    void copy(const Word &other){
        this->word=new char [strlen(other.word)+1];
        strcpy(this->word,other.word);
    }
public:
    Word(char *word="UNDIFINED"){
        this->word=new char [strlen(word)+1];
        strcpy(this->word,word);
    }
    Word(const Word &other){
        copy(other);
    }
    Word &operator=(const Word &other){
        if(this==&other){
            return *this;
        }
        delete [] word;
        copy(other);
        return *this;
    }
    ~Word(){
        delete [] word;
    }
    void print(){
        cout<<word;
    }
};

class Sentence{
private:
    Word *words;
    int numOfWords;
    int totalCapacity;
    void copy(const Sentence &other){
        this->totalCapacity=other.totalCapacity;
        this->numOfWords=other.numOfWords;
        this->words=new Word [other.totalCapacity];
        for(int i=0 ; i<numOfWords ; i++){
            this->words[i]=other.words[i];
        }
    }
public:
    Sentence(int totalCapacity=10){
        this->totalCapacity=totalCapacity;
        this->numOfWords=0;
        this->words=new Word [this->totalCapacity];
    }
    Sentence(const Sentence &other){
        copy(other);
    }
    Sentence &operator=(const Sentence &other){
        if(this==&other){
            return *this;
        }
        delete [] words;
        copy(other);
        return *this;
    }
    ~Sentence(){
        delete [] words;
    }

    void increaseCapacity(){
        Word *tmp=new Word [this->totalCapacity+10];

        for(int i=0 ; i<numOfWords ; i++){
            tmp[i]=words[i];
        }
        delete [] words;
        words=tmp;
        this->totalCapacity+=10;
    }

    void add(Word word) {
        if(this->numOfWords==this->totalCapacity){
            increaseCapacity();
        }
        words[numOfWords++]=word;
    }

    void print() {
        for(int i=0 ; i<numOfWords ; i++){
            words[i].print();
            cout<<" ";
        }
        cout<<endl;
    }

    void swap(int i, int j) {
        Word tmp=words[i];
        words[i]=words[j];
        words[j]=tmp;
    }
};
int main() {
    int n;
    cin >> n;
    cin.get();
    cout << "CONSTRUCTOR" << endl;
    Sentence s;
    cout << "ADD WORD" << endl;
    for (int i = 0; i < n; ++i) {
        char w[100];
        cin.getline(w, 100);
        Word word(w);
        s.add(word);
    }
    cout << "PRINT SENTENCE" << endl;
    s.print();
    cout << "COPY" << endl;
    Sentence x = s;
    cout << "SWAP" << endl;
    x.swap(n / 2, n / 3);
    x.print();
    cout << "ORIGINAL" << endl;
    s.print();
    return 0;
}
