#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define TAM_MAX 100

typedef struct BL{
    int cor;
    int d;
    int p;
}BL;

typedef struct Cell{
    int key;
    struct Cell *next;
}Cell;

typedef struct Lista{
    Cell *head;
}Lista;

typedef struct GrafoLA{
   int V; 
   int A; 
   Lista **adj;
}GrafoLA;

typedef struct ItemF{
    int chave;
} ItemF;

typedef struct Fila{
    ItemF item[TAM_MAX];
    int ini;
    int fim;
    int tam;
} Fila;

Fila *criar_fila(){
    Fila *f = (Fila *)malloc(sizeof(Fila));

    f->ini = -1;
    f->fim = -1;
    f->tam = 0;

    return f;
}

int fila_cheia(Fila *f){

    if (f == NULL)
        return -1;
    else if (f->tam < TAM_MAX)
        return 0;
    else
        return 1;
}

int fila_vazia(Fila *f){
    if (f == NULL)
        return -1;
    else if (f->tam > 0)
        return 0;
    else
        return 1;
}

Lista* criar_lista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->head = NULL;

    return l;
}

Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->key = key;
    c->next = NULL;

    return c;
}

int lista_vazia(Lista *l){
    return (l == NULL) || (l->head == NULL);
}

static Lista** iniciar_LA(int n){
    int i;
    Lista **adj = (Lista**) malloc(n * sizeof(Lista*));

    for (i = 0; i < n; i++)
        adj[i] = criar_lista();

    return adj;
}

int liberar_lista(Lista *l){
    Cell *aux;

    if ((l != NULL) && !lista_vazia(l)){

        while(l->head != NULL){
            aux = l->head;

            l->head = aux->next;

            free(aux);
        }

        free(l);

        return 1;
    }

    return 0;
}

void inserir_na_lista(int key, Lista *l){
    Cell *auxA, *auxP;
    Cell* c;

    if (lista_vazia(l)){
        if (l == NULL)
            l = criar_lista();

        l->head = criar_celula(key);
    }else{
        c = criar_celula(key);

        if (l->head->key >= key){
           c->next = l->head;


           l->head = c;
        }else{
            auxA = l->head;
            auxP = auxA;

            while ((auxP != NULL) && (auxP->key < key)){
                auxA = auxP;
                auxP = auxP->next;
            }

            auxA->next = c;
            c->next = auxP;
        }
    }
}

GrafoLA* iniciar_grafoLA(int v){
    GrafoLA* G = (GrafoLA*) malloc(sizeof(GrafoLA));

    G->V = v;
    G->A = 0;
    G->adj = iniciar_LA(G->V);

    return G;
}

int procurar(int key, Lista *l){
    Cell *aux;

    if (l != NULL){
        aux = l->head;

        while ((aux != NULL) && (key < aux->key))
            aux = aux->next;
    }

    if ((aux != NULL) && (key == aux->key))
        return 1;
    else
        return 0;
}

int aresta_existeLA(GrafoLA* G, int v1, int v2){
    if ((G!= NULL) && (G->adj[v1]->head != NULL))
        return procurar(v2, G->adj[v1]);

    return 0;
}

void inserir_arestaLA(GrafoLA* G, int v1, int v2){
    if (!aresta_existeLA(G, v1, v2)){
        inserir_na_lista(v2, G->adj[v1]);
        G->A++;
    }
}

void imprimirInfo(int V, BL info[V]){
    int i;
    
    printf("v d p\n");
    for (i = 0; i < V; i++){
        printf("%d", i);

        if (info[i].d == -1)
            { printf(" -"); }
        else
            { printf(" %d", info[i].d); }
        
        if (info[i].p == -1)
            { printf(" -\n"); }
        else
            { printf(" %d\n", info[i].p); }
    }
}

int enfileirar(Fila *f, int chave){
    ItemF item;

    if (f == NULL)
        f = criar_fila();

    if (!fila_cheia(f))
    {
        item.chave = chave;

        if (f->ini < 0)
            f->ini = 0;

        if (f->fim < TAM_MAX - 1)
            f->fim++;
        else
            f->fim = 0;

        f->item[f->fim] = item;

        f->tam++;

        return 1;
    }

    return 0;
}

ItemF *desenfileirar(Fila *f){
    ItemF *item = NULL;

    if (!fila_vazia(f))
    {
        item = (ItemF *)malloc(sizeof(ItemF));

        *item = f->item[f->ini];

        if (f->ini < TAM_MAX - 1)
            f->ini++;
        else
            f->ini = 0;

        f->tam--;

        if (f->tam == 0)
        {
            f->ini = -1;
            f->fim = -1;
        }
    }

    return item;
}

void buscaEmLargura(GrafoLA *G, int s){
    int i;
    BL info[G->V];
    for(i=0; i<G->V; i++){
        if(i != s){
            info[i].cor = -1;
            info[i].d = -1;
            info[i].p = -1;
        }else{
            info[i].cor = 0;
            info[i].d = 0;
            info[i].p = -1;
        }
    }
    
    Fila *f = criar_fila();
    ItemF *aux;
    Cell *adjAux;
    
    enfileirar(f, s);
    while(f->tam != 0){
        aux = desenfileirar(f);
        
        adjAux = G->adj[aux->chave]->head;  
        while(adjAux != NULL){
            if(info[adjAux->key].cor == -1){
                info[adjAux->key].cor = 0;
                info[adjAux->key].d = (info[aux->chave].d)+1;
                info[adjAux->key].p = aux->chave;
                enfileirar(f, adjAux->key);
            }
            adjAux = adjAux->next;
        }
        info[aux->chave].cor = 1;
    }
    imprimirInfo(G->V, info);
}

int main(){
    int num_vertices;
    scanf("%d", &num_vertices);
    
    GrafoLA *G = iniciar_grafoLA(num_vertices);
   
    int i, v;
    for(i=0; i<G->V; i++){
        do{
            scanf("%d", &v);
            
            if(v != -1){
               inserir_arestaLA(G, i, v); 
            }
        }while(v != -1);
    }
    
    int s;
    scanf("%d", &s);
    buscaEmLargura(G, s);
    
    return 0;
}