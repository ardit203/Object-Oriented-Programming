#include <iostream>
#include <cstring>

using namespace std;

class SubscriptionGame;

class Game{
protected:
    char name[100];
    float price;
    bool onSale;
    void copy(const Game &other){
        strcpy(this->name,other.name);
        this->price=other.price;
        this->onSale=other.onSale;
    }
public:
    Game(char *name="", float price=0, bool onSale= false){
        strcpy(this->name,name);
        this->price=price;
        this->onSale=onSale;
    }
    Game(const Game &other){
        copy(other);
    }
    Game &operator=(const Game &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    friend istream &operator>>(istream &in, Game &g){
        in.get();
        in.getline(g.name,100);
        //cin.get();
        in>>g.price>>g.onSale;
        return in;
    }
    friend ostream &operator<<(ostream &out, Game &g){
        //Game: World of Warcraft, regular price: $40
        out<<"Game: "<<g.name<<", regular price: $"<<g.price;
        if(g.onSale){
            out<<", bought on sale"<<endl;
        } else{
            out<<endl;
        }
        return out;
    }
    bool operator==(Game &other){
        return strcmp(name,other.name)==0;
    }
    bool operator==(SubscriptionGame &other);
    char *getName(){
        return name;
    }
    virtual float calculatedPrice(){
        if (onSale){
            return price*0.3;
        }
        return price;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////


class SubscriptionGame:public Game{
private:
    float monthly_fee;
    int month;
    int year;
    void copy(const SubscriptionGame &other){
        Game::copy(other);
        this->monthly_fee=other.monthly_fee;
        this->month=other.month;
        this->year=other.year;
    }
public:
    SubscriptionGame(char *name="", float price=0, bool onSale= false, float monthly_fee=0,
                     int month=0, int year=0): Game(name,price,onSale){
        this->monthly_fee=monthly_fee;
        this->month=month;
        this->year=year;
    }
    SubscriptionGame (const SubscriptionGame &other){
        copy(other);
    }
    SubscriptionGame &operator=(const SubscriptionGame &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    friend istream &operator>>(istream &in, SubscriptionGame &g){
        in.get();
        in.getline(g.name,100);
        //cin.get();
        in>>g.price>>g.onSale;
        in>>g.monthly_fee;
        in>>g.month>>g.year;
        return in;
    }
    friend ostream &operator<<(ostream &out, SubscriptionGame &g){
        //Game: World of Warcraft, regular price: $40, monthly fee: $10, purchased: 1-2017
        out<<"Game: "<<g.name<<", regular price: $"<<g.price;
        if(g.onSale){
            out<<", bought on sale, monthly fee: $"<<g.monthly_fee<<", purchased: ";
            out<<g.month<<"-"<<g.year<<endl;
        } else{
            out<<", monthly fee: $"<<g.monthly_fee<<", purchased: ";
            out<<g.month<<"-"<<g.year<<endl;
        }

        return out;
    }
    bool operator==(SubscriptionGame &other){
        return strcmp(name,other.name)==0;
    }
    bool operator==(Game &other){
        return strcmp(name,other.getName())==0;
    }

    float calculatedPrice() override {
        float price = Game::calculatedPrice();

        int months=0;
        if (year<2018){
            months = (12 - this->month) + (2017 - year)*12 + 5;
        }
        else {
            months = 5 - this->month;
        }

        price += months * monthly_fee;

        return price;
    }
};

bool Game::operator==(SubscriptionGame &other) {
    return strcmp(name,other.name)==0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////


class ExistingGame{
private:
public:
    ExistingGame(){
    //todo
}
    void message(){
        cout<<"The game is already in the collection"<<endl;
    }

};


/////////////////////////////////////////////////////////////////////////////////////////////////////////

class User{
    char username[100];
    Game **games;
    int n;
    void copy(const User &other){
        strcpy(this->username,other.username);
        this->n=other.n;
        this->games=new Game * [n];
        for(int i=0 ; i<n ; i++){
            games[i]=other.games[i];
        }
    }
public:
    User(char *username=""){
        strcpy(this->username,username);
        this->n=0;
        this->games=new Game * [n];
    }
    User(const User &other){
        copy(other);
    }
    User &operator=(const User &other){
        if(this==&other){
            return *this;
        }
        delete [] games;
        copy(other);
        return *this;
    }
    ~User(){
        delete [] games;
    }
    User &operator+=(Game &g){
        for(int i=0 ; i<n ; i++){
            if(*games[i]==g){
                throw ExistingGame();
            }
        }
        Game **tmp=new Game * [n+1];
        for(int i=0 ; i<n ; i++){
            tmp[i]=games[i];
        }
        delete[] games;
        SubscriptionGame *sg=dynamic_cast<SubscriptionGame*>(&g);
        if(sg!= nullptr){
            tmp[n++]=new SubscriptionGame(*sg);
        } else{
            tmp[n++]=new Game(g);
        }
        games=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, User &u){
        out<<endl<<"User: "<<u.username<<endl;
        for(int i=0 ; i<u.n ; i++){
            SubscriptionGame *sg=dynamic_cast<SubscriptionGame*>(u.games[i]);
            if(sg!= nullptr){
                out<<"- "<<*sg;
            } else{
                out<<"- "<<*u.games[i];
            }
        }
        out<<endl;
        return out;
    }
    float total_spent(){
        float sum=0;
        for(int i=0 ; i<n ; i++){
            sum+=games[i]->calculatedPrice();
        }
        return sum;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////






int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
                --i;
                --num_user_games;
            }
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
