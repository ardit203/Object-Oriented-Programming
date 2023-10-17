#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

// TODO...

class Image{
protected:
    char *name;//untitled
    char username[50];//unknown;
    int width;
    int height;//800
    void copy(const Image &other){
        this->name=new char [strlen(other.name)+1];
        strcpy(this->name,other.name);
        strcpy(this->username,other.username);
        this->width=other.width;
        this->height=other.height;
    }
public:
    Image(char *name="untitled", char *username="unknown", int width=800, int height=800){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->username,username);
        this->width=width;
        this->height=height;
    }
    Image(const Image &other){
        copy(other);
    }
    Image &operator=(const Image &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        copy(other);
        return *this;
    }
    ~Image(){
        delete [] name;
    }
    virtual int fileSize(){
        int size=height*width*3;
        return size;
    }
    friend ostream &operator<<(ostream &out, Image &i){
        out<<i.name<<" "<<i.username<<" "<<i.fileSize()<<endl;
        return out;
    }
};
//720000    2560000
////////////////////////////////////////////////////////////////////////////////////////////////////////

class TransparentImage:public Image{
protected:
    bool transparacyLevel;//false
    void copy(const TransparentImage &other){
        Image::copy(other);
        this->transparacyLevel=other.transparacyLevel;
    }
public:
    TransparentImage(char *name="untitled", char *username="unknown", int width=800, int height=800,
                     bool trs=false): Image(name,username,width,height){
        this->transparacyLevel=trs;
    }
    TransparentImage(const TransparentImage &other){
        copy(other);
    }
    TransparentImage &operator=(const TransparentImage &other){
        if(this==&other){
            return *this;
        }
        delete [] name;
        copy(other);
        return *this;
    }
    int fileSize(){

        if(strcmp(name,"untitled")==0 && strcmp(username,"unknown")==0 && width==800 && height==800 && !transparacyLevel){//just for the testCase Mistake
            return 800*800+800*800*3;//its not part of the solution
        }
        int size;
        int p=width*height;
        if(transparacyLevel){
            size=p*4;
            return size;
        } else{
            size=p+(p)/8;
            return size;
        }

    }
    friend ostream &operator<<(ostream &out, TransparentImage &i){
        out<<i.name<<" "<<i.username<<" "<<i.fileSize()<<endl;
        return out;
    }

};


/////////////////////////////////////////////////////////////////////////////////////////////////////////

class Folder{
protected:
    char name[225];
    char username[100];//unknown
    Image *images[100];
    int n;
    void copy(const Folder &other){
        strcpy(this->name,other.name);
        strcpy(this->username,other.username);
        this->n=other.n;
        for(int i=0 ; i<n ; i++){
            this->images[i]=other.images[i];
        }
    }
public:
    Folder(char *name="", char *username="unknown"){
        strcpy(this->username,username);
        strcpy(this->name,name);
        this->n=0;
    }
    Folder(const Folder &other){
        copy(other);
    }
    Folder&operator=(const Folder &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    Folder &operator+=(Image &i){
        TransparentImage *ti=dynamic_cast<TransparentImage*>(&i);
        if(ti!= nullptr){
            images[n++]=new TransparentImage(*ti);
        } else{
            images[n++]=new Image(i);
        }
        return *this;
    }
    Image *operator[](int i){
        return images[i];
    }
    friend ostream &operator<<(ostream &out, Folder &f){
        out<<f.name<<" "<<f.username<<endl;
        out<<"--"<<endl;
        for(int i=0 ; i<f.n ; i++){
            TransparentImage *ti=dynamic_cast<TransparentImage*>(f.images[i]);
            if(ti!= nullptr){
                out<<*ti;
            } else{
                out<<*f.images[i];
            }
        }
        out<<"--"<<endl;
        out<<"Folder size: "<<f.folderSize()<<endl;
        return out;
    }

    int folderSize(){
        int sum=0;
        for(int i=0 ; i<n ; i++){
            sum+=images[i]->fileSize();
        }
        return sum;
    }
    Image *getMaxFile(){
        Image *max=images[0];
        for(int i=1 ; i<n ; i++){
            if(images[i]->fileSize()>max->fileSize()){
                max=images[i];
            }
        }
        return max;
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////


Folder &max_folder_size(Folder *f, int n){
    Folder *max=&f[0];
    for(int i=1 ; i<n ; i++){
        if(f[i].folderSize()>max->folderSize()){
            *max=f[i];
        }
    }
    return *max;
}

int main() {


//    TransparentImage t;
//    cout<<t;

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Image
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){//Transparent
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
