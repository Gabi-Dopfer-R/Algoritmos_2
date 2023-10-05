#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int id;
    int ini;
    int fim;
}horario;

void bubblesort(horario vet[], int tam)
{
    int i, j;
    horario aux;

    for(i=0; i<tam; i++)
    {
        for(j=tam-1; j>0; j--)
        {
            if(vet[j].fim < vet[j-1].fim)
            {
                aux = vet[j];
                vet[j] = vet[j-1];
                vet[j-1] = aux;
            }
        }
    }
}

void definirMaterias(int num, horario aulas[]) {
    int fim_aux = aulas[0].fim;;
    int i;

    printf("Aulas alocadas: %d ", aulas[0].id);

    for(i=1; i<num; i++){
        if(aulas[i].ini > fim_aux) {
            printf("%d ", aulas[i].id);

            fim_aux = aulas[i].fim;
        }
    }

    return;
}

int main() {
    int num;
    scanf("%d", &num);

    horario aulas[num];
    int i;

    for(i=0; i<num; i++){
        scanf("%d", &aulas[i].id);
        scanf("%d", &aulas[i].ini);
        scanf("%d", &aulas[i].fim);
    }

    bubblesort(aulas, num);
    definirMaterias (num, aulas);

    return 0;
}
