#include <iostream>
#include <cstring>
using namespace std;

class Team{
private:
    char name[20];
    int year_found;
    char city[20];
public:
    Team(char *_name, int _year_found, char *_city){
        strcpy(name,_name);
        year_found=_year_found;
        strcpy(city,_city);
    }
    Team(){
        strcpy(name,"");
        year_found=1900;
        strcpy(city,"");
    }
    Team(const Team &other){//copy constructor
        cout << "The copy constructor of the class Team is called!" << endl;
        strcpy(name,other.name);
        year_found=other.year_found;
        strcpy(city,other.city);
    }
    void print(){
        cout << name << " " << city << " (" << year_found << ")" << endl;
    }

    const char *getName() const {
        return name;
    }

    int getYearFound() const {
        return year_found;
    }

    const char *getCity() const {
        return city;
    }
};

class Game{//composition
private:
    Team home;
    Team away;
    int home_team_goals;
    int away_team_goals;
public:
    Game(Team _home, Team _away, int _home_team_goals, int _away_team_goals){
        home=_home;
        away=_away;
        home_team_goals=_home_team_goals;
        away_team_goals=_away_team_goals;
    }

    Game(const Game &other){//copy constructor
        cout << "The copy constructor of the class Game is called!" << endl;
        home=other.home;
        away=other.away;
        home_team_goals=other.home_team_goals;
        away_team_goals=other.away_team_goals;
    }

    Team &getHome() {
        return home;
    }

    Team &getAway(){
        return away;
    }

    int getHomeTeamGoals() const {
        return home_team_goals;
    }

    int getAwayTeamGoals() const {
        return away_team_goals;
    }

    void print(){
        cout << "Home: ";
        home.print();
        cout << "Away: ";
        away.print();
        cout << "Result - " << home_team_goals << ":" << away_team_goals;
    }
    bool rematch(Game other){
        return strcmp(home.getName(),other.away.getName())==0 && strcmp(away.getName(),other.home.getName())==0;
    }
};

void rematch(Game first, Game second){
    if(first.rematch(second)){//we are calling the implicit copy-constructor of Game.
        int totalGoalsTeam1=first.getHomeTeamGoals()+second.getAwayTeamGoals();
        int totalGoalsTeam2=first.getAwayTeamGoals()+second.getHomeTeamGoals();
        if(totalGoalsTeam1>totalGoalsTeam2){
            cout<<"WINNER:"<<endl;
            first.getHome().print();
        } else if(totalGoalsTeam1>totalGoalsTeam2){
            cout<<"WINNER:"<<endl;
            first.getAway().print();
        } else{
            cout<<"DRAW!";
        }
    }else{
        cout<<"Not a rematch!";
    }
}

int main(){
    Team team1("Barca", 1899, "Barcelona");
    Team team2("Real Madrid", 1891, "Madrid");
    Team team3("Chelsea", 1900, "London");

    Game game(team1, team2, 5, 3);//we are calling the implicit copy-constructor of Team twice.
    Game second(team2, team1, 6, 4);//we are calling the implicit copy-constructor of Team twice.


//    game.print();

    rematch(game ,second); //we are calling the implicit copy-constructor of Game twice.
    return 0;
}