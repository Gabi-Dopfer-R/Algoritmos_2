#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int calcular (int num1, int num2) {
    int resp = num1 - num2;
    if(resp < 0) { resp *= -1; }
    return resp;
}

void distanciaTotal(int v1[], int v2[], int ini, int fim, int *dist) {
    if(fim == ini){ 
        *dist += calcular(v1[ini], v2[ini]);
        return;
    }
    else {
        int meio = (ini+fim)/2;
        distanciaTotal(v1, v2, ini, meio, dist);
        distanciaTotal(v1, v2, meio+1, fim, dist);
    }
    return;
}

int main() {
    int tam;
    scanf("%d", &tam);

    int i, v1[tam], v2[tam];
    for(i=0; i<tam; i++) {
        scanf("%d", &v1[i]);
    }
    for(i=0; i<tam; i++) {
        scanf("%d", &v2[i]);
    }

    int dist = 0;
    distanciaTotal(v1, v2, 0, tam-1, &dist);
    printf("%d", dist);
    return 0;
}