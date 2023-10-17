#include <iostream>
#include <cstring>
using namespace std;

class Podcast{
protected:
    char name[100];
    char url[1000];
    float price;
    int discount;
    void copy(const Podcast &other){
        strcpy(this->name,other.name);
        strcpy(this->url,other.url);
        this->price=other.price;
        this->discount=other.discount;
    }
public:
    Podcast(char *name="", char *url="", float price=0, int discount=0){
        strcpy(this->name,name);
        strcpy(this->url,url);
        this->price=price;
        this->discount=discount;
    }
    Podcast(const Podcast &other){
        copy(other);
    }
    Podcast &operator=(const Podcast &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    virtual float calculatedPrice(){
        float p=price*(1-discount/100.0);
        return p;
    }
    friend istream &operator>>(istream &in, Podcast &p){
        cin.get();
        in.getline(p.name,100);
        in.getline(p.url, 1000);
        in>>p.price>>p.discount;
        return in;
    }
    const char *getname()const{
        return name;
    }
    friend ostream &operator<<(ostream &out,const Podcast &p){
        out<<"Podcast: "<<p.getname()<<endl;
        out<<"URL: "<<p.url<<endl;
        if(p.discount>0){
            out<<"regular PRC: $"<<p.price<<", bought on discount"<<endl;
        } else{
            out<<"regular PRC: $"<<p.price<<endl;
        }
        return out;
    }
    bool operator==(const Podcast &p){
        int d=strcmp(this->url,p.url);
        return d==0;
    }
    virtual ~Podcast(){}
};


//============================================================================================

class StreamingPodcast:public Podcast{
protected:
    float monthly_fee;
    int month;
    int year;
    void copy(const StreamingPodcast &other){
        strcpy(this->name,other.name);
        strcpy(this->url,other.url);
        this->price=other.price;
        this->discount=other.discount;
        this->monthly_fee=other.monthly_fee;
        this->month=other.month;
        this->year=other.year;
    }
public:
    StreamingPodcast(char *name="", char *url="", float price=0, int discount=0,
                     float monthly_fee=0, int month=0, int year=0):
                     Podcast(name,url,price,discount){
        this->monthly_fee=monthly_fee;
        this->month=month;
        this->year=year;
    }
    StreamingPodcast(const StreamingPodcast &other){
        copy(other);
    }
    StreamingPodcast &operator=(const StreamingPodcast &other){
        if(this==&other){
            return *this;
        }
        copy(other);
        return *this;
    }
    float calculatedPrice() override {
        float p = Podcast::calculatedPrice();

        int months=0;
        if (year<2018){
            months = (12 - this->month) + (2017 - year)*12 + 5;
        }
        else {
            months = 5 - this->month;
        }

        p += months * monthly_fee;

        return p;
    }
    friend istream &operator>>(istream &in, StreamingPodcast &s){
        cin.get();
        in.getline(s.name,100);
        in.getline(s.url, 1000);
        //cin.get();
        in>>s.price>>s.discount;
        in>>s.monthly_fee;
        in>>s.month>>s.year;
        return in;
    }
    friend ostream &operator<<(ostream &out, const StreamingPodcast &s) {
        out << "Podcast: " << s.name << endl;
        out << "URL: " << s.url << endl;
        if (s.discount > 0) {
            out << "regular PRC: $" << s.price;
            out << ", bought on discount, monthly fee: $" << s.monthly_fee;
            out << ", purchased: " << s.month << "-" << s.year << endl;
        } else {
            out << "regular PRC: $" << s.price;
            out << ", monthly fee: $" << s.monthly_fee;
            out << ", purchased: " << s.month << "-" << s.year << endl;
        }
        return out;
    }
    virtual ~StreamingPodcast(){}
};

//===============================================================================================

class ExistingPodcast{
public:
    ExistingPodcast(){
    }
    void message(){
        cout<<"The podcast is already in the collection"<<endl;
    }
};


//================================================================================================



class Playlist{
    char name[100];
    Podcast **podcasts;
    int n;
    void copy(const Playlist &other){
        strcpy(this->name,other.name);
        this->n=other.n;
        this->podcasts=new Podcast * [this->n];
        for(int i=0 ; i<n ; i++){
            StreamingPodcast *sp=dynamic_cast<StreamingPodcast *>(other.podcasts[i]);
            if(sp!= nullptr){
                podcasts[i]=new StreamingPodcast(*sp);
            } else{
                podcasts[i]=new Podcast(*(other.podcasts[i]));
            }

        }
    }
public:
    Playlist(char* name = "") {
        strcpy(this->name, name);
        this->n = 0;
        this->podcasts = nullptr; // Initialize to nullptr
    }
    Playlist(const Playlist &other){
        copy(other);
    }
    Playlist &operator=(const Playlist &other){
        if(this==&other){
            return *this;
        }
        delete [] podcasts;
        copy(other);
        return *this;
    }
    ~Playlist(){
        for (int i=0; i < this->n ; ++i){
            delete this->podcasts[i];
        }
        delete [] podcasts;
    }
    Playlist &operator+=(Podcast &p){
        for (int i = 0; i < n; i++) {
            if (*(podcasts[i]) == p) { // Use the == operator to compare podcasts
                throw ExistingPodcast();
            }
        }
        Podcast **tmp=new Podcast * [n+1];
        for(int i=0 ; i<n ; i++){
            tmp[i]=podcasts[i];
        }
        delete [] podcasts;
        StreamingPodcast *sp=dynamic_cast<StreamingPodcast *>(&p);
        if(sp!= nullptr){
            tmp[n++]=new StreamingPodcast(*sp);

        } else{
            tmp[n++]=new Podcast(p);
        }
        podcasts=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, Playlist &p){
        out<<endl<<"Playlist: "<<p.name<<endl;
        for(int i=0 ; i<p.n ; i++){
            StreamingPodcast *tmp=dynamic_cast<StreamingPodcast *>(p.podcasts[i]);
            if(tmp!= nullptr){
                out<<*tmp;
            } else{
                out<<*p.podcasts[i];
            }

        }
        return out;
    }
    float total_spent(){
        float sum=0;
        for(int i=0 ; i<n ; i++){
            sum+=podcasts[i]->calculatedPrice();
        }
        return sum;
    }
};

//===================================================================================================



int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Podcast
    char podcast_name[100];
    char podcast_url[1000];
    float podcast_price;
    int podcast_discount;

    // for StreamingPodcast
    float sub_podcast_monthly_fee;
    int sub_podcast_month, sub_podcast_year;

    // for Playlist
    char name[100];
    int num_podcasts_in_playlist;

    if (test_case_num == 1){
        cout<<"Testing class Podcast and operator&lt;&lt; for Podcast"<<std::endl;
        cin.get();
        cin.getline(podcast_name,100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin>>podcast_price>>podcast_discount;

        Podcast p(podcast_name, podcast_url, podcast_price, podcast_discount);

        cout<<p;
    }
    else if (test_case_num == 2){
        cout<<"Testing class StreamingPodcast and operator&lt;&lt; for StreamingPodcast"<<std::endl;
        cin.get();
        cin.getline(podcast_name,100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin>>podcast_price>>podcast_discount;

        cin>>sub_podcast_monthly_fee;
        cin>>sub_podcast_month>>sub_podcast_year;

        StreamingPodcast sp(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
        cout<<sp;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator&gt;&gt; for Podcast"<<std::endl;
        Podcast p;

        cin>>p;

        cout<<p;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator&gt;&gt; for StreamingPodcast"<<std::endl;
        StreamingPodcast sp;

        cin>>sp;

        cout<<sp;
    }
    else if (test_case_num == 5){
        cout<<"Testing class Playlist and operator+= for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_user_podcasts;
        int podcast_type;
        cin >>num_user_podcasts;

        try {
            for (int i=0; i<num_user_podcasts; ++i){

                cin >> podcast_type;

                Podcast *g;
                // 1 - Game, 2 - SubscriptionGame
                if (podcast_type == 1){
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin>>podcast_price>>podcast_discount;
                    g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
                }
                else if (podcast_type == 2){
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin>>podcast_price>>podcast_discount;

                    cin>>sub_podcast_monthly_fee;
                    cin>>sub_podcast_month>>sub_podcast_year;
                    g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingPodcast &ex){
            ex.message();
        }

        cout<<u;

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingPodcast for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >>num_podcasts_in_playlist;

        for (int i=0; i<num_podcasts_in_playlist; ++i){

            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            }
            else if (podcast_type == 2){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;

                cin>>sub_podcast_monthly_fee;
                cin>>sub_podcast_month>>sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingPodcast &ex){
                ex.message();
            }
        }

        cout<<u;
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >>num_podcasts_in_playlist;

        for (int i=0; i<num_podcasts_in_playlist; ++i){

            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            }
            else if (podcast_type == 2){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;

                cin>>sub_podcast_monthly_fee;
                cin>>sub_podcast_month>>sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingPodcast &ex){
                ex.message();
            }
        }

        cout<<u;

        cout<<endl<<"Total money spent: $"<<u.total_spent()<<endl;
    }
    return 0;
}