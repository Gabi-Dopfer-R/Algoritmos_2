#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct NO NO;

struct NO{
    int val;
    NO *r; //right
    NO *l; //left
};

NO* criar_no(int num){
    NO *no = (NO*) malloc(sizeof(NO));
    no->val = num;
    no->r = NULL;
    no->l = NULL;

    return no;
}

NO* inserir_no(NO* aux, int num) {
    if(aux == NULL)
        { aux = criar_no(num); }
    else if(num < aux->val)
        { aux->l = inserir_no(aux->l, num); }
    else
        { aux->r = inserir_no(aux->r, num); }
    return aux;
}

int maior_valor(int num1, int num2){
    if(num1 > num2) { return num1; }
    return num2;
}

int contar_altura(NO *aux, int altura) {
    int alt1, alt2;

    if(aux != NULL) {
        alt1 = maior_valor(altura, contar_altura(aux->l, altura));
        alt2 = maior_valor(altura, contar_altura(aux->r, altura));
        altura = maior_valor(alt1, alt2);

        if(aux->l == NULL && aux->r == NULL) { return altura; }
        return altura+1;
    }
    return NULL;
}

void contar_no (NO *aux, int *num_no) {
    if(aux != NULL) {
        contar_no(aux->l, num_no);
        contar_no(aux->r, num_no);
        num_no++;
    }
}

int qtdeNosFaltantes (NO* aux) {
    int altura = contar_altura(aux, 0);
    int num_no = 0;
    contar_no(aux, &num_no);
    
    /*
    quantidade de nos faltantes = nos maximos - num_no
    nos maximos = 2^(altura + 1) - 1  
    */
    
    return (pow(2, altura + 1) - 1 - num_no);
}

int main() {
    NO* arvore;

    int num_no;
    scanf("%d", &num_no);

    int i, num;
    for(i=0; i<num_no; i++) {
       scanf("%d", &num);

       if(i == 0)
            { arvore = criar_no(num); }
        else
            { inserir_no(arvore, num); }
    }

    printf("%d", qtdeNosFaltantes(arvore)); 

    return 0;
}