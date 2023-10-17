#include <stdio.h>

typedef struct Vector{
    float x,y,z;
} vector;

vector readVector(){
    vector Vector;
    scanf("%f %f %f",&Vector.x,&Vector.y,&Vector.z);
    return Vector;
}

float scalarProduct(vector vector1,vector vector2){
    return vector1.x*vector2.x+vector1.y*vector2.y+vector1.z+vector2.z;
}

vector vectorProduct(vector v1, vector v2){
    vector v;
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return v;
}

int main(){
    vector vector1=readVector();
    vector vector2=readVector();
    vector Vector= vectorProduct(vector1,vector2);
    printf("v1 * v2 = %.2f\n", scalarProduct(vector1,vector2));
    printf("v1 x v2 = [%.2f , %.2f , %.2f]",Vector.x,Vector.y,Vector.z);
    return 0;
}
