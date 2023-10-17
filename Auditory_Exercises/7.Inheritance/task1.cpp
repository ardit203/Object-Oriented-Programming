#include <iostream>
#include <cstring>

using namespace std;

class TennisPlayer{
protected:
    char name[10];
    char surname[10];
    bool playsInLeague;
    void copy(const TennisPlayer &other){
        strcpy(this->name,other.name);
        strcpy(this->surname,other.surname);
        this->playsInLeague=other.playsInLeague;
    }
public:
    TennisPlayer(char *name="", char *surname="", bool playsInLeague=false){
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        this->playsInLeague=playsInLeague;
    }
    ~TennisPlayer(){

    }
    TennisPlayer(const TennisPlayer &other){
        copy(other);
    }
    TennisPlayer &operator=(TennisPlayer &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    friend ostream &operator<<(ostream &out, const TennisPlayer &tp){
        out<<tp.name<<" "<<tp.surname<<" ";
        if(tp.playsInLeague==true){
            out<<"Yes";
        } else{
            out<<"No";
        }
        return out;
    }
};

class RankedTennisPlayer : public TennisPlayer{
    int rank;
public:
    RankedTennisPlayer(char *name="", char *surname="", int rank=1000): TennisPlayer(name,surname, true){
        this->rank=rank;
    }
    RankedTennisPlayer(TennisPlayer &tp, int rank=1000): TennisPlayer(tp){
        this->rank=rank;
    }
//    RankedTennisPlayer(const TennisPlayer &other, int rank) : TennisPlayer(other), rank(rank) {//Auto Generate CLion}
//    RankedTennisPlayer(char *name, char *surname,  int rank) : TennisPlayer(name, surname,true),rank(rank) {//Auto Generate CLion}

    friend ostream &operator<<(ostream &out, const RankedTennisPlayer &rtp){
        TennisPlayer tp(rtp);
        out<<tp<<" Rank: "<<rtp.rank;
        return out;
    }
//    friend ostream &operator<<(ostream &os, const RankedTennisPlayer &player) {//Auto Generate CLion
//        os <<TennisPlayer(player) << " Rank: " << player.rank;
//        return os;
//    }
};

int main(){
    TennisPlayer tp("Ardit","Selmani", true);
    cout<<tp<<endl;
    cout<<"----------------"<<endl;
    RankedTennisPlayer rtp("Ardit","Selmani",1);
    cout<<rtp<<endl;
    cout<<"----------------"<<endl;
    RankedTennisPlayer A(tp);
    cout<<A<<endl;

    return 0;
}