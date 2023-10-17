//Solution

#include <stdio.h>
#include <string.h>

typedef struct {
    char avtor[100];
    float cena;
    int tip;
} UmetnickoDelo;

typedef struct {
    char ime[50];
    UmetnickoDelo delo[30];
    int brojDelo;
} Galerija;

void print(Galerija g) {
    printf("%s\n", g.ime);
    for (int i = 0; i < g.brojDelo; i++) {
        printf("%s %.2f %d\n", g.delo[i].avtor, g.delo[i].cena, g.delo[i].tip);
    }
}

void najdobra_ponuda(Galerija galerii[], int brojGalerii, int tipNaDelo) {
    char najdobraGalerija[50];
    float minCena = -1;

    for (int i = 0; i < brojGalerii; i++) {
        for (int j = 0; j < galerii[i].brojDelo; j++) {
            if (galerii[i].delo[j].tip == tipNaDelo) {
                if (minCena == -1 || galerii[i].delo[j].cena <= minCena) {
                    minCena = galerii[i].delo[j].cena;
                    strncpy(najdobraGalerija, galerii[i].ime, sizeof(najdobraGalerija));
                }
            }
        }
    }
    if (minCena != -1) {
        printf("Najevtino umetnicko delo tip %s go nudi galerijata: %s so cena: %.2f\n", tipNaDelo==1?"slika":"skulptura", najdobraGalerija, minCena);
    } else {
        printf("Ne e pronajdeno umetnicko delo od tip %s\n", tipNaDelo==1?"slika":"skulptura");
    }
}

int main() {
    int brojGalerii;
    scanf("%d", &brojGalerii);

    Galerija galerii[brojGalerii];

    for (int i = 0; i < brojGalerii; i++) {
        scanf("%s %d", galerii[i].ime, &galerii[i].brojDelo);
        for (int j = 0; j < galerii[i].brojDelo; j++) {
            scanf("%s %f %d", galerii[i].delo[j].avtor, &galerii[i].delo[j].cena, &galerii[i].delo[j].tip);
        }
    }
    for (int i = 0; i < brojGalerii; i++) {
        print(galerii[i]);
    }

    int tipNaDelo;
    scanf("%d",&tipNaDelo);
    najdobra_ponuda(galerii, brojGalerii, tipNaDelo);

    return 0;
}