#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int somar(int num) {
    if(num >= 0)
        { return (num); }
    else {return 0;}
}

void somaMax(int v[], int ini, int fim, int *soma) {
    if(fim == ini){ 
        *soma += somar(v[ini]);
        return;
    }
    else {
        int meio = (ini+fim)/2;
        somaMax(v, ini, meio, soma);
        somaMax(v, meio+1, fim, soma);
    }
    return;
}

int main() {
    int tam;
    scanf("%d", &tam);

    int v[tam];
    int i;
    for(i=0; i<tam; i++) {
        scanf("%d", &v[i]);
    }

    int soma = 0;
    somaMax(v, 0, tam-1, &soma);
    printf("%d", soma);
    return 0;
}