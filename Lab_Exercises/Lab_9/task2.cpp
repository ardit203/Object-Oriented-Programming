#include <iostream>
#include <cstring>

using namespace std;

class Game{
protected:
    char title[50];
public:
    Game(char *title=""){
        strcpy(this->title,title);
    }

    virtual void displayInfo()=0;
    virtual int complexity()=0;
};

//-------------------------------------------------------------------------------//

class BoardGame: virtual public Game{
protected:
    int maxPlayers;
public:
    BoardGame(char *title="", int maxPlayers=0): Game(title){
        this->maxPlayers=maxPlayers;
    }

    void displayInfo() override{
        cout<<"Game: "<< title<<endl;
        cout<<"Max Players: "<<maxPlayers<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }

    int complexity() override{
        if(maxPlayers>6){
            return 10;
        } else if(maxPlayers<6 && maxPlayers>3){
            return 5;
        } else
            return 3;
    }
};



//-------------------------------------------------------------------------------//


class CardGame: virtual public Game{
protected:
    int numOfCards;
public:
    CardGame(char *title="", int numOfCards=0): Game(title){
        this->numOfCards=numOfCards;
    }

    void displayInfo() override {
        cout<<"Game: "<< title<<endl;
        cout<<"Number Of Cards: "<<numOfCards<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }

    int complexity() override{
        if(numOfCards>20){
            return 10;
        } else if(numOfCards>10 && numOfCards<20){
            return 5;
        } else
        return 3;
    }
};




//-------------------------------------------------------------------------------//



class BoardCardGame : public BoardGame, public CardGame{
public:

    BoardCardGame(char *title="", int maxPlayers=0, int numOfCards=0): Game(title), BoardGame(title,maxPlayers), CardGame(title,numOfCards){}
    void displayInfo() override {
        cout<<"Game: "<<title<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }

    int complexity() override {
        return (CardGame::complexity()+BoardGame::complexity())/2;
    }
};

Game *mostComplexCardGame(Game **g, int n){
    CardGame *mostComplexCardGame, *pG;
    int flag=1;
    for(int i=0 ; i<n ; i++){
        pG=dynamic_cast<CardGame *>(g[i]);
        if(pG!= nullptr){
            if(flag){
                mostComplexCardGame=pG;
                flag=0;
            } else if(g[i]->complexity()>mostComplexCardGame->complexity()){
                mostComplexCardGame=pG;
            }
        }
    }
    return mostComplexCardGame;
}

int main() {
    char title[50];
    int maxPlayers;
    int numCards;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>title;
        BoardCardGame boardCardGame(title, 8, 15);
        boardCardGame.displayInfo();
    }
    else {

        cin >> n;

        Game **g = new Game *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> title >> maxPlayers;

                g[i] = new BoardGame(title, maxPlayers);
            } else {
                cin >> title >> numCards;

                g[i] = new CardGame(title, numCards);
            }

        }

        mostComplexCardGame(g,n)->displayInfo();

    }


    return 0;
}





//#include <iostream>
//#include <cstring>
//using namespace std;
//
//
//class Game {
//protected:
//    char title[50];
//
//
//public:
//    Game(){}
//
//
//    Game(char *title) {
//        strcpy(this->title, title);
//    }
//
//
//    virtual void displayInfo() = 0;
//
//
//    virtual int complexity() = 0;
//};
//
//
//class BoardGame : virtual public Game {
//protected:
//    int maxPlayers;
//public:
//    BoardGame(){}
//
//
//    BoardGame(char *title, int maxPlayers) : Game(title) {
//        this->maxPlayers = maxPlayers;
//    }
//
//
//    void displayInfo() {
//        cout<< "Game: "<<title;
//        cout << "Max players: " << maxPlayers << endl;
//        cout << "Complexity: "<<complexity()<<endl;
//    }
//
//
//    int complexity(){
//        if (maxPlayers>6)
//            return 10;
//        else if(maxPlayers>3)
//            return 5;
//        else return 3;
//    }
//
//
//};
//
//
//class CardGame : virtual public Game {
//protected:
//    int numCards;
//public:
//    CardGame(){}
//
//
//    CardGame(char *title, int numCards) : Game(title) {
//        this->numCards = numCards;
//    }
//
//
//    void displayInfo() {
//        cout<< "Game: "<<title<<endl;
//        cout << "Number of cards: " << numCards << endl;
//        cout << "Complexity: "<<complexity()<<endl;
//    }
//
//
//    int complexity(){
//        if(numCards>20)
//            return 10;
//        else if(numCards>10)
//            return 5;
//        else return 3;
//    }
//
//
//
//
//};
//
//
//class BoardCardGame : public BoardGame, public CardGame {
//private:
//
//
//public:
//    BoardCardGame(){}
//    BoardCardGame(char *title, int maxPlayers, int numCards)
//            : BoardGame(title, maxPlayers), CardGame(title, numCards), Game(title)  {
//    }
//
//
//    void displayInfo() {
//        cout<<"Game: "<<title<<endl;
//        cout<<"Complexity: "<<complexity()<<endl;
//    }
//
//
//    int complexity(){
//        int complexityBoard = BoardGame::complexity();
//        int complexityCard = CardGame::complexity();
//        return (complexityBoard+complexityCard)/2;
//    }
//
//
//
//
//
//
//};
//
//
//Game *mostComplexCardGame(Game **games, int n)
//{
//    CardGame *mostComplexCardGame, *tmpGame;
//    int index=-1;
//    for(int i=0;i<n;i++)
//    {
//        tmpGame = dynamic_cast<CardGame *>(games[i]);
//
//
//        if(tmpGame){
//            if(index == -1)
//            {
//                index = i;
//                mostComplexCardGame = tmpGame;
//            }
//            else if(mostComplexCardGame->complexity() < tmpGame->complexity())
//            {
//                mostComplexCardGame = tmpGame;
//            }
//        }
//
//
//    }
//
//
//    return mostComplexCardGame;
//}
//
//
//
//
//int main() {
//    char title[50];
//    int maxPlayers;
//    int numCards;
//    int n;
//    int choice;
//
//
//    cin>>choice;
//    if(choice==1)
//    {
//        cin>>title;
//        BoardCardGame boardCardGame(title, 8, 15);
//        boardCardGame.displayInfo();
//    }
//    else {
//
//
//        cin >> n;
//
//
//        Game **g = new Game *[n];
//        for (int i = 0; i < n; i++) {
//            cin >> choice;
//            if (choice == 1) {
//                cin >> title >> maxPlayers;
//
//
//                g[i] = new BoardGame(title, maxPlayers);
//            } else {
//                cin >> title >> numCards;
//
//
//                g[i] = new CardGame(title, numCards);
//            }
//
//
//        }
//
//
//        mostComplexCardGame(g,n)->displayInfo();
//
//
//    }
//
//
//
//    return 0;
//}