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

void mostrar_nos(NO *aux) {
    if(aux != NULL) {
        mostrar_nos(aux->l);
        if((aux->l == NULL) && (aux->r == NULL))
            { printf(" %d", aux->val); }
        mostrar_nos(aux->r);
    }
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
    mostrar_nos(arvore);

    return 0;
}
