#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define TAM_MAX 100

typedef struct BP{
    int cor;
    int d;
    int p;
    int f;
}BP;

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
   BP **info; 
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

 BP* criar_bp(){
    BP* bp = (BP*) malloc(sizeof(BP));
    
    bp->cor = -1;
    bp->p = -1;
    bp->d = 0;
    bp->f = -1;
     
    return bp; 
}

static BP** iniciar_info (int V){
    BP **info = (BP**) malloc(V * sizeof(BP*));
    
    int i;
    for(i=0; i<V; i++){
        info[i] = criar_bp();
    }
    
    return info;
}

GrafoLA* iniciar_grafoLA(int v){
    GrafoLA* G = (GrafoLA*) malloc(sizeof(GrafoLA));

    G->V = v;
    G->A = 0;
    G->adj = iniciar_LA(G->V);
    G->info = iniciar_info(G->V);

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

void imprimirInfo(GrafoLA *G){
    int i;
    
    printf("v d f p\n");
    for (i = 0; i < G->V; i++){
        printf("%d %d %d", i, G->info[i]->d, G->info[i]->f);
        
        if (G->info[i]->p == -1)
            { printf(" -\n"); }
        else
            { printf(" %d\n", G->info[i]->p); }
    }
}

void BPvisita(GrafoLA *G, int i, int *tempo){
    Cell *adjAux;
    G->info[i]->cor = 0;
    (*tempo)++;
    G->info[i]->d = *tempo;
        
    adjAux = G->adj[i]->head;  
    while(adjAux != NULL){
        if(G->info[adjAux->key]->cor == -1){
            G->info[adjAux->key]->p = i;
            BPvisita(G, adjAux->key, tempo);
        }
        adjAux = adjAux->next;
    }
    G->info[i]->cor = 1;
    (*tempo)++;
    G->info[i]->f = *tempo;
}

void buscaEmProfundidade(GrafoLA *G){
    int i;
    int tempo = 0;
    
    for(i=0; i<G->V; i++){
        if(G->info[i]->cor == -1){
            BPvisita(G, i, &tempo);
        }
    }
    
    imprimirInfo(G);
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

    buscaEmProfundidade(G);
    
    return 0;
}