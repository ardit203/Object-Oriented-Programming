#include <stdio.h>
#include <math.h>

typedef struct ThreeDimensionalSpace{
    float x,y,z;
}point3D;

point3D readPoint3D(){
    point3D point;
    scanf("%f%f%f",&point.x,&point.y,&point.z);
    return point;
}

float distance3D(point3D p1, point3D p2){
    return sqrtf((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)+(p2.z-p1.z)*(p2.z-p1.z));
}

typedef struct TwoDimensionalSpace{
    float x,y;
}point2D;

point2D readPoint2D(){
    point2D point;
    scanf("%f %f",&point.x,&point.y);
    return point;
}

int colinear(point2D p1,point2D p2, point2D p3){
    float m1=(p2.y-p1.y)/(p2.x-p1.x);
    float m2=(p3.y-p1.y)/(p3.x-p1.x);
    if(m1==m2){
        return 1;
    } else
        return 0;
}


int main(){
    point2D p1=readPoint2D();
    point2D p2=readPoint2D();
    point2D p3=readPoint2D();
    printf("%d", colinear(p1,p2,p3));
    return 0;
}