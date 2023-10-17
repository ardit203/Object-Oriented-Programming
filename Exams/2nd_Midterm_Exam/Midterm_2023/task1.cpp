#include <iostream>
#include <cstring>

using namespace std;

class Book{
private:
    char *title;
    char *author;
    int year;
    void copy(const Book &b){
        this->title=new char [strlen(b.title)+1];
        strcpy(this->title,b.title);
        this->author=new char [strlen(b.author)+1];
        strcpy(this->author,b.author);
        this->year=b.year;
    }
public:
    Book(char *title="", char *author="", int year=0){
        this->title=new char [strlen(title)+1];
        strcpy(this->title,title);
        this->author=new char [strlen(author)+1];
        strcpy(this->author,author);
        this->year=year;
    }
    Book(const Book &b){
        copy(b);
    }
    Book &operator=(const Book &b){
        if(this==&b){
            return *this;
        }
        delete [] title;
        delete [] author;
        copy(b);
        return *this;
    }
    ~Book(){
        delete [] title;
        delete [] author;
    }

    friend ostream &operator<<(ostream &os, const Book &book) {
        os<< book.title << " " << book.author << "  " << book.year<<endl;
        return os;
    }
    friend istream &operator>>(istream &in,  Book &book){
        in>>book.author>>book.title;
        in>>book.year;
        return in;
    }
    char *getAuthor(){
        return author;
    }

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LibraryFull{
public:
    void show(){
        cout<<"Library is Full"<<endl;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Library{
private:
    char *name;
    Book books[30];
    int numOfBooks;
    int spaceForBooks;
    void copy(Library &l){
        this->name=new char [strlen(l.name)+1];
        strcpy(this->name,l.name);
        this->numOfBooks=l.numOfBooks;
        for(int i=0 ; i<numOfBooks ; i++){
            books[i]=l.books[i];
        }
        this->spaceForBooks=l.spaceForBooks;
    }
public:
    Library(char *name=""){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->numOfBooks=0;
        this->spaceForBooks=0;
    }
    Library(Library &l){
        copy(l);
    }
    Library &operator=(Library &l){
        if(this==&l){
            return *this;
        }
        delete [] name;
        copy(l);
        return *this;
    }
    ~Library(){
        delete [] name;
    }
    Library &operator+=(Book &b){
        if(spaceForBooks==0){
            spaceForBooks+=5;
        } else if(numOfBooks==spaceForBooks){
            spaceForBooks*=2;
            throw LibraryFull();
        }

        books[numOfBooks]=b;
        numOfBooks++;
        return *this;
    }
    friend ostream &operator<<(ostream &out, Library &l){
        out<<l.name<<endl;
        for(int i=0 ; i<l.numOfBooks ; i++){
            out<<l.books[i];
        }
        return out;
    }
    Book *bookByAuthor(char *author, int *found){
        Book *BOOKS=new Book[numOfBooks];
        for(int i=0 ; i<numOfBooks ; i++){
            if(strcmp(author,books[i].getAuthor())==0){
                BOOKS[*(found)]=books[i];
                (*found)++;
            }
        }
        return BOOKS;
    }
};

int main(){//My main function
    int testCase;
    cin>>testCase;
    if(testCase==1){
        cout<<"CLASS BOOK CONSTRUCTORS"<<endl;
        Book A("ARdit","SeLmani",2012);
        Book B("ARMEND", "SELMANI",2022);
        Book C(A);
        C=B;
        cout<<"ALL GOOD";
    } else if(testCase==2){
        cout<<"CLASS BOOK << OPERATOR"<<endl;
        Book A("ARdit","SeLmani",2012);
        Book B("ARMEND", "SELMANI",2022);
        Book C(A);
        cout<<A<<B<<C;
        C=B;
        cout<<C;
    } else if(testCase==3){
        cout<<"CLASS LIBRARY CONSTRUCTORS"<<endl;
        Library l1("LIKOVA");
        Library l2(l1);
        Library l3;
        l3=l2;
        cout<<"ALL GOOD";
    } else if(testCase==4){
        cout<<"CLASS LIBRARY << & += OPERATOR & BOOK BY AUTHOR METHOD"<<endl;
        Library l("LIKOVA");
        Book b1("Book1","Ardit",2023);
        try {
            l+=b1;
        }catch (LibraryFull &e){
            e.show();
        }
        Book b2("Book2", "Armend",2022);
        try {
            l+=b2;
        }catch (LibraryFull &e){
            e.show();
        }
        Book b3("Book3","Arian", 2021);
        try {
            l+=b3;
        }catch (LibraryFull &e){
            e.show();
        }
        Book b4("Book4", "Hasan",2020);
        try {
            l+=b4;
        }catch (LibraryFull &e){
            e.show();
        }
        Book b5("Book5","Ardit",2019);
        try {
            l+=b5;
        }catch (LibraryFull &e){
            e.show();
        }
        Book b6("Book6","Kushtrim",2018);
        try {
            l+=b6;
        }catch (LibraryFull &e){
            e.show();
        }
        Book b7("Book7","Ardit",2017);
        try {
            l+=b7;
        }catch (LibraryFull &e){
            e.show();
        }
        cout<<l;
        int found=0;
        char author[30]="Ardit";
        Book *b=l.bookByAuthor(author,&found);
        if(found==0){
            cout<<"\nNo Books by "<<author<<endl;
        } else{
            cout<<"\nBooks by "<<author<<":"<<endl;
            for(int i=0 ; i<found ; i++){
                cout<<b[i];
            }
        }
    }
    return 0;
}