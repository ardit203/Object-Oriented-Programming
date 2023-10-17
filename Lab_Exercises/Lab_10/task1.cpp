//
// Created by Stefan Andonov on 13.5.23.
//

#include<iostream>
#include<cstring>
using namespace std;

class UserAlreadyExistsException {
private:
    char username[50];
public:
    UserAlreadyExistsException(char *username){
        strcpy(this->username,username);
    }
    void show_message(){
        cout<<"User with username "<<username<<" already exists!"<<endl;
    }
};

class UserNotFoundException {
private:
    char username[50];
public:
    UserNotFoundException(char *username){
        strcpy(this->username,username);
    }
    void show_message(){
        cout<<"User with username "<<username<<" was not found!"<<endl;
    }
};



class User {
private:
    char username[50];
    int age;
    int friends;
    static int N_FRIENDS;
public:
    User(char *username = "", int age = 18) : age(age) {
        strcpy(this->username, username);
        friends = 0;
    }

    friend ostream &operator<<(ostream &os, const User &user) {
        os << "Username: " << user.username << " Age: " << user.age << " # of friends: " << user.friends;
        return os;
    }

    User &operator++() {
        ++friends;
        return *this;
    }

    friend class SocialNetwork;

    static int setLimit(int n){
        N_FRIENDS=n;
    }
    static int getN(){
        return N_FRIENDS;
    }

};



int User::N_FRIENDS=3;

class FriendsLimitExceededException {
private:
    char username[50];
public:
    FriendsLimitExceededException(char *username){
        strcpy(this->username,username);
    }
    void show_message(){
        cout<<"Can't have more than "<<User::getN()<<" friends."<<endl;
    }
};

class SocialNetwork {
private:
    User *users;
    int n;
public:
    SocialNetwork() {
        n = 0;
        users = new User[n];
    }

    SocialNetwork &operator+=(User &u) {
        if(n!=0){
            for(int i=0 ; i<n ; i++){
                if(strcmp(users[i].username,u.username)==0){
                    throw UserAlreadyExistsException(u.username);
                }
            }
        }
        User *tmp = new User[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete[] users;
        users = tmp;
        return *this;
    }

    void friendRequest(char *firstUsername, char *secondUsername) {
        int flag1=0;
        int flag2=0;
        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, firstUsername) == 0) {
                flag1=1;
                for (int j = 0; j < n; j++) {
                    if (strcmp(users[j].username, secondUsername) == 0) {
                        flag2=1;
                        if(users[i].friends==User::N_FRIENDS){
                            throw FriendsLimitExceededException(users[i].username);
                        }
                        if(users[j].friends==User::N_FRIENDS){
                            throw FriendsLimitExceededException(users[j].username);
                        }
                        ++users[i];
                        ++users[j];
                        return;
                    }
                }
            }
        }
        if(flag1==0){
            throw UserNotFoundException(firstUsername);
        }
        if(flag2==0){
            throw UserNotFoundException(secondUsername);
        }
    }

    friend ostream &operator<<(ostream &os, const SocialNetwork &network) {
        os << "Users: " << endl;
        for (int i=0;i<network.n;i++) {
            os << network. users[i] << endl;
        }
        return os;
    }
};


int main() {
    SocialNetwork sn;
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        char username[50]; int age;
        cin >> username >> age;
        try {
            User u(username, age);
            sn += u;
        }catch (UserAlreadyExistsException &e){
            e.show_message();
        }


    }

    cout << "Registration of users " << endl;
    cout << sn << endl;
    cout << "Friend requests " << endl;

    int friendships;
    cin >> friendships;
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        }catch (UserNotFoundException &e){
            e.show_message();
        }catch (FriendsLimitExceededException &e){
            e.show_message();
        }


    }

    cout << sn << endl;

    cout << "CHANGE STATIC VALUE" << endl;

    int maxFriends;
    cin >> maxFriends;
    cin >> friendships;
    User::setLimit(maxFriends);
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        }catch (UserNotFoundException &e){
            e.show_message();
        }catch (FriendsLimitExceededException &e){
            e.show_message();
        }

    }
    cout << sn;
    return 0;
}