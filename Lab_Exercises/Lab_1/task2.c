#include <stdio.h>
#define MAX 100

//Create the structure Point
typedef struct Point{
    int x,y;
}point;

//Function for reading the point
point readPoint(){
    point p;
    scanf("%d%d",&p.x,&p.y);
    return p;
}

//Create structure Circle
typedef struct Circle{
    point center;
    int radius;
}circle;

//Function for reading the Circle
circle readCircle(){
    circle c;
    c.center=readPoint();
    scanf("%d",&c.radius);
    return c;
}

int main(){
    int n;
    scanf("%d",&n);
    circle circles[MAX];
    for(int i=0 ; i<n ; i++){
        circles[i]=readCircle();
    }
    circle _max=circles[0];
    for(int i=1 ; i<n ; i++){
        if(circles[i].radius>_max.radius){//A=pi*r*r, so wich of the circle has the biggest radius also has the biggest area;
            _max=circles[i];
        }
    }
    float maxArea=3.14*_max.radius*_max.radius;
    printf("Largest circle has area of: %.2f with centre: (%d,%d)",maxArea,_max.center.x,_max.center.y);
    return 0;
}