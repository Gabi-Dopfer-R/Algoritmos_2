#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void troco(int valor, int tam, int v[]) {
    int i=0;
    while(i < tam) {
        if(valor >= v[i]) {
            printf("%d\n", v[i]);
            valor -= v[i];
        }
        else { i++; }
    }
    return;
}

int main() {
    int tam, valor;
    scanf("%d", &valor);
    scanf("%d", &tam);

    int v[tam];
    int i;
    for(i=0; i<tam; i++) {
        scanf("%d", &v[i]);
    }

    troco(valor, tam, v);
    return 0;
}