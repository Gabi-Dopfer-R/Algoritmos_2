#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

struct Pointer {
    int item;
    int fb;
    struct Pointer *left;
    struct Pointer *right;
} typedef Node;

Node* criar(int item){
    Node *tree = (Node *)malloc(sizeof(Node));

    tree->item = item;
    tree->left = NULL;
    tree->right = NULL;
    tree->fb = 0;

    return tree;
}

Node* rotateL(Node *tree){
    Node *auxA = tree->left, *auxB;

    if (auxA->fb == +1){
        tree->left = auxA->right;
        auxA->right = tree;
        tree->fb = 0;
        tree = auxA;
    }
    else{
        auxB = auxA->right;
        auxA->right = auxB->left;
        auxB->left = auxA;
        tree->left = auxB->right;
        auxB->right = tree;

        if (auxB->fb == +1)
            tree->fb = -1;
        else
            tree->fb = 0;

        if (auxB->fb == -1)
            auxA->fb = +1;
        else
            auxA->fb = 0;

        tree = auxB;
    }

    return tree;
}

Node* rotateR(Node *tree){
    Node *auxA = tree->right, *auxB;

    if (auxA->fb == -1){
        tree->right = auxA->left;
        auxA->left = tree;
        tree->fb = 0;
        tree = auxA;
    }
    else{
        auxB = auxA->left;
        auxA->left = auxB->right;
        auxB->right = auxA;
        tree->right = auxB->left;
        auxB->left = tree;

        if (auxB->fb == -1)
            tree->fb = +1;
        else
            tree->fb = 0;

        if (auxB->fb == +1)
            auxA->fb = -1;
        else
            auxA->fb = 0;

        tree = auxB;
    }

    return tree;
}

Node* inserir(Node *tree, int value, int *grown){
    Node *auxA, *auxB;

    if (tree == NULL)
    {
        tree = criar(value);

        *grown = 1;
    }
    else if (value < tree->item)
    {
        tree->left = inserir(tree->left, value, grown);

        if (*grown)
        {
            switch (tree->fb)
            {
            case -1:
                tree->fb = 0;
                *grown = 0;
                break;
            case 0:
                tree->fb = +1;
                break;
            case +1:
                tree = rotateL(tree);
                tree->fb = 0;
                *grown = 0;
            }
        }
    }
    else if (value > tree->item)
    {
        tree->right = inserir(tree->right, value, grown);

        if (*grown)
        {
            switch (tree->fb)
            {
            case +1:
                tree->fb = 0;
                *grown = 0;
                break;
            case 0:
                tree->fb = -1;
                break;
            case -1:
                tree = rotateR(tree);
                tree->fb = 0;
                *grown = 0;
            }
        }
    }

    return tree;
}

void SomarFatores(int *soma, Node *tree) {
    if (tree != NULL) {
        *soma += tree->fb;
        SomarFatores(soma, tree->left);
        SomarFatores(soma, tree->right);
    }
}

int main() {
    Node *tree;
    
    int quant;
    scanf("%d", &quant);

    int i, num, grown = 0;
    for(i=0; i<quant; i++){
        scanf("%d", &num);
        
        if(i==0){ tree = criar(num); }
        else { tree = inserir(tree, num, &grown); }
    }

    int soma = 0;
    SomarFatores(&soma, tree);
    printf("%d", soma);
    return 0;
}