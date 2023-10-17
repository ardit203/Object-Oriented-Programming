#include <iostream>

using namespace std;

struct player{
    char name[15];
    int currentLevel;
    int points;
    void readPlayer(){
        cin>>name>>currentLevel>>points;
    }
    void printPlayer(){
        cout<<name<<" "<<currentLevel<<" "<<points<<endl;
    }
    int intCmp(int n1, int n2){
        if(n1>n2){
            return 1;
        } else if(n1<n2){
            return -1;
        } else{
            return 0;
        }
    }
    int pointsCmp(player other){
        return intCmp(points,other.points);
    }
    int levelCmp(player other){
        return currentLevel>other.currentLevel;
    }
};

struct computerGame{
    char name[20];
    player players[30];
    int nPlayers;
    void readComputerGame(){
        cin>>name;
        cin>>nPlayers;
        for(int i=0 ; i< nPlayers ; i++){
            players[i].readPlayer();
        }
    }
    void printComputerGame(){
        cout<<name<<endl<<nPlayers<<endl;
        for(int i=0 ; i<nPlayers ; i++){
            players[i].printPlayer();
        }
    }
    int computerGameCmp(computerGame other){
        return nPlayers>other.nPlayers;
    }

};

void bestPlayer(computerGame *array , int n){
    computerGame BestGame=array[0];
    for(int i=1 ; i<n ; i++){
        if(array[i].computerGameCmp(BestGame)){
            BestGame=array[i];
        }
    }
    player BestPlayer=BestGame.players[0];
    for(int i=1 ; i<BestGame.nPlayers ; i++){
        if(BestGame.players[i].pointsCmp(BestPlayer)==1){
            BestPlayer=BestGame.players[i];
        } else if(BestGame.players[i].pointsCmp(BestPlayer)==0){
            if(BestGame.players[i].levelCmp(BestPlayer)==1)
                BestPlayer=BestGame.players[i];
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<BestPlayer.name<<" koj ja igra igrata "<<BestGame.name;
}

int main(){
    int n;
    cin>>n;
    computerGame games[100];
    for(int i=0 ; i<n ; i++){
        games[i].readComputerGame();
    }
    //for(int i=0 ; i<n ; i++){to test if every thing is read properly
    //games[i].printComputerGame();
    //}
    bestPlayer(games,n);
    return 0;
}
