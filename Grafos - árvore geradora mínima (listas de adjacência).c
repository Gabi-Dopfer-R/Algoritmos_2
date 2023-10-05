#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define TAM_MAX 100

typedef struct BL{
    int key;
    int p;
    int id;
}BL;

typedef struct Cell{
    int key;
    int peso;
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

typedef struct Fila{
    BL item[TAM_MAX];
    int ini;
    int fim;
    int tam;
} Fila;

///////////////////////////////////////
Lista* criar_lista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->head = NULL;

    return l;
}

Cell* criar_celula(int key, int peso){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->key = key;
    c->peso = peso;
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

void inserir_na_lista(int key, Lista *l, int peso){
    Cell *auxA, *auxP;
    Cell* c;

    if (lista_vazia(l)){
        if (l == NULL)
            l = criar_lista();

        l->head = criar_celula(key, peso);
    }else{
        c = criar_celula(key, peso);

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
///////////////////////////////////////////////

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

void inserir_arestaLA(GrafoLA* G, int v1, int v2, int peso){
    if (!aresta_existeLA(G, v1, v2)){
        inserir_na_lista(v2, G->adj[v1], peso);
        G->A++;
    }
}
////////////////////////////////

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

int esta_na_fila(Fila *f, int id){
    for (int i = 0; i < f->tam; i++)
    {
        if (f->item[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}

int enfileirar(Fila *f, BL chave){
    if (f == NULL)
        f = criar_fila();

    if (!fila_cheia(f))
    {

        if (f->ini < 0)
            f->ini = 0;

        if (f->fim < TAM_MAX - 1)
            f->fim++;
        else
            f->fim = 0;

        f->item[f->fim] = chave;

        f->tam++;

        return 1;
    }

    return 0;
}

BL *desenfileirar(Fila *f){
    BL *item = NULL;
    int menor_prior = -INT_MAX;
    int indice = 0;

    if (!fila_vazia(f))
    {
        item = (BL *)malloc(sizeof(BL));

        for (int i = 0; i < f->tam; i++)
        {
            if (f->item[i].key < menor_prior)
            {
                menor_prior = f->item[i].key;
                indice = i;
            }
        }

        *item = f->item[indice];

        for (int i = indice; i < f->tam - 1; i++)
        {
            f->item[i] = f->item[i + 1];
        }

        f->tam--;

        if (f->tam == 0)
        {
            f->ini = -1;
            f->fim = -1;
        }
    }

    return item;
}
/////////////////////////////////

void imprimirInfo(int V, BL info[V]){
    int i;
    
    for (i = 0; i < V; i++){
        printf("%d:", i);
        
        if (info[i].p == -1)
            { printf(" -\n"); }
        else
            { printf(" %d\n", info[i].p); }
    }
}

void arvoreGeradoraMinima(GrafoLA *G){
    BL info[G->V];
    Fila *f = criar_fila();
    
    info[0].id = 0;
    info[0].key = 0;
    info[0].p = -1;
    enfileirar(f, info[0]);
    
    int i;
    for(i=1; i<G->V; i++){
        info[i].id = i;
        info[i].key = INT_MAX;
        info[i].p = -1;
        enfileirar(f, info[i]);        
    }
    
    Cell *aux;
    BL* u;
    while(f->tam != 0){
        u = desenfileirar(f);
       
        aux = G->adj[u->id]->head;
        while(aux != NULL){
            if(esta_na_fila(f, aux->key)){
                if(aux->peso < info[aux->key].key){
                    info[aux->key].p = u->id;
                    info[aux->key].key = aux->peso;
                } 
            }
            aux = aux->next;
        }      
    }
    imprimirInfo(G->V, info);
}

int main(){
    int num_vertices, num_arestas;
    scanf("%d", &num_vertices);
    GrafoLA *G = iniciar_grafoLA(num_vertices);
    scanf("%d", &num_arestas);
   
    int i, v1, v2, peso;
    for(i=0; i<num_arestas; i++){
        scanf("%d", &v1);
        scanf("%d", &v2);
        scanf("%d", &peso);

        inserir_arestaLA(G, v1, v2, peso); 
    }

    arvoreGeradoraMinima(G);
    
    return 0;
}