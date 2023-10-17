#include <stdio.h>

typedef struct complexNumber{
    float real,imaginary;
} complex;

complex readComplexNumber(){
    complex z;
    scanf("%f + %fi",&z.real,&z.imaginary);
    return z;
}

void print(complex z){
    printf("%.2f + %.2f*i",z.real,z.imaginary);
}

void sum(complex z1, complex z2){
    complex c;
    c.real=z1.real+z2.real;
    c.imaginary=z1.imaginary+z2.imaginary;
    print(z1);
    printf(" + ");
    print(z2);
    printf(" = ");
    print(c);
    printf("\n");
}

void subtraction(complex z1, complex z2){
    complex c;
    c.real=z1.real-z2.real;
    c.imaginary=z1.imaginary-z2.imaginary;
    print(z1);
    printf(" - ");
    print(z2);
    printf(" = ");
    print(c);
    printf("\n");
}

void product(complex z1, complex z2){
    complex c;
    c.real=z1.real*z2.real;
    c.imaginary=z1.imaginary*z2.imaginary;
    print(z1);
    printf(" * ");
    print(z2);
    printf(" = ");
    print(c);
    printf("\n");
}

int main(){
    complex z1=readComplexNumber();
    complex z2=readComplexNumber();
    sum(z1,z2);
    subtraction(z1,z2);
    product(z1,z2);
    return 0;
}
