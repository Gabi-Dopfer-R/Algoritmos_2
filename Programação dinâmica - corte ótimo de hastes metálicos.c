#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int maior (int n1, int n2) {
    if(n1 > n2) { return n1; }
    return n2;
}

int corteOtimo(int tam, int haste, int preco[tam]) {
    if (haste == 0)
    { return 0; }

    int corte = 0;
    int i;
    for(i=1; i <= haste; i++) {
        corte = maior(corte, preco[i-1] + corteOtimo(tam, haste - i, preco));
    }
    return corte;
}

int main() {
    int tam, haste;
    scanf("%d", &haste);
    scanf("%d", &tam);

    int preco[tam];
    int i;
    for(i=0; i<tam; i++) {
        scanf("%d", &preco[i]);
    }

    printf("%d", corteOtimo(tam, haste, preco));
    return 0;
}
