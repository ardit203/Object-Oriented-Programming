#include <iostream>
#include <cstring>
using namespace std;


// Your code here

class InvalidTeamName{
private:
    char team[50];
public:
    InvalidTeamName(char *team=""){
        strcpy(this->team,team);
    }
    char *what(){
        return team;
    }
};


//==============================================================//


class Goal{
private:
    char *player;
    int minute;
    char team[50];
    void copy(const Goal &other){
        this->player=new char [strlen(other.player)+1];
        strcpy(this->player,other.player);
        this->minute=other.minute;
        strcpy(this->team,other.team);
    }
public:
    Goal(char *player="", int minute=0, char *team="") {
        this->player=new char [strlen(player)+1];
        strcpy(this->player,player);
        this->minute=minute;
        strcpy(this->team,team);
    }
    ~Goal(){
        delete [] player;
    }
    Goal(const Goal &other){
        copy(other);
    }
    Goal &operator=(const Goal &other){
        if(this==&other){
            return *this;
        }
        delete [] player;
        copy(other);
        return *this;
    }
    friend ostream &operator<<(ostream &out, const Goal &g){
        out<<g.minute<<" "<<g.player;
        return out;
    }

    Goal operator++(int){
        ++minute;
        Goal Copy(*this);
        return Copy;
    }
    Goal &operator--(){
        --minute;
        return *this;
    }
    char *getTeam(){
        return team;
    }
};


//======================================================================//


class Game{
private:
    Goal *goals;
    int numOfGoals;
    char team1[50];
    char team2[50];
    void copy(const Game &other){
        this->numOfGoals=other.numOfGoals;
        this->goals=new Goal[numOfGoals];
        for(int i=0 ; i<numOfGoals ; i++){
            goals[i]=other.goals[i];
        }
        strcpy(this->team1,other.team1);
        strcpy(this->team2,other.team2);
    }
public:
    Game(char *team1="", char *team2=""){
        this->numOfGoals=0;
        this->goals= nullptr;
        strcpy(this->team1,team1);
        strcpy(this->team2,team2);
    }
    Game(const Game &other){
        copy(other);
    }
    ~Game(){
        delete [] goals;
    }
    Game &operator+=(Goal &g){
        if(strcmp(g.getTeam(),team1)!=0 && strcmp(g.getTeam(),team2)!=0){
            throw InvalidTeamName(g.getTeam());
        }
        Goal *tmp=new Goal[numOfGoals+1];
        for(int i=0 ; i<numOfGoals ; i++){
            tmp[i]=goals[i];
        }
        delete [] goals;
        tmp[numOfGoals++]=g;
        goals=tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Game &game) {
        os<<game.team1<<" - "<<game.team2<<endl;
        for(int i=0 ; i<game.numOfGoals ; i++){
            os<<game.goals[i]<<endl;
        }
        return os;
    }
};

int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for(int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        try {
            n += g;
        } catch(InvalidTeamName &e) {
            cout << "Invalid team name: " << e.what() << endl;
        }
    }
    cout << n << endl;
    return 0;
}
