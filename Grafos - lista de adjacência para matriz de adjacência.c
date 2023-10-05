#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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

typedef struct GrafoMA{
   int V; 
   int A; 
   int **mat;
}GrafoMA;

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

static int** iniciar_MA(int n){
    int i;
    int **mat = (int**) malloc(n * sizeof(int*));

    for (i = 0; i < n; i++)
        mat[i] = (int*) calloc(n, sizeof(int));

    return mat;
}

GrafoMA* iniciar_grafoMA(int v){
    GrafoMA* G = (GrafoMA*) malloc(sizeof(GrafoMA));

    G->V = v;
    G->A = 0;
    G->mat = iniciar_MA(G->V);

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
        //inserir_na_lista(v1, G->adj[v2]);
        G->A++;
    }
}

void liberarGLA(GrafoLA* G){
    int i;

    if (G != NULL){
        for (i = 0; i < G->V; i++)
            liberar_lista(G->adj[i]);

        free(G);
    }
}

void imprimir_GMA(GrafoMA* G){
    int i, j;

    for (i = 0; i < G->V; i++){
        for (j = 0; j < G->V; j++){
            printf("%d ", G->mat[i][j]);
        }
        printf("\n");
    }
    
    return;
}

void LA_to_MA(GrafoLA* GLA, GrafoMA* GMA){
    int i, j;
    Cell *aux;
    
    for(i=0; i<GMA->V; i++){
        aux = GLA->adj[i]->head;
        
        for(j=0; j<GMA->V; j++){
            if(j == aux->key){
                GMA->mat[i][j] = 1;
                
                if(aux->next != NULL){
                    aux = aux->next;
                }
            }else{
                GMA->mat[i][j] = 0;
            }
        }
    }
    
    return;
}

int main(){
    int num_vertices;
    scanf("%d", &num_vertices);
    
    GrafoLA *GLA = iniciar_grafoLA(num_vertices);
    
    int i, v;
    for(i=0; i<GLA->V; i++){
        do{
            scanf("%d", &v);
            
            if(v != -1){
               inserir_arestaLA(GLA, i, v); 
            }
        }while(v != -1);
    }
    
    GrafoMA *GMA = iniciar_grafoMA(num_vertices);
    LA_to_MA(GLA, GMA);
    imprimir_GMA(GMA);
    
    return 0;
}