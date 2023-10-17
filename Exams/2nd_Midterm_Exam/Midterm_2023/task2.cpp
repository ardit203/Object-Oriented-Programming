#include <iostream>
#include <cstring>

using namespace std;

class Post{
protected:
    char username[30];
    char *content;
    int likes;
    int comments;
    bool hasPhoto;
    void copy(const Post &p){
        strcpy(this->username,p.username);
        this->content=new char [strlen(p.content)+1];
        strcpy(this->content,p.content);
        this->likes=p.likes;
        this->comments=p.comments;
        this->hasPhoto=p.hasPhoto;
    }
public:
    Post(char *username="", char *content="", int likes=0, int comments=0, bool hasPhoto= true){
        strcpy(this->username,username);
        this->content=new char [strlen(content)+1];
        strcpy(this->content,content);
        this->likes=likes;
        this->comments=comments;
        this->hasPhoto=hasPhoto;
    }
    Post(Post &p){
        copy(p);
    }
    Post &operator=(Post &p){
        if(this==&p){
            return *this;
        }
        delete [ ] content;
        copy(p);
        return *this;
    }
    ~Post(){
        delete [] content;
    }
    virtual double popularity()=0;
    virtual void print()=0;
    bool operator>=(Post &p){
        return popularity()>=p.popularity();
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class FacebookPost:public Post{
private:
    int shares;
public:
    FacebookPost(char *username="", char *content="", int likes=0, int comments=0, bool hasPhoto= true, int shares=0): Post(username,content,likes,comments,hasPhoto){
        this->shares=shares;
    }

    double popularity() override {
        double pop=likes*comments;
        if(shares>20){//+15%
            //pop=pop+pop*15%          //pop + 15% of the pop
            //pop=pop+pop*(15/100.0);
            //pop=pop*(1+15/100.0);
            //pop=pop*(1+0.15);
            //pop=pop*1.15;
            pop*=1.15;
        }
        if(hasPhoto){//+10%
            //pop=pop+pop*(10/100.0);
            //pop=pop*(1+10/100.0);
            //pop=pop*(1+0.1);
            //pop=pop*1.1;
            pop*=1.1;
        }
        return pop;
    }

    void print() override {
        cout<<"Post"<<endl;
        cout<<"Facebook post"<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        cout<<"Likes : "<<likes<<endl;
        cout<<"Comments: "<<comments<<endl;
        cout<<"Shares: "<<shares<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////

class TwitterPost:public Post{
private:
    int retweets;
    int replies;
public:
    TwitterPost(char *username="", char *content="", int likes=0, int comments=0, bool hasPhoto= true, int retweets=0, int replies=0)
            : Post(username, content,likes,comments,hasPhoto){
        this->replies=replies;
        this->retweets=retweets;
    }

    double popularity() override {
        double pop=likes*comments;
        if(replies>10){//+10%
            //pop=pop+pop*(10/100.0);
            //pop=pop*(1+10/100.0);
            //pop=pop*(1+0.1);
            //pop=pop*1.1;
            pop*=1.1;
        }
        if(retweets>10){//+10%
            //pop=pop+pop*(10/100.0);
            //pop=pop*(1+10/100.0);
            //pop=pop*(1+0.1);
            //pop=pop*1.1;
            pop*=1.1;
        }
        if(hasPhoto){//+10%
            //pop=pop+pop*(10/100.0);
            //pop=pop*(1+10/100.0);
            //pop=pop*(1+0.1);
            //pop=pop*1.1;
            pop*=1.1;
        }
        if(strstr("#crypto",content)!= nullptr){//+20%
            //pop=pop+pop*(20/100.0);
            //pop=pop*(1+20/100.0);
            //pop=pop*(1+0.2);
            //pop=pop*1.2;
            pop*=1.2;
        }
        return pop;
    }

    void print() override {
        cout<<"Post"<<endl;
        cout<<"Twitter post"<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        cout<<"Likes : "<<likes<<endl;
        cout<<"Comments: "<<comments<<endl;
        cout<<"Retweets: "<<retweets<<endl;
        cout<<"Replies: "<<replies<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }
};

double highestPopularity(Post **posts, int n){
    double max=posts[0]->popularity();
    for(int i=1 ; i<n ; i++){
        if(posts[i]->popularity()>max){
            max=posts[i]->popularity();
        }
    }
    return max;
}


int main(){//My main function

    Post **pPost=new Post * [4];
    pPost[0]=new FacebookPost ("Ardit","CA BOT", 15,20, true,4);
    pPost[1]=new FacebookPost ("Armend","SI JE",30,30, true,5);
    pPost[2]=new TwitterPost ("Ardit","EJJ #crypto", 30, 50, false,5,6);
    pPost[3]=new TwitterPost ("Armend","RSPP",40,30, true,3,4);
    for(int i=0 ; i<4 ; i++){
        pPost[i]->print();
        cout<<endl;
    }
    cout<<highestPopularity(pPost,4);
    return 0;
}