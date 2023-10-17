#include <iostream>
using namespace std;

struct player{
    char name[15];
    int current_level;
    int points;
    void readPlayer(){
        cin>>name>>current_level>>points;
    }
};

struct computerGame{
    char name[20];
    player players[30];
    int number_players;
    void readComputerGame(){
        cin>>name>>number_players;
        for(int i=0 ; i<number_players ; i++){
            players[i].readPlayer();
        }
    }
    int compcmp(computerGame other){
        if(number_players>other.number_players){
            return 1;
        } else if(number_players<other.number_players){
            return -1;
        } else{
            return 0;
        }
    }
    player bestP(){
        player best=players[0];
        for(int i=1 ; i<number_players ; i++){
            if(players[i].points>best.points){
                best=players[i];
            } else if(players[i].points==best.points && players[i].current_level>best.current_level){
                best=players[i];
            }
        }
        return best;
    }
};

void bestPlayer(computerGame *array, int n){
    computerGame bestGame=array[0];
    for(int i=1 ; i<n ; i++){
        if(array[i].compcmp(bestGame)==1){
            bestGame=array[i];
        }
    }
    player bestPlayer=bestGame.bestP();
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<bestPlayer.name<<" koj ja igra igrata "<<bestGame.name;

}

int main(){
    int n;
    cin>>n;
    computerGame games[100];
    for(int i=0 ; i<n ; i++){
        games[i].readComputerGame();
    }
    bestPlayer(games,n);
    return 0;
}