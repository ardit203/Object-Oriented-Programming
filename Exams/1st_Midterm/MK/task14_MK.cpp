#include<iostream>
#include<cstring>

using namespace std;
enum Extension{
    pdf,txt,exe
};

class File{
private:
    char *name;
    Extension ext;
    char *fileOwner;
    int size;
    void copy(const File &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->fileOwner=new char [strlen(other.fileOwner)+1];
        strcpy(this->fileOwner,other.fileOwner);
        this->size=other.size;
        this->ext=other.ext;
    }
public:
    File(char *name="", char *fileOwner="",int size=0, Extension ext=Extension(0)){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->fileOwner=new char [strlen(fileOwner)+1];
        strcpy(this->fileOwner,fileOwner);
        this->size=size;
        this->ext=ext;
    }
    File(const File &other){
        copy(other);
    }
    File &operator=(const File &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        delete [] fileOwner;
        copy(other);
        return *this;
    }
    ~File(){
        delete [] name;
        delete [] fileOwner;
    }

    void print() {
        cout<<"File name: "<<name<<".";
        if(ext==Extension(0)){
            cout<<"pdf"<<endl;
        } else if(ext==Extension(1)){
            cout<<"txt"<<endl;
        }else{
            cout<<"exe"<<endl;
        }
        cout<<"File owner: "<<fileOwner<<endl;
        cout<<"File size: "<<size<<endl;
    }
    bool equals(const File & that){
        return strcmp(name,that.name)==0 && strcmp(fileOwner,that.fileOwner)==0 && ext==that.ext;
    }
    bool equalsType(const File & that){
        return strcmp(name,that.name)==0 && ext==that.ext;
    }
};

class Folder{
    char *name;
    int numOfFiles;
    File *files;
public:
    Folder(char *name){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->numOfFiles=0;
        this->files=new File [numOfFiles];
    }
    Folder(const Folder &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->numOfFiles=other.numOfFiles;
        this->files=new File [numOfFiles];
        for(int i=0 ; i<numOfFiles ; i++){
            files[i]=other.files[i];
        }
    }
    ~Folder(){
        delete [] name;
        delete [] files;
    }

    void print() {
        cout<<"Folder name: "<<name<<endl;
        for(int i=0 ; i<numOfFiles ; i++){
            files[i].print();
        }
    }

    void add(File &file) {
        File *tmp=new File [numOfFiles+1];
        for(int i=0 ; i<numOfFiles ; i++){
            tmp[i]=files[i];
        }
        delete [] files;
        tmp[numOfFiles++]=file;
        files=tmp;
    }

    void remove(File file) {
        File *tmp=new File[numOfFiles];
        int k=0;
        for(int i=0 ; i<numOfFiles ; i++){
            if(!files[i].equals(file)){
                tmp[k++]=files[i];
            }
        }
        delete [] files;
        files=tmp;
        numOfFiles=k;

    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}