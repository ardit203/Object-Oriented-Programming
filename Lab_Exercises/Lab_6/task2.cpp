#include <iostream>
#include <cstring>

using namespace std;

class Book{
    char *name;
    int *ISBN;
    int numOfPages;
    void copy(const Book &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->ISBN=new int [5];
        for(int i=0 ; i<5 ; i++){
            this->ISBN[i]=other.ISBN[i];
        }
        this->numOfPages=other.numOfPages;
    }
public:
    Book(){
        this->name=new char [strlen("")+1];
        strcpy(this->name,"");
        this->ISBN=new int [5];
        for(int i=0 ; i<5 ; i++){
            this->ISBN[i]=0;
        }
        this->numOfPages=0;
    }
    Book(char *name, const int *ISBN, int numOfPages){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->ISBN=new int [5];
        for(int i=0 ; i<5 ; i++){
            this->ISBN[i]=ISBN[i];
        }
        this->numOfPages=numOfPages;
    }
    Book(const Book &other){
        copy(other);
    }
    Book &operator=(const Book &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        delete [] ISBN;
        copy(other);
        return *this;
    }
    ~Book(){
        delete [] name;
        delete [] ISBN;
    }
    bool operator==(Book &other){
        for(int i=0 ; i<5 ; i++){
            if(ISBN[i]!=other.ISBN[i]){
                return false;
            }
        }
        return true;
    }
        int getNumberOfPages(){
        return numOfPages;
    }
};

class BorrowABook{
    char name[100];
    Book *books;
    int numOfBooks;
public:
    BorrowABook(char *name=""){
        strcpy(this->name,name);
        numOfBooks=0;
        books=new Book [numOfBooks];
    }
    BorrowABook &operator+=(const Book &book){
        Book *tmp=new Book [numOfBooks+1];
        for(int i=0 ; i<numOfBooks ; i++){
            tmp[i]=books[i];
        }
        delete [] books;
        tmp[numOfBooks++]=book;
        books=tmp;
        return *this;
    }
    BorrowABook &operator-=(Book &book){
        Book *tmp=new Book[numOfBooks];
        int k=0;
        for(int i=0 ; i<numOfBooks ; i++){
            if(books[i]==book){
                continue;
            }
            tmp[k++]=books[i];
        }
        delete [] books;
        numOfBooks=k;
        books=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const BorrowABook &book){
        out<<book.name<<endl;
        for(int i=0 ; i<book.numOfBooks ; i++){
            if(book.books[i].getNumberOfPages()>150){
                out<<book.books[i];
            }
        }
        return out;
    }


    void printNumberOfPages(int i) {

    }
};

/// Do NOT edit the main() function
int main()
{
    BorrowABook library("FINKI-Library");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char title[100];
        int isbn[5];
        int pages;

        cin>>title;

        for (int j=0;j<5;j++)
            cin>>isbn[j];

        cin>>pages;

        Book nov=Book(title,isbn,pages);

        //adding a new book
        library+=nov;

    }
    cout<<library;
    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin>>title;
    for (int i=0;i<5;i++)
        cin>>isbn[i];
    cin>>pages;

    Book greshka=Book(title,isbn,pages);

    //deleting a book
    library-=greshka;

    library.printNumberOfPages(150);

    return 0;
}