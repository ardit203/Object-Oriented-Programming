#include <iostream>
#include <cmath>
using namespace std;

class Triangle{
private:
    float a,b,c;
public:
    Triangle (float _a=1,float _b=1, float _c=1){
        a=_a;
        b=_b;
        c=_c;
    }
    float perimeter(){
        return a+b+c;
    }
    float area(){
        float s=perimeter()/2;
        return sqrtf(s*(s-a)*(s-b)*(s-c));
    }
};

int main(){
    int n;
    cin>>n;
    Triangle triangles[10];
    for(int i=0 ; i<n ; i++){
        float a,b,c;
        cin>>a>>b>>c;
        triangles[i]=Triangle(a,b,c);
        cout << "Area: " << triangles[i].area() << endl;
        cout << "Permeter: " << triangles[i].perimeter() << endl;
    }
    return 0;
}