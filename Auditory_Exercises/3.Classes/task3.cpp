#include <iostream>
#include <cstring>
#define EMAIL 50
#define BODY 1000
using namespace std;


class e_mail{
private:
    char from[EMAIL];
    char to[EMAIL];
    char subject[EMAIL];
    char body[BODY];
public:
    e_mail(char *_from="", char *_to="",char *_subject="", char *_body=""){
        strcpy(from,_from);
        strcpy(to,_to);
        strcpy(subject,_subject);
        strcpy(body,_body);
    }
    void printE_mail(){
        cout << "From: \t" << from << endl;
        cout << "To: \t" << to << endl;
        cout<<"---------------------------------------------------"<<endl;
        cout << "Subject: \t" << subject << endl;
        cout<<"---------------------------------------------------"<<endl;
        cout << body << endl;
    }
};
bool validEmail(char *email){
    int k;
    for(int i=0 ; i< strlen(email); i++){
        if(email[i]=='@'){
            for(int j=i+1 ; j< strlen(email) ; j++){
                if(email[j]=='.'){
                    return true;
                }
            }
        }
    }
    return false;
}

bool validEmail2(char *email){
    char *res= strchr(email,'@');
    if(res!=NULL){
        return strchr(res,'.')!=NULL;
    }
    return false;
}

int main(){
    char from[EMAIL];
    char to[EMAIL];
    char subject[EMAIL];
    char body[BODY];
    cin.getline(from,EMAIL);
    cin.getline(to,EMAIL);

    if(validEmail(from) && validEmail(to)){
        e_mail eMail(from,to,subject,body);
        cin.getline(subject,EMAIL);
        cin.getline(body, BODY);
        eMail.printE_mail();
    } else{
        cout<<"Invalid E-mails!";
    }
    return 0;
}