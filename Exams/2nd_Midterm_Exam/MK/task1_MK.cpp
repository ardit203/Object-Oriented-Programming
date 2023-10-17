#include <iostream>
#include <cstring>
using namespace std;

class Book{
protected:
    char isbn[20];
    char title[50];
    char author[50];
    float price;
public:
    Book(char *isbn="", char *title="", char *author="", float price=0){
        strcpy(this->isbn,isbn);
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->price=price;
    }
    void setISBN(char *str){
        strcpy(isbn,str);
    }
    virtual float bookPrice()=0;
        bool operator>(Book &b){
        return bookPrice()>b.bookPrice();
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////

class OnlineBook:public Book{
private:
    char *url;
    int size;
    void copy(const OnlineBook &other){
        strcpy(this->isbn,other.isbn);
        strcpy(this->title,other.title);
        strcpy(this->author,other.author);
        this->price=other.price;
        this->url=new char [strlen(other.url)+1];
        strcpy(this->url,other.url);
        this->size=other.size;
    }
public:
    OnlineBook(char *isbn="", char *title="", char *author="", float price=0, char *url="", int size=0)
    : Book(isbn,title,author,price){
        this->url=new char [strlen(url)+1];
        strcpy(this->url,url);
        this->size=size;
    }
    OnlineBook(const OnlineBook &other){
        copy(other);
    }
    OnlineBook &operator=(const OnlineBook &other){
        if(this==&other){
            return *this;
        }
        delete [] url;
        copy(other);
        return *this;
    }
    ~OnlineBook(){
        delete [] url;
    }

    float bookPrice() override {
        if(size>20){
            return price*1.2;
        }
        return price;
    }
    friend ostream &operator<<(ostream &out, OnlineBook &p){
        out<<p.isbn<<": "<<p.title<<", "<<p.author<<" "<<p.bookPrice()<<endl;
      return out;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////

class PrintBook: public Book{
private:
    float weight;
    bool inStock;
public:
    PrintBook(char *isbn="", char *title="", char *author="", float price=0, float weight=0, bool inStock=false)
            : Book(isbn,title,author,price){
        this->weight=weight;
        this->inStock=inStock;
    }
    float bookPrice() override {
        if(weight>0.7){
            return price*1.15;
        }
        return price;
    }
    friend ostream &operator<<(ostream &out, PrintBook &p){
        out<<p.isbn<<": "<<p.title<<", "<<p.author<<" "<<p.bookPrice()<<endl;
        return out;
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////


void mostExpensiveBook (Book** books, int n){
    cout<<"FINKI-Education"<<endl;
    int online=0, printed=0;
    Book *max=books[0];
    for(int i=0 ; i<n ; i++){
        OnlineBook *o=dynamic_cast<OnlineBook *>(books[i]);
//        PrintBook *p=dynamic_cast<PrintBook *>(books[i]);
        if(o!= nullptr){
            online++;
        } else{
            printed++;
        }
        if(books[i]->bookPrice()>max->bookPrice()){
            max=books[i];
        }
    }
//    Total number of online books: 2
//    Total number of print books: 1
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<printed<<endl;
    cout<<"The most expensive book is:"<<endl;
    cout<<*max;
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
