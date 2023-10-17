#include <iostream>
#include <cstring>
using namespace std;

class BasketballPlayer{
private:
    char name[20];
    char surname[20];
    int jersey_number;
    int point_1st;
    int point_2nd;
    int point_3rd;
public:
    BasketballPlayer(char *_name, char *_surname,int _jersey_number, int _points_1st, int _points_2nd, int _points_3rd){
        strcpy(name,_name);
        strcpy(surname,_surname);
        jersey_number=_jersey_number;
        point_1st=_points_1st;
        point_2nd=_points_2nd;
        point_3rd=_points_3rd;
    }
    void print(){
        cout<<"Player: "<<name<<" "<<surname<<" with number: "<<jersey_number<<" has "<<(point_1st+point_2nd+point_3rd)/3.0;
        cout<<" points on average"<<endl;
    }

};

int main(){
    char name[20];
    char surname[20];
    int jersey_number;
    int points1,points2,points3;
    cin>>name>>surname>>jersey_number>>points1>>points2>>points3;
    BasketballPlayer b(name,surname,jersey_number,points1,points2,points3);
    b.print();
    return 0;
}